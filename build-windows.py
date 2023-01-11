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
subprocess.run(["git", "submodule", "update",
               "--init", "--recursive", "caj2pdf"])
subprocess.run(["git", "clean", "-dfx", "--", "."])

# build cli
workdir_cli = join(workdir, "caj2pdf")
os.chdir(workdir_cli)
subprocess.run(["git", "clean", "-dfx", "--", "."])
subprocess.run(["git", "checkout", "--", "."])
subprocess.run(["git", "apply", "../patches/caj2pdf.diff"])
subprocess.run([sys.executable, "-m", "venv", "venv"])
subprocess.run([".\\venv\\Scripts\\python.exe", "-m", "pip", "install",
               "-r", "requirements.txt", "-i", "https://mirrors.aliyun.com/pypi/simple"])
subprocess.run([".\\venv\\Scripts\\python.exe", "-m", "pip", "install",
               "pyinstaller", "-i", "https://mirrors.aliyun.com/pypi/simple"])
subprocess.run([".\\venv\\Scripts\\pyinstaller.exe", "-F", "caj2pdf"])
subprocess.run(["git", "checkout", "--", "."])

# build project
os.chdir(workdir)
subprocess.run(["git", "clean", "-dfx", "--", "."])
qt_path = sys.argv[1]
cmake_path = qt_path + "\\Tools\\CMake_64\\bin"
ninja_path = qt_path + "\\Tools\\Ninja"
os.environ["PATH"] = cmake_path + ";" + ninja_path + ";" + os.environ["PATH"]
dist_dir = join(workdir, "dist")
os.mkdir(dist_dir)
dist_external_dir = join(dist_dir, "external")
os.mkdir(dist_external_dir)
build_dir = join(workdir, "build")
os.mkdir(build_dir)
os.chdir(workdir)
subprocess.run(["windres", "app.rc", "-o", "build\\app.o"])
os.chdir(build_dir)
subprocess.run(["cmake", "-G", "Ninja", "-DCMAKE_BUILD_TYPE=Release", ".."])
subprocess.run(["cmake", "--build", ".", "--parallel", str(os.cpu_count())])
os.chdir(dist_dir)
move(join(build_dir, "caj2pdf.exe"),
     dist_dir)
move(join(join(workdir_cli, "dist"), "caj2pdf.exe"),
     join(dist_external_dir, "caj2pdf.exe"))
if sys.argv[2] == "64bit":
    copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbigdec-w64.dll"),
             join(join(dist_dir, "external"), "libjbigdec.dll"))
    copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbig2codec-w64.dll"),
             join(join(dist_dir, "external"), "libjbig2codec.dll"))
else:
    copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbigdec-w32.dll"),
             join(join(dist_dir, "external"), "libjbigdec.dll"))
    copyfile(join(join(join(workdir_cli, "lib"), "bin"), "libjbig2codec-w32.dll"),
             join(join(dist_dir, "external"), "libjbig2codec.dll"))
subprocess.run(["windeployqt", "caj2pdf.exe"])
