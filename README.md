# realsense-sensor-get-info

# realsense의 센서 데이터를 받기 위한 라이브러리 추가.
=> pro 파일

CONFIG(debug, debug|release):LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"

CONFIG(release, debug|release):LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"
명령어를 추가해준다.

# realsense의 센서 데이터를 받기 위한 헤더 추가.

#include <librealsense2/rs.hpp>

#include <opencv2/opencv.hpp>

#include <QTimer>
  
#include <map>
  
#include <chrono>
  
#include <mutex>
  
#include <thread>
  
#include <string>
  
  
