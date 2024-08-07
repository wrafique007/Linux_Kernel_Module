# Project Description
This project is about a Linux Kernel Module for LCD which used HD44780 LCD controller. The kernel module was developed for embedded Linux(version 5.4) executing on BeagleBone Black

# Hardware Used
* BeagleBone black
* FTDI USB to TTL converter (This was used for communicating with Linux over UART) 

# Source Code Description
  ### Makefile
  This file compiles the Kernel module. As the result of running this file a .ko file is created which is Linux Kernel Module file.
  ### gpio-platform.c
  This file is the source code for linux kernel module in C.
  ### lcd.c
  This file contains HD44780 LCD controller functions. Thus this file represents LCD low lever driver.
