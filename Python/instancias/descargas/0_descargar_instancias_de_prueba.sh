#!/bin/bash
# Descarga todas las instancias de prueba a ./download_data
raros=(brazil58.tsp brg180.tsp fri26.tsp gr17.tsp gr21.tsp gr24.tsp gr48.tsp hk48.tsp si1032.tsp si175.tsp si535.tsp swiss42.tsp brg180.opt.tour fri26.opt.tour gr24.opt.tour gr48.opt.tour)
grandes=(brd14051.tsp d18512.tsp pla33810.tsp pla85900.tsp rl11849.tsp usa13509.tsp)

mkdir download_data
mkdir download_data/ceros
mkdir download_data/descartadas
python ./scripts/descargar_instancias.py

for i in "${raros[@]}"
do
	mv ./download_data/$i ./download_data/ceros/$i
done

for i in "${grandes[@]}"
do
	mv ./download_data/$i ./download_data/descartadas/$i
done
