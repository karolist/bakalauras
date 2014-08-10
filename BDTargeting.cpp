#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "BDTargeting.h"

#include <QtGui/QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QTime>
#include <QTest>
#include <QMutex>
#include <QWaitCondition>
#include <QTextCodec>

#include "firmware/requests.h"   // request numeriai
#include "firmware/usbconfig.h"  // irenginio VID/PID

BDTargeting::BDTargeting(): QDialog()
{
     QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    
     QGroupBox *ServoGroup = new QGroupBox("Kreipimo mechanizmai");
     Servo1_checkbox = new QCheckBox("Pirmas kreipimo mechanizmas");
     Servo2_checkbox = new QCheckBox("Antras kreipimo mechanizmas");
     addServo_checkbox = new QCheckBox("Papildomas servo mechanizmas");
     
     QGroupBox *ConfigGroup = new QGroupBox("Kiti parametrai:");
     Supply_checkbox = new QCheckBox("5V maitinimas");
     Laser_3V_checkbox = new QCheckBox("Lazeris 3V");
     Laser_5V_checkbox = new QCheckBox("Lazeris 5V");
     Buzzer_checkbox = new QCheckBox("Garsinis signalizatorius");
     
     Servo1_checkbox->setChecked(true);
     Supply_checkbox->setChecked(true);
     Laser_3V_checkbox->setChecked(true);
     
     QGroupBox *EditorGroup = new QGroupBox("Irenginio busena");
     smallEditor = new QTextEdit;
     //smallEditor->setPlainText("");
     
     QGroupBox *SpinGroup = new QGroupBox("Rankinis valdymas");
     QLabel* xlabel = new QLabel( "x kordinate" );
     spinbox1 = new QSpinBox;
     spinbox1->setRange(0, 1200);
     spinbox1->setValue(600);
     QLabel* ylabel = new QLabel( "y kordinate" );
     spinbox2 = new QSpinBox;
     spinbox2->setRange(0, 1200);
     spinbox2->setValue(600);
     Laser_checkbox = new QCheckBox("Lazeris");
     QPushButton *button4 = new QPushButton("Send");
     QPushButton *button5 = new QPushButton("Circle");
     QPushButton *button6 = new QPushButton("Random pos.");
     
     
     QGroupBox *ConfigGroupBig = new QGroupBox("Irenginio konfiguravimas");
     
     QPushButton *button1 = new QPushButton("Cancel");
     QPushButton *button2 = new QPushButton("Config");
     QPushButton *button3 = new QPushButton("Test");
  
     QWidget *windowButtons = new QWidget;
     QHBoxLayout * butLayout = new QHBoxLayout;
     butLayout->addWidget(button1);
     butLayout->addWidget(button2);
     butLayout->addWidget(button3);
     windowButtons->setLayout(butLayout);
     
     QVBoxLayout *servoLayout = new QVBoxLayout;
     servoLayout->addWidget(Servo1_checkbox);
     servoLayout->addWidget(Servo2_checkbox);
     servoLayout->addWidget(addServo_checkbox);
     servoLayout->addSpacing(12);
     ServoGroup->setLayout(servoLayout);
     
     QVBoxLayout *configLayout = new QVBoxLayout;
     configLayout->addWidget(Supply_checkbox);
     configLayout->addWidget(Laser_3V_checkbox);
     configLayout->addWidget(Laser_5V_checkbox);
     configLayout->addWidget(Buzzer_checkbox);
     configLayout->addSpacing(12);
     ConfigGroup->setLayout(configLayout);
     
     QVBoxLayout * configBigLayout = new QVBoxLayout;
     configBigLayout->addSpacing(12);
     configBigLayout->addWidget(ServoGroup);
     configBigLayout->addWidget(ConfigGroup);
     configBigLayout->addStretch(1);
     ConfigGroupBig->setLayout(configBigLayout);

     QVBoxLayout *editorLayout = new QVBoxLayout;
     editorLayout->addWidget(smallEditor);
     EditorGroup->setLayout(editorLayout);
     
     QGridLayout *manualLayout = new QGridLayout;
     manualLayout->addWidget(xlabel, 0, 0);
     manualLayout->addWidget(spinbox1, 0, 1);
     manualLayout->addWidget(ylabel, 1, 0);
     manualLayout->addWidget(spinbox2, 1, 1);
     manualLayout->addWidget(Laser_checkbox, 2, 0);
     manualLayout->addWidget(button4, 2, 1);
     manualLayout->addWidget(button5, 3, 1);
     manualLayout->addWidget(button6, 4, 1);
     SpinGroup->setLayout(manualLayout);
     
     QWidget *windowEditor = new QWidget;
     QVBoxLayout * edLayout = new QVBoxLayout;
     edLayout->addWidget(EditorGroup);
     edLayout->addWidget(SpinGroup);
     windowEditor->setLayout(edLayout);
     
     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(ConfigGroupBig, 0, 0);
     mainLayout->addWidget(windowEditor, 0, 1);
     mainLayout->addWidget(windowButtons, 1, 1);
     setLayout(mainLayout);
     
     connect(button1, SIGNAL(clicked()), this, SLOT(close()));
     connect(button2, SIGNAL(clicked()), this, SLOT(check_config()));
     connect(button3, SIGNAL(clicked()), this, SLOT(test_device()));
     connect(button4, SIGNAL(clicked()), this, SLOT(DATA_SEND_EXAMPLE()));
     connect(button5, SIGNAL(clicked()), this, SLOT(DATA_SEND_EXAMPLE_2()));
     connect(button6, SIGNAL(clicked()), this, SLOT(DATA_SEND_EXAMPLE_3()));
     
}

void BDTargeting::check_config()
{
     int C_SERVO1, C_SERVO2, C_ASERVO, C_SUPPLY, C_BUZZER, C_LASER3V, C_LASER5V;
    
    Qt::CheckState Servo1_checkbox_state, Servo2_checkbox_state, addServo_checkbox_state;
    Qt::CheckState Supply_checkbox_state, Laser_3V_checkbox_state, Laser_5V_checkbox_state, Buzzer_checkbox_state;
    
    Servo1_checkbox_state = Servo1_checkbox->checkState();
    Servo2_checkbox_state = Servo2_checkbox->checkState();
    addServo_checkbox_state = addServo_checkbox->checkState();
    Buzzer_checkbox_state = Buzzer_checkbox->checkState();
    Supply_checkbox_state = Supply_checkbox->checkState();
    Laser_3V_checkbox_state = Laser_3V_checkbox->checkState();
    Laser_5V_checkbox_state = Laser_5V_checkbox->checkState();
    
    
    Servo1_checkbox_state == Qt::Checked ? C_SERVO1 = (1<<0) : C_SERVO1 = 0;
    Servo2_checkbox_state == Qt::Checked ? C_SERVO2 = (1<<1) : C_SERVO2 = 0;
    addServo_checkbox_state == Qt::Checked ? C_ASERVO = (1<<2) : C_ASERVO = 0;
    Supply_checkbox_state == Qt::Checked ? C_SUPPLY = (1<<3) : C_SUPPLY = 0;
    Buzzer_checkbox_state == Qt::Checked ? C_BUZZER = (1<<4) :  C_BUZZER = 0;
    Laser_3V_checkbox_state == Qt::Checked ? C_LASER3V = (1<<5) : C_LASER3V = 0;
    Laser_5V_checkbox_state == Qt::Checked ? C_LASER5V = (1<<6) : C_LASER5V = 0;
    //if ( Servo2_checkbox_state == Qt::Checked ) label2->setText("Passwords match!");
    
    set_config(C_SERVO1 | C_SERVO2 | C_ASERVO | C_SUPPLY | C_BUZZER | C_LASER3V | C_LASER5V);

}

int BDTargeting::set_config(int config)
{
//     int timeout = 5000;			// SETUP paketo leidziama siuntimo trukme,
//     int cnt_transfer =0;			// sekmingai perduotu baitu skaicius arba klaidos kodas
//     int cnt;
//     unsigned char buffer[4];			// buferis duomenu grazinimui
//     int rxConfig;				// primtu duomenu kintamasis
//     
//     libusb_device_handle *dev_handle;		// irenginio handle
//     libusb_context *ctx = NULL; 		// libusb sesija, NULL kadangi vienas vartotojas
//   
//     cnt = open_device(&dev_handle, &ctx);	// atidarome irengini, gauname jo handle ir sesijos info
//     smallEditor->clear();
//     
//     if(cnt == 1)
//     cnt_transfer = libusb_control_transfer(dev_handle, LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN, CUSTOM_RQ_SET_CONFIG , config, 0, buffer, sizeof(buffer), timeout);
//     else
//     {
//         smallEditor->append( "Klaida: nepavyko atidaryti irenginio");
//         return cnt_transfer;    
//     }
//     
//     rxConfig= (int)buffer[0] & 0xff;
//     if (config == rxConfig) smallEditor->append( "Konfiguravimas atliktas sekmingai.");
//     else smallEditor->append( "Duomenu perdavimo klaida !");
//     
//     libusb_close(dev_handle);			// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		          // sesijos uzdarimas
//     return cnt_transfer;			// graziname sekmingai perduotu baitu skaiciu arba klaidos koda
}

int BDTargeting::send_data(int servo, int pos_x, int pos_y, int lazer_enbl, int restart_enbl, int buzzer, libusb_device_handle *dev_handle)
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

int BDTargeting::open_device(libusb_device_handle **device, libusb_context **uctx)
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
//     if(cnt < 1) return 0;			// ivyko klaida //TIKRIAUSIAIA ne 0 o 1 cnt lyginamas !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
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
    return 1;
}

void BDTargeting::DATA_SEND_EXAMPLE()
{
/*    int Laser_on_off;
    int xposition, yposition;
    Qt::CheckState Laser_state;
    Laser_state = Laser_checkbox->checkState();
    Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
    
    xposition = spinbox1->value() + X_calib;
    yposition = spinbox2->value() + Y_calib;
    
    smallEditor->append( "x kordinate: " + QString::number(xposition) );
    smallEditor->append( "y kordinate: " + QString::number(yposition) );
    
    
    int cnt, cnt_transfer;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
    libusb_device_handle *dev_handle;			// irenginio handle
    libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
    
    
    
    cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
    if(cnt == 1)
    {
        cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
        
        if (cnt_transfer < 0) smallEditor->append( "Klaida: dnepavyko perduoti duomenu");
        else smallEditor->append( "Grazintu baitu skaicius: " + QString::number(cnt_transfer));
    }
    else smallEditor->append( "Klaida: nepavyko atidaryti irenginio");
    libusb_close(dev_handle);				// uzdarome atidaryta irengini
    libusb_exit(ctx); 	*/	        		// sesijos uzdarymas
}

void BDTargeting::test_device()
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
//     smallEditor->clear();
//     
//     for( i=0; i < 500; i++)
//     {
//         int value = qrand() & 0xffff, index = qrand() & 0xffff;
//         int rxValue, rxIndex;
//         if((i+1) % 100 ==  0) smallEditor->append( "Iteraciju: " + QString::number(i+1));
//         
//         if(cnt == 1)
//         {
// 	  cnt_transfer = libusb_control_transfer(dev_handle, LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN, CUSTOM_RQ_ECHO , value, index, buffer, sizeof(buffer), timeout);
// 	  if(cnt_transfer < 0)
// 	  {
// 	      smallEditor->append( "Irenginio klaida iteracijoje: " + QString::number(i));
// 	      break;
// 	  }
// 	  else if(cnt_transfer != 4)
// 	  {
// 	      smallEditor->append( "Klaida iteracijoje: " + QString::number(i) + ". Gauta "+QString::number(cnt_transfer) + "baitai vietuoje 4 baitu ");
// 	      break;
// 	  }
//         }
//         else
//         {
// 	  smallEditor->append( "Klaida: nepavyko atidaryti irenginio");
// 	  break;
//         }
//     
//         rxValue = ((int)buffer[0] & 0xff) | (((int)buffer[1] & 0xff) << 8);
//         rxIndex = ((int)buffer[2] & 0xff) | (((int)buffer[3] & 0xff) << 8);
//         
//         if(rxValue != value || rxIndex != index)
//         {
// 	  smallEditor->append( "Duomenu klaida iteracijoje: " + QString::number(i));
// 	  smallEditor->append( "rxValue: " + QString::number(rxValue) + " Value: " + QString::number(value));
// 	  smallEditor->append( "rxIndex: " + QString::number(rxIndex) + " Value: " + QString::number(index));
//         }
//         
//     }
//     
//     Thread::msleep(5);
//     
//     smallEditor->append( "Testo pabaiga.");
//     libusb_close(dev_handle);			// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		          // sesijos uzdarimas
    return;			// graziname sekmingai perduotu baitu skaiciu arba klaidos koda

}

void BDTargeting::DATA_SEND_EXAMPLE_2()
{
  /*  int Laser_on_off;
    int xposition, yposition;
    Qt::CheckState Laser_state;
    Laser_state = Laser_checkbox->checkState();
    Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
    
    xposition = 128;
    yposition = 128;
   
    int cnt, cnt_transfer, i;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
    libusb_device_handle *dev_handle;			// irenginio handle
    libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas

    cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
    if(cnt == 1)
    {
        for(i=0; i < 1201; i+=20)
        {
	  xposition = i + X_calib;
	  yposition = sqrt(pow(600, 2) - pow((i-600), 2)) + 600 + Y_calib;
	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
	  if (cnt_transfer < 0) smallEditor->append( "Klaida: dnepavyko perduoti duomenu");
	  Thread::msleep(50);
        }
        for(i=1200; i > -1; i-=20)
        {
	  xposition = i + X_calib;
	  yposition = -sqrt(pow(600, 2) - pow((i-600), 2)) + 600 + Y_calib;
	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
	  if (cnt_transfer < 0) smallEditor->append( "Klaida: dnepavyko perduoti duomenu");
	  Thread::msleep(50);
        }
        
    }
    else{ 
        smallEditor->append( "Klaida: nepavyko atidaryti irenginio");
        return;
    }
    smallEditor->append( "Duomenys issiusti sekmingai");
    libusb_close(dev_handle);				// uzdarome atidaryta irengini
    libusb_exit(ctx); 		        */		// sesijos uzdarymas
}

void BDTargeting::DATA_SEND_EXAMPLE_3()
{
 /*   int Laser_on_off;
    int xposition, yposition;
    Qt::CheckState Laser_state;
    Laser_state = Laser_checkbox->checkState();
    Laser_state == Qt::Checked ? Laser_on_off = 1 : Laser_on_off = 0;
    
    int cnt, cnt_transfer, i;				// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
    libusb_device_handle *dev_handle;			// irenginio handle
    libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
    
    cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
    if(cnt == 1)
    {
        for(i=0; i < 100; i+=3)
        {
	  xposition = qrand()%600 + 400;
	  yposition = qrand()%600 + 400;
	  cnt_transfer = send_data(1, xposition, yposition, Laser_on_off, 0, 0, dev_handle);		// Paketo SETUP siuntimas su duomenimis
	  if (cnt_transfer < 0) smallEditor->append( "Klaida: dnepavyko perduoti duomenu");
	  Thread::msleep(50);
        }  
    }
    else{
        smallEditor->append( "Klaida: nepavyko atidaryti irenginio");
        return;
    }
    smallEditor->append( "Duomenys sėkmingai išsiųsti.");
    libusb_close(dev_handle);				// uzdarome atidaryta irengini
    libusb_exit(ctx); 		        	*/	// sesijos uzdarymas
}


BDTargeting::~BDTargeting()
{}

// #include "BDTargeting.moc"

// void BDTargeting::DATA_SEND_EXAMPLE()
// {
//     int cnt;					// cnt = 1 jeigu irenginis atidarytas, kitu atveju 0
//     libusb_device_handle *dev_handle;			// irenginio handle
//     libusb_context *ctx = NULL; 			// libusb sesija, NULL kadangi vienas vartotojas
//    
//     
//     cnt = open_device(&dev_handle, &ctx);		// atidarome irengini, jeigu cnt=1 irenginis atidarytas
//     if(cnt == 1)
//         send_data(1, 60, 110, Laser_on_off, 0, dev_handle);	// Paketo SETUP siuntimas su duomenimis
//     libusb_close(dev_handle);				// uzdarome atidaryta irengini
//     libusb_exit(ctx); 		        		// sesijos uzdarymas
// }

