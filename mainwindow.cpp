#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
using std::vector;

MainWindow::MainWindow(QWidget *parent) //생성자에서 초기화를 진행
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//,cap(1)//생성자에서 이니셜라이징 오픈씨브이랑 싸우니까 둘 중에 하나만 쓰렴.
{
    ui->setupUi(this);
    connect(this,SIGNAL(timeout()),this,SLOT(msg()));
//    connect(&timer,SIGNAL(timeout()),this,SLOT(timeloop()));

    connect (this, SIGNAL(stringChanged(QString)), this, SLOT( setString(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_GeneralCam_clicked()
{
    cap.open(1);//생성자에서 이니셜라이징을 못했을 때 버튼을 눌렀을 때 카메라 오픈.
    cout<<"hi"<<endl;
    bool CamStart = true;// 카메라를 켜기 위해 버튼이 눌리면 초기에 한 번 플래그를 1로 변경

    if (CamStart == true)// 초기화를 위한 로컬 변수 한 개를 플래그로 설정
    {
        cout<<CamStart<<endl;
        connect(&timer,SIGNAL(timeout()),this,SLOT(timeloop()));
        CamStart = false;
//        cout<<CamStart<<endl;
    }
    timer.setInterval(33);//몇 미리세컨드마다 쓸 것인가???, 타이머의 멤버 함수
    timer.start();// 타이머 켜는 함수, 타이머의 멤버 함수
}

void MainWindow::timeloop()
{
//    cout<<"camera is opend"<<endl;
    if (cap.isOpened())// 카메라가 열렸을 때
    {
        Mat img;
//        cv 클래스의 Mat함수를 리턴받을 이미지를 저장할 인자의 이름을 img라 선언.
//        OpenCV 에서 기본적으로 이미지를 로딩하면 cv::Mat 을 리턴하게 된다. cv::Mat 에 이미지의 각 픽셀에 대한 정보가 기록되어 있으며,
//        프로그래머는 값을 읽고 수정할 수 있다. 이미지는 어떤 형태로 로딩을 하느냐에 따라 cv::Mat 의 데이터 구조가 다르며,
//        값을 읽고 수정하는 방법도 여러 가지 방법이 있다.

        cap >> img; // 카메라로 부터 받은 이미지를 img 에 저장

        QImage qimg(img.data, img.cols, img.rows,QImage::Format_BGR888);
        ui->image->setPixmap(QPixmap::fromImage(qimg));}
//        QImage로 이미지를 불러온다. -> QPixmap에 옮긴다. -> QLabel에서 QPixmap를 불러와서 화면에 출력한다.
}

void MainWindow::on_feature_clicked()
{
    //rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);

//    map<int, int> counters;
//    map<int, string> stream_names;
//    mutex mutex;

    // Define frame callback // 프레임을 받아서 카운터를 증가.
    // The callback is executed on a sensor thread and can be called simultaneously from multiple sensors
    // Therefore any modification to common memory should be done under lock
    auto callback = [&](const rs2::frame& frame)
    {
//        cout<<frame.get_profile().unique_id()<<endl;
//        cout<<"hi"<<endl;
//        std::lock_guard<std::mutex> lock(mutex);
        if (rs2::frameset fs = frame.as<rs2::frameset>())
        {
            // With callbacks, all synchronized stream will arrive in a single frameset
//            cout<<"im in"<<endl;
            for (const rs2::frame& f : fs)
            {
                counters[f.get_profile().unique_id()]++;
//                cout<<"ok1"<<endl;
            }

        }
        else
        {
            // Stream that bypass synchronization (such as IMU) will produce single frames
            counters[frame.get_profile().unique_id()]++; //해당하는 값이 들어오면 카운터 증가
//            cout<<"ok2"<<endl;

        }

//        vector<string> str_arr1;
        string msg_name="";
        for (auto p : counters)
        {

//            std::cout << stream_names[p.first] << "[" << p.first << "]: " << p.second << " [frames] || ";
            msg_name += stream_names[p.first] + "[" + to_string(p.first) + "]: " + to_string(p.second) + " [frames] || ";


//            ui->image->setText(QString::fromStdString(msg_name));

        }
        emit stringChanged(QString::fromStdString(msg_name));//시그널 함수 생성.

//        for(auto s : str_arr1){
//            std::cout<<s;
//        }
//        std::cout<<msg_name<<std::endl;


    };

    // Declare RealSense pipeline, encapsulating the actual device and sensors.
    /*rs2::pipeline pipe;*/ //rs2의 파이프라인 생성
//    cout<<"run now"<<endl;

    // Start streaming through the callback with default recommended configuration
    // The default video configuration contains Depth and Color streams
    // If a device is capable to stream IMU data, both Gyro and Accelerometer are enabled by default
    //

    rs2::config cfg;
    cfg.enable_all_streams();

    rs2::pipeline_profile profiles = pipe.start(cfg, callback); //파이프 라인 있는 스타트라는 맴버 펑션을 실행.(콜백을 매개변수로 받음.)
    cout<<"run now"<<endl;

    /*
    // Collect the enabled streams names
    for (auto element : profiles.get_streams()) //자신이 가지고 있는 get_streams 에서 센서 스트림을 받아옴
    {
        cout<<"run"<<endl;
        stream_names[element.unique_id()] = element.stream_name(); //받아온 스트림의 이름을 배열로 저장
    }
    */

    //rs2::stream_profile list[7];
    std::vector<rs2::stream_profile> list;//std::vector를 선언하면 빈 리스트가 생성됨.(아파트 방 부지)
    list = profiles.get_streams();//리스트를 선언하고 get_streams()를 통해 프로파일의 정보가 리스트에 입력되어 정의됨.
    for(int p = 0; p < list.size(); p++)
    {
        rs2::stream_profile element = list[p];
        stream_names[element.unique_id()] = element.stream_name();

    }

//    for(int p = 0; p < stream_names.size(); p++)
//    {
////        cout << stream_names[p] << endl;
////        string msg_name = stream_names[p];
////        ui->image->setText(QString::fromStdString(msg_name));
//    }

    cout << "RealSense callback sample" << endl ;

        //스트림 이름과 카운터 값을 출력

    cout << "\r";


//    for (auto p : counters)
//    {
//        cout<<"im in"<<endl;
//        cout << stream_names[p.first] << "[" << p.first << "]: " << p.second << " [frames] || ";

//        string msg_name = stream_names[p.first] + "[" + to_string(p.first) + "]: " + to_string(p.second) + " [frames] || ";
//        ui->image->setText(QString::fromStdString(msg_name));
//    }

}


void MainWindow::on_stop_clicked() // 영상 송출을 잠시 멈추고 싶을 때 사용.
{
//    cap.(1);
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(timeloop()));
    cout<<"bye"<<endl;
}


void MainWindow::setString(QString msg){
    ui->image->setText(msg);
}
