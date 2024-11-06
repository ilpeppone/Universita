#!/bin/bash

if [ -z "$1" ]; 
then
    echo "usage:     makeC.sh [program.c] [arg1] [arg2] ... [argn]"
    exit 1
fi

program=$1
shift

case $program in
    *.c )
        if [ -f "$program" ];
        then
            elf="${program%.*}".elf
            gcc "$program" -o "$elf"
            ./"$elf" "$@"

            #rimuovo il file out che non serve
            rm $elf
        else
            echo "error: $program is not a file!"
        fi
    ;;

    * )
        echo "error required only .java arguments"
        exit 1
    ;;
esac