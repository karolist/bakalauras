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


#ifndef ANALYZER_H
#define ANALYZER_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "opencv2/video/tracking.hpp"
#include <stdio.h>
#include <iostream>

#include <QObject>
#include <QTime>

using namespace cv;
using namespace std;

class Analyzer : public QObject
{
  Q_OBJECT
public:
    Analyzer();
    void AllocateImages();
    void build_average();
    void find_objects();
    void draw_rectangle();
    void analyze_loop(cv::Mat frame_source);
    
    cv::Mat abs_frame;
    cv::Mat frame;
    cv::Mat frame_gray;
    cv::Mat average;
    cv::VideoCapture cap;
    cv::Mat element;
    cv::Mat drawing;
    cv::Mat drawing2;
        cv::Mat drawing3;
    cv::Mat last_drawing;
    cv::Mat movement_mask;
    cv::Mat output;
    std::vector< cv::Point2f> detected_corners;
    cv::Point2f target;
    bool target_detected;
    int frame_length;
    bool laser_calibrating_process;	
    int laser_value_x;
    int laser_value_y;
        bool start_tracking;
public slots:
  void calibration_init();
  void show_undistorted(bool);
  void change_acumulate_sensitivity(int);
  void change_threshold_sensitivity(int);
  void center();
  void start_tracking_function(bool);
  void laser_calibration(bool);
  void laser_change_x(int);
  void laser_change_y(int);
  void fix_laser_position();
signals:
  void got_calibration_frame(int);
  void send_reprojection_error(double);
  void target_state(bool);
  void frame_analyze_length(int);
  void number_of_features_to_track(int);
  void tracked_object_x(int);
  void tracked_object_y(int);
  void get_depth(cv::Point2f);
  void laser_calibration_status(bool);
  
private:
    double accumulate_ratio;
    cv::Mat tmp_frame;
    bool first_frame;
//     std::vector<cv::Point2f> features;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > contours2;
    std::vector<cv::Vec4i> hierarchy2;
    std::vector<std::vector<cv::Point2f> > imagePoints;
    int targetingPoint_strike;
    int minimum_distance_to_target;
    bool targetingPoint_refreshed;
    
    std::vector<cv::Point2f> list_of_objects;
    std::vector<int> distance_to_point;
    
    cv::Mat cameraMatrix, distCoeffs;
    cv::Size imageSize;
    
    int mode; //???
    clock_t prevTimestamp;
    bool calibrating;
    bool showUndistorted;
    cv::Point2f last_targetingPoint;
    std::vector<cv::Point2f> points_to_track[2];
    float acumulate_sensitivity;
    int threshold;
    cv::Mat prevGray;
    cv::TermCriteria termcrit;
    cv::Size winSize;
    int ttl_for_last_point;
    QTime time;
    int frame_length_temp;
    int frame_length_count;

    cv::Mat laser_calibration_matrix;

};

#endif // ANALYZER_H
