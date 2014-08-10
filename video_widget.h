/*
    Qt widget for video output
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


#ifndef VIDEO_WIDGET_H
#define VIDEO_WIDGET_H
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <QGLWidget>
#include <QtOpenGL>

class video_widget : public QGLWidget
{
  Q_OBJECT
public:
  video_widget();
  void send_image(cv::Mat img);
  virtual int heightForWidth ( int w ) const { return w*3/4;};
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
private:
  QImage qframe;
};

#endif // VIDEO_WIDGET_H
