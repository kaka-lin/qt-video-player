#include <iostream>
#include <unistd.h>

#include "my_media_player.h"

#define MAXPATHLEN 256

using namespace std;

MyMediaPlayer::MyMediaPlayer(QObject *parent): QObject(parent)
{
    m_player = new QMediaPlayer(this);

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MyMediaPlayer::onMediaStatusChanged);
    qDebug() << "My Media Player Initialized!";
    qDebug() << "Status: " << m_player->mediaStatus();

    char cwd[MAXPATHLEN];
    string path;
    size_t pos;


    if (getcwd(cwd, sizeof(cwd)) != NULL && video_path.isEmpty()) {
        printf("Current working dir: %s\n", cwd);
        path = string(cwd);
        pos = path.find("custom_media_player");
        video_path = QString::fromStdString(path.substr(0, pos) + "videos/wids-workshop-2020.mp4");
        qDebug() << video_path;
    } else {
        qDebug() << "Please replace the path with your video path";
    }

    m_player->setMedia(QMediaContent(QUrl::fromLocalFile(video_path)));
}

QAbstractVideoSurface *MyMediaPlayer::videoSurface() const
{
    return m_surface;
}

void MyMediaPlayer::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface == surface)
        return;

    if (m_surface && m_surface != surface && m_surface->isActive()) {
        m_surface->stop();
    }

    m_surface = surface;
    m_player->setVideoOutput(m_surface);
}

QString MyMediaPlayer::videoPath() const
{
    return video_path;
}

void MyMediaPlayer::setVideoPath(QString path)
{
    if (video_path == path)
        return;

    video_path = path;
    m_player->setMedia(QMediaContent(QUrl::fromLocalFile(video_path)));
}

void MyMediaPlayer::getMetaData()
{
    // Get the list of keys there is metadata available for
    QStringList metadatalist = m_player->availableMetaData();
    QString metadata_key;
    QVariant var_data;

    // Get the size of the list
    int list_size = metadatalist.size();

    qDebug() << "==================================================";
    for (int index = 0; index < list_size; index++) {
        // Get the key from the list
        metadata_key = metadatalist.at(index);

        // Get the value for the key
        var_data = m_player->metaData(metadata_key);

        qDebug() << metadata_key << var_data.toString();
    }
    qDebug() << "==================================================";
}

void MyMediaPlayer::onNewVideoContentReceived(const QVideoFrame &frame)
{
    if (m_surface) {
        qDebug() << "receive: "<< frame.pixelFormat() << frame.handleType();
        m_surface->present(frame);
    }
}

void MyMediaPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "Status: " << status;
    if (status == QMediaPlayer::BufferedMedia)
        getMetaData();
}

void MyMediaPlayer::play()
{
    qDebug() << "Playing...";
    m_player->play();
}

void MyMediaPlayer::pause()
{
    qDebug() << "Pausing...";
    m_player->pause();
}

void MyMediaPlayer::stop()
{
    qDebug() << "Stop!!!";
    m_player->stop();
}
