# panda
Tests with Franka Emika Robot (FER).

These are bash commands fyi :)
Setup based on instructions from [frankaemika](https://frankaemika.github.io/docs/franka_ros2.html)


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

# Install libfranka
sudo apt update
sudo apt install ros-noetic-libfranka ros-noetic-franka-ros

# Configure Kernel for realtime
sudo apt-get install build-essential bc curl ca-certificates gnupg2 libssl-dev lsb-release libelf-dev bison flex dwarves zstd libncurses-dev

curl -SLO https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.9.tar.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.9.tar.sign
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/6.9/patch-6.9-rt5.patch.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/6.9/patch-6.9-rt5.patch.sign

xz -d *.xz
tar xf linux-*.tar
cd linux-*/
patch -p1 < ../patch-*.patch

touch /boot/config-$(uname -r) # ONLY DO IF ON CONTAINER
cp -v /boot/config-$(uname -r) .config
make olddefconfig
make menuconfig

```
The second command brings up a terminal interface in which you can configure the preemption model. Navigate with the arrow keys to General Setup > Preemption Model and select Fully Preemptible Kernel (Real-Time) (PREEMTIBLE KERNEL???)

After that navigate to Cryptographic API > Certificates for signature checking (at the very bottom of the list) > Provide system-wide ring of trusted keys > Additional X.509 keys for default system keyring

Remove the “debian/canonical-certs.pem” from the prompt and press Ok. Save this configuration to .config and exit the TUI.

```bash

# Set up Workspace
cd workspace
source /opt/ros/noetic/setup.sh

```


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





