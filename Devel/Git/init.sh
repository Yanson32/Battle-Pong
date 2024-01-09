#!/bin/sh
#Author Wayne J Larson Jr.
#Date   1/8/24 
#This script initializes and updates the git repositories
#This script should be run from the root directory

git submodule init
git submodule update --recursive 
