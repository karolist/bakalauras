/*
    Analyzer class function
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

#include <iostream>
#include "analyzer.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#define MAX_CONTOURS 100

Analyzer::Analyzer(): QObject()
{
    double accumulate_ratio=1.5;
    element = cv::getStructuringElement( cv::MORPH_RECT,
                                         cv::Size( 2*2+ 1, 2*2+1 ),
                                         cv::Point( 2, 2) );
    average.create(480,640,CV_32FC3);
    laser_calibration_matrix.create(480,640,CV_8UC3);
    std::vector<cv::Point2f> targetingPoint(1);
    const Scalar RED(0,0,255), GREEN(0,255,0);
    int ESC_KEY = 27;
    targetingPoint_strike=0;
    drawing2 = cv::Mat::zeros( average.size(), CV_8UC1 );
    acumulate_sensitivity = 0.6;
    threshold = 10;
    start_tracking = FALSE;
    termcrit.type=(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS);
    termcrit.maxCount=20;
    termcrit.epsilon= 0.03;
    laser_calibrating_process=false;
    winSize = cv::Size(31,31);
//     points_to_track[2];
    movement_mask.create(480,640,CV_8UC1);
    ttl_for_last_point = 30;
    frame_length_temp = 0;
    laser_value_x=0;
    laser_value_y=0;
}

void Analyzer::analyze_loop(cv::Mat frame_source)
{
  if(start_tracking)
  {
  time.restart();
  build_average();
  find_objects();
  draw_rectangle();
  frame_length_temp = frame_length_temp + time.elapsed();
  if(frame_length_count++>=30)
  {
    emit frame_analyze_length(frame_length_temp/30);
    frame_length_count = 0;
    frame_length_temp = 0;
  };
  }
  else if(laser_calibrating_process== false)
  {
    frame_source.copyTo(output);
  }
  else
  {
      frame_source.copyTo(laser_calibration_matrix);
    cv::circle(laser_calibration_matrix, cv::Point2f(10,10), 3, cv::Scalar(240,10,240), 2,8);
    cv::circle(laser_calibration_matrix, cv::Point2f(630,10), 3, cv::Scalar(240,10,240), 2,8);
    cv::circle(laser_calibration_matrix, cv::Point2f(10,470), 3, cv::Scalar(240,10,240), 2,8);
    cv::circle(laser_calibration_matrix, cv::Point2f(630,470), 3, cv::Scalar(240,10,240), 2,8);
    cv::circle(laser_calibration_matrix, cv::Point2f(320,240), 3, cv::Scalar(240,80,240), 2,8);
    laser_calibration_matrix.copyTo(output);
  }
}

void Analyzer::change_acumulate_sensitivity(int value)
{
  acumulate_sensitivity = (float)((value+0.001)/100);
}

void Analyzer::change_threshold_sensitivity(int value)
{
  threshold = value;
};

void Analyzer::build_average()
{
    cv::accumulateWeighted(frame,average, acumulate_sensitivity);
    average.convertTo(tmp_frame, CV_8UC3);
    cv::absdiff(frame,tmp_frame,abs_frame);
    cv::cvtColor(abs_frame,abs_frame,CV_RGB2GRAY);
    cv::threshold(abs_frame, abs_frame, threshold, 255, CV_THRESH_BINARY);
//     cv::imshow("abs_frame_int", abs_frame);
//     cv::dilate(abs_frame,abs_frame, element);
//     cv::imshow("abs_frame_out", abs_frame);
}

void Analyzer::find_objects()
{
    findContours( abs_frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    drawing = cv::Mat::zeros( abs_frame.size(), CV_8UC3 );
    if(contours.size() > MAX_CONTOURS)
    {
        contours.resize(MAX_CONTOURS);
    };
    for( int i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( 20, 180, 20);
        cv::drawContours( drawing, contours, i, color, -1, 8, hierarchy, 0, cv::Point() );
    };
}

void Analyzer::show_undistorted(bool value)
{
    showUndistorted = value;
}

void Analyzer::draw_rectangle()
{
    drawing2 = cv::Mat::zeros( abs_frame.size(), CV_8UC1 );
    drawing3 = cv::Mat::zeros( abs_frame.size(), CV_8UC1 );
    frame.copyTo(output);
    
    //isimam raudona spalva del lazerio
//     int from_to[] = {0,0,1,1,0,2};
//     cv::mixChannels(&frame, 1, &output, 1, from_to, 3);
    cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
    
//     targetingPoint_refreshed = FALSE;
    //calculate moments
    std::vector<cv::Moments> mu(contours.size() );
    std::vector<cv::Point2f> mc( contours.size() );

//         qDebug("Contours mass centers: %i", mc.size());
    for( int i = 0; i < contours.size() ; i++ )
    {
        mu[i] = cv::moments( contours[i], false );
        //get the mass centers
        mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
        //draw mass centers
        cv::circle( drawing2, mc[i], 30, cv::Scalar(255,255,255), -1, 8, 0);
    };

    findContours( drawing2, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    
    for( int i = 0; i< contours2.size(); i++ )
    {
        cv::drawContours( drawing2, contours2, i, cv::Scalar(255,255,255), 4, 8, hierarchy2, 0, cv::Point() );
    };
    std::vector<cv::Moments> mu2(contours2.size() );
    std::vector<cv::Point2f> mc2( contours2.size() );
    
//         qDebug("Contours mass centers: %i", mc.size());
    for( int i = 0; i < contours2.size() ; i++ )
    {
// // 	qDebug("Contours mass centers: %i", mc2.size());
        mu2[i] = cv::moments( contours2[i], false );
//         //get the mass centers
        mc2[i] = cv::Point2f( mu2[i].m10/mu2[i].m00 , mu2[i].m01/mu2[i].m00 );
    };
    
    
    int centered_iterator, tmp=0, dis=801;
    for(int i =0 ; i < mc2.size(); i++)
    {
      tmp = sqrt(pow((mc2[i].x - 320),2)+pow((mc2[i].y - 240),2));
      if(tmp<dis)
      {
	dis = tmp;
	centered_iterator = i;
      };
    };
    movement_mask = cv::Scalar::all(0);
    emit number_of_features_to_track(mc2.size());
    if(mc2.size()!=0)
    {
    cv::circle(movement_mask, mc2[centered_iterator], 15, cv::Scalar(255,255,255), -1, 8, 0);
    
    if((points_to_track[1].empty()))
    {
      ttl_for_last_point = 0;
      target_detected = false;
      emit target_state(false);
      goodFeaturesToTrack(frame_gray, points_to_track[1], 5, 0.01, 10, movement_mask, 3, 0, 0.04);
      cornerSubPix(frame_gray, points_to_track[1], cv::Size(10,10), cv::Size(-1,-1), termcrit);
    }
    };
    if(!points_to_track[0].empty())
    {
      std::vector<uchar> status;
           std::vector<float> err;
            if(prevGray.empty())
                frame_gray.copyTo(prevGray);
		calcOpticalFlowPyrLK(prevGray, frame_gray, points_to_track[0], points_to_track[1], status, err, winSize, 3, termcrit, 0, 0.001);
            size_t i, k;

            for( i = k = 0; i < points_to_track[1].size(); i++ )
            {
	      if(sqrt(pow((points_to_track[0][i].x - points_to_track[1][i].x),2)+pow((points_to_track[0][i].y - points_to_track[1][i].y),2))<4)
	      {
		if(((points_to_track[1].size()>1)&&(points_to_track[0].size()>1)) or (ttl_for_last_point>=30))
		{
		points_to_track[1].erase(points_to_track[1].begin()+i);
		points_to_track[0].erase(points_to_track[0].begin()+i);
		}
		else
		{
		ttl_for_last_point++;
		};
	      }
                if( !status[i] )
                continue;
                points_to_track[1][k++] = points_to_track[1][i];
                cv::circle( output, points_to_track[1][i], 4, Scalar(255,255,255), -1, 8); //turetu but points_to_track[1][i]
// 		qDebug("target x, y: %d, %d", points_to_track[1][0].x, target.x);
		target = points_to_track[1][0];
		emit tracked_object_x(points_to_track[1][0].x);
		emit tracked_object_y(points_to_track[1][0].y);
		emit get_depth(target);
		target_detected = true;
		emit target_state(true);
		
            }
    };
    std::swap(points_to_track[1], points_to_track[0]);
    swap(prevGray, frame_gray);
}

void Analyzer::center()
{
 target.x = 320;
 target.y = 240;
}

void Analyzer::calibration_init()
{
    qDebug("Beginning calibration procedure");
    calibrating = TRUE;

}

void Analyzer::start_tracking_function(bool value)
{
  start_tracking = !start_tracking;
  qDebug("Tracking: %d", start_tracking);
}

void Analyzer::laser_calibration(bool )
{
  laser_calibrating_process = !laser_calibrating_process;
  if(laser_calibrating_process == TRUE)
  {
  qDebug("Calibrating laser"); 
  }else
  {
    qDebug("Canceling");
  };
  emit laser_calibration_status(laser_calibrating_process);
}

void Analyzer::laser_change_x(int value)
{
  laser_value_x = value;
};

void Analyzer::laser_change_y(int value)
{
  laser_value_y = value;
};

void Analyzer::fix_laser_position()
{
  qDebug("Coordinates: %d, %d", laser_value_x, laser_value_y);
}