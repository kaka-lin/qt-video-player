#include <string>

#include <QVideoFrame>

#include "opencv_thread.h"

#define MAXPATHLEN 256

using namespace std;

OpenCVThread::OpenCVThread(QObject *parent)
    : QObject(parent), isRunning(false), isPausing(false)
{
    cv::VideoCapture cap;
}

void OpenCVThread::start()
{
    char cwd[MAXPATHLEN];
    string path;
    size_t pos;
    string data_path;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
        path = string(cwd);
        pos = path.find("opencv_qml");
        data_path = path.substr(0, pos) + "videos/wids-workshop-2020.mp4";
    } else {
        qDebug() << "Please replace the path with your video path";
    }

    cap.open(data_path);
    if (!cap.isOpened()) {
        cout << ">>>> ERROR: Unable to open camera" << endl;
        emit finished("OpenCV");
        return;
    }

    this->isRunning = true;
    while (this->isRunning) {
        cap.read(this->frame);
        if (this->frame.empty()) {
            qDebug() << "ERROR! blank frame grabbed\n";
            break;
        } else {
            emit frameReady(this->frame);
            usleep(30000); // 30ms (30fps, 0.03s)
        }
    }

    this->cap.release();
    emit finished("OpenCV");
}

void OpenCVThread::stop()
{
    this->isRunning = false;
}
