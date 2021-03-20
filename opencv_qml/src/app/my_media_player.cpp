#include <iostream>
#include <unistd.h>

#include "my_media_player.h"

#define MAXPATHLEN 256

using namespace std;

MyMediaPlayer::MyMediaPlayer(QObject *parent)
    : QObject(parent), m_isFormatSet(false)
{
    m_backend = new BackendThread(this);
    connect(m_backend, &BackendThread::frameReady, this, &MyMediaPlayer::onVideoFrameReady);
}

QAbstractVideoSurface *MyMediaPlayer::videoSurface() const
{
    return m_surface;
}

void MyMediaPlayer::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface == surface)
        return;

    if (m_surface && m_surface != surface  && m_surface->isActive()) {
        m_surface->stop();
    }

    m_surface = surface;
    emit surfaceChanged(m_surface);

    //m_backend->start();
    if (m_surface && m_format.isValid()) {
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void MyMediaPlayer::setFormat(int width, int heigth, QVideoFrame::PixelFormat frame_format)
{
    QSize size(width, heigth);
    QVideoSurfaceFormat format(size, frame_format);
    m_format = format;

    if (m_surface) {
        if (m_surface->isActive()) {
            m_surface->stop();
        }
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void MyMediaPlayer::onVideoFrameReady(cv::Mat curr_frame)
{
    if (!m_surface || curr_frame.empty())
        return;

    cv::Mat continuousFrame;
    if (!curr_frame.isContinuous())
        continuousFrame = curr_frame.clone();
    else
        continuousFrame = curr_frame;

    if (!m_isFormatSet) {
        setFormat(continuousFrame.cols,
                  continuousFrame.rows,
                  QVideoFrame::Format_RGB32);
        m_isFormatSet = true;
    }

    m_image = QImage(continuousFrame.data,
                     continuousFrame.cols,
                     continuousFrame.rows,
                     continuousFrame.step,
                     QImage::Format_RGB888);

    m_image = m_image.rgbSwapped();
    m_image = m_image.convertToFormat(QVideoFrame::imageFormatFromPixelFormat(QVideoFrame::Format_RGB32));

    m_surface->present(m_image);
}

void MyMediaPlayer::play()
{
    m_backend->opencvStart();
}

void MyMediaPlayer::pause()
{
}

void MyMediaPlayer::stop()
{
    m_backend->opencvStop();
}
