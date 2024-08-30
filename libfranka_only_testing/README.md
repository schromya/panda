# Libfranka (only) Testing

This directory contains scripts that only use libfranka, not ROS.

## Setup
Follow the instructions of setup.md (in the root of this repo) up to and including the "Real time Kernel" section.


This directory should have a copy of the libfranka library. You should not need to install it. 


You will also need to install the following:
```bash
sudo apt install build-essential cmake git libpoco-dev libeigen3-dev
```


## Running

main.cpp uses the IP 192.168.1.2 for the robot. You need to change it if your robot is different.

Before you can run anything with code, make sure joints are unlocked and FCI Control is enabled in the Franka desktop (more details in setup.md).

Run the following to compile and run main:
```bash
cd libfranka_only_testing # Make sure you are in this directory (may need another command)

g++ -o main main.cpp -I./libfranka/include -I./libfranka/examples -I/usr/include/eigen3 -L./libfranka/build -L./libfranka/build/examples -Wl,-rpath,./libfranka/build:./libfranka/build/examples -lfranka -lpthread -lexamples_common


./main # WARNING: This command will move the robot! Please make sure to have the user stop button at hand!
```


## Troubleshooting
Check setup.md for errors and solutions I ran into while setting up.

