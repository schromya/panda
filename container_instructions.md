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

# Allow Display forwarding
xhost +local:
```

## Run container

### Run image connected to current directory (which will be in /workspace directory in the container) and allow host to display gui using X11 Display Forwarding
```bash
cd ros_noetic
sudo docker build -t panda-container .
sudo docker run -it --privileged --cap-add=SYS_NICE --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace --net=host panda-container

```


### Prep ROS workspace
```bash
source /opt/ros/noetic/setup.sh
cd catkin_ws
catkin_make -DCMAKE_BUILD_TYPE=Release
source devel/setup.sh
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