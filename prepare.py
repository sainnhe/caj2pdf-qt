# -----------------------------------------------------------------------------
# Name:           CAJ2PDF Qt
# Description:    CAJ 转 PDF 转换器
# Author:         Sainnhe Park <i@sainnhe.dev>
# Website:        https://caj2pdf-qt.sainnhe.dev
# License:        GPL3
# -----------------------------------------------------------------------------

import os
import sys
from os.path import join
from shutil import copyfile, move
import subprocess

# update submodules
workdir = os.getcwd()
os.chdir(workdir)
subprocess.run(["git", "submodule", "update", "--init", "--recursive", "caj2pdf"])
subprocess.run(["git", "clean", "-dfx", "--", "."])

# build cli
workdir_cli = join(workdir, "caj2pdf")
os.chdir(workdir_cli)
subprocess.run(["git", "clean", "-dfx", "--", "."])
subprocess.run(["git", "checkout", "--", "."])
subprocess.run(["git", "apply", "../patches/caj2pdf.diff"])
subprocess.run([sys.executable, "-m", "venv", "venv"])
subprocess.run([".\\venv\\Scripts\\python.exe", "-m", "pip", "install", "--index-url=https://mirrors.aliyun.com/pypi/simple", "pypdf2", "pyinstaller"])
subprocess.run([".\\venv\\Scripts\\pyinstaller.exe", "-F", "caj2pdf"])
subprocess.run(["git", "checkout", "--", "."])

# build project
dist_dir = join(workdir, "dist")
build_external_dir = join(dist_dir, "external")
os.mkdir(dist_dir)
os.mkdir(build_external_dir)
os.chdir(workdir)
subprocess.run(["windres", "app.rc", "-o", "app.o"])
os.chdir(dist_dir)
move(join(join(workdir_cli, "dist"), "caj2pdf.exe"),
     join(build_external_dir, "caj2pdf.exe"))
copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbigdec-w64.dll"),
         join(join(dist_dir, "external"), "libjbigdec.dll"))
copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbig2codec-w64.dll"),
         join(join(dist_dir, "external"), "libjbig2codec.dll"))
