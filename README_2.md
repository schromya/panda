Install ROS noetic https://wiki.ros.org/noetic/Installation/Ubuntu

Build from source: https://frankaemika.github.io/docs/installation_linux.html
```bash
sudo apt remove "*libfranka*"

sudo apt install build-essential cmake git libpoco-dev libeigen3-dev

git clone --recursive https://github.com/frankaemika/libfranka # only for panda
cd libfranka

git checkout 0.9.1
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

sudo apt install python3-rosdep2

rosdep install --from-paths src --ignore-src --rosdistro noetic -y --skip-keys libfranka
rosdeb update

catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=../libranka/build 
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

```bash
# comms test
sudo communication_test 192.168.1.2

````
