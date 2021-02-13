#!/bin/sh

if (! test "$#" = 4) || 
    (! test -f "$1") || 
    (! test -d "$2") || 
    (! test -d "$3") ||
    (! test -d "$4")
then
    echo "Usage: "$0" program input-folder output-folder afl-folder"
    exit 1
fi

# change kernel settings
sudo sh -c 'echo core >/proc/sys/kernel/core_pattern'
sudo sh -c 'cd /sys/devices/system/cpu && echo performance | tee cpu*/cpufreq/scaling_governor'

# build the image
sudo docker build -t socker-stuffer \
--build-arg Program="$1" \
--build-arg Input="$2" \
--build-arg Output="$3" \
--build-arg Afl="$4" \
--build-arg USER_ID=$(id -u) \
--build-arg GROUP_ID=$(id -g) .

# run docker
sudo docker run -it -v `realpath "$3"`:/test/output socker-stuffer
