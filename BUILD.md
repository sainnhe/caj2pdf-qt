## Windows

### Requirements

- git
- qt5 (安装了 MinGW 8 和 CMake)
- python3.8 (因为这是最后一个支持 Windows 7 的版本)
- [mupdf 1.8](https://mupdf.com/releases) (因为这是最后一个可以下载的 32 位的版本)

### Steps

如果要编译 64 位程序，在开始菜单搜索并启动 "Qt 5.15.2 (MinGW 8.1.0 64-bit)" 命令行（版本号可能有差别）。如果搜不到这个应用，可以从开始菜单 -> 所有应用 -> Qt -> Qt 5.15.2 (MinGW 8.1.0 64-bit) 打开。

如果要编译 32 位的，则打开 "Qt 5.15.2 (MinGW 8.1.0 32-bit)"，并确保 Python 是 32 位的。

在命令行中执行以下命令：

```shell
> %HOMEDRIVE%
> cd %HOMEPATH%\Desktop
> git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
> cd caj2pdf-qt
> python3 .\build-windows.py <qt-path> <architecture>
```

其中 `<qt-path>` 是 Qt 安装的根目录，比如 `C:\Qt`。这个根目录下包含了 `Tools`、`Docs`、`Licenses` 等目录。

`<architecture>` 是要编译的架构，可以是 `32bit` 或 `64bit`。

编译完成后的程序位于桌面的  `caj2pdf` 目录下的 `dist` 目录下。

最后去 [MuPDF 官网](https://mupdf.com/releases) 下载 mupdf 1.8 版本 (因为这是最后一个可以下载的 32 位的版本)，解压后将 `mutool.exe` 复制到 `dist\external` 目录下。

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
