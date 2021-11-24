#!/usr/bin/env python

# -----------------------------------------------------------------------------
# Name:           CAJ2PDF Qt
# Description:    CAJ 转 PDF 转换器
# Author:         Sainnhe Park <sainnhe@gmail.com>
# Website:        https://caj2pdf-qt.sainnhe.dev
# License:        GPL3
# -----------------------------------------------------------------------------

import os
import platform
import subprocess
from shutil import move, copyfile

# update submodules
workdir = os.getcwd()
os.chdir(workdir)
subprocess.run(["git", "submodule", "update", "--init", "--recursive", "caj2pdf"])
if os.name != "nt":
    subprocess.run(["git", "submodule", "update", "--init", "--recursive", "mupdf"])

# build caj2pdf
workdir_caj2pdf = os.path.join(workdir, "caj2pdf")
if os.name != "nt":
    os.chdir(os.path.join(workdir_caj2pdf, "lib"))
    pkg_config_cflags = subprocess.getoutput("pkg-config --cflags jbig2dec")
    pkg_config_libs = subprocess.getoutput("pkg-config --libs jbig2dec")
    os.system("gcc -Wall -fPIC --shared -o libjbigdec.so jbigdec.cc JBigDecode.cc")
    os.system("gcc -Wall " + pkg_config_cflags + " -fPIC -shared -o libjbig2codec.so decode_jbig2data_x.cc " + pkg_config_libs)
os.chdir(workdir_caj2pdf)
subprocess.run(["git", "apply", "../caj2pdf.diff"])
subprocess.run(["python", "-m", "venv", "venv"])
if platform.system() == "Windows":
    subprocess.run([".\\venv\\Scripts\\python.exe", "-m", "pip", "install", "--index-url=https://mirrors.aliyun.com/pypi/simple", "pypdf2", "pyinstaller"])
    subprocess.run([".\\venv\\Scripts\\pyinstaller.exe", "-F", "caj2pdf"])
else:
    subprocess.run(["./venv/bin/python", "-m", "pip", "install", "--index-url=https://mirrors.aliyun.com/pypi/simple", "pypdf2", "pyinstaller"])
    subprocess.run(["./venv/bin/pyinstaller", "-F", "caj2pdf"])
subprocess.run(["git", "checkout", "--", "."])

# build mupdf
if os.name != "nt":
    workdir_mupdf = os.path.join(workdir, "mupdf")
    os.chdir(workdir_mupdf)
    subprocess.run(["make", "--jobs=" + str(os.cpu_count())])

# build project
build_dir = os.path.join(workdir, "build")
build_external_dir = os.path.join(build_dir, "external")
src_dir = os.path.join(workdir, "src")
os.mkdir(build_dir)
os.mkdir(build_external_dir)
if os.name != "nt":
    move(os.path.join(os.path.join(workdir_caj2pdf, "dist"), "caj2pdf"),
         os.path.join(build_external_dir, "caj2pdf"))
    move(os.path.join(os.path.join(os.path.join(workdir_mupdf, "build"), "release"), "mutool"),
         os.path.join(build_external_dir, "mutool"))
os.chdir(src_dir)
if platform.system() == "Windows":
    subprocess.run(["windres", "app.rc", "-o", "app.o"])
else:
    subprocess.run(["cmake", "."])
    subprocess.run(["cmake", "--build", ".", "--config", "Release", "--", "--jobs=" + str(os.cpu_count())])
os.chdir(build_dir)
if platform.system() == "Darwin":
    move(os.path.join(src_dir, "caj2pdf.app"),
         os.path.join(build_dir, "caj2pdf.app"))
    move(os.path.join(build_dir, "external"),
         os.path.join(os.path.join(os.path.join(build_dir, "caj2pdf.app"), "Contents"), "MacOS"))
    os.mkdir(os.path.join(os.path.join(os.path.join(build_dir, "caj2pdf.app"), "Contents"), "Resources"))
    copyfile(os.path.join(os.path.join(workdir, "icons"), "convert.icns"),
             os.path.join(os.path.join(os.path.join(os.path.join(build_dir, "caj2pdf.app"), "Contents"), "Resources"), "convert.icns"))
    subprocess.run(["open", "."])
elif platform.system() != "Windows":
    move(os.path.join(src_dir, "caj2pdf"),
         os.path.join(build_dir, "caj2pdf"))
