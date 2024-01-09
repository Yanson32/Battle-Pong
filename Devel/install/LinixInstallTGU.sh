#!/bin/sh


if ["$1" -eq ""]
then
    URL="https://github.com/texus/TGUI/archive/refs/tags/v1.0-alpha.tar.gz";
else
    URL="$1";
fi

mkdir TGUI
curl -L "$URL" --output TGUI.tar.gz
tar -xf ./TGUI.tar.gz -C TGUI --strip-components=1
cd TGUI
mkdir build
cd build
mkdir gcc
cd gcc
mkdir debug release

#Compile and install debug version of TGUI
cd debug
if ["$URL" -eq "https://github.com/texus/TGUI/archive/refs/tags/v1.0-alpha.tar.gz"]
then
    cmake ../../../ -DCMAKE_BUILD_TYPE="Debug" -DTGUI_BACKEND=SFML_GRAPHICS
else
    cmake ../../../ -DCMAKE_BUILD_TYPE="Debug" 
fi
make
sudo make install

#Compile and install release version of TGUI
cd ../release

if ["$URL" -eq "https://github.com/texus/TGUI/archive/refs/tags/v1.0-alpha.tar.gz"]
then
    cmake ../../../ -DCMAKE_BUILD_TYPE="Release"  -DTGUI_BACKEND=SFML_GRAPHICS  
else
    cmake ../../../ -DCMAKE_BUILD_TYPE="Debug" 
fi

make
sudo make install
cd ../../../../

