# GtkQR
## Create codes easily and efficiently

GtkQR is a gtk library for generating QR codes .

## Features
- versions for gtk 2,3 and 4  
- numeric, alphanumeric, byte and kanji mode 
- micro QR mode
- supports utf8 character set 
- supports different character sets  
- customizable colors 
- support for use without UI 

## Installation

GtkQR requires development files for gtk this is libgtk-4-dev,libgtk-3-dev or libgtk2.0-dev , use: 

for version 4 use: 
```sh
make VERSION=4
sudo make install
make clean
```

for version 3 use:

```sh
make
sudo make install
make clean
```

for version 2 use: 
```sh
make VERSION=2
sudo make install
make clean
```

## Use

You only need build your programs with `pkg-config gtkqr-4.0 --cflags  --libs` ,`pkg-config gtkqr-3.0 --cflags  --libs` or `pkg-config gtkqr-2.0 --cflags --libs`.Without UI use `pkg-config qrutils --cflags --libs`

## Documentation 
to generate the documentation use 

```sh
make doxygen
```
