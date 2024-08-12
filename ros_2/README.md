# panda
Tests with Franka Emika Pandas Robot.

These are bash commands fyi :)
Setup based on instructions from [frankaemika](https://frankaemika.github.io/docs/franka_ros2.html)


## Setup the Container
``` bash
# Pull ROS2 humble image
sudo docker pull osrf/ros:humble-desktop-full

# Allow X11 forwarding
xhost +local:
```

## Run container

```bash
# Run image connected to current directory (which will be in /workspace directory in the container) and allow host to display gui using X11 Display Forwarding
sudo docker run -it --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace/panda --net host osrf/ros:humble-desktop-full bash

# Install Pinnochia (for libfranka)
# Pinnochia instructions from https://stack-of-tasks.github.io/pinocchio/download.html
sudo apt install -qqy lsb-release curl
sudo mkdir -p /etc/apt/keyrings
curl http://robotpkg.openrobots.org/packages/debian/robotpkg.asc \
    | sudo tee /etc/apt/keyrings/robotpkg.asc
echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/robotpkg.asc] http://robotpkg.openrobots.org/packages/debian/pub $(lsb_release -cs) robotpkg" \
    | sudo tee /etc/apt/sources.list.d/robotpkg.list

sudo apt update
sudo apt install -qqy robotpkg-py3*-pinocchio

echo 'export PATH=/opt/openrobots/bin:$PATH' >> ~/.bashrc
echo 'export PKG_CONFIG_PATH=/opt/openrobots/lib/pkgconfig:$PKG_CONFIG_PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/opt/openrobots/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
echo 'export PYTHONPATH=/opt/openrobots/lib/python3.10/site-packages:$PYTHONPATH' >> ~/.bashrc  # Adapt your desired python version here
echo 'export CMAKE_PREFIX_PATH=/opt/openrobots:$CMAKE_PREFIX_PATH' >> ~/.bashrc

source ~/.bashrc


# Install libfranka and associated packages
# Instructions from https://frankaemika.github.io/docs/franka_ros2.htmls
sudo apt update
sudo apt install -y libpoco-dev libeigen3-dev

cd workspace/panda
git clone https://github.com/frankaemika/libfranka.git --recursive

cd libfranka
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF  ..
cmake --build . -j$(nproc)
cpack -G DEB
sudo dpkg -i libfranka-*.deb


# Setup bash
echo "export RCUTILS_COLORIZED_OUTPUT=1" >> ~/.bashrc
echo "export LC_NUMERIC=en_US.UTF-8" >> ~/.bashrc
source ~/.bashrc


# Setup From Source
sudo apt install -y \
ros-humble-ament-cmake \
ros-humble-ament-cmake-clang-format \
ros-humble-angles \
ros-humble-ros2-controllers \
ros-humble-ros2-control \
ros-humble-ros2-control-test-assets \
ros-humble-controller-manager \
ros-humble-control-msgs \
ros-humble-control-toolbox \
ros-humble-generate-parameter-library \
ros-humble-joint-state-publisher \
ros-humble-joint-state-publisher-gui \
ros-humble-moveit \
ros-humble-pinocchio \
ros-humble-realtime-tools \
ros-humble-xacro \
ros-humble-hardware-interface \
ros-humble-ros-gz \
python3-colcon-common-extensions

# Build repo
cd /workspace/panda
mkdir src
source /opt/ros/humble/setup.bash
git clone https://github.com/frankaemika/franka_ros2.git src/franka_ros2
git clone https://github.com/frankaemika/franka_description.git src/franka_description
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
source install/setup.sh  # Need to do this every time in panda directory




```

## Run  Simulation

```bash
ros2 launch franka_fr3_moveit_config moveit.launch.py robot_ip:=dont-care use_fake_hardware:=true
```
NEED TO UNLOCK ROBOT and activate FCI
## Run Robot 
```bash
ros2 launch franka_fr3_moveit_config moveit.launch.py robot_ip:=192.168.1.2  # THIS IS CONTROLLER IP NOT ROBOT IP
```


## Useful Commands

```bash
# Open multiple terminals
docker exec -it  91b7a6b27900 bash

# Show running docker containers
docker ps



# Run existing image
sudo docker run -it --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace/panda --net host franka_ros2 bash
```





