/*
    MJPEG Video decoder using Gstreamer
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


#ifndef VIDEOIN_H
#define VIDEOIN_H
#include <QDebug>

#include <qt4/QtCore/QtGlobal>
#include <opencv2/opencv.hpp>
#include <QtGStreamer/QGst/Element>
#include <QGst/Pipeline>
#include <QtGStreamer/QGst/Utils/ApplicationSink>

class VideoIN : public QObject
{
  Q_OBJECT
public:
    VideoIN();
    void create_pipeline();
    void get_frame(cv::Mat destination);
    void start_stream();
    QString irenginys;
    cv::Mat bandinys;
    bool flip;
public slots:
  void flip_image();

private:
    QGst::ElementPtr source;
    QGst::ElementPtr sink;
    QGst::ElementPtr filtr;
    QGst::ElementPtr filtr2;
    QGst::ElementPtr filtr3;
    QGst::ElementPtr jpegdec;
    QGst::PipelinePtr pipeline;
    QGst::Utils::ApplicationSink app_sink;
    QGst::BufferPtr buferis;
    QGst::ElementPtr ffmpeg;
    QGst::ElementPtr ffmpeg2;
    
};
#endif // VIDEOIN_H
