#ifndef MY_MEDIA_PLAYER_H
#define MY_MEDIA_PLAYER_H

#include <QObject>
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>

#include "src/threads/backend_thread.h"

class QAbstractVideoSurface;

class MyMediaPlayer : public QObject
{
    private:
        Q_OBJECT
        Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface NOTIFY surfaceChanged)

    public:
        Q_INVOKABLE void play();
        Q_INVOKABLE void pause();
        Q_INVOKABLE void stop();

    public:
        explicit MyMediaPlayer(QObject *parent = nullptr);
        ~MyMediaPlayer() {};

        QAbstractVideoSurface *videoSurface() const;

    public slots:
        void setVideoSurface(QAbstractVideoSurface *surface);
        void onVideoFrameReady(cv::Mat curr_frame);

    signals:
        void surfaceChanged(QAbstractVideoSurface* surface);

    private:
        void setFormat(int width, int height, QVideoFrame::PixelFormat frame_format);

        QAbstractVideoSurface *m_surface = NULL;
        QVideoSurfaceFormat m_format;
        BackendThread *m_backend;

        bool m_isFormatSet;
        QImage m_image;
        int count = 0;
};

#endif // MY_MEDIA_PLAYER_H

