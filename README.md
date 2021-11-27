![caj2pdf-qt](https://gitlab.com/sainnhe/img/-/raw/master/caj2pdf-qt.png)

## 关于

这是一个 GUI 版本的 CAJ 转 PDF 转换器，基于 [caj2pdf](https://github.com/caj2pdf/caj2pdf) 和 [mupdf](https://mupdf.com) 实现。

## 安装

[GitHub Release](https://github.com/sainnhe/caj2pdf-qt/releases) 页面提供了编译好的 Windows x86_64 版本，你可以从这个页面直接下载（可能需要科学上网）。

如果暂时无法科学上网，可以通过 [FastGit](https://doc.fastgit.org/zh-cn/guide.html#release-%E5%92%8C%E6%BA%90%E7%A0%81%E5%AD%98%E6%A1%A3%E7%9A%84%E4%B8%8B%E8%BD%BD) 镜像加速器下载。

例如，v0.1.3 版本的下载链接为 [https://github.com/sainnhe/caj2pdf-qt/releases/download/v0.1.3/caj2pdf-qt-windows-x86_64-0.1.3.zip](https://github.com/sainnhe/caj2pdf-qt/releases/download/v0.1.3/caj2pdf-qt-windows-x86_64-0.1.3.zip),

那么它的 fastgit 镜像下载链接为 [https://download.fastgit.org/sainnhe/caj2pdf-qt/releases/download/v0.1.3/caj2pdf-qt-windows-x86_64-0.1.3.zip](https://download.fastgit.org/sainnhe/caj2pdf-qt/releases/download/v0.1.3/caj2pdf-qt-windows-x86_64-0.1.3.zip)。

Arch Linux 用户可以从 [AUR](https://aur.archlinux.org/packages/caj2pdf-qt/) 或我的[个人仓库](https://repo.sainnhe.dev/archlinux/)安装。

其它操作系统和架构的用户需要从源代码编译，参考 [BUILD.md](./BUILD.md)。

## 使用

### Windows

解压缩后点 `caj2pdf.exe` 启动。

注意，Windows Defender 或其它一些杀毒软件可能会拦截转换进程，导致转换失败。

如果你信任编译好的压缩包，可以将这个文件夹添加到排除项：[将排除项添加到 Windows 安全中心](https://support.microsoft.com/zh-cn/windows/%E5%B0%86%E6%8E%92%E9%99%A4%E9%A1%B9%E6%B7%BB%E5%8A%A0%E5%88%B0-windows-%E5%AE%89%E5%85%A8%E4%B8%AD%E5%BF%83-811816c0-4dfd-af4a-47e4-c301afe13b26)

或者你也可以选择自行从源代码编译，参考 [BUILD.md](./BUILD.md)。

### macOS

编译好之后会自动打开包含这个 App 的文件夹，双击启动即可。

你也可以将这个 App 拖拽到“应用程序”文件夹中，以后就可以直接从启动台启动了。

### Linux

编译好后直接运行 `./build/caj2pdf`。

## 反馈

请移步 [GitHub Issues](https://github.com/sainnhe/caj2pdf-qt/issues)。

## 变更

请移步 [CHANGELOG.md](./CHANGELOG.md)。

## 许可

`/caj2pdf` 和 `/mupdf` 目录下的源代码请参考对应的项目；

其余部分的代码以 [GPL3](https://github.com/sainnhe/caj2pdf-qt/blob/master/LICENSE) 分发。
