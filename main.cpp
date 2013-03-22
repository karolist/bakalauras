
#include <iostream>
#include <QApplication>
#include <QtGStreamer/QGst/Init>
#include <opencv2/opencv.hpp>

// #include "videoin.h"
#include "analyzer.h"

int main(int argc, char **argv)
{
//     std::cout << "Hello, world!" << std::endl;
//     QGst::init(&argc, &argv);
    
//     VideoIN left_cam;
    Analyzer left_cam_movement_map;
    
//     left_cam.create_pipeline();
    cv::namedWindow("input",1);
    cv::namedWindow("output",1);
//     IplImage *testas;
//     testas=cvLoadImage("/home/karolis/testas.png");
//     cv::imshow("hello", testas2);
    cv::VideoCapture cap(1);
    while(1)
    {
        cap >> left_cam_movement_map.input;
        left_cam_movement_map.canny();
        cv::imshow("input",left_cam_movement_map.input);
        cv::imshow("output",left_cam_movement_map.output);
                if(cv::waitKey(30) >= 0) break;
    };
    return 0;
}
