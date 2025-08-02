#!/bin/bash
mkdir -p build
cp init_vis.mac ./build
cd build
cmake -DCMAKE_PREFIX_PATH="/opt/anaconda3/envs/G4/" -DZLIB_ROOT=/opt/homebrew/opt/zlib ../
make
echo " "
echo "*** Compilación finalizada ***"
echo " "
echo "=> Ingresa a build y Ejecuta: ./main "
echo " "
