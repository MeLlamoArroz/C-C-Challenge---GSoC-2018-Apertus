# C/C++ Challenge - T872
My solution to the C/C++ Challenge from Apertus for GSoC.

**Goals :**

The goal is to build a small application which decodes a buffer with raw image data from the AXIOM Beta and converts it using the LodePNG library to create a viewable PNG image.

1. Create a simple C/C++ console application using the development environment of your choice
2. Add lodepng.c/cpp and lodepng.h from the LodePNG website to your project / Makefile / whatever you use
3. Read image data from a RAW12 file (sample file: portrait-gainx2-offset2047-20ms-02.raw12, 4096x3072, 12bit, color sensor with bayer color filter array)
4. Save one of the Bayer color channels (red, green1, green2 or blue) as a grayscale 8-bit PNG (2048x1536 Resolution) using the LodePNG library. This PNG should be view-able/compatible with any image-viewer that can display PNG.
Optional:

5. Bonus points if your application runs on the AXIOM Beta firmware in QEMU.
6. Bonus points if you use an existing debayering method to recover a color image.

# How to run in Linux

1. Run the makefile.
```
make
```
2. Run the executable and write the argument.
```
./run <filename>
```
