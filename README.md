# Hazeron Export Splitter

Hazeron explorations files are too big to load in memory. Keep only parts that you need.

## Installation & usage

make
./hes -f inputfile.xml -g 'Name of galaxy to keep'

It will create (or if exist, erase) cut.xml file which contain only systems of specified galaxy.

## Notes

Tested on cygwin, should works on linux and windows.
