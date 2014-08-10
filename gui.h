/*
    Main gui class
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


#ifndef GUI_H
#define GUI_H
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <opencv2/calib3d/calib3d.hpp>
#include <libusb-1.0/libusb.h>
#include "firmware/requests.h"   // request numeriai
#include "firmware/usbconfig.h"  // irenginio VID/PID
#define X_calib	 80  		// Lazerio kampo koregavimas.
#define Y_calib	220		// Spindulis kiek imanoma statmenesnis korpuso priekinei sienelei.
#include <QThread> 


class Gui : public QMainWindow
{
  Q_OBJECT
public:
  Gui( QMainWindow *parent = 0);
  virtual ~Gui();
  void refresh_view(cv::Mat view_l, cv::Mat view_r, cv::Mat depth, cv::Mat movement);
  Ui_MainWindow window;
  bool close;
private:
  int current_tab;
  int open_device(libusb_device_handle **device, libusb_context **uctx);
  int set_config(int config);
  int send_data(int servo, int pos_x, int pos_y, int lazer_enbl, int restart_enbl, int buzzer, libusb_device_handle *dev_handle);

public slots:
  void refresh_view_in_tab(int);
  void calibration_status(bool);
  void laser_calibration_status(bool);
  void refresh_depth_data(cv::Ptr<CvStereoBMState>);
  void check_config();
  void DATA_SEND_EXAMPLE();
  void test_device();
  void DATA_SEND_EXAMPLE_2();
  void DATA_SEND_EXAMPLE_3();
  void close_app();
};

#endif // GUI_H

class aThread : public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};
