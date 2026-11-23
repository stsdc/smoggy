# Smoggy dev container

Open the repository with **Dev Containers: Reopen in Container**. On first
start the container installs PlatformIO Core and runs `pio pkg install`, which
downloads the ESP32 toolchain and the libraries from `platformio.ini`.

Toolchains are cached in the `smoggy-platformio` Docker volume, so they survive
container rebuilds. Remove it with `docker volume rm smoggy-platformio` to
start from a clean cache.

## Build and flash

```sh
pio run                 # compile
pio run -t upload       # compile + flash
pio device monitor      # serial monitor (115200 baud)
pio run -t upload -t monitor
```

The serial port is usually detected automatically. If there are several
devices, pass one explicitly:

```sh
pio run -t upload --upload-port /dev/ttyUSB0
pio device monitor --port /dev/ttyUSB0
```

## Serial access

The container runs with `--privileged` and binds the host `/dev`, so
`/dev/ttyUSB*` and `/dev/ttyACM*` are visible inside it. The `vscode` user is a
member of the common serial-device groups. Because the host's numeric GIDs are
used for the bind-mounted devices, `devcontainer.json` grants GIDs 20
(Debian/Ubuntu `dialout`), 18 (Fedora `dialout`) and 14 (Arch `uucp`). If your
host uses a different GID, check it with `stat -c '%g' /dev/ttyUSB0` and add it
as another `--group-add=<gid>`.

* **Linux:** the container works directly. The host user may also need to be in
  the serial group for permissions outside the container. If a device was
  plugged in after the container started and does not show up, reopen the
  container.
* **Windows:** expose the COM port with
  [usbipd-win](https://github.com/dorssel/usbipd-win) before starting the
  container. Docker Desktop does not pass USB serial devices through by itself.
* **macOS:** Docker Desktop cannot pass USB serial devices into Linux
  containers; flash from the host or use a Linux machine.

## PlatformIO version

The image installs PlatformIO Core 6.2.0, and `platformio.ini` pins the
`espressif32` platform to 6.13.0. That is the Arduino core 2.x line, which is
required by the pinned `AutoConnect` library. Newer 7.x/8.x platforms use
Arduino core 3.x and fail to build this project.

To use the PlatformIO Core bundled with the VS Code extension instead of the
one installed in the image, set `platformio-ide.useBuiltinPIOCore` to `true`
in `devcontainer.json`.
