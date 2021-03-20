#include <iostream>

#include "backend_thread.h"
#include "opencv_thread.h"

BackendThread::BackendThread(QObject *parent) : QObject(parent)
{
}

void BackendThread::opencvStart()
{
    qDebug() << ">>> [Backend] OpenCV Thread Start <<<";
    QThread *thread = new QThread(0);
    OpenCVThread *worker = new OpenCVThread();
    threads["OpenCV"] = thread;
    workers["OpenCV"] = QVariant::fromValue(worker);
    worker->moveToThread(thread);

    connect(worker, &OpenCVThread::frameReady, this, &BackendThread::frameReady);
    connect(worker, &OpenCVThread::finished, this, &BackendThread::finished);

    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::started, worker, &OpenCVThread::start);

    thread->start();
}

void BackendThread::opencvStop()
{
    OpenCVThread *worker;
    if (workers.contains("OpenCV")) {
        worker = qvariant_cast<OpenCVThread*>(workers.value("OpenCV"));
        worker->stop();
    }
}

void BackendThread::finished(QString thread_name)
{
    QThread *thread;
    if (threads.contains(thread_name)) {
        thread = threads.value(thread_name);
        thread->quit();
        thread->wait();
        qDebug() << qPrintable(QString(">>> [Backend] %1 Thread Finish <<<").arg(thread_name));
    }
}
