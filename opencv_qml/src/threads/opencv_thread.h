#ifndef OPENCV_THREAD_H
#define OPENCV_THREAD_H

#include <iostream>
#include <unistd.h>

#include <QObject>
#include <QDebug>
#include <opencv2/opencv.hpp>

class OpenCVThread : public QObject
{
    private:
        Q_OBJECT

    public:
        explicit OpenCVThread(QObject *parent = nullptr);
        ~OpenCVThread() {};

    public slots:
        void start();
        void stop();

    signals:
        void frameReady(cv::Mat frame);
        void finished(QString thread_name);

    private:
        cv::VideoCapture cap;
        cv::Mat frame;

        bool isRunning;
        bool isPausing;
};
Q_DECLARE_METATYPE(OpenCVThread*)

#endif // OPENCV_THREAD_H

