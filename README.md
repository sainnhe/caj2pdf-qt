![caj2pdf-qt](https://gitlab.com/sainnhe/img/-/raw/master/caj2pdf-qt.png)

## 介绍

这是一个 GUI 版本的 CAJ 转 PDF 转换器，基于 [caj2pdf](https://github.com/caj2pdf/caj2pdf) 和 [mupdf](https://mupdf.com) 实现。

特性：

- [x] 跨平台 (Windows 7, 8, 10, 11; macOS; Linux)
- [x] 多线程转换
- [x] 批量转换
- [x] 文件拖拽
- [ ] 闭源引擎 ([caj2pdf#63](https://github.com/caj2pdf/caj2pdf/issues/63))

## 安装

[GitHub Release](https://github.com/sainnhe/caj2pdf-qt/releases) 页面提供了编译好的 Windows x86_64 版本和 macOS aarch64 版本，你可以从这个页面直接下载（可能需要科学上网）。

如果暂时无法科学上网，可以通过 [GitHub Proxy](https://ghproxy.com) 镜像加速器下载。将 GitHub Release 页面的下载链接复制粘贴到输入框即可下载。

Arch Linux 用户可以从 [AUR](https://aur.archlinux.org/packages/caj2pdf-qt/) 或我的[个人仓库](https://repo.sainnhe.dev/archlinux/)安装。

MacPorts 用户可以从我的[个人仓库](https://repo.sainnhe.dev/macports/)安装。

其它操作系统和架构的用户需要从源代码编译，参考 [BUILD.md](./BUILD.md)。

## 使用

### Windows

解压缩后点 `caj2pdf.exe` 启动。

注意，Windows Defender 或其它一些杀毒软件可能会拦截转换进程，导致转换失败。

这是由于在构建程序的时候使用了 [PyInstaller](https://github.com/pyinstaller/pyinstaller) 将 [caj2pdf](https://github.com/caj2pdf/caj2pdf) 命令行工具打包成了单个可执行文件，而一些杀毒软件会将 PyInstaller 打包的程序当成病毒处理，参考 [pyinstaller/pyinstaller#5492](https://github.com/pyinstaller/pyinstaller/issues/5492)。

如果你信任编译好的压缩包，可以将这个文件夹添加到排除项：[将排除项添加到 Windows 安全中心](https://support.microsoft.com/zh-cn/windows/%E5%B0%86%E6%8E%92%E9%99%A4%E9%A1%B9%E6%B7%BB%E5%8A%A0%E5%88%B0-windows-%E5%AE%89%E5%85%A8%E4%B8%AD%E5%BF%83-811816c0-4dfd-af4a-47e4-c301afe13b26)

或者你也可以选择自行从源代码编译，参考 [BUILD.md](./BUILD.md)。

### macOS

解压后拖到“应用程序”文件夹中，这时候如果直接运行会提示已损坏。

打开终端，运行以下命令：

```bash
xattr -cr /Applications/caj2pdf.app
```

### Linux

直接从应用程序菜单启动。

## 反馈

请移步 [GitHub Issues](https://github.com/sainnhe/caj2pdf-qt/issues)。

## 变更

请移步 [CHANGELOG.md](./CHANGELOG.md)。

## 许可

`/caj2pdf` 和 `/mupdf` 目录下的源代码请参考对应的项目；

其余部分的代码以 [GPL3](https://github.com/sainnhe/caj2pdf-qt/blob/master/LICENSE) 分发。
