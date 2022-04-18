#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <map>
#include <chrono>
#include <mutex>
#include <thread>
#include <string>

using namespace cv;
using namespace std;
//string msg_name="";// 메시지로 보내기 위해 전역변수로 설정.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer timer; //타이머 클래스의 객체 생성
    VideoCapture cap;// cv클래스의 videocapture 함수를 사용하기 위해 cap이라는 객체를 생성.


private slots:
    void on_GeneralCam_clicked();

    void timeloop();

    void on_feature_clicked();

    void on_stop_clicked();



    void setString(QString msg);

signals:
    void stringChanged(QString msg);

private:
    Ui::MainWindow *ui;
    rs2::pipeline pipe;
    map<int, int> counters;
    map<int, string> stream_names;
//    mutex mutex;
};
#endif // MAINWINDOW_H
