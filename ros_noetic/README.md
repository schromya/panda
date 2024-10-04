# FER Panda FCI Instruction 
For running the FER Panda bot with code, the minimum you need to install is libfranka. If you want to use ROS as well, you also need the franka_ros library.

The following instructions are for setting up FCI control on the Franka Emika Robot (FER) Panda using libfranka and franka_ros. These instructions allow you to launch a container so that you don't have to face most of the pain and suffering I went through in the installation process. However, you will still nee to install a Real-Time kernel patch (required by libfranka) on your host computer because containers share the host's machines kernel.

## Setup
These are instructions for software setup for interfacing with the Franka Emika Robot (FER) Panda. The instructions assume you have set up the robot and can interface with it using the Franka Desktop. If that is not the case, reference your user manual or follow the start of [this viedo](https://youtu.be/91wFDNHVXI4?si=_RWVrXJ0wC-qe6NI).

Here is what you need to start with:
* Robot system version: 4.2.2 (FER pandas)
* Robot / Gripper Server version: 5/3
* Ubuntu version: 20.04.06 Focal Fossil (any 20.04 version should work fine)
* Docker Containers. [Here](https://docs.docker.com/engine/install/ubuntu/) are the instructions to install Docker on Ubuntu if you need to.


Here is what you are going to run on a Docker Container:
* ROS 1 version: Noetic
* libfranka version: 0.9.2
* franka_ros version: 0.9.1

If you have a different versions of the above robot software, reference the [compatible versions](https://frankaemika.github.io/docs/compatibility.html). WARNING: version compatibility is SUPER important.


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


### Building and Starting the container
``` bash
# Allow Display forwarding
xhost +local:

# Compile Kernel
cd ros_noetic
sudo docker build -t panda-container .

# Start the container with real-time kernel privelages, mount onto the current directory, and allow display forwarding
sudo docker run -it --privileged --cap-add=SYS_NICE --env DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $(pwd):/workspace --net=host panda-container


# Now the container should be running and you should be in the container's terminal
# Prepare the ROS workspace
cd src/relaxed_ik_ros1/relaxed_ik_core
cargo build
cd /workspace
source /opt/ros/noetic/setup.sh
rm -f src/CMakeLists.txt 
catkin_init_workspace src
catkin_make
source devel/setup.sh
```

## Running
Before you can run anything with code, make sure joints are unlocked and FCI Control is enabled in the Franka desktop ( our robot is [192.168.1.2](https://192.168.1.2/desk/)). Directions for doing that are [here](https://youtu.be/91wFDNHVXI4?si=4-ZArdrxOMAiCc5H&t=484). WARNING: I could not get Firefox to access the desk because of security reasons. However I could access through chrome once I clicked "Advanced" > "Proceed to 192.168.1.2 (unsafe)".

You should still be in the container's terminal to run the following commands. Make sure to subsitute 192.168.1.2 with your robot's IP.
```bash
sudo communication_test 192.168.1.2  # Tests realtime kernel and robot by moving bot
```

###  Notes

Every time you open a new terminal, you'll need to run:
```bash
source /opt/ros/noetic/setup.sh

cd catkin_ws  # May need to use other command to get to this directory
source devel/setup.sh
```

If you make changes, in catkin_ws, you'll need to run:

```bash
cd catkin_ws # May need to use other command to get to this directory
catkin_make -DCMAKE_BUILD_TYPE=Release  # Make sure you're in catkin_ws directory
source devel/setup.sh
```

If you make changes to libfranka (which you probably should not be doing), you'll need to run:
``` bash
cd libfranka/build  # May need to use other command to get to this directory
rm -r * # For cleaning the cache to avoid errors of builds on different machines
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF .. 
cmake --build .
cpack -G DEB
sudo dpkg -i libfranka-0.9.2-x86_64.deb

```

## Troubleshooting + Tips
Check the "Panda Notes" section at the bottom of [setup.md](/setup.md) for tips you should know about Panda.