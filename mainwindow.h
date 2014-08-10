#ifndef DESIGNERN14265_H
#define DESIGNERN14265_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QStatusBar>
#include <QWidget>
#include "video_widget.h"
#include "kled.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;

    QTabWidget *tabs;
    
    // Raw Tab
    QWidget *raw_tab;
    QPushButton *calibrate_button, *load_calibration_data_raw, *save_calibration_data_raw;
    QProgressBar *calibration_process;
    video_widget *video_frame_l;
    video_widget *video_frame_r;
    QCheckBox *display_undistorted;
    
    // Depth Tab
    QWidget *depth_tab;
    QWidget *gridLayoutWidget_depth;
    
    QPushButton *load_calibration_data_depth, *save_calibration_data_depth;
    QGridLayout *gridLayout_raw;
    QGridLayout *gridLayout_depth;
    QGridLayout *gridLayout_settings;
    
    video_widget *video_frame_depth;
    QSlider *sad_window_size, *number_of_disparities, *prefilter_size, *prefilter_cap, *min_disparity, *texture_Threshold, *uniqueness_ratio, *speckle_window_size, *speckle_range, *disp12_maxdiff;
    QLabel *sad_window_size_label, *number_of_disparities_label, *prefilter_size_label, *prefilter_cap_label, *min_disparity_label, *texture_Threshold_label, *uniqueness_ratio_label, *speckle_window_size_label, *speckle_range_label, *disp12_maxdiff_label;
    QSpinBox *sad_window_size_spinbox, *number_of_disparities_spinbox, *prefilter_size_spinbox, *prefilter_cap_spinbox, *min_disparity_spinbox, *texture_Threshold_spinbox, *uniqueness_ratio_spinbox, *speckle_window_size_spinbox, *speckle_range_spinbox, *disp12_maxdiff_spinbox;
    
    // Movement Tab
    QWidget *movement_tab;
    QWidget *gridLayoutWidget_movement_map;
    QGridLayout *gridLayout_movement_map, *coordinates_gridlayout, *laser_calibration_gridLayout;
    
    QSlider *acumulate_sensitivity, *threshold_sensitivity, *x_koordinates, *y_koordinates;
    QSpinBox *acumulate_sensitivity_spinbox, *threshold_sensitivity_spinbox;
    QLabel *acumulate_sensitivity_label, *threshold_sensitivity_label, *calculation_time, *horizontal_slider_label, *vertical_slider_label;
    video_widget *video_frame_movement_map;
    QPushButton *save_laser_data, *load_laser_data, *start_tracking, *calibrate_laser, *fix_laser_position;
    QLCDNumber *time_to_calculate, *num_of_tracked_features;
    QLabel *horizontal_label, *vertical_label, *depth_label, *horizontal_data, *vertical_data, *depth_data, *coordinates_label, *time_to_calculate_label, *num_of_tracked_features_label;
    QHBoxLayout *vertical_movement_layout;
    QRadioButton *up_left, *up_right, *center, *down_left, *down_right;
    
    QGroupBox *laser_calibration;
    
    // Settings Tab
    QWidget *settings_tab;
    QGridLayout *settings_tab_gridlayout, *manual_control_group_layout, *device_selector_layout;
    QWidget *gridLayoutWidget_settings;

    QGroupBox *servo_group, *config_group, *editor_group, *manual_control_group, *config_group_big, *device_selector;
    QCheckBox *servo1_check, *servo2_check, *addservo_check, *supply_check, *laser3v_check, *laser5v_check, *buzzer_check, *laser_en_check, *left_cam_flip, *right_cam_flip;
    
    QSpinBox *x_coordinate_spin, *y_coordinate_spin, *fps_spin;
    QPushButton *cancel_but, *config_but, *test_but, *send_but, *circle_but, *random_pos_but;
    QVBoxLayout *servo_group_layout, *config_group_layout, *editor_group_layout;
    QTextEdit *small_editor;
    
    QLabel *x_label, *y_label, *left_cam_label, *right_cam_label, *resolution_label, *fps_label;
    QComboBox *left_cam_selector, *right_cam_selector, *resolution_selector;
    
    QMenuBar *menubar;
    QStatusBar *statusbar;
    
    
    
    
    QHBoxLayout *horizontalLayout, *horizontalLayout_raw_tab, *horizontalLayout_movement_tab, *horizontalLayout_depth_tab, *horizontalLayout_settings_tab;
    
    
    
    void setupUi(QMainWindow *MainWindow)
    {
//         if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("Moving object targeting system"));
	
//         MainWindow->resize(1290, 666);
	
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString("centralwidget"));
	
	horizontalLayout = new QHBoxLayout(centralwidget);
	horizontalLayout->setObjectName(QString("horizontalLayout"));
	
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName("Tab widget");

	horizontalLayout->addWidget(tabs);
	
        raw_tab = new QWidget();
        raw_tab->setObjectName("Raw tab");
	
	horizontalLayout_raw_tab = new QHBoxLayout(raw_tab);
	horizontalLayout_raw_tab->setObjectName(QString("horizontalLayout_raw_tab"));
	
        depth_tab = new QWidget();
	depth_tab->setObjectName("Depth tab");
	
	horizontalLayout_depth_tab = new QHBoxLayout(depth_tab);
	horizontalLayout_depth_tab->setObjectName(QString("horizontalLayout_depth_tab"));
	
        movement_tab = new QWidget();
	movement_tab->setObjectName("Movement tab");
	
	horizontalLayout_movement_tab = new QHBoxLayout(movement_tab);
	horizontalLayout_movement_tab->setObjectName(QString("horizontalLayout_movement_tab"));
	
        settings_tab = new QWidget();
	settings_tab->setObjectName("Settings tab");
	
	horizontalLayout_settings_tab = new QHBoxLayout(settings_tab);
	horizontalLayout_settings_tab->setObjectName(QString("horizontalLayout_settings_tab"));
	
        tabs->addTab(raw_tab, "Raw");
        tabs->addTab(depth_tab, "Depth");
        tabs->addTab(movement_tab, "Movement");
        tabs->addTab(settings_tab, "Settings");

	gridLayout_raw = new QGridLayout();
        gridLayout_raw->setObjectName(QString("gridLayout_raw_tab"));
	
// 	
        gridLayout_depth = new QGridLayout();
        gridLayout_depth->setObjectName(QString("gridLayout_depth_tab"));
// 
	
        video_frame_l = new video_widget();
        video_frame_l->setObjectName(QString("video_frame_l"));
        video_frame_l->setEnabled(true);
//         video_frame_l->setMinimumSize(640,480);
        video_frame_l->setMaximumSize(640,480);
        gridLayout_raw->addWidget(video_frame_l, 0, 0, 1, 2);
// 
        video_frame_r = new video_widget();
        video_frame_r->setObjectName(QString("video_frame_r"));
        video_frame_r->setEnabled(true);
//         video_frame_r->setMinimumSize(640,480);
        video_frame_r->setMaximumSize(640,480);
        gridLayout_raw->addWidget(video_frame_r, 0, 2, 1, 2);
	
	calibrate_button = new QPushButton(raw_tab);
        calibrate_button->setObjectName(QString("calibrate_button"));
	calibrate_button->setText(QString("Calibrate"));
        gridLayout_raw->addWidget(calibrate_button, 1, 0, 1, 1);
// 
	load_calibration_data_raw = new QPushButton(raw_tab);
        load_calibration_data_raw->setObjectName(QString("load_calibration_data"));
	load_calibration_data_raw->setText(QString("Load calibration file"));
        gridLayout_raw->addWidget(load_calibration_data_raw, 1, 2, 1, 1);
	
	save_calibration_data_raw = new QPushButton(raw_tab);
        save_calibration_data_raw->setObjectName(QString("save_calibration_data"));
	save_calibration_data_raw->setText(QString("Save calibration file"));
// 	save_calibration_data_raw->setDisabled(true);
        gridLayout_raw->addWidget(save_calibration_data_raw, 1, 3, 1, 1);
	
	calibration_process = new QProgressBar(raw_tab);
        calibration_process->setObjectName(QString("calibration_process"));
        calibration_process->setValue(0);
	calibration_process->setVisible(false);
        gridLayout_raw->addWidget(calibration_process, 2, 0, 1, 4);
	horizontalLayout_raw_tab->addLayout(gridLayout_raw);

        display_undistorted = new QCheckBox(raw_tab);
        display_undistorted->setObjectName("Display undistorted");
        display_undistorted->setText("Display undistorted");
	display_undistorted->setChecked(false);
        gridLayout_raw->addWidget(display_undistorted, 1, 1, 1, 1);


	//Depth Tab
	horizontalLayout_depth_tab->addLayout(gridLayout_depth);
	video_frame_depth = new video_widget();
	video_frame_depth->setObjectName("video_frame_depth");
	video_frame_depth->setEnabled(true);
	video_frame_depth->setMinimumSize(640,480);
	video_frame_depth->setMaximumSize(640,480);

// 	
	sad_window_size_label = new QLabel();
	sad_window_size_label->setText(QString("SAD window size"));
	number_of_disparities_label = new QLabel();
	number_of_disparities_label->setText(QString("Number of disparities"));
	prefilter_size_label = new QLabel();
	prefilter_size_label->setText(QString("preFilter size"));
	prefilter_cap_label = new QLabel();
	prefilter_cap_label->setText(QString("preFilter cap"));
	min_disparity_label = new QLabel();
	min_disparity_label->setText(QString("min disparity"));
	texture_Threshold_label = new QLabel();
	texture_Threshold_label->setText(QString("texture threshold"));
	uniqueness_ratio_label = new QLabel();
	uniqueness_ratio_label->setText(QString("uniqueness ratio"));
	speckle_window_size_label = new QLabel();
	speckle_window_size_label->setText(QString("speckle window size"));
	speckle_range_label = new QLabel();
	speckle_range_label->setText(QString("speckle range"));
	disp12_maxdiff_label = new QLabel();
	disp12_maxdiff_label->setText(QString("disp12 maxdiff"));
// 	
	sad_window_size = new QSlider();
	sad_window_size->setValue(2);
	sad_window_size->setMinimum(2);
	sad_window_size->setMaximum(32);
	sad_window_size->setOrientation(Qt::Horizontal);
	
	number_of_disparities = new QSlider();
	number_of_disparities->setValue(1);
	number_of_disparities->setMinimum(1);
	number_of_disparities->setMaximum(16);
	number_of_disparities->setOrientation(Qt::Horizontal);
	
	prefilter_size = new QSlider(); 
	prefilter_size->setValue(2);
	prefilter_size->setMinimum(2);
	prefilter_size->setMaximum(127);
	prefilter_size->setOrientation(Qt::Horizontal);
	
	prefilter_cap = new QSlider();
	prefilter_cap->setValue(1);
	prefilter_cap->setMinimum(1);
	prefilter_cap->setMaximum(63);
	prefilter_cap->setOrientation(Qt::Horizontal);
	
	min_disparity = new QSlider();
	min_disparity->setValue(-128);
	min_disparity->setMinimum(-128);
	min_disparity->setMaximum(128);
	min_disparity->setOrientation(Qt::Horizontal);
	
	texture_Threshold = new QSlider(); //?????
	texture_Threshold->setValue(1);
	texture_Threshold->setMinimum(1);
	texture_Threshold->setMaximum(128);
	texture_Threshold->setOrientation(Qt::Horizontal);
	
	uniqueness_ratio = new QSlider();
	uniqueness_ratio->setValue(5);
	uniqueness_ratio->setMinimum(5);
	uniqueness_ratio->setMaximum(64);
	uniqueness_ratio->setOrientation(Qt::Horizontal);
	
	speckle_window_size = new QSlider();
	speckle_window_size->setValue(0);
	speckle_window_size->setMinimum(0);
	speckle_window_size->setMaximum(255);
	speckle_window_size->setOrientation(Qt::Horizontal);
	
	speckle_range = new QSlider();
	speckle_range->setValue(-128);
	speckle_range->setMinimum(-128);
	speckle_range->setMaximum(128);
	speckle_range->setOrientation(Qt::Horizontal);
	
	disp12_maxdiff = new QSlider();
	disp12_maxdiff->setValue(0);
	disp12_maxdiff->setMinimum(0);
	disp12_maxdiff->setMaximum(1);
	disp12_maxdiff->setOrientation(Qt::Horizontal);

	sad_window_size_spinbox = new QSpinBox();
	sad_window_size_spinbox->setValue(2);
	sad_window_size_spinbox->setMinimum(2);
	sad_window_size_spinbox->setMaximum(32);
	
	number_of_disparities_spinbox = new QSpinBox();
	number_of_disparities_spinbox->setValue(1);
	number_of_disparities_spinbox->setMinimum(1);
	number_of_disparities_spinbox->setMaximum(16);
	
	prefilter_size_spinbox = new QSpinBox();
	prefilter_size_spinbox->setValue(2);
	prefilter_size_spinbox->setMinimum(2);
	prefilter_size_spinbox->setMaximum(127);
	
	prefilter_cap_spinbox = new QSpinBox();
	prefilter_cap_spinbox->setValue(1);
	prefilter_cap_spinbox->setMinimum(1);
	prefilter_cap_spinbox->setMaximum(63);
	
	min_disparity_spinbox = new QSpinBox();
	min_disparity_spinbox->setValue(-128);
	min_disparity_spinbox->setMinimum(-128);
	min_disparity_spinbox->setMaximum(128);
	
	texture_Threshold_spinbox = new QSpinBox();
	texture_Threshold->setValue(1);
	texture_Threshold->setMinimum(1);
	texture_Threshold->setMaximum(128);
	
	uniqueness_ratio_spinbox = new QSpinBox();
	uniqueness_ratio_spinbox->setValue(5);
	uniqueness_ratio_spinbox->setMinimum(5);
	uniqueness_ratio_spinbox->setMaximum(64);
	
	speckle_window_size_spinbox = new QSpinBox();
	speckle_window_size_spinbox->setValue(0);
	speckle_window_size_spinbox->setMinimum(0);
	speckle_window_size_spinbox->setMaximum(255);
	
	speckle_range_spinbox = new QSpinBox();
	speckle_range_spinbox->setValue(-128);
	speckle_range_spinbox->setMinimum(-128);
	speckle_range_spinbox->setMaximum(128);
	
	disp12_maxdiff_spinbox = new QSpinBox();
	disp12_maxdiff_spinbox->setValue(0);
	disp12_maxdiff_spinbox->setMinimum(0);
	disp12_maxdiff_spinbox->setMaximum(1);
	
	save_calibration_data_depth = new QPushButton();
	save_calibration_data_depth->setText(QString("Save settings to file"));
	
	load_calibration_data_depth = new QPushButton();
	load_calibration_data_depth->setText(QString("Load settings from file"));
// 	
// 	
	gridLayout_depth->addWidget(video_frame_depth, 0, 0, 10, 2);
	gridLayout_depth->addWidget(sad_window_size_label, 0,2,1,1);
	gridLayout_depth->addWidget(number_of_disparities_label, 1,2,1,1);
	gridLayout_depth->addWidget(prefilter_size_label, 2,2,1,1);
	gridLayout_depth->addWidget(prefilter_cap_label, 3,2,1,1);
	gridLayout_depth->addWidget(min_disparity_label, 4,2,1,1);
	gridLayout_depth->addWidget(texture_Threshold_label, 5,2,1,1);
	gridLayout_depth->addWidget(uniqueness_ratio_label, 6,2,1,1);
	gridLayout_depth->addWidget(speckle_window_size_label, 7,2,1,1);
	gridLayout_depth->addWidget(speckle_range_label, 8,2,1,1);
	gridLayout_depth->addWidget(disp12_maxdiff_label, 9,2,1,1);
// 	
	gridLayout_depth->addWidget(sad_window_size, 0,3,1,2);
	gridLayout_depth->addWidget(number_of_disparities, 1,3,1,2);
	gridLayout_depth->addWidget(prefilter_size, 2,3,1,2);
	gridLayout_depth->addWidget(prefilter_cap, 3,3,1,2);
	gridLayout_depth->addWidget(min_disparity, 4,3,1,2);
	gridLayout_depth->addWidget(texture_Threshold, 5,3,1,2);
	gridLayout_depth->addWidget(uniqueness_ratio, 6,3,1,2);
	gridLayout_depth->addWidget(speckle_window_size, 7,3,1,2);
	gridLayout_depth->addWidget(speckle_range, 8,3,1,2);
	gridLayout_depth->addWidget(disp12_maxdiff, 9,3,1,2);
	
	gridLayout_depth->addWidget(sad_window_size_spinbox, 0,5,1,1);
	gridLayout_depth->addWidget(number_of_disparities_spinbox, 1,5,1,1);
	gridLayout_depth->addWidget(prefilter_size_spinbox, 2,5,1,1);
	gridLayout_depth->addWidget(prefilter_cap_spinbox, 3,5,1,1);
	gridLayout_depth->addWidget(min_disparity_spinbox, 4,5,1,1);
	gridLayout_depth->addWidget(texture_Threshold_spinbox, 5,5,1,1);
	gridLayout_depth->addWidget(uniqueness_ratio_spinbox, 6,5,1,1);
	gridLayout_depth->addWidget(speckle_window_size_spinbox, 7,5,1,1);
	gridLayout_depth->addWidget(speckle_range_spinbox, 8,5,1,1);
	gridLayout_depth->addWidget(disp12_maxdiff_spinbox, 9,5,1,1);
	
	gridLayout_depth->addWidget(save_calibration_data_depth, 10,5,1,1);
	gridLayout_depth->addWidget(load_calibration_data_depth, 10,4,1,1);

	QObject::connect(sad_window_size, SIGNAL(valueChanged(int)), sad_window_size_spinbox, SLOT(setValue(int)));
	QObject::connect(number_of_disparities, SIGNAL(valueChanged(int)), number_of_disparities_spinbox, SLOT(setValue(int)));
	QObject::connect(prefilter_size, SIGNAL(valueChanged(int)), prefilter_size_spinbox, SLOT(setValue(int)));
	QObject::connect(prefilter_cap, SIGNAL(valueChanged(int)), prefilter_cap_spinbox, SLOT(setValue(int)));
	QObject::connect(min_disparity, SIGNAL(valueChanged(int)), min_disparity_spinbox, SLOT(setValue(int)));
	QObject::connect(texture_Threshold, SIGNAL(valueChanged(int)), texture_Threshold_spinbox, SLOT(setValue(int)));
	QObject::connect(uniqueness_ratio, SIGNAL(valueChanged(int)), uniqueness_ratio_spinbox, SLOT(setValue(int)));
	QObject::connect(speckle_window_size, SIGNAL(valueChanged(int)), speckle_window_size_spinbox, SLOT(setValue(int)));
	QObject::connect(speckle_range, SIGNAL(valueChanged(int)), speckle_range_spinbox, SLOT(setValue(int)));
	QObject::connect(disp12_maxdiff, SIGNAL(valueChanged(int)), disp12_maxdiff_spinbox, SLOT(setValue(int)));
	
	QObject::connect(sad_window_size_spinbox, SIGNAL(valueChanged(int)), sad_window_size, SLOT(setValue(int)));
	QObject::connect(number_of_disparities_spinbox, SIGNAL(valueChanged(int)), number_of_disparities, SLOT(setValue(int)));
	QObject::connect(prefilter_size_spinbox, SIGNAL(valueChanged(int)), prefilter_size, SLOT(setValue(int)));
	QObject::connect(prefilter_cap_spinbox, SIGNAL(valueChanged(int)), prefilter_cap, SLOT(setValue(int)));
	QObject::connect(min_disparity_spinbox, SIGNAL(valueChanged(int)), min_disparity, SLOT(setValue(int)));
	QObject::connect(texture_Threshold_spinbox, SIGNAL(valueChanged(int)), texture_Threshold, SLOT(setValue(int)));
	QObject::connect(uniqueness_ratio_spinbox, SIGNAL(valueChanged(int)), uniqueness_ratio, SLOT(setValue(int)));
	QObject::connect(speckle_window_size_spinbox, SIGNAL(valueChanged(int)), speckle_window_size, SLOT(setValue(int)));
	QObject::connect(speckle_range_spinbox, SIGNAL(valueChanged(int)), speckle_range, SLOT(setValue(int)));
	QObject::connect(disp12_maxdiff_spinbox, SIGNAL(valueChanged(int)), disp12_maxdiff, SLOT(setValue(int))); 	
	
	gridLayout_movement_map = new QGridLayout();
	horizontalLayout_movement_tab->addLayout(gridLayout_movement_map);
	
	video_frame_movement_map = new video_widget();
	video_frame_movement_map->setObjectName("video_frame_movement_map");
	video_frame_movement_map->setEnabled(true);
	video_frame_movement_map->setMinimumSize(640,480);
	video_frame_movement_map->setMaximumSize(640,480);
 	
	acumulate_sensitivity = new QSlider();
	acumulate_sensitivity->setOrientation(Qt::Horizontal);
	acumulate_sensitivity->setValue(60);
	acumulate_sensitivity->setMinimum(0);
	acumulate_sensitivity->setMaximum(100);
 	
	threshold_sensitivity = new QSlider();
	threshold_sensitivity->setOrientation(Qt::Horizontal);
	threshold_sensitivity->setValue(10);
	threshold_sensitivity->setMinimum(1);
	threshold_sensitivity->setMaximum(255);
	
	acumulate_sensitivity_spinbox = new QSpinBox();
	acumulate_sensitivity_spinbox->setValue(60);
	acumulate_sensitivity_spinbox->setMinimum(0);
	acumulate_sensitivity_spinbox->setMaximum(100);
	
	threshold_sensitivity_spinbox = new QSpinBox();
	threshold_sensitivity_spinbox->setValue(10);
	threshold_sensitivity_spinbox->setMinimum(1);
	threshold_sensitivity_spinbox->setMaximum(255);
	
	acumulate_sensitivity_label = new QLabel();
	acumulate_sensitivity_label->setText(QString("Acumulate sensitivity"));
	threshold_sensitivity_label = new QLabel();
	threshold_sensitivity_label->setText(QString("Threshold sensitivity"));
	
	num_of_tracked_features_label = new QLabel();
	num_of_tracked_features_label->setText(QString("Number of tracked features:"));
	num_of_tracked_features = new QLCDNumber();

	time_to_calculate_label = new QLabel();
	time_to_calculate_label->setText(QString("Time to calculate"));
	
	time_to_calculate = new QLCDNumber();
	
	start_tracking = new QPushButton();
	start_tracking->setText(QString("Start tracking"));
	
	calibrate_laser = new QPushButton();
	calibrate_laser->setText(QString("Calibrate laser"));
	
	load_laser_data = new QPushButton();
	load_laser_data->setText(QString("Load calibration data"));
	
	save_laser_data = new QPushButton();
	save_laser_data->setText(QString("Save calibration data"));
	
	coordinates_label = new QLabel();
	coordinates_label->setText(QString("Tracked object coordinates"));
	
	horizontal_label = new QLabel();
	horizontal_label->setText(QString("Horizontal"));

	vertical_label = new QLabel();
	vertical_label->setText(QString("Vertical"));
	
	depth_label = new QLabel();
	depth_label->setText(QString("Depth"));
	
	horizontal_data = new QLabel();
	horizontal_data->setText(QString("0"));

	vertical_data = new QLabel();
	vertical_data->setText(QString("0"));
	
	depth_data = new QLabel();
	depth_data->setText(QString("0"));	
	
	

	
	horizontal_slider_label = new QLabel();
	horizontal_slider_label->setText("Horizontal movement");
	
	vertical_slider_label = new QLabel();
	vertical_slider_label->setText("Vertical movement");
	
	x_koordinates = new QSlider();
	x_koordinates->setOrientation(Qt::Horizontal);
	x_koordinates->setMinimum(0);
	x_koordinates->setMaximum(1800);
	
	y_koordinates = new QSlider();
	y_koordinates->setOrientation(Qt::Horizontal);
	y_koordinates->setMinimum(0);
	y_koordinates->setMaximum(1800);
	
	up_left = new QRadioButton();
	up_left->setText("Upper left");
	
	up_right = new QRadioButton();
	up_right->setText("Upper right");
	
	center = new QRadioButton();
	center->setText("Center");
	
	down_left = new QRadioButton();
	down_left->setText("Bottom left");
	
	down_right = new QRadioButton();
	down_right->setText("Bottom right");
	
	fix_laser_position = new QPushButton();
	fix_laser_position->setText("Fix laser position");
	
	laser_calibration = new QGroupBox();
	laser_calibration->setTitle("Laser calibrationca");
	laser_calibration_gridLayout = new QGridLayout(laser_calibration);
	laser_calibration_gridLayout->addWidget(horizontal_slider_label, 0,0,1,1);
	laser_calibration_gridLayout->addWidget(vertical_slider_label, 1,0,1,1);
	laser_calibration_gridLayout->addWidget(x_koordinates,0,1,1,2);
	laser_calibration_gridLayout->addWidget(y_koordinates, 1,1,1,2);
	
	laser_calibration_gridLayout->addWidget(up_left,2,0,1,1);
	laser_calibration_gridLayout->addWidget(up_right,2,2,1,1);
	laser_calibration_gridLayout->addWidget(center,3,1,1,1);
	laser_calibration_gridLayout->addWidget(down_left,4,0,1,1);
	laser_calibration_gridLayout->addWidget(down_right,4,2,1,1);
	laser_calibration_gridLayout->addWidget(fix_laser_position,5,1,1,1);
	
	
// 	laser_calibration->addWidget(laser_calibration_gridLayout);
	vertical_movement_layout = new QHBoxLayout();
	vertical_movement_layout->addWidget(start_tracking, 0);
	vertical_movement_layout->addWidget(calibrate_laser,1);
	vertical_movement_layout->addWidget(load_laser_data,2);
	vertical_movement_layout->addWidget(save_laser_data,3);
	
	coordinates_gridlayout = new QGridLayout();
	coordinates_gridlayout->addWidget(coordinates_label,0,0,1,2);
	coordinates_gridlayout->addWidget(horizontal_label, 1,0,1,1);
	coordinates_gridlayout->addWidget(horizontal_data, 1,1,1,1);
	coordinates_gridlayout->addWidget(vertical_label, 2,0,1,1);
	coordinates_gridlayout->addWidget(vertical_data, 2,1,1,1);
	coordinates_gridlayout->addWidget(depth_label, 3,0,1,1);
	coordinates_gridlayout->addWidget(depth_data, 3,1,1,1);
	
	gridLayout_movement_map->addWidget(video_frame_movement_map, 0, 0, 10, 2);
	gridLayout_movement_map->addWidget(acumulate_sensitivity_label, 0,2,1,1);
	gridLayout_movement_map->addWidget(acumulate_sensitivity, 0,3,1,1);
	gridLayout_movement_map->addWidget(acumulate_sensitivity_spinbox, 0,4,1,1);
	gridLayout_movement_map->addWidget(threshold_sensitivity_label, 1,2,1,1);
	gridLayout_movement_map->addWidget(threshold_sensitivity, 1,3,1,1);
	gridLayout_movement_map->addWidget(threshold_sensitivity_spinbox, 1,4,1,1);	
	gridLayout_movement_map->addWidget(num_of_tracked_features_label, 2,2,1,2);
	gridLayout_movement_map->addWidget(num_of_tracked_features, 2,4,1,1);
	gridLayout_movement_map->addWidget(time_to_calculate_label, 3,2,1,1);
	gridLayout_movement_map->addWidget(time_to_calculate, 3,4,1,1);	
	gridLayout_movement_map->addWidget(laser_calibration, 4,2,6,2);
	gridLayout_movement_map->addLayout(coordinates_gridlayout, 6,4,1,1);
	gridLayout_movement_map->addLayout(vertical_movement_layout, 10,0,1,5);
	
	
	QObject::connect(acumulate_sensitivity, SIGNAL(valueChanged(int)), acumulate_sensitivity_spinbox, SLOT(setValue(int)));
	QObject::connect(threshold_sensitivity, SIGNAL(valueChanged(int)), threshold_sensitivity_spinbox, SLOT(setValue(int)));
	
	QObject::connect(acumulate_sensitivity_spinbox, SIGNAL(valueChanged(int)), acumulate_sensitivity, SLOT(setValue(int)));
	QObject::connect(threshold_sensitivity_spinbox, SIGNAL(valueChanged(int)), threshold_sensitivity, SLOT(setValue(int)));
	
	//settings tabs
	
// 	settings_tab_gridlayout = new QGridLayout();
	
	gridLayout_settings = new QGridLayout();
	horizontalLayout_settings_tab->addLayout(gridLayout_settings);
	
	servo_group = new QGroupBox();
	servo_group->setTitle("Targeting mechanisms:");
	
	servo1_check = new QCheckBox();
	servo1_check->setText("I targeting mechanism");
	servo2_check = new QCheckBox();
	servo2_check->setText("II targeting mechanism");
	addservo_check = new QCheckBox();
	addservo_check->setText("Additional targeting mechanism");

	servo_group_layout = new QVBoxLayout();
	servo_group_layout->addWidget(servo1_check);
	servo_group_layout->addWidget(servo2_check);
	servo_group_layout->addWidget(addservo_check);
	servo_group->setLayout(servo_group_layout);
	
	config_group = new QGroupBox();
	config_group->setTitle("Other settings:");
	supply_check = new QCheckBox();
	supply_check->setText("5V power supply");
	laser3v_check = new QCheckBox();
	laser3v_check->setText("Laser 3V");
	laser5v_check = new QCheckBox();
	laser5v_check->setText("Laser 5V");
	buzzer_check = new QCheckBox();
	buzzer_check->setText("Buzzer");
	
	config_group_layout = new QVBoxLayout();
	config_group_layout->addWidget(supply_check);
	config_group_layout->addWidget(laser3v_check);
	config_group_layout->addWidget(laser5v_check);
	config_group_layout->addWidget(buzzer_check);
	
	config_group->setLayout(config_group_layout);
	
	editor_group = new QGroupBox();
	editor_group->setTitle("Device status:");
	small_editor = new QTextEdit();
	editor_group_layout = new QVBoxLayout();
	editor_group_layout->addWidget(small_editor);
	editor_group->setLayout(editor_group_layout);
	
	manual_control_group = new QGroupBox();
	manual_control_group->setTitle("Manual control");
	manual_control_group_layout = new QGridLayout();
	
	x_label = new QLabel();
	x_label->setText("X coordinate");
	y_label = new QLabel();
	y_label->setText("Y coordinate");
	
	x_coordinate_spin = new QSpinBox();
	x_coordinate_spin->setRange(0,1600);
	x_coordinate_spin->setValue(800);
	
	y_coordinate_spin = new QSpinBox();
	y_coordinate_spin->setRange(0,1600);
	y_coordinate_spin->setValue(800);
	
	laser_en_check = new QCheckBox();
	laser_en_check->setText("Laser");
	
	send_but = new QPushButton();
	send_but->setText("Send command");
	
	circle_but = new QPushButton();
	circle_but->setText("Draw cicle");
	
	random_pos_but = new QPushButton();
	random_pos_but->setText("Random position");
	
	config_but = new QPushButton();
	config_but->setText("Send config");
	
	test_but = new QPushButton();
	test_but->setText("Test");
	
	manual_control_group_layout->addWidget(x_label,0,0);
	manual_control_group_layout->addWidget(x_coordinate_spin,0,1);
	manual_control_group_layout->addWidget(y_label,1,0);
	manual_control_group_layout->addWidget(y_coordinate_spin,1,1);
	manual_control_group_layout->addWidget(laser_en_check,2,0);
	manual_control_group_layout->addWidget(send_but,2,1);
	manual_control_group_layout->addWidget(circle_but,3,1);
	manual_control_group_layout->addWidget(random_pos_but,4,1);
	manual_control_group_layout->addWidget(test_but,3,0);
	manual_control_group_layout->addWidget(config_but,4,0);
	manual_control_group->setLayout(manual_control_group_layout);
	
	device_selector = new QGroupBox();
	device_selector->setTitle("Camera selector");
	
	device_selector_layout = new QGridLayout();
	
	left_cam_label = new QLabel();
	left_cam_label->setText("Left camera");
	
	right_cam_label = new QLabel();
	right_cam_label->setText("Right camera");
	
	left_cam_selector = new QComboBox();
	left_cam_selector->addItem("/dev/video0");
	left_cam_selector->addItem("/dev/video1");
	left_cam_selector->addItem("/dev/video2");
	left_cam_selector->setCurrentIndex(1);
	
	right_cam_selector = new QComboBox();
	right_cam_selector->addItem("/dev/video0");
	right_cam_selector->addItem("/dev/video1");
	right_cam_selector->addItem("/dev/video2");
	right_cam_selector->setCurrentIndex(2);
	
	resolution_label = new QLabel();
	resolution_label->setText("Resolution");
	
	resolution_selector = new QComboBox();
	resolution_selector->addItem("320x240");
	resolution_selector->addItem("640x480");
	resolution_selector->addItem("1280x800");
	resolution_selector->setCurrentIndex(1);
	resolution_selector->setDisabled(true);
	fps_label = new QLabel();
	fps_label->setText("Fps");
	
	fps_spin = new QSpinBox();
	fps_spin->setMinimum(0);
	fps_spin->setMaximum(30);
	fps_spin->setValue(30);
	fps_spin->setDisabled(true);
	
	left_cam_flip = new QCheckBox();
	left_cam_flip->setText("Flip cam");
	
	right_cam_flip = new QCheckBox();
	right_cam_flip->setText("Flip cam");
	
	device_selector_layout->addWidget(left_cam_label,0,0,1,1);
	device_selector_layout->addWidget(left_cam_selector,0,1,1,1);
	device_selector_layout->addWidget(left_cam_flip,0,2,1,1);
	device_selector_layout->addWidget(right_cam_label,1,0,1,1);
	device_selector_layout->addWidget(right_cam_selector,1,1,1,1);
	device_selector_layout->addWidget(right_cam_flip,1,2,1,1);
	device_selector_layout->addWidget(resolution_label,2,0,1,1);
	device_selector_layout->addWidget(resolution_selector,2,1,1,2);
	device_selector_layout->addWidget(fps_label,3,0,1,1);
	device_selector_layout->addWidget(fps_spin,3,1,1,2);
	
	device_selector->setLayout(device_selector_layout);
	
	gridLayout_settings->addWidget(servo_group,0,2,1,1);
	gridLayout_settings->addWidget(config_group,1,2,1,1);
	gridLayout_settings->addWidget(editor_group,0,3,1,1);
	gridLayout_settings->addWidget(manual_control_group,1,3,1,1);
	gridLayout_settings->addWidget(device_selector,0,0,1,2);
	
	
// 	horizontalLayout_settings_tab>addLayout(settings_tab_gridlayout);
// 	settings_tab->setLayout(settings_tab_gridlayout);
	
	
	
        MainWindow->setCentralWidget(centralwidget);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("Moving object targeting system", "Moving object targeting system", 0));
//         calibrate_button->setText(QApplication::translate("MainWindow", "Calibrate", 0));
    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERN14265_H
