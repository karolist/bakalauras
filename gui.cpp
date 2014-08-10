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


#include "gui.h"
#include "mainwindow.h"
#include "video_widget.h"
#include <QApplication>
#include <QMainWindow>
#include <QThread>


Gui::Gui(QMainWindow *parent) : QMainWindow(parent)
{
  window.setupUi(this);
  current_tab = 0;
  close = FALSE;
}

Gui::~Gui()
{

}

void Gui::refresh_view(cv::Mat view_l, cv::Mat view_r, cv::Mat depth, cv::Mat movement)
{
  switch(current_tab)
  {
    case(0):
  window.video_frame_l->send_image(view_l);
  window.video_frame_r->send_image(view_r);
  break;
    case(1):
      window.video_frame_depth->send_image(depth);
      break;
    case(2):
      window.video_frame_movement_map->send_image(movement);

  }
    
//   window.video_frame_depth->send_image(view_l);
//   window.video_frame_movement_map->send_image(view_l);
}

void Gui::refresh_view_in_tab(int tabas)
{
  current_tab = tabas;
}

void Gui::calibration_status(bool status)
{
  if(status)
    window.calibrate_button->setText("Cancel calibration");
  else
    window.calibrate_button->setText("Calibrate");
}

void Gui::laser_calibration_status(bool status)
{
  if(status)
    window.calibrate_laser->setText("Cancel laser calibration");
  else
    window.calibrate_laser->setText("Calibrate laser");
}

void Gui::refresh_depth_data(cv::Ptr< CvStereoBMState > data)
{
  qDebug("Refresh data");
  window.sad_window_size_spinbox->setValue(data->SADWindowSize/2 -1);
  window.number_of_disparities_spinbox->setValue(data->numberOfDisparities/16);
  window.prefilter_size_spinbox->setValue(data->preFilterSize/2 -1);
  window.prefilter_cap_spinbox->setValue(data->preFilterCap);
  window.min_disparity_spinbox->setValue(data->minDisparity);
  window.texture_Threshold_spinbox->setValue(data->textureThreshold);
  window.uniqueness_ratio_spinbox->setValue(data->uniquenessRatio);
  window.speckle_window_size_spinbox->setValue(data->speckleWindowSize);
  window.speckle_range_spinbox->setValue(data->speckleRange);
  window.disp12_maxdiff_spinbox->setValue(data->disp12MaxDiff);
}


void Gui::check_config()
{
//      int C_SERVO1, C_SERVO2, C_ASERVO, C_SUPPLY, C_BUZZER, C_LASER3V, C_LASER5V;
//     
//     Qt::CheckState Servo1_checkbox_state, Servo2_checkbox_state, addServo_checkbox_state;
//     Qt::CheckState Supply_checkbox_state, Laser_3V_checkbox_state, Laser_5V_checkbox_state, Buzzer_checkbox_state;
//     
//     Servo1_checkbox_state = window.servo1_check->checkState();
//     Servo2_checkbox_state = window.servo2_check->checkState();
//     addServo_checkbox_state = window.addservo_check->checkState();
//     Buzzer_checkbox_state = window.buzzer_check->checkState();
//     Supply_checkbox_state = window.supply_check->checkState();
//     Laser_3V_checkbox_state = window.laser3v_check->checkState();
//     Laser_5V_checkbox_state = window.laser5v_check->checkState();
//     
//     
//     Servo1_checkbox_state == Qt::Checked ? C_SERVO1 = (1<<0) : C_SERVO1 = 0;
//     Servo2_checkbox_state == Qt::Checked ? C_SERVO2 = (1<<1) : C_SERVO2 = 0;
//     addServo_checkbox_state == Qt::Checked ? C_ASERVO = (1<<2) : C_ASERVO = 0;
//     Supply_checkbox_state == Qt::Checked ? C_SUPPLY = (1<<3) : C_SUPPLY = 0;
//     Buzzer_checkbox_state == Qt::Checked ? C_BUZZER = (1<<4) :  C_BUZZER = 0;
//     Laser_3V_checkbox_state == Qt::Checked ? C_LASER3V = (1<<5) : C_LASER3V = 0;
//     Laser_5V_checkbox_state == Qt::Checked ? C_LASER5V = (1<<6) : C_LASER5V = 0;
//     //if ( Servo2_checkbox_state == Qt::Checked ) label2->setText("Passwords match!");
//     
//     set_config(C_SERVO1 | C_SERVO2 | C_ASERVO | C_SUPPLY | C_BUZZER | C_LASER3V | C_LASER5V);
}
// 
int Gui::set_config(int config)
{
//     int timeout = 5000;			// SETUP paketo leidziama siuntimo trukme,
//     int cnt_transfer =0;			// sekmingai perduotu baitu skaicius arba klaidos kodas
//     int cnt;
//     unsigned char buffer[4];			// buferis duomenu grazinimui
//     int rxConfig;				// primtu duomenu kintamasis
//     
// //     libusb_device_handle *dev_handle;		// irenginio handle
// //     libusb_context *ctx = NULL; 		// libusb sesija, NULL kadangi vienas vartotojas
//   
//     cnt = open_device(&dev_handle, &ctx);	// atidarome irengini, gauname jo handle ir sesijos info
//     window.small_editor->clear();
//     
//     if(cnt == 1)
// //     cnt_transfer = libusb_control_transfer(dev_handle, LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN, CUSTOM_RQ_SET_CONFIG , config, 0, buffer, sizeof(buffer), timeout);
//     else
//     {
//         window.small_editor->append( "Warning: cannot open device");
//         return cnt_transfer;    
//     }
//     
//     rxConfig= (int)buffer[0] & 0xff;
//     if (config == rxConfig) window.small_editor->append( "Configuration completed successfully.");
//     else window.small_editor->append( "Data transmission error !");
//     
// //     libusb_close(dev_handle);			// uzdarome atidaryta irengini
// //     libusb_exit(ctx); 		          // sesijos uzdarimas
//     return cnt_transfer;			// graziname sekmingai perduotu baitu skaiciu arba klaidos koda
}

int Gui::open_device(libusb_device_handle **device, libusb_context **uctx)
{
//     int r;				// libusb_init() grazinamoms reiksmems,
//     int vid, pid;				// vendorID , productID,
//     size_t cnt;				// saugos irenginiu skaiciu sarase
//     const unsigned char rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
//     
//     libusb_device **devs; 			// nuoroda i nuoroda i irenginius, naudojamn irenginiu sarasui gauti
//     libusb_device_handle *dev_handle;		// irenginio handle
//     libusb_context *ctx = NULL; 		// libusb sesija, NULL kadangi vienas vartotojas
//   
//     r = libusb_init(&ctx); 			// biblotekos sesijos inicializacija
//     *uctx = ctx;
//     if(r < 0) return 0;		          // ivyko klaida
//   
//     libusb_set_debug(ctx, 3);			// nustatyti detalizacijos lygį iki 3, kaip siūloma dokumente
//     
//     cnt = libusb_get_device_list(ctx, &devs);	// gauname irenginiu sarasa
//     if(cnt < 0) return 0;			// ivyko klaida
// 
//     vid = rawVid[1] * 256 + rawVid[0];		// apskaiciuojame VID/PID is usbconfig.h
//     pid = rawPid[1] * 256 + rawPid[0];
//  
//     dev_handle = libusb_open_device_with_vid_pid(ctx, vid, pid);
// 					// Aatidarome irengini pagal VendorID ir ProductID
//     *device = dev_handle;
//     if(dev_handle == NULL) return 0;		// ivyko klaida
//     
//     libusb_free_device_list(devs, 1); 		// atlaisvinamas irenginiu sarasas
//     
//     return 1;
}
// 
void Gui::DATA_SEND_EXAMPLE()
{
//     int Laser_on_off;
//     int xposition, yposition;
//     Qt::CheckState Laser_state;
//     Laser_state = window.laser_en_check->checkState();
//     Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
//     
//     xposition = window.x_coordinate_spin->value() + X_calib;
//     yposition = window.y_coordinate_spin->value() + Y_calib;
//     
//     window.small_editor->append( "x coordinate: " + QString::number(xposition) );
//     window.small_editor->append( "y coordinate: " + QString::number(yposition) );
//     
//     
//     int cnt, cnt_transfer;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
//     libusb_device_handle *dev_handle;			// irenginio handle
//     libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
//     
//     
//     
//     cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
//     if(cnt == 1)
//     {
//         cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
//         
//         if (cnt_transfer < 0) window.small_editor->append( "Warning: failed to transmit data");
//         else window.small_editor->append( "Number of bytes received: " + QString::number(cnt_transfer));
//     }
//     else window.small_editor->append( "Warning: cannot open device");
//     libusb_close(dev_handle);				// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		        		// sesijos uzdarymas
}
// 
int Gui::send_data(int servo, int pos_x, int pos_y, int lazer_enbl, int restart_enbl, int buzzer, libusb_device_handle *dev_handle)
{
//     int timeout = 5000;			// SETUP paketo leidziama siuntimo trukme,
//     int cnt_transfer =-1;			// sekmingai perduotu baitu skaicius arba klaidos kodas
//     unsigned char buffer[4];			// buferis duomenu grazinimui
//     int value =0, index = 0;			// kintameji saugos siunciamus duomenys
//     
//     if (servo == 1) index = 1;
//     if (servo == 2) index = 2;
//     if (servo == 3) index = 4;
//     if (lazer_enbl == 1) index |= (1<<4);
//     if (restart_enbl == 1) index |= (1<<3);
//     if (buzzer == 1) index |= (1<<5);
//     if (buzzer == 2) index |= (1<<6);
//     
//     
//     index *=256;
//     
//     index |= ((pos_x & 0xf00) / 256 + (pos_y & 0xf00) / 16);
//     value = (pos_x & 0xff) + (pos_y & 0xff) * 256;
//    
//     cnt_transfer = libusb_control_transfer(dev_handle, LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT, CUSTOM_RQ_SET_POSITION, value, index, buffer, sizeof(buffer), timeout);
//     
//     return cnt_transfer;
}
// 
void Gui::test_device()
{
//     int timeout = 5000;			// SETUP paketo leidziama siuntimo trukme,
//     int cnt_transfer =0;			// sekmingai perduotu baitu skaicius arba klaidos kodas
//     int cnt, i;
//     unsigned char buffer[4];			// buferis duomenu grazinimui	
//     
//     libusb_device_handle *dev_handle;		// irenginio handle
//     libusb_context *ctx = NULL; 		// libusb sesija, NULL kadangi vienas vartotojas
//   
//     cnt = open_device(&dev_handle, &ctx);	// atidarome irengini, gauname jo handle ir sesijos info
//     //srand(time(NULL));
//     window.small_editor->clear();
//     
//     for( i=0; i < 500; i++)
//     {
//         int value = qrand() & 0xffff, index = qrand() & 0xffff;
//         int rxValue, rxIndex;
//         if((i+1) % 100 ==  0) window.small_editor->append( "Iteraciju: " + QString::number(i+1));
//         
//         if(cnt == 1)
//         {
// 	  cnt_transfer = libusb_control_transfer(dev_handle, LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN, CUSTOM_RQ_ECHO , value, index, buffer, sizeof(buffer), timeout);
// 	  if(cnt_transfer < 0)
// 	  {
// 	      window.small_editor->append( "Device error in iteration: " + QString::number(i));
// 	      break;
// 	  }
// 	  else if(cnt_transfer != 4)
// 	  {
// 	      window.small_editor->append( "Error in iteration: " + QString::number(i) + ". Received: "+QString::number(cnt_transfer) + "bytes instead of 4 ");
// 	      break;
// 	  }
//         }
//         else
//         {
// 	  window.small_editor->append( "Warning: cannot open device");
// 	  break;
//         }
//     
//         rxValue = ((int)buffer[0] & 0xff) | (((int)buffer[1] & 0xff) << 8);
//         rxIndex = ((int)buffer[2] & 0xff) | (((int)buffer[3] & 0xff) << 8);
//         
//         if(rxValue != value || rxIndex != index)
//         {
// 	 window.small_editor->append( "Data error in iteration: " + QString::number(i));
// 	 window.small_editor->append( "rxValue: " + QString::number(rxValue) + " Value: " + QString::number(value));
// 	 window.small_editor->append( "rxIndex: " + QString::number(rxIndex) + " Value: " + QString::number(index));
//         }
//         
//     }
//     
//     aThread::msleep(5);
//     
//    window.small_editor->append( "Test completed.");
//     libusb_close(dev_handle);			// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		          // sesijos uzdarimas
// //     return;			// graziname sekmingai perduotu baitu skaiciu arba klaidos koda
// 
}
void Gui::DATA_SEND_EXAMPLE_2()
{
//     int Laser_on_off;
//     int xposition, yposition;
//     Qt::CheckState Laser_state;
//     Laser_state = window.laser_en_check->checkState();
//     Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
//     
//     xposition = 128;
//     yposition = 128;
//    
//     int cnt, cnt_transfer, i;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
//     libusb_device_handle *dev_handle;			// irenginio handle
//     libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
// 
//     cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
//     if(cnt == 1)
//     {
//         for(i=0; i < 1201; i+=20)
//         {
// 	  xposition = i + X_calib;
// 	  yposition = sqrt(pow(600, 2) - pow((i-600), 2)) + 600 + Y_calib;
// 	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
// 	  if (cnt_transfer < 0) window.small_editor->append( "Warning: failed to transmit data");
// 	  aThread::msleep(50);
//         }
//         for(i=1200; i > -1; i-=20)
//         {
// 	  xposition = i + X_calib;
// 	  yposition = -sqrt(pow(600, 2) - pow((i-600), 2)) + 600 + Y_calib;
// 	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
// 	  if (cnt_transfer < 0) window.small_editor->append( "Warning: failed to transmit data");
// 	  aThread::msleep(50);
//         }
//         
//     }
//     else{ 
//         window.small_editor->append( "Warning: cannot open device");
//         return;
//     }
//     window.small_editor->append( "Data sent successfully");
//     libusb_close(dev_handle);				// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		        		// sesijos uzdarymas
}
// 
void Gui::DATA_SEND_EXAMPLE_3()
{
//     int Laser_on_off;
//     int xposition, yposition;
//     Qt::CheckState Laser_state;
//     Laser_state = window.laser_en_check->checkState();
//     Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
//     
//     int cnt, cnt_transfer, i;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
//     libusb_device_handle *dev_handle;			// irenginio handle
//     libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
//     
//     cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
//     if(cnt == 1)
//     {
//         for(i=0; i < 100; i+=3)
//         {
// 	  xposition = qrand()%600 + 400;
// 	  yposition = qrand()%600 + 400;
// 	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
// 	  if (cnt_transfer < 0) window.small_editor->append( "Warning: failed to transmit data");
// 	  aThread::msleep(50);
//         }  
//     }
//     else{
//         window.small_editor->append( "Warning: cannot open device");
//         return;
//     }
//     window.small_editor->append( "Data sent successfully.");
//     libusb_close(dev_handle);				// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		        		// sesijos uzdarymas
}

void Gui::close_app()
{
  qDebug("closing");
  close= ! close;
}
