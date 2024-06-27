# Qt Video Player

Example code for playing videos with Qt/QML

![](images/video-player.png)

## Usage

### 1-1. Run with Docker (Recommend)

You can use the docker image that we already build, as below

```bash
$ docker pull kakalin/qt:5.12.0
```

> If you want to build if from scratch, please check [here](https://github.com/kaka-lin/qt-template/tree/master/docker)

And then running with docker:

```bash
$ ./docker-run.sh
```

> If you have some issues with using it, please check here or here, please check [here](https://github.com/kaka-lin/qt-video-player/blob/master/doc/run_with_docker.md) or [here](https://github.com/kaka-lin/qt-template/tree/master/docker)


### 1-2. Run with local Qt

Please install Qt/QML on your local machine.

### Runing the Example

Running the relate example as below:

- [Custom Media Player](https://github.com/kaka-lin/qt-video-player/tree/master/custom_media_player)
- [OpenCV and QML](https://github.com/kaka-lin/qt-video-player/tree/master/opencv_qml)

## Acknowledgements

- Thanks to [Display cv::Mat as QVideoFrame in a QML VideoOutput](https://stackoverflow.com/questions/62069201/display-cvmat-as-qvideoframe-in-a-qml-videooutput) for convert `cv::Mat` to `QVideoFrame` part.
