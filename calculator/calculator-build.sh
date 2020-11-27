#!/bin/sh

rm -Rf calculator_Build
mkdir calculator_Build
cd calculator_Build
mkdir calculator.AppDir
export QMAKE=/home/vinicius/Qt/5.15.1/gcc_64/bin/qmake 
$QMAKE /home/vinicius/exaud/qt-stuff/qt-calculator/calculator/calculator.pro
make -j8
make install INSTALL_ROOT=calculator.AppDir
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
chmod +x linuxdeploy*.AppImage
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/vinicius/Qt/5.15.1/gcc_64/lib
./linuxdeploy-x86_64.AppImage --appdir calculator.AppDir -e calculator -i /home/vinicius/exaud/qt-stuff/qt-calculator/calculator/resources/icon.png -d /home/vinicius/exaud/qt-stuff/qt-calculator/calculator/resources/calc.desktop --plugin qt --output appimage
cp calculator-x86_64.AppImage ../calculator
