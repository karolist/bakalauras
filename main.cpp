
#include <iostream>
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <QtGStreamer/QGst/Init>
#include <QObject>
#include <QFile>

#include "videoin.h"
#include "analyzer.h"
#include "mainwindow.h"
#include "gui.h"
#include "stereo_vision.h"
#include "BDTargeting.h"


int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    QGst::init();

    Analyzer left_stream,right_stream;
    VideoIN left_cam, right_cam;
    stereo_vision stereo;
    BDTargeting valdymas;
    
    Gui langas;
    
    QObject::connect(langas.window.calibrate_button, SIGNAL(clicked()), &stereo, SLOT(calibration_init()));
    QObject::connect(langas.window.display_undistorted, SIGNAL(toggled(bool)), &stereo, SLOT(show_undistorted(bool)));
    QObject::connect(&stereo, SIGNAL(calibration_running(bool)), &langas, SLOT(calibration_status(bool)));
    QObject::connect(&stereo, SIGNAL(calibration_running(bool)), langas.window.calibration_process, SLOT(setVisible(bool)));
    QObject::connect(&stereo, SIGNAL(calibration_progress(int)), langas.window.calibration_process, SLOT(setValue(int)));
 
    QObject::connect(langas.window.sad_window_size_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(SADWindowSize_changed(int)));
    QObject::connect(langas.window.number_of_disparities_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(numberOfDisparities_changed(int)));
    QObject::connect(langas.window.prefilter_size_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(preFilterSize_changed(int)));
    QObject::connect(langas.window.prefilter_cap_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(preFilterCap_changed(int)));
    QObject::connect(langas.window.min_disparity_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(minDisparity_changed(int)));
    QObject::connect(langas.window.texture_Threshold_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(textureThreshold_changed(int)));
    QObject::connect(langas.window.uniqueness_ratio_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(uniquenessRatio_changed(int)));
    QObject::connect(langas.window.speckle_window_size_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(speckleWindowSize_changed(int)));
    QObject::connect(langas.window.speckle_range_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(speckleRange_changed(int)));
    QObject::connect(langas.window.disp12_maxdiff_spinbox, SIGNAL(valueChanged(int)), &stereo, SLOT(disp12MaxDiff_changed(int)));
    QObject::connect(langas.window.acumulate_sensitivity_spinbox, SIGNAL(valueChanged(int)), &left_stream, SLOT(change_acumulate_sensitivity(int)));
    QObject::connect(langas.window.threshold_sensitivity_spinbox, SIGNAL(valueChanged(int)), &left_stream, SLOT(change_threshold_sensitivity(int)));
    QObject::connect(langas.window.tabs, SIGNAL(currentChanged(int)), &langas, SLOT(refresh_view_in_tab(int)));
    QObject::connect(&left_stream, SIGNAL(frame_analyze_length(int)), langas.window.time_to_calculate, SLOT(display(int)));
    QObject::connect(&left_stream, SIGNAL(number_of_features_to_track(int)), langas.window.num_of_tracked_features, SLOT(display(int)));
    QObject::connect(&left_stream, SIGNAL(tracked_object_x(int)), langas.window.horizontal_data, SLOT(setNum(int)));
    QObject::connect(&left_stream, SIGNAL(tracked_object_y(int)), langas.window.vertical_data, SLOT(setNum(int)));
    QObject::connect(langas.window.load_calibration_data_depth, SIGNAL(clicked(bool)), &stereo, SLOT(load_data()));
    QObject::connect(langas.window.save_calibration_data_depth, SIGNAL(clicked(bool)), &stereo, SLOT(save_data()));
    QObject::connect(&stereo, SIGNAL(refresh_depth_settings(cv::Ptr<CvStereoBMState>)), &langas, SLOT(refresh_depth_data(cv::Ptr<CvStereoBMState>)));
    QObject::connect(langas.window.save_calibration_data_raw, SIGNAL(clicked(bool)), &stereo, SLOT(save_calibration_file()));
    QObject::connect(langas.window.load_calibration_data_raw, SIGNAL(clicked(bool)), &stereo, SLOT(load_calibration_file()));
    QObject::connect(&left_stream, SIGNAL(get_depth(cv::Point2f)), &stereo, SLOT(depth_report(cv::Point2f)));
    QObject::connect(&stereo, SIGNAL(give_depth_to_gui(int)), langas.window.depth_data, SLOT(setNum(int)));
    QObject::connect(langas.window.start_tracking, SIGNAL(clicked(bool)), &left_stream, SLOT(start_tracking_function(bool)));
    QObject::connect(langas.window.calibrate_laser, SIGNAL(clicked(bool)), &left_stream, SLOT(laser_calibration(bool)));
    QObject::connect(langas.window.x_koordinates, SIGNAL(valueChanged(int)), &left_stream, SLOT(laser_change_x(int)));
    QObject::connect(langas.window.y_koordinates, SIGNAL(valueChanged(int)), &left_stream, SLOT(laser_change_y(int)));
    QObject::connect(&left_stream, SIGNAL(laser_calibration_status(bool)), &langas, SLOT(laser_calibration_status(bool)));
    QObject::connect(langas.window.fix_laser_position, SIGNAL(clicked(bool)), &left_stream, SLOT(fix_laser_position()));
    
    QObject::connect(langas.window.config_but, SIGNAL(clicked(bool)), &langas, SLOT(check_config()));
    QObject::connect(langas.window.test_but, SIGNAL(clicked(bool)), &langas, SLOT(test_device()));
    QObject::connect(langas.window.send_but, SIGNAL(clicked(bool)), &langas, SLOT(DATA_SEND_EXAMPLE()));
    QObject::connect(langas.window.circle_but, SIGNAL(clicked(bool)), &langas, SLOT(DATA_SEND_EXAMPLE_2()));    
    QObject::connect(langas.window.random_pos_but, SIGNAL(clicked(bool)), &langas, SLOT(DATA_SEND_EXAMPLE_3()));
    
    QObject::connect(langas.window.left_cam_flip, SIGNAL(clicked(bool)), &left_cam, SLOT(flip_image()));
    QObject::connect(langas.window.right_cam_flip, SIGNAL(clicked(bool)), &right_cam, SLOT(flip_image()));
//     QObject::connect(langas.window, SIGNAL(), &langas, SLOT(close_app()));
    left_cam.irenginys = "/dev/video1";
    left_cam.create_pipeline();
    left_cam.start_stream();
    right_cam.irenginys = "/dev/video0";
    right_cam.create_pipeline();
    right_cam.start_stream();
    int blink = 0;
    langas.show();
    
    libusb_device_handle *dev_handle;			// irenginio handle
    libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
    valdymas.open_device(&dev_handle, &ctx);
//     valdymas.send_data(1,680,820,0,0,1,dev_handle);
//     app.setAttribute(Qt::WA_QuitOnClose);
    while(1)
    {
	app.processEvents();
	
        left_cam.get_frame(left_stream.frame);
 	right_cam.get_frame(right_stream.frame);
	left_cam.bandinys.copyTo(left_stream.frame);
 	right_cam.bandinys.copyTo(right_stream.frame);
	if(left_cam.flip)
	{
	cv::flip(left_stream.frame,left_stream.frame,-1);
	};
	if(right_cam.flip)
	{
 	cv::flip(right_stream.frame,right_stream.frame,-1);
	};
        if(!((left_stream.frame.empty())/*&&(right_stream.frame.empty())*/))
	{
	  stereo.stereo_procedure(left_stream.frame,right_stream.frame);
	  if(stereo.undistort)
	  {
	    left_stream.analyze_loop(stereo.left_output);
	    langas.refresh_view(stereo.left_output, stereo.right_output, stereo.depth_map, left_stream.output);
	  }
	  else
	  {
	    left_stream.analyze_loop(left_stream.frame);
	  langas.refresh_view(left_stream.frame, right_stream.frame, stereo.depth_map, left_stream.output);
	  };
	  if(left_stream.laser_calibrating_process==true)
	  {
	    qDebug("Laser_value_x and y: %d \t %d", left_stream.laser_value_x, left_stream.laser_value_y);
	    valdymas.send_data(1, left_stream.laser_value_x, left_stream.laser_value_y,1,0,1,dev_handle);
	    
	  };
	  if(left_stream.start_tracking)
	  {
	    if(blink++>=30)
	    {
	    valdymas.send_data(1, (int)(1.5*left_stream.target.x+164), (int)(-1.4*left_stream.target.y+1164), 1,0,1, dev_handle);
	    blink = 0;
	    }
	    else
	    {
	      	    valdymas.send_data(1, (int)(1.5*left_stream.target.x+164), (int)(-1.4*left_stream.target.y+1164), 0,0,1, dev_handle);
	    };
	  }
	}
	
      
    if(langas.close)
    {
    return app.exec();
    };
    };
}
