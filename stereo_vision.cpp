/*
    Stereo vision class
    Copyright (C) 2013  Karolis Tarasauskas <karolis.tarasauskas@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "stereo_vision.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <KFileDialog>


#include "settings.h"

stereo_vision::stereo_vision(): QObject()
{
  
  settings.boardSize.width = 9;
  settings.boardSize.height = 6;
  settings.squareSize = 25;
  settings.calibrationPattern = Settings::CHESSBOARD;
  undistort = FALSE;
//   state = cvCreateStereoBMState(CV_STEREO_BM_BASIC, 64);
//   depth_map.create(480,640, CV_8UC3);
  left_gray.create(480,640,CV_8UC1);
  right_gray.create(480,640,CV_8UC1);
  frames = 15;
  frame_n = 0;
  chessboard_sec_delay = 0.5;
  time_stamp = 0;
        time.start();
  
 
  cv::setIdentity(cameraMatrix_left);
  cv::setIdentity(cameraMatrix_right);
  
  distCoeffs_left.zeros(1,5, CV_64FC1);
  distCoeffs_right.zeros(1,5, CV_64FC1);
  
 
  bm.state->SADWindowSize = 31;
  bm.state->numberOfDisparities = 64;
  bm.state->preFilterSize = 5;
  bm.state->preFilterCap = 31;
  bm.state->minDisparity = 0;
  bm.state->textureThreshold = 10;
  bm.state->uniquenessRatio = 15;
  bm.state->speckleWindowSize = 100;
  bm.state->speckleRange = 32;
  bm.state->disp12MaxDiff = 1;

}

void stereo_vision::calibration_init()
{
  if(!cameraMatrix_left.empty())
  {
    R.release();
    T.release();
    E.release();
    F.release();
    cameraMatrix_left.release();
    cameraMatrix_right.release();
    distCoeffs_left.release();
    distCoeffs_right.release();
    imagePoints1.clear();
    imagePoints2.clear();
    objectPoints.clear();
  }
  emit calibration_progress(0);
  frame_n=0;
  qDebug("Beggining calibration");
  if(mode == CALIBRATING)
  {
    mode = UNCALIBRATED;  
    qDebug("Beggining calibration");
    emit calibration_running(0);
  }
  else
  {
  mode = CALIBRATING;
  emit calibration_running(1);
  };
}

void stereo_vision::stereo_procedure(cv::Mat left,cv::Mat right)
{

  switch(mode)
  {
    case UNCALIBRATED:
      
      break;
    case CALIBRATING:
      
      if(time.elapsed() - time_stamp > chessboard_sec_delay*1000)
      {
      calibrating_get_corners(left,right);
      time_stamp = time.elapsed();
      };
      break;
    case CALIBRATED:
      remap(left,left_output, rmap_left[0], rmap_left[1], CV_INTER_LINEAR);
      remap(right,right_output, rmap_right[0], rmap_right[1], CV_INTER_LINEAR);
      for(int j=0;j<left_output.rows; j+=16)
      {
// 	cv::line(left_output, cv::Point(0,j), cv::Point(left_output.cols, j), cv::Scalar(0,255,0), 1, 8);
// 	cv::line(right_output, cv::Point(0,j), cv::Point(left_output.cols, j), cv::Scalar(0,255,0), 1, 8);
      }
//       cv::line(depth_map, cv::Point(0,0), cv::Point(depth_map.cols, depth_map.rows), cv::Scalar(0,255,0), 1, 8);
      stereo_correspondence(left_output,right_output);
      break;
  };
}

void stereo_vision::stereo_correspondence(cv::Mat left, cv::Mat right)
{
//   cv::cvtColor(leftar,left_gray,CV_RGB2GRAY,1);
//   qDebug("hello");
//   cv::cvtColor(rightar,right_gray,CV_RGB2GRAY,1);
//   qDebug("left image data: %d %d ", left_gray.channels(), left_gray.size().width);
//   sbm(left_gray,right_gray,depth_map);
//   cv::normalize(depth_map,depth_map,128,255,CV_MINMAX);
  
  cv::cvtColor(left,left_gray, CV_RGB2GRAY);
  cv::cvtColor(right,right_gray, CV_RGB2GRAY); 
  
  bm(left_gray, right_gray, depth_map_raw);
//   depth_map_raw.convertTo(depth_map, CV_8U);
  cv::normalize(depth_map_raw, depth_map, 0,255, cv::NORM_MINMAX, CV_8UC1);
  cv::cvtColor(depth_map, depth_map, CV_GRAY2BGR);
};

void stereo_vision::calcBoardCornerPositions(cv::Size boardSize, float squareSize, std::vector<std::vector< cv::Point3f > > corners)
{
  qDebug("%d, %d, %f", boardSize.height, boardSize.width, squareSize);
    for(int i=0; i < frames; i++)
    {
        for( int j = 0; j < boardSize.height; j++ )
        {
            for( int k = 0; k < boardSize.width; k++ )
            {
// 	      corners.push_back(cv::Point3f(float(i*squareSize), float(j*squareSize),0.0));
                objectPoints[i].push_back(cv::Point3f(j*squareSize, k*squareSize,0));
            };
        };
    };
    qDebug("Success");

}

void stereo_vision::calibrating_get_corners(cv::Mat left,cv::Mat right)
{
  cv::cvtColor(left,left_gray,CV_RGB2GRAY);
  cv::cvtColor(right,right_gray,CV_RGB2GRAY);

  left_found= cv::findChessboardCorners(left_gray, settings.boardSize, pointBuf_left, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
  right_found= cv::findChessboardCorners(right_gray, settings.boardSize, pointBuf_right, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
  
  cv::drawChessboardCorners(left,settings.boardSize, pointBuf_left, left_found);
  cv::drawChessboardCorners(right,settings.boardSize, pointBuf_right, right_found);
    
  if((left_found)&&(right_found))
  {
    qDebug("Both found");
    cv::cornerSubPix(left_gray, pointBuf_left, cv::Size(11,11), cv::Size(-1,-1),cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    cv::cornerSubPix(right_gray, pointBuf_right, cv::Size(11,11), cv::Size(-1,-1),cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
//     std::vector<std::vector<cv::Point3f> > imagePoints1(frames);
    imagePoints1.push_back(pointBuf_left);
    imagePoints2.push_back(pointBuf_right);
    
    frame_n++;
    
    emit calibration_progress((frame_n*100/frames));
    
    if(frame_n >= frames)
    {
     qDebug("Finished getting images, now starting calculations");
     emit(calibration_running(0));
    objectPoints.resize(frames);
    calcBoardCornerPositions(settings.boardSize, settings.squareSize, objectPoints);
    
    imageSize = left.size();
    qDebug("%d %d", imageSize.height, imageSize.width);
    cameraMatrix_left = cv::Mat::eye(3, 3, CV_64F);
    cameraMatrix_right = cv::Mat::eye(3, 3, CV_64F);
    imagePoints1.resize(frames);
    imagePoints2.resize(frames);
    double rms = stereoCalibrate(objectPoints,imagePoints1,imagePoints2, cameraMatrix_left, distCoeffs_left,
                    cameraMatrix_right, distCoeffs_right, imageSize, R, T, E, F, cv::TermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5),CV_CALIB_FIX_ASPECT_RATIO +
                    CV_CALIB_ZERO_TANGENT_DIST +
                    CV_CALIB_SAME_FOCAL_LENGTH +
                    CV_CALIB_RATIONAL_MODEL +
                    CV_CALIB_FIX_K3 + CV_CALIB_FIX_K4 + CV_CALIB_FIX_K5);
    qDebug("Kalibravimo rezultatas %f",rms);
    cv::stereoRectify(cameraMatrix_left, distCoeffs_left, cameraMatrix_right, distCoeffs_right, imageSize, R, T, R1, R2, P1, P2, Q, CV_CALIB_ZERO_DISPARITY, 0, imageSize, &roi_left, &roi_right );
    bm.state->roi1 = roi_left;
    bm.state->roi2 = roi_right;
    cv::initUndistortRectifyMap(cameraMatrix_left, distCoeffs_left, R1, P1, imageSize, CV_16SC2, rmap_left[0], rmap_left[1]);
    cv::initUndistortRectifyMap(cameraMatrix_right, distCoeffs_right, R2, P2, imageSize, CV_16SC2, rmap_right[0], rmap_right[1]);
/*    
    double err = 0;
    int npoints = 0;
    
    std::vector<cv::Vec3f> lines1;
    std::vector<cv::Vec3f> lines2;
    
    for( int i = 0; i < frames; i++ )
    {
        int npt = (int)imagePoints1[i].size();
        cv::Mat imgpt1,imgpt2;
            
	imgpt1 = cv::Mat(imagePoints1[i]);
        cv::undistortPoints(imgpt1, imgpt1, cameraMatrix_left, distCoeffs_left, cv::Mat(), cameraMatrix_left);
        cv::computeCorrespondEpilines(imgpt1, 1, F, lines1);
	
	imgpt2 = cv::Mat(imagePoint[i]);
        cv::undistortPoints(imgpt2, imgpt2, cameraMatrix_right, distCoeffs_right, cv::Mat(), cameraMatrix_right);
        cv::computeCorrespondEpilines(imgpt2, 2, F, lines2);
        for( int j = 0; j < npt; j++ )
        {
            double errij = fabs(imagePoints1[i][j].x*lines2[j][0] +
                                imagePoints1[i][j].y*lines2[j][1] + lines2[j][2]) +
                           fabs(imagePoints2[i][j].x*lines1[j][0] +
                                imagePoints2[i][j].y*lines1[j][1] + lines1[j][2]);
            err += errij;
        }
        npoints += npt;
    }
    
    qDebug("Reprojection error: %d", err/npoints); << "average reprojection err = " <<  err/npoints << endl;
    }
*/
     mode = CALIBRATED;
  }
  }
}

void stereo_vision::show_undistorted(bool distort)
{
  undistort = distort;
};

void stereo_vision::SADWindowSize_changed(int value)
{
  bm.state->SADWindowSize=value*2+1;
//   bm.SADWindowSize=value*2+1;
}

void stereo_vision::numberOfDisparities_changed(int value)
{
  bm.state->numberOfDisparities = value*16;
//   bm.numberOfDisparities = value*16;
}

void stereo_vision::preFilterSize_changed(int value)
{
  bm.state->preFilterSize = value*2+1;
//   bm.preFilterSize = value*2+1;
}

void stereo_vision::preFilterCap_changed(int value)
{
  bm.state->preFilterCap = value;
//   bm.preFilterCap = value;
}

void stereo_vision::minDisparity_changed(int value)
{
  bm.state->minDisparity = value;
//   bm.minDisparity = value;
  
}

void stereo_vision::textureThreshold_changed(int value)
{
  bm.state->textureThreshold = value;
//   bm.textureThreshold = value;
}

void stereo_vision::uniquenessRatio_changed(int value)
{
  bm.state->uniquenessRatio = value;
//   bm.uniquenessRatio = value;
}

void stereo_vision::speckleWindowSize_changed(int value)
{
  bm.state->speckleWindowSize = value;
//   bm.speckleWindowSize = value;
}

void stereo_vision::speckleRange_changed(int value)
{
  bm.state->speckleRange = value;
//   bm.speckleRange = value;
}

void stereo_vision::disp12MaxDiff_changed(int value)
{
  bm.state->disp12MaxDiff = value;
//   bm.disp12MaxDiff = value;
}

void stereo_vision::load_data()
{
  qDebug("Load data clicked");
 fileName = KFileDialog::getOpenFileName ( KUrl("~"), QString("*.dcf | Depth calibration file" ) );
//  qDebug("Filename contents: %s", fileName);
 QFile file(fileName);
 if(!(file.open(QIODevice::ReadOnly)))
 {
   return;
 }
 eilute = file.readLine();
    if( eilute != QString("Moving object targeting system depth calibration file.\n"))
    {
    qDebug("Netinkamas failas");
    error.setText("Sugadintas kalibracijos failas");
    error.setIcon(QMessageBox::Critical);
    error.setWindowTitle("Klaida");
    error.setStandardButtons(QMessageBox::Ok);
    error.exec();
   return;  
    };
    // Nelabai grazu, taciau veikia :)
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->SADWindowSize = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->numberOfDisparities = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->preFilterSize = eilute.toInt();
        eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->preFilterCap = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->minDisparity = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->textureThreshold = eilute.toInt();
        eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->uniquenessRatio = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->speckleWindowSize = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->speckleRange = eilute.toInt();
    eilute = file.readLine();
    eilute.truncate(eilute.length()-1);
    bm.state->disp12MaxDiff = eilute.toInt();
    emit refresh_depth_settings(bm.state);
}

void stereo_vision::save_data()
{
  fileName = KFileDialog::getSaveFileName ( KUrl("~"), QString("*.dcf | Depth calibration file" ) );
  if(fileName.isEmpty())
    return;
  else
  {
    QFile file (fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream stream ( &file);
    stream << "Moving object targeting system depth calibration file." <<endl;
    stream << bm.state->SADWindowSize << endl;
    stream << bm.state->numberOfDisparities << endl;
    stream << bm.state->preFilterSize << endl;
    stream << bm.state->preFilterCap << endl;
    stream << bm.state->minDisparity << endl;
    stream << bm.state->textureThreshold << endl;
    stream << bm.state->uniquenessRatio << endl;
    stream << bm.state->speckleWindowSize << endl;
    stream << bm.state->speckleRange << endl;
    stream << bm.state->disp12MaxDiff << endl;
  }
  
};

void stereo_vision::save_calibration_file()
{
  fileName = KFileDialog::getSaveFileName ( KUrl("~"), QString("*.ccf | Camera calibration file" ) );
  if(fileName.isEmpty())
    return;
  else
  {
    cv::FileStorage f;
    std::string file = fileName.toUtf8().constData();
    f.open(file, cv::FileStorage::WRITE);
    f << "R" << R;
    f << "T" << T;
    f << "E" << E;
    f << "F" << F;
    f << "cameramatrix_left" << cameraMatrix_left;
    f << "cameramatrix_right" << cameraMatrix_right;
    f << "distCoeffs_left" << distCoeffs_left;
    f << "distCoeffs_right" << distCoeffs_right;
    f << "rmap_left_0" << rmap_left[0];
    f << "rmap_left_1" << rmap_left[1];
    f << "rmap_right_0" << rmap_right[0];
    f << "rmap_right_1" << rmap_right[1];
    f.release();
  }
};

void stereo_vision::load_calibration_file()
{
   qDebug("Load data clicked");
 fileName = KFileDialog::getOpenFileName ( KUrl("~"), QString("*.ccf | Camera calibration file" ) );
 cv::FileStorage f;
 std::string file = fileName.toUtf8().constData();
 if(!f.isOpened())
 {
 f.open(file, cv::FileStorage::READ);
 f["R"] >> R;
 f["T"] >> T;
 f["E"] >> E;
 f["F"] >> F;
 f["cameramatrix_left"] >> cameraMatrix_left;
 f["cameramatrix_right"] >> cameraMatrix_right;
 f["distCoeffs_left"] >> distCoeffs_left;
 f["distCoeffs_right"] >> distCoeffs_right;
 f["rmap_left_0"] >> rmap_left[0];
 f["rmap_left_1"] >> rmap_left[1];
 f["rmap_right_0"] >> rmap_right[0];
 f["rmap_right_1"] >> rmap_right[1];
 qDebug("Loaded");
 f.release();
      mode=CALIBRATED;
 };
};

void stereo_vision::depth_report(cv::Point2f point)
{
  if(mode==CALIBRATED)
  {
  target_depth = depth_map.at<uchar>(point);
  emit give_depth_to_gui(target_depth);
  qDebug("Target depth = %d", target_depth);
  };
}
