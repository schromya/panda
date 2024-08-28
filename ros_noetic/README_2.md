
## Setup
These are instructions for software setup for interfacing with the Franka Emika Robot (FER) Panda, version 4.2.2.

### Real time Kernel
Make sure you are running Ubuntu 20.04 (Focal Fossil).
Install ROS noetic using [these instructions](https://wiki.ros.org/noetic/Installation/Ubuntu).

Set up realtime kernel by following [these instructions](https://frankaemika.github.io/docs/installation_linux.html#setting-up-the-real-time-kernel) (I would run them all in your Downloads directory).
* For the curl step, I am running Kernel 5.17.0 so I ran:
```bash
curl -SLO https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.17.1.tar.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.17.1.tar.sign
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/5.17/patch-5.17.1-rt17.patch.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/5.17/patch-5.17.1-rt17.patch.sign
```

* In the `make menuconfig` step, if you can not see the option to enable  "Fully Preemptible Kernel (Real-Time)", you need to enable General Setup -> Embedded System, save, and then try again ([source](https://unix.stackexchange.com/questions/582075/trouble-selecting-fully-preemptible-kernel-real-time-when-configuring-compil))

* If you run into errors you can't see when compiling the kernel, run the verbose version on a single core: `make V=1 deb-pkg` (warning: this will take forever) and reference (this source)[https://gist.github.com/FrankieWOO/3d3b04ef1de1817142c8131708cf6dee] for error messages.

### Building libfranka and franka_ros
Build from source using the following commands bc you will need versions that are compatible with the Robots 4.2.2 version. Commands adapted from [here](https://frankaemika.github.io/docs/installation_linux.html).

```bash
sudo apt update

sudo apt install ros-noetic-rosbash

sudo apt remove "*libfranka*"
sudo apt-get update


sudo apt install build-essential cmake git libpoco-dev libeigen3-dev
sudo apt-get install ros-noetic-actionlib
sudo apt-get install ros-noetic-combined-robot-hw
sudo apt-get install ros-noetic-joint-limits-interface
sudo apt-get install ros-noetic-controller-manager
sudo apt-get install ros-noetic-realtime-tools
sudo apt-get install ros-noetic-tf
sudo apt-get install ros-noetic-dynamic-reconfigure
sudo apt-get install ros-noetic-tf-conversions
sudo apt-get install ros-noetic-gazebo-ros-control
sudo apt-get install ros-noetic-kdl-parser


git clone --recursive https://github.com/frankaemika/libfranka # only for panda
cd libfranka

git checkout 0.9.2
git submodule update

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF ..
cmake --build .

# cpack -G DEB
# sudo dpkg -i libfranka*.deb


cd ../..  # go to ros_noetic directory
mkdir -p catkin_ws/src
cd catkin_ws
source /opt/ros/noetic/setup.sh
catkin_init_workspace src

git clone --recursive https://github.com/frankaemika/franka_ros src/franka_ros # Newest version should be compatible so don't need to checkout specific version
git checkout 0.8.0

sudo apt install python3-rosdep
sudo rosdep init 
sudo rosdep update
sudo rosdep install --from-paths src --ignore-src --rosdistro noetic -y --skip-keys libfranka


catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=../libranka/build  # Make sure you're in catkin_ws directory
source devel/setup.sh

```


```bash
# Set up realtime configs
sudo addgroup realtime
sudo usermod -a -G realtime $(whoami)

echo "@realtime soft rtprio 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime soft priority 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime soft memlock 102400" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard rtprio 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard priority 99" | sudo tee -a /etc/security/limits.conf
echo "@realtime hard memlock 102400" | sudo tee -a /etc/security/limits.conf

```

## Running Libfranka w/out ROS
```bash
cd libfranka/build/examples
./echo_robot_state 192.168.1.2  # YAYA THIS WORKED

# OR
./communication_test 192.168.1.2
## BUT GOT THE FOLLOWING :(
libfranka: Running kernel does not have realtime capabilities.
```


## Running w/ ROS
Make sure joints are unlocked and FCI Control is enabled in desktop ([192.168.1.2](https://192.168.1.2/desk/))
```bash
# comms test
sudo communication_test 192.168.1.2
rosrun libfranka echo_robot_state 192.168.1.2
```


## Notes
Every time you open a new terminal, you'll need to run:
```bash
source /opt/ros/noetic/setup.sh
source devel/setup.sh  # NOT SURE ABOUT THIS ONE
```

If you make changes to libfranka, you'll need to rerun:

``` bash
cd libfranka/build  # Get to libfranka/build directory (may need to use different command)
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF ..
cmake --build .

cd ../../catkin_ws
catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=../libranka/build  # Make sure you're in catkin_ws directory
source devel/setup.sh
```


If you make changes to catkin_ws, you'll need to rerun:
``` bash
cd catkin_ws # Get to catkin_ws directory (may need to use different command)
catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=../libranka/build  
source devel/setup.sh
```


Error messages:
https://gist.github.com/FrankieWOO/3d3b04ef1de1817142c8131708cf6dee

find_package(Franka ${libfranka_VERSION} EXACT REQUIRED)

