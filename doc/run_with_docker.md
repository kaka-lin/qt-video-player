# Run Qt/QML with docker

## Prepare

Download image from  Docker Hub

```bash
$ docker pull kakalin/qt:5.12.0
```

## Run

- [Ubuntu](#ubuntu)
- [macOS](#2-macos)

### Ubuntu

```bash
# Expose the X server on the host
$ xhost +local:docker
```

```bash
$ docker run --rm -it \
    -e DISPLAY=$DISPLAY \
    -e QT_X11_NO_MITSHM=1 \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix" \
    --volume="$PWD:/home/user/qt-video-player" \
    --device /dev/snd \
    -e PULSE_SERVER=unix:${XDG_RUNTIME_DIR}/pulse/native \
    -v ${XDG_RUNTIME_DIR}/pulse/native:${XDG_RUNTIME_DIR}/pulse/native \
    --privileged \
    kakalin/qt:5.12.0
```

#### Note:

- GPU: Please refer to [nvidia-docker](https://github.com/NVIDIA/nvidia-docker)

### `macOS`

Reference: [X11 in docker on macOS](https://gist.github.com/cschiewek/246a244ba23da8b9f0e7b11a68bf3285)

1. Install [XQuartz](https://dl.bintray.com/xquartz/downloads/XQuartz-2.7.11.dmg) from official website or through [Homebrew](https://brew.sh/)

    ```bash
    $ brew install --cask xquartz
    ```

    and then `Restart OS`.

2. Open XQuartz and Check the option: `XQuartz -> Preferences -> Security -> "Allow connections from network clients"`

    ```bash
    # open XQuartz
    $ open -a XQuartz
    ```

3. In terminal:

    ```bash
    # Expose the X server on the host
    $ xhost +localhost
    ```

    ```bash
    $ docker run --rm -it \
        -e DISPLAY=host.docker.internal:0 \
        -e QT_X11_NO_MITSHM=1 \
        --volume="/tmp:/tmp" \
        --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
        --volume="$PWD:/home/user/qt-video-player" \
        --device /dev/dri \
        --device /dev/snd \
        --privileged \
        kakalin/qt:5.12.0
    ```

## Troubleshooting

1. `Qt is not found`

    Opening ```CMakeLists.txt``` and uncomment ```list(APPEND CMAKE_PREFIX_PATH ${Your Qt path})``` and modify Qt location

2. `libGL error: No matching fbConfigs or visuals found`

    ```bash
    $ export LIBGL_ALWAYS_INDIRECT=1
    ```

3. `QGLXContext: Failed to create dummy context`

    Workaround:

    ```bash
    $ export QT_QUICK_BACKEND=software
    ```
