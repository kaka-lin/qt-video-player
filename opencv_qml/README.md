# OpenCV and QML's VideoOutput

Example code of show video on QML ([VideoOutput ](https://doc.qt.io/qt-5/qml-qtmultimedia-videooutput.html)) use OpenCV

## Require

- Qt5.10+
- CMake & Ninja

## Build and Run

### 1. qmake

```bash
$ ./build.sh
```

### 2. CMake

```bash
$ ./cmake-build.sh
```

### 3. Run with Docker

Please see this [doc](../doc/run_with_docker.md)

## Other

### Enable Qt Logging Info

export QT_LOGGING_RULES=<category>[.type]=true|false

For example:

```bash
# Turn on all debug logging
$ export QT_LOGGING_LURES=*.debug=true

# Turn on all logging level of all multimedia module
$ export QT_LOGGING_LURES=qt.multimedia.*=true
```

### Enable OpenCV Logging Info

```bash
# Enable OpenCV debug message
$ export OPENCV_LOG_LEVEL=DEBUG

# Enable OpenCV VideoIO debug message
$ export OPENCV_VIDEOIO_DEBUG=1
```
