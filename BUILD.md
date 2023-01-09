## Windows

### Requirements

- git
- qt5 (with mingw 8 && cmake)
- python3.8
- [mupdf](https://mupdf.com/releases)

### Steps

在开始菜单搜索并启动 "Qt 5.15.2 (MinGW 8.1.0 64-bit)" 命令行（版本号可能有差别）。如果搜不到这个应用，可以从开始菜单 -> 所有应用 -> Qt -> Qt 5.15.2 (MinGW 8.1.0 64-bit) 打开

```shell
> git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
> cd caj2pdf-qt
> python3 .\build-windows.py <qt-path>
```

其中 `<qt-path>` 是 Qt 安装的根目录，比如 `C:\Qt`。这个根目录下包含了 `Tools`、`Docs`、`Licenses` 等目录。

在执行命令前，请确保 Python 版本是 3.8 ，因为这是最后一个支持 Windows 7 的 Python 版本，在命令行中输入以下命令来确认 Python 版本号：

```shell
> python3 -V
```

编译完成后的程序位于 `dist` 目录下。

最后去 [MuPDF 官网](https://mupdf.com/releases) 下载最新的 mupdf 压缩包，解压后将 `mutool.exe` 复制到 `dist\external` 目录下。

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
$ ./build-unix.sh
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
$ ./build-unix.sh
```

输出位于 `dist` 目录下
