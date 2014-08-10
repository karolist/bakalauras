/*
    Qt widget for video output
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


#include "video_widget.h"

video_widget::video_widget() : QGLWidget(QGLFormat(QGL::SampleBuffers))
{
  setMinimumSize(640,480);
  
  initializeGL();
  paintGL();
  resizeGL(640,480);
}

void video_widget::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void video_widget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0,0.0,0.0,1.0);
  if(!qframe.isNull())
  {
    qframe = qframe.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    glDrawPixels(qframe.width(),qframe.height(), GL_RGBA, GL_UNSIGNED_BYTE, qframe.bits());
    glFlush();
  }
}

void video_widget::resizeGL(int w, int h)
{
  glViewport(0,0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode (GL_MODELVIEW);
  
}

void video_widget::send_image(cv::Mat img)
{
  qframe = QImage((const unsigned char*)(img.data), img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped();
  qframe = QGLWidget::convertToGLFormat(qframe);
  this->updateGL();
}
