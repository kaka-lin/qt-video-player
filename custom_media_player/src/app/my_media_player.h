#ifndef MY_MEDIA_PLAYER_H
#define MY_MEDIA_PLAYER_H

#include <QObject>
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QMediaPlayer>

class MyMediaPlayer : public QObject
{
    private:
        Q_OBJECT
        Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
        Q_PROPERTY(QString videoPath READ videoPath WRITE setVideoPath)

    public:
        Q_INVOKABLE void play();
        Q_INVOKABLE void pause();
        Q_INVOKABLE void stop();

    public:
        explicit MyMediaPlayer(QObject *parent = nullptr);
        ~MyMediaPlayer() {};

        void setFormat(int width, int height, int format);
        void getMetaData();

    public slots:
        QAbstractVideoSurface *videoSurface() const;
        void setVideoSurface(QAbstractVideoSurface *surface);

        QString videoPath() const;
        void setVideoPath(QString path);

        void onNewVideoContentReceived(const QVideoFrame &frame);
        void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    signals:
        void frameFinished();

    private:
        QAbstractVideoSurface *m_surface = NULL;
        QVideoSurfaceFormat m_format;
        QMediaPlayer *m_player;
        QString video_path = "";
};


#endif // MY_MEDIA_PLAYER_H
