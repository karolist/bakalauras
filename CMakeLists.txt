cmake_minimum_required(VERSION 2.8)
    
project(bakalauras)

find_package(OpenCV REQUIRED)
find_package(Qt4 REQUIRED)
find_package(QtGStreamer REQUIRED)


include_directories(${QT_INCLUDES} ${QTGSTREAMER_INCLUDES} {$GSTREAMER_INCLUDE_DIR})

add_executable(bakalauras analyzer.cpp videoin.cpp main.cpp)

install(TARGETS bakalauras RUNTIME DESTINATION bin)

target_link_libraries(bakalauras ${OpenCV_LIBS} ${QT_LIBRARIES} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QTGSTREAMER_LIBRARIES} ${QT_GLIB_LIBRARY} ${QTGSTREAMER_UTILS_LIBRARY} ${GSTREAMER_LIBRARIES})