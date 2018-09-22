﻿# SmashRangeGetter
Given picture files of each individual frame of each existing move in the video game Super Smash Brothers for Wii U, this program is designed to go through these files, and assign values to each frame. These values describe the location, length, and width of each hit-box, hurt-box, and other various properties found at each frame. The values are then outputted to a txt file for use. This program is almost finished.  (Note: Program is directory sensitive. To use this program, change the path variable in pathfinder.cpp to represent where your picture files are located on your computer.) The picture files used are in the debug directory, which is in the build directory. Picture files were supplied from data dumped from my Wii U, which were then converted to gif files through Smash Forge. These Gif files were then converted to multiple Png files using ImageMagick. This program builds upon code found in a maze traversal assignment received in Data Structures course, which contained an image class that allows for pictures files to be examined pixel by pixel.
