#!/bin/sh

if [ "$1" == "-t" ]; then
    picotool load ../bdfconv/data/ibml14.fnt -t bin -o 0x10100000
    picotool load ../bdfconv/data/ibmm18.fnt -t bin -o 0x10118000
    picotool load ../bdfconv/data/kpop20.fnt -t bin -o 0x10138000
    picotool load ../bdfconv/data/kpop22.fnt -t bin -o 0x10160000
    picotool load ../bdfconv/data/maru20.fnt -t bin -o 0x10188000
    picotool load ../bdfconv/data/maru22.fnt -t bin -o 0x101B0000
fi
sleep 1
if [ -e /Volumes/RPI-RP2/badger2040.uf2 ]; then
    rmdir /Volumes/RPI-RP2/badger2040.uf2
fi
cp ./build/badger2040.uf2 /Volumes/RPI-RP2
