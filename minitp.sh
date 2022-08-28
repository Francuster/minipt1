#!/bin/bash

echo "start program..."

echo "directory: " $1

if [ -z "$1" ];
then 
echo "Error: debe ejecutar con un parametro al menos"

else

cd /home/fran
pwd

mkdir $1

ls -o>$1/contenido_home.txt

cat $1/contenido_home.txt

# input="USER INPUT"
read -p "Press enter to finish: " input

fi

