cmake_minimum_required(VERSION 2.8)
    
project(bakalauras)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
find_package(Qt4 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtTest REQUIRED)

find_package(QtGStreamer REQUIRED)
find_package(OpenGL REQUIRED)
# find_package(libusb-1.0 REQUIRED)

set(QT_USE_OPENGL TRUE)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES} ${QTGSTREAMER_INCLUDES})
include(${QT_USE_FILE})

set(CMAKE_CXX_FLAGS "-fexceptions")

if (${CMAKE_VERSION} VERSION_LESS "2.8.6")
  find_package(Automoc4 REQUIRED)
else()
  set(CMAKE_AUTOMOC TRUE)

  macro(automoc4_add_executable)
    add_executable(${ARGV} gui.cpp )
  endmacro()
endif()


add_executable(bakalauras settings.cpp stereo_vision.cpp video_widget.cpp depth.cpp analyzer.cpp videoin.cpp gui.cpp BDTargeting.cpp main.cpp)


install(TARGETS bakalauras RUNTIME DESTINATION bin)

qt4_wrap_ui(mainwindow_UI_SRCS mainwindow.ui)

target_link_libraries(bakalauras ${LIBUSB_1_LIBRARY}  ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${QT_LIBRARIES} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_GLIB_LIBRARY} ${QTGSTREAMER_LIBRARIES} ${QTGSTREAMER_UTILS_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})