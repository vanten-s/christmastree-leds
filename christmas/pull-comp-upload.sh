#!/bin/sh

git pull

arduino --port /dev/ttyUSB0 --upload /home/svante/christmastree-leds/christmas/christmas.ino

