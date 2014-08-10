/*
    Stereo vision class
    Copyright (C) 2013  <copyright holder> <email>

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


#ifndef STEREO_VISION_H
#define STEREO_VISION_H
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <QDebug>
#include "settings.h"
#include <QTime>
#include <QMessageBox>
#include <QFile>

class stereo_vision: public QObject
{
    Q_OBJECT
public:
    stereo_vision();
    void stereo_procedure(cv::Mat left, cv::Mat right);
    void stereo_correspondence(cv::Mat left, cv::Mat right);
    bool undistort;
    cv::Mat depth_map;
//   CvStereoBMState *state;
//   cv::StereoSGBM bm;
    cv::StereoBM bm;
    void calibrating_get_corners(cv::Mat left, cv::Mat right);
    cv::Mat left_output,right_output,left_gray,right_gray;

public slots:
    void calibration_init();
    void show_undistorted(bool);
    void SADWindowSize_changed(int);
    void numberOfDisparities_changed(int);
    void preFilterSize_changed(int);
    void preFilterCap_changed(int);
    void minDisparity_changed(int);
    void textureThreshold_changed(int);
    void uniquenessRatio_changed(int);
    void speckleWindowSize_changed(int);
    void speckleRange_changed(int);
    void disp12MaxDiff_changed(int);
    void load_data();
    void save_data();
    void load_calibration_file();
    void save_calibration_file();
    void depth_report(cv::Point2f);
signals:
    void calibration_running(bool);
    void calibration_progress(int);
    void refresh_depth_settings(cv::Ptr<CvStereoBMState>);
    void give_depth_to_gui(int);
private:
    cv::Mat depth_map_raw;
    bool calibrating;
    bool left_found;
    bool right_found;
    cv::Mat R;
    cv::Mat T;
    cv::Mat E;
    cv::Mat F;

    cv::Mat R1,R2;
    cv::Mat P1,P2;
    cv::Mat Q;
    cv::Rect roi_left;
    cv::Rect roi_right;
    cv::Mat rmap_left[2], rmap_right[2];
    cv::Size imageSize;
    Settings settings;
    QTime time;
    void calcBoardCornerPositions(cv::Size boardSize, float squareSize, std::vector<std::vector< cv::Point3f > > corners);

    std::vector< std::vector < cv::Point2f > > imagePoints1;
    std::vector< std::vector < cv::Point2f > > imagePoints2;
    cv::Mat cameraMatrix_left, cameraMatrix_right;
    cv::Mat distCoeffs_left, distCoeffs_right;
    std::vector<cv::Point2f> pointBuf_left;
    std::vector<cv::Point2f> pointBuf_right;
    std::vector<std::vector<cv::Point3f> > objectPoints;
    QMessageBox error;
QString fileName;
QString eilute;
    int mode;
    enum { UNCALIBRATED = 0, CALIBRATING = 1, CALIBRATED = 2 };
    int frame_n;
    int  frames;
    uint32_t time_stamp;
    float   chessboard_sec_delay;
    void finish_calibration(void);
    int target_depth;
};

#endif // STEREO_VISION_H
