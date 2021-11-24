## Windows

### Requirements

- git
- qt6
- python3
- cmake
- mingw
- mupdf

### Steps

```shell
> git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
> cd caj2pdf-qt
> python .\build.py
```

配置 Qt Creator 环境, 用 Qt Creator 打开项目文件 `\path\to\caj2pdf-qt\src\CMakeLists.txt`；

点击左下角 "caj2pdf Debug"，选择 "Release"；

点击左下角构建按钮开始构建，生成的可执行文件位于 `\path\to\caj2pdf-qt\build-src-*` 目录下；

将这个目录下的 `caj2pdf.exe` 复制到 `\path\to\caj2pdf-qt\build` 目录下；

将 `\path\to\caj2pdf-qt\caj2pdf\dist\caj2pdf.exe` 复制到 `\path\to\caj2pdf-qt\build\external` 目录下；

在命令行中用 `which mutool` 定位 `mutool.exe` 的位置，将 `mutool.exe` 复制到 `\path\to\caj2pdf-qt\build\external` 目录下；

在开始菜单搜索 "Mingw", 启动 "Qt 6.2.1 (MinGW 8.1.0 64-bit)" 命令行（版本号可能有差别），从这个命令行中进入到 `\path\to\caj2pdf-qt\build` 目录下；

执行 `windeployqt --release caj2pdf.exe`。

## macOS

### Requirements

- git
- qt6
- python3
- cmake

### Steps

```shell
$ git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
$ cd caj2pdf-qt
$ ./build.py
```

## Linux

### Requirements

- git
- qt6
- python3
- cmake

### Steps

```shell
$ git clone --depth 1 https://github.com/sainnhe/caj2pdf-qt.git
$ cd caj2pdf-qt
$ ./build.py
```

