# FER Panda FCI Instruction 
For running the FER Panda bot with code, the minimum you need to install is libfranka. libfranka requires a realtime-kernel patch on your host machine (even if you are running on a container bc the container shares a kernel with the host). If you want to use ROS, you'll also need to also install franka_ros.

## Setup
These are instructions for software setup for interfacing with the Franka Emika Robot (FER) Panda. The instructions assume you have set up the robot and can interface with it using the Franka Desktop. If that is not the case, reference your user manual or follow the start of [this viedo](https://youtu.be/91wFDNHVXI4?si=_RWVrXJ0wC-qe6NI).

Here is what we start with:
* Robot system version: 4.2.2 (FER pandas)
* Robot / Gripper Server version: 5/3
* Ubuntu version: 20.04.6


Here is what we are going to install:
* ROS 1 version: Noetic
* libfranka version: 0.9.2
* franka_ros version: 0.9.1

If you have a different versions, reference the [compatible versions](https://frankaemika.github.io/docs/compatibility.html). WARNING: version compatibility is SUPER important.



### Base environment.
Make sure you are running Ubuntu 20.04 (Focal Fossil).


### Real time Kernel
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

###  libfranka 
Build from source using the following commands bc you will need versions that are compatible with the Robots 4.2.2 version. Commands adapted from [here](https://frankaemika.github.io/docs/installation_linux.html).

```bash
sudo apt update

sudo apt remove "*libfranka*"


sudo apt install build-essential cmake git libpoco-dev libeigen3-dev

git clone --recursive https://github.com/frankaemika/libfranka 
cd libfranka

git checkout 0.9.2
git submodule update

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF ..
cmake --build .
cpack -G DEB
sudo dpkg -i libfranka-0.9.2-x86_64.deb

```


###  franka_ros (only needed if you want to use ROS)
Install ROS noetic using [these instructions](https://wiki.ros.org/noetic/Installation/Ubuntu).

```bash
sudo apt update

sudo apt install ros-noetic-rosbash

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
sudo apt-get install ros-noetic-eigen-conversions
sudo apt install ros-noetic-boost-sml


cd ../..  # go to ros_noetic directory
mkdir -p catkin_ws/src
cd catkin_ws
source /opt/ros/noetic/setup.sh
catkin_init_workspace src

git clone --recursive https://github.com/frankaemika/franka_ros src/franka_ros
git checkout 0.9.1 # TODO, 0.8.2

sudo apt install python3-rosdep
sudo rosdep init 
sudo rosdep update
sudo rosdep install --from-paths src --ignore-src --rosdistro noetic -y --skip-keys libfranka


catkin_make -DCMAKE_BUILD_TYPE=Release  # Make sure you're in catkin_ws directory
source devel/setup.sh

```

## Running
Before you can run anything with code, make sure joints are unlocked and FCI Control is enabled in the Franka desktop ( our robot is [192.168.1.2](https://192.168.1.2/desk/)). Directions for doing that are [here](https://youtu.be/91wFDNHVXI4?si=4-ZArdrxOMAiCc5H&t=484). WARNING: I could not get Firefox to access the desk because of security reasons. However I could access through chrome once I clicked "Advanced" > "Proceed to 192.168.1.2 (unsafe)".

### Running libfranka w/out ROS

```bash
cd libfranka/build/examples
./echo_robot_state 192.168.1.2 # Tests comms (does not require real time kernel)

./communication_test 192.168.1.2 # Tests realtime kernel and robot by moving bot
```

### Running w/ ROS

```bash
# comms test
rosrun libfranka echo_robot_state 192.168.1.2 # Tests comms (does not require real time kernel) 
sudo communication_test 192.168.1.2  # Tests realtime kernel and robot by moving bot
```

## Running Notes
### libfranka 
If you make changes to libfranka, you'll need to rerun:

``` bash
cd libfranka/build  # Get to libfranka/build directory (may need to use different command)
rm -r * # For cleaning the cache to avoid errors of builds on different machines
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF .. 
cmake --build .
cpack -G DEB
sudo dpkg -i libfranka-0.9.2-x86_64.deb
```

### frank_ros
Every time you open a new terminal, you'll need to run:
```bash
source /opt/ros/noetic/setup.sh

cd ros_noetics/catkin_ws  # May need to use other command to get to catkin_ws
source devel/setup.sh
```

If you make changes, you'll need to rerun:

``` bash
# For changes made to libfranka
cd libfranka/build  # Get to libfranka/build directory (may need to use different command)
rm -r * # For cleaning the cache to avoid errors of builds on different machines
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF .. 
cmake --build .
cpack -G DEB
sudo dpkg -i libfranka-0.9.2-x86_64.deb
# For changes made to catkin_ws
cd ../../catkin_ws
catkin_make -DCMAKE_BUILD_TYPE=Release # Make sure you're in catkin_ws directory
#/home/hcilab/Desktop/github/panda/ros_noetic/libfranka/build
source devel/setup.sh
```


## Panda Notes
Panda limits for motion are located [here](https://frankaemika.github.io/docs/control_parameters.html#limits-for-panda).
If you go beyond them, you will get the error `libfranka: Move command aborted: motion aborted by reflex! ["cartesian_reflex"]`.
After that any other command will throw the error `libfranka: Set Joint Impedance command rejected: command not possible in the current mode ("Reflex")!` **UNTIL  the joints are locked and unlocked**.

