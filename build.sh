#!/usr/bin/env sh

# -----------------------------------------------------------------------------
# Name:           CAJ2PDF Qt
# Description:    CAJ 转 PDF 转换器
# Author:         Sainnhe Park <i@sainnhe.dev>
# Website:        https://caj2pdf-qt.sainnhe.dev
# License:        GPL3
# -----------------------------------------------------------------------------

# 项目根目录
BASEDIR="$( cd "$( dirname "$0" )" && pwd )"
cd "${BASEDIR}"

# 初始化 Git 仓库，清理缓存，检查依赖
_init() {
    git submodule update --init --recursive caj2pdf mupdf
    git clean -dfx -- .
    git checkout -- .
    cd "${BASEDIR}/caj2pdf"
    git clean -dfx -- .
    git checkout -- .
    cd "${BASEDIR}/mupdf"
    git clean -dfx -- .
    git checkout -- .
    [ -x "$(command -v cc)" ] || echo "C compiler not found"
    [ -x "$(command -v c++)" ] || echo "C++ compiler not found"
    [ -x "$(command -v git)" ] || echo "Command 'git' not found"
    [ -x "$(command -v python3)" ] || echo "Command 'python3' not found"
    [ -x "$(command -v cmake)" ] || echo "Command 'cmake' not found"
    [ -x "$(command -v pkg-config)" ] || echo "Command 'pkg-config' not found"
    pkg-config --cflags jbig2dec &> /dev/null || echo "Can't find jbig2dec"
    [ -x "$(command -v qmake)" ] || echo "Qt not installed"
    if [ "$(uname)" = Darwin ]; then
        [ -x "$(command -v macdeployqt)" ] || echo "Command 'macdeployqt' not found"
    fi
}

# 构建 caj2pdf 命令行版本
_cli() {
    cd "${BASEDIR}/caj2pdf"
    git clean -dfx -- .
    git checkout -- .
    cd "${BASEDIR}/caj2pdf/lib"
    cc -Wall -fPIC --shared -o libjbigdec.so jbigdec.cc JBigDecode.cc
    cc -Wall `pkg-config --cflags jbig2dec` -fPIC -shared -o libjbig2codec.so decode_jbig2data_x.cc `pkg-config --libs jbig2dec`
    cd "${BASEDIR}/caj2pdf"
    git apply ../caj2pdf.diff
    python3 -m venv venv
    "${BASEDIR}/caj2pdf/venv/bin/python" -m pip install --index-url=https://mirrors.aliyun.com/pypi/simple pypdf2 pyinstaller
    "${BASEDIR}/caj2pdf/venv/bin/pyinstaller" -F caj2pdf
    git checkout -- .
}

# 构建 mupdf
_mupdf() {
    cd "${BASEDIR}/mupdf"
    git clean -dfx -- .
    git checkout -- .
    git apply ../mupdf.diff
    if [ -x "$(command -v nproc)" ]; then
        make --jobs=$(nproc) release
    elif [ -x "$(command -v gnproc)" ]; then
        make --jobs=$(gnproc) release
    else
        make release
    fi
    git checkout -- .
}

# 构建 qt
_qt() {
    cd "${BASEDIR}"
    rm -rf build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ..
    if [ -x "$(command -v nproc)" ]; then
        cmake --build . --parallel $(nproc)
    elif [ -x "$(command -v gnproc)" ]; then
        cmake --build . --parallel $(gnproc)
    else
        cmake --build .
    fi
}

# 打包程序
_package() {
    cd "${BASEDIR}"
    rm -rf dist
    mkdir dist
    if [ "$(uname)" = Darwin ]; then
        cp -r build/caj2pdf.app dist/
        macdeployqt dist/caj2pdf.app
        mkdir dist/caj2pdf.app/Contents/MacOS/external
        cp mupdf/build/release/mutool dist/caj2pdf.app/Contents/MacOS/external/
        cp caj2pdf/dist/caj2pdf dist/caj2pdf.app/Contents/MacOS/external/
        cp caj2pdf/lib/*.so dist/caj2pdf.app/Contents/MacOS/external/
    else
        cp build/caj2pdf dist/
        mkdir dist/external
        cp mupdf/build/release/mutool dist/external/
        cp caj2pdf/dist/caj2pdf dist/external/
        cp caj2pdf/lib/*.so dist/external/
    fi
}

if [ "${1}" = init ]; then
    _init
elif [ "${1}" = cli ]; then
    _cli
elif [ "${1}" = mupdf ]; then
    _mupdf
elif [ "${1}" = qt ]; then
    _qt
elif [ "${1}" = package ]; then
    _package
else
    _init
    _cli
    _mupdf
    _qt
    _package
fi
