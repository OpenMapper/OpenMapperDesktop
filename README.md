# OpenMapperDesktop
Desktop GUI for the OpenMapper App


## Build status

| Platform  | Status   | Packaging |
| --------- | ---------| ---------|
| Linux     | [![Build Status](https://travis-ci.org/OpenMapper/OpenMapperDesktop.svg?branch=master)](https://travis-ci.org/OpenMapper/OpenMapperDesktop) | [![Snap Status](https://build.snapcraft.io/badge/OpenMapper/OpenMapperDesktop.svg)](https://build.snapcraft.io/user/OpenMapper/OpenMapperDesktop) |
| macOS | [![Build Status](https://travis-ci.org/OpenMapper/OpenMapperDesktop.svg?branch=master)](https://travis-ci.org/OpenMapper/OpenMapperDesktop) | TODO |
| Windows   | TODO | TODO |


## Licence

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)


## GUI
![gui](https://github.com/OpenMapper/OpenMapperDesktop/blob/feature/gui_improvements/doc/gui.png)


## File Tree

```
├── build.sh
├── CMakeLists.txt
├── doc
│   └── gui.png
├── include
│   └── openmapper_desktop
│       ├── config.h
│       ├── myglwidget.h
│       └── window.h
├── libs
│   └── OpenMapper
│       ├── CMakeLists.txt
│       ├── cmake_modules
│       ├── include
│       ├── LICENSE
│       ├── README.md
│       ├── src
│       ├── test
│       ├── thirdparty
│       ├── tools
│       └── wrapper
├── LICENSE
├── package.sh
├── README.md
├── run.sh
├── snap
│   └── snapcraft.yaml
└── src
    ├── main.cc
    ├── myglwidget.cc
    ├── window.cc
    └── window.ui
```


## Installation
### Linux
As Debian package, Install the following dependencies first:

* `sudo apt-get install freeglut3-dev qt5-default libqt5opengl5-dev libopencv-dev libc6 libgcc1 libgl1 libqt5core5a libqt5gui5 libqt5gui5-gles libqt5opengl5 libqt5opengl5-gles libqt5widgets5 libstdc++6`

* `sudo dpkg -i OpenMapperDesktop_x.y.z.deb`

As Snap:

* `sudo snap install --devmode OpenMapperDesktop_x.y.z_arch.snap`

### macOS
TODO
