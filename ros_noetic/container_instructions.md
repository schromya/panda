# panda
Tests with Franka Emika Robot (FER).

These are bash commands fyi :)
Setup based on instructions from [frankaemika](https://frankaemika.github.io/docs/franka_ros2.html)

Make sure your host kernel has real-time ubuntu installed. [Here](https://github.com/2b-t/docker-realtime/blob/main/doc/PreemptRt.md) are example instructions on how to install that (not sure if they work bc I didn't need to try them).

Make sure docker is installed as well.


## Setup the Container
``` bash
# Pull ROS noetic image
sudo docker pull osrf/ros:noetic-desktop-full

# Allow X11 forwarding
xhost +local:
```

## Run container

```bash
# Run image connected to current directory (which will be in /workspace directory in the container) and allow host to display gui using X11 Display Forwarding
sudo docker run -it --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace/ --net host osrf/ros:noetic-desktop-full bash

sudo docker run -it \
    --env DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $(pwd):/workspace/ \
    --net host \
    --cap-add SYS_NICE \
    --ulimit rtprio=99 \
    --ulimit rttime=-1 \
    --ulimit memlock=8428281856 \
    osrf/ros:noetic-desktop-full bash

# Install libfranka
sudo apt update
sudo apt install ros-noetic-libfranka ros-noetic-franka-ros

# Set up realtime configs
sudo addgroup realtime
sudo usermod -a -G realtime $(whoami)

echo "@realtime soft rtprio 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime soft priority 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime soft memlock 102400" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard rtprio 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard priority 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard memlock 102400" | sudo tee -a /etc/security/limits.conf



# Set up Workspace
cd workspace
source /opt/ros/noetic/setup.sh

```


```bash
# comms test
sudo communication_test 192.168.1.2

````


## Useful Commands

```bash
# Open multiple terminals
docker exec -it  91b7a6b27900 bash

# Show running docker containers
docker ps

# Save current container
docker commit d02e31662877 franka_ros_noetic:latest

# Run existing image
sudo docker run -it --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace --net host franka_ros_noetic:latest bash


# Kernel version
uname -r

# Ubuntu version
sb_release -a
```







# WITHOUT CONTAINER
```bash

sudo apt update
sudo apt install ros-noetic-libfranka ros-noetic-franka-ros

cd ros_noetic
# Setup workspace
source /opt/ros/noetic/setup.sh

```