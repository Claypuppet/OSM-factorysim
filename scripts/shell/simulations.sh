#!/bin/sh
if [ "$#" -lt 2 ]
then
    echo "Not enough arguments! run with  ./simulations.sh production_control_exe [config_file ...]"
else
    pc_exe="$1"
    shift

    if [ ! -x ${pc_exe} ]
    then
        echo "production control executable \"$pc_exe\" not found or no execute rights"
    else
        for config_file in "$@"
        do
            if [ ! -r ${config_file} ]
            then
                echo "config file \"$config_file\" not found or no read rights"
            else
                echo "executing with $config_file..."
                ${pc_exe} "$config_file"
            fi
        done
        echo "All simulation done"
    fi
fi
