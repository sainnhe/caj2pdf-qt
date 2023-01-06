## Windows

### Requirements

- git
- qt5 (with mingw 8 && cmake)
- python3
- [mupdf](https://mupdf.com/releases)

### Steps

```shell
> git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
> cd caj2pdf-qt
> python3 .\prepare.py
```

配置 Qt Creator 环境，用 Qt Creator 打开项目文件 `\path\to\caj2pdf-qt\CMakeLists.txt`，选择 "Desktop Qt 5.15.2 MinGW 64-bit"；

点击左下角 "caj2pdf Debug"，选择 "Release"；

点击左下角构建按钮开始构建，生成的可执行文件位于 `\path\to\caj2pdf-qt` 的上一级目录的 `build-caj2pdf-qt-Desktop_Qt_5_15_2_MinGW_64_bit-Release` 目录下；

将这个目录下的 `caj2pdf.exe` 复制到 `\path\to\caj2pdf-qt\dist` 目录下；

去 [MuPDF 官网](https://mupdf.com/releases) 下载最新的 mupdf 压缩包，解压后将 `mutool.exe` 复制到 `\path\to\caj2pdf-qt\dist\external` 目录下

在开始菜单搜索并启动 "Qt 5.15.2 (MinGW 8.1.0 64-bit)" 命令行（版本号可能有差别）。如果搜不到这个应用，可以从开始菜单 -> 所有应用 -> Qt -> Qt 5.15.2 (MinGW 8.1.0 64-bit) 打开

从这个命令行中进入到 `\path\to\caj2pdf-qt\dist` 目录下；

执行 `windeployqt caj2pdf.exe`

输出位于 `dist` 目录下

## macOS

### Requirements

- C/C++ 编译工具 (GCC 或 Clang)
- git
- qt5
- python3
- cmake
- make
- pkg-config
- jbig2dec

### Steps

```shell
$ git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
$ cd caj2pdf-qt
$ ./build.sh
```

输出位于 `dist` 目录下

## Linux

### Requirements

- C/C++ 编译工具 (GCC 或 Clang)
- git
- qt5
- python3
- cmake
- make
- pkg-config
- jbig2dec

### Steps

```shell
$ git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
$ cd caj2pdf-qt
$ ./build.sh
```

输出位于 `dist` 目录下
