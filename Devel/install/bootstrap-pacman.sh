#!/bin/sh
#This script downloads all of the dependencies needed to build this game on arch linux

#update pacman
sudo pacman -Syu --noconfirm

#install a compiler
sudo pacman -S gcc --noconfirm

#install make
sudo pacman -S make --noconfirm

#install cmake
sudo pacman -S cmake --noconfirm

#install sfml
sudo pacman -S sfml --noconfirm

sudo ldconfig


