
## Setup
Make sure you are running Ubuntu 20.04 (Focal Fossil)
Install ROS noetic using [these instructions](https://wiki.ros.org/noetic/Installation/Ubuntu)

Set up realtime kernel using Ubuntu Pro by  following [these instructions](https://frankaemika.github.io/docs/installation_linux.html) located in the second section. For the curl portion, I am running Kernel 5.17.0 so I ran:
```bash
curl -SLO https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.17.1.tar.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.17.1.tar.sign
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/5.17/patch-5.17.1-rt17.patch.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/5.17/patch-5.17.1-rt17.patch.sign
```

Build from source using the following commands. Sourced from [here](https://frankaemika.github.io/docs/installation_linux.html)
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


## Running
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




find_package(Franka ${libfranka_VERSION} EXACT REQUIRED)




  LD [M]  sound/soc/codecs/snd-soc-cs42l56.ko
  LD [M]  sound/soc/codecs/snd-soc-cs42l73.ko
  LD [M]  sound/soc/codecs/snd-soc-cs42xx8-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-cs42xx8.ko
  LD [M]  sound/soc/codecs/snd-soc-cs43130.ko
  LD [M]  sound/soc/codecs/snd-soc-cs4341.ko
  LD [M]  sound/soc/codecs/snd-soc-cs4349.ko
  LD [M]  sound/soc/codecs/snd-soc-cs53l30.ko
  LD [M]  sound/soc/codecs/snd-soc-cx2072x.ko
  LD [M]  sound/soc/codecs/snd-soc-da7213.ko
  LD [M]  sound/soc/codecs/snd-soc-da7219.ko
  LD [M]  sound/soc/codecs/snd-soc-dmic.ko
  LD [M]  sound/soc/codecs/snd-soc-es7134.ko
  LD [M]  sound/soc/codecs/snd-soc-es7241.ko
  LD [M]  sound/soc/codecs/snd-soc-es8316.ko
  LD [M]  sound/soc/codecs/snd-soc-es8328-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-es8328-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-es8328.ko
  LD [M]  sound/soc/codecs/snd-soc-gtm601.ko
  LD [M]  sound/soc/codecs/snd-soc-hdac-hda.ko
  LD [M]  sound/soc/codecs/snd-soc-hdac-hdmi.ko
  LD [M]  sound/soc/codecs/snd-soc-hdmi-codec.ko
  LD [M]  sound/soc/codecs/snd-soc-ics43432.ko
  LD [M]  sound/soc/codecs/snd-soc-inno-rk3036.ko
  LD [M]  sound/soc/codecs/snd-soc-lpass-rx-macro.ko
  LD [M]  sound/soc/codecs/snd-soc-lpass-tx-macro.ko
  LD [M]  sound/soc/codecs/snd-soc-lpass-va-macro.ko
  LD [M]  sound/soc/codecs/snd-soc-lpass-wsa-macro.ko
  LD [M]  sound/soc/codecs/snd-soc-max9759.ko
  LD [M]  sound/soc/codecs/snd-soc-max98088.ko
  LD [M]  sound/soc/codecs/snd-soc-max98090.ko
  LD [M]  sound/soc/codecs/snd-soc-max98357a.ko
  LD [M]  sound/soc/codecs/snd-soc-max98373-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-max98373-sdw.ko
  LD [M]  sound/soc/codecs/snd-soc-max98373.ko
  LD [M]  sound/soc/codecs/snd-soc-max98390.ko
  LD [M]  sound/soc/codecs/snd-soc-max98504.ko
  LD [M]  sound/soc/codecs/snd-soc-max98520.ko
  LD [M]  sound/soc/codecs/snd-soc-max9860.ko
  LD [M]  sound/soc/codecs/snd-soc-max9867.ko
  LD [M]  sound/soc/codecs/snd-soc-max98927.ko
  LD [M]  sound/soc/codecs/snd-soc-msm8916-analog.ko
  LD [M]  sound/soc/codecs/snd-soc-msm8916-digital.ko
  LD [M]  sound/soc/codecs/snd-soc-mt6351.ko
  LD [M]  sound/soc/codecs/snd-soc-mt6358.ko
  LD [M]  sound/soc/codecs/snd-soc-mt6660.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8315.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8540.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8810.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8821.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8822.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8824.ko
  LD [M]  sound/soc/codecs/snd-soc-nau8825.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm1681.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm1789-codec.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm1789-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm179x-codec.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm179x-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm179x-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm186x-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm186x-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm186x.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3060-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3060-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3060.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3168a-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3168a-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm3168a.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm5102a.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm512x-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm512x-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-pcm512x.ko
  LD [M]  sound/soc/codecs/snd-soc-rk3328.ko
  LD [M]  sound/soc/codecs/snd-soc-rl6231.ko
  LD [M]  sound/soc/codecs/snd-soc-rl6347a.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1011.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1015.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1015p.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1019.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1308-sdw.ko
  LD [M]  sound/soc/codecs/snd-soc-rt1316-sdw.ko
  LD [M]  sound/soc/codecs/snd-soc-rt286.ko
  LD [M]  sound/soc/codecs/snd-soc-rt298.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5514-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5514.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5616.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5631.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5640.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5645.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5651.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5659.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5660.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5663.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5670.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5677-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5677.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5682-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5682-sdw.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5682.ko
  LD [M]  sound/soc/codecs/snd-soc-rt5682s.ko
  LD [M]  sound/soc/codecs/snd-soc-rt700.ko
  LD [M]  sound/soc/codecs/snd-soc-rt711-sdca.ko
  LD [M]  sound/soc/codecs/snd-soc-rt711.ko
  LD [M]  sound/soc/codecs/snd-soc-rt715-sdca.ko
  LD [M]  sound/soc/codecs/snd-soc-rt715.ko
  LD [M]  sound/soc/codecs/snd-soc-rt9120.ko
  LD [M]  sound/soc/codecs/snd-soc-sgtl5000.ko
  LD [M]  sound/soc/codecs/snd-soc-si476x.ko
  LD [M]  sound/soc/codecs/snd-soc-sigmadsp-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-sigmadsp-regmap.ko
  LD [M]  sound/soc/codecs/snd-soc-sigmadsp.ko
  LD [M]  sound/soc/codecs/snd-soc-simple-amplifier.ko
  LD [M]  sound/soc/codecs/snd-soc-simple-mux.ko
  LD [M]  sound/soc/codecs/snd-soc-spdif-rx.ko
  LD [M]  sound/soc/codecs/snd-soc-spdif-tx.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm2305.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm2518.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm2602-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm2602-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm2602.ko
  LD [M]  sound/soc/codecs/snd-soc-ssm4567.ko
  LD [M]  sound/soc/codecs/snd-soc-sta32x.ko
  LD [M]  sound/soc/codecs/snd-soc-sta350.ko
  LD [M]  sound/soc/codecs/snd-soc-sti-sas.ko
  LD [M]  sound/soc/codecs/snd-soc-tas2552.ko
  LD [M]  sound/soc/codecs/snd-soc-tas2562.ko
  LD [M]  sound/soc/codecs/snd-soc-tas2764.ko
  LD [M]  sound/soc/codecs/snd-soc-tas2770.ko
  LD [M]  sound/soc/codecs/snd-soc-tas5086.ko
  LD [M]  sound/soc/codecs/snd-soc-tas571x.ko
  LD [M]  sound/soc/codecs/snd-soc-tas5720.ko
  LD [M]  sound/soc/codecs/snd-soc-tas6424.ko
  LD [M]  sound/soc/codecs/snd-soc-tda7419.ko
  LD [M]  sound/soc/codecs/snd-soc-tfa9879.ko
  LD [M]  sound/soc/codecs/snd-soc-tfa989x.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320adc3xxx.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320adcx140.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic23-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic23-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic23.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic31xx.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic32x4-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic32x4-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic32x4.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic3x-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic3x-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-tlv320aic3x.ko
  LD [M]  sound/soc/codecs/snd-soc-tpa6130a2.ko
  LD [M]  sound/soc/codecs/snd-soc-ts3a227e.ko
  LD [M]  sound/soc/codecs/snd-soc-tscs42xx.ko
  LD [M]  sound/soc/codecs/snd-soc-tscs454.ko
  LD [M]  sound/soc/codecs/snd-soc-uda1334.ko
  LD [M]  sound/soc/codecs/snd-soc-wcd-mbhc.ko
  LD [M]  sound/soc/codecs/snd-soc-wcd9335.ko
  LD [M]  sound/soc/codecs/snd-soc-wcd934x.ko
  LD [M]  sound/soc/codecs/snd-soc-wcd938x-sdw.ko
  LD [M]  sound/soc/codecs/snd-soc-wcd938x.ko
  LD [M]  sound/soc/codecs/snd-soc-wm-adsp.ko
  LD [M]  sound/soc/codecs/snd-soc-wm5102.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8510.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8523.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8524.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8580.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8711.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8728.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8731.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8737.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8741.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8750.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8753.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8770.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8776.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8782.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8804-i2c.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8804.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8903.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8804-spi.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8904.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8962.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8960.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8974.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8978.ko
  LD [M]  sound/soc/codecs/snd-soc-wsa881x.ko
  LD [M]  sound/soc/codecs/snd-soc-zl38060.ko
  LD [M]  sound/soc/codecs/snd-soc-wm8985.ko
  LD [M]  sound/soc/dwc/designware_i2s.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-asrc.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-audmix.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-esai.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-micfil.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-easrc.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-mqs.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-rpmsg.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-sai.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-ssi.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-spdif.ko
  LD [M]  sound/soc/fsl/snd-soc-fsl-xcvr.ko
  LD [M]  sound/soc/fsl/snd-soc-imx-audmux.ko
  LD [M]  sound/soc/generic/snd-soc-simple-card-utils.ko
  LD [M]  sound/soc/generic/snd-soc-simple-card.ko
  LD [M]  sound/soc/hisilicon/hi6210-i2s.ko
  LD [M]  sound/soc/img/img-i2s-in.ko
  LD [M]  sound/soc/img/img-i2s-out.ko
  LD [M]  sound/soc/img/img-parallel-out.ko
  LD [M]  sound/soc/img/img-spdif-in.ko
  LD [M]  sound/soc/img/img-spdif-out.ko
  LD [M]  sound/soc/img/pistachio-internal-dac.ko
  LD [M]  sound/soc/intel/atom/snd-soc-sst-atom-hifi2-platform.ko
  LD [M]  sound/soc/intel/atom/sst/snd-intel-sst-acpi.ko
  LD [M]  sound/soc/intel/atom/sst/snd-intel-sst-core.ko
  LD [M]  sound/soc/intel/atom/sst/snd-intel-sst-pci.ko
  LD [M]  sound/soc/intel/boards/snd-skl_nau88l25_max98357a.ko
  LD [M]  sound/soc/intel/boards/snd-soc-cml_rt1011_rt5682.ko
  LD [M]  sound/soc/intel/boards/snd-soc-ehl-rt5660.ko
  LD [M]  sound/soc/intel/boards/snd-soc-intel-hda-dsp-common.ko
  LD [M]  sound/soc/intel/boards/snd-soc-intel-sof-maxim-common.ko
  LD [M]  sound/soc/intel/boards/snd-soc-kbl_da7219_max98357a.ko
  LD [M]  sound/soc/intel/boards/snd-soc-kbl_da7219_max98927.ko
  LD [M]  sound/soc/intel/boards/snd-soc-kbl_rt5660.ko
  LD [M]  sound/soc/intel/boards/snd-soc-kbl_rt5663_max98927.ko
  LD [M]  sound/soc/intel/boards/snd-soc-kbl_rt5663_rt5514_max98927.ko
  LD [M]  sound/soc/intel/boards/snd-soc-skl_hda_dsp.ko
  LD [M]  sound/soc/intel/boards/snd-soc-skl_nau88l25_ssm4567.ko
  LD [M]  sound/soc/intel/boards/snd-soc-skl_rt286.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sof_cs42l42.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sof_da7219_max98373.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sof_es8336.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sof_nau8825.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sof_rt5682.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bdw-rt5650-mach.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bdw-rt5677-mach.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-broadwell.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bxt-da7219_max98357a.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bxt-rt298.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-byt-cht-cx2072x.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-byt-cht-da7213.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-byt-cht-es8316.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bytcr-rt5640.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bytcr-rt5651.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-bytcr-wm5102.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-cht-bsw-max98090_ti.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-cht-bsw-nau8824.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-cht-bsw-rt5645.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-cht-bsw-rt5672.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-glk-rt5682_max98357a.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-haswell.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-sof-pcm512x.ko
  LD [M]  sound/soc/intel/boards/snd-soc-sst-sof-wm8804.ko
  LD [M]  sound/soc/intel/catpt/snd-soc-catpt.ko
  LD [M]  sound/soc/intel/common/snd-soc-acpi-intel-match.ko
  LD [M]  sound/soc/intel/common/snd-soc-sst-dsp.ko
  LD [M]  sound/soc/intel/common/snd-soc-sst-ipc.ko
  LD [M]  sound/soc/intel/skylake/snd-soc-skl-ssp-clk.ko
  LD [M]  sound/soc/intel/skylake/snd-soc-skl.ko
  LD [M]  sound/soc/snd-soc-acpi.ko
  LD [M]  sound/soc/snd-soc-core.ko
  LD [M]  sound/soc/sof/amd/snd-sof-amd-acp.ko
  LD [M]  sound/soc/sof/amd/snd-sof-amd-renoir.ko
  LD [M]  sound/soc/sof/intel/snd-sof-acpi-intel-bdw.ko
  LD [M]  sound/soc/sof/intel/snd-sof-acpi-intel-byt.ko
  LD [M]  sound/soc/sof/intel/snd-sof-intel-atom.ko
  LD [M]  sound/soc/sof/intel/snd-sof-intel-hda-common.ko
  LD [M]  sound/soc/sof/intel/snd-sof-intel-hda.ko
  LD [M]  sound/soc/sof/intel/snd-sof-pci-intel-apl.ko
  LD [M]  sound/soc/sof/intel/snd-sof-pci-intel-cnl.ko
  LD [M]  sound/soc/sof/intel/snd-sof-pci-intel-icl.ko
  LD [M]  sound/soc/sof/intel/snd-sof-pci-intel-tgl.ko
  LD [M]  sound/soc/sof/intel/snd-sof-pci-intel-tng.ko
  LD [M]  sound/soc/sof/snd-sof-acpi.ko
  LD [M]  sound/soc/sof/snd-sof-pci.ko
  LD [M]  sound/soc/sof/snd-sof.ko
  LD [M]  sound/soc/sof/xtensa/snd-sof-xtensa-dsp.ko
  LD [M]  sound/soc/xilinx/snd-soc-xlnx-formatter-pcm.ko
  LD [M]  sound/soc/xilinx/snd-soc-xlnx-i2s.ko
  LD [M]  sound/soc/xilinx/snd-soc-xlnx-spdif.ko
  LD [M]  sound/soc/xtensa/snd-soc-xtfpga-i2s.ko
  LD [M]  sound/soundcore.ko
  LD [M]  sound/synth/emux/snd-emux-synth.ko
  LD [M]  sound/synth/snd-util-mem.ko
  LD [M]  sound/usb/6fire/snd-usb-6fire.ko
  LD [M]  sound/usb/bcd2000/snd-bcd2000.ko
  LD [M]  sound/usb/caiaq/snd-usb-caiaq.ko
  LD [M]  sound/usb/hiface/snd-usb-hiface.ko
  LD [M]  sound/usb/line6/snd-usb-line6.ko
  LD [M]  sound/usb/line6/snd-usb-pod.ko
  LD [M]  sound/usb/line6/snd-usb-podhd.ko
  LD [M]  sound/usb/line6/snd-usb-toneport.ko
  LD [M]  sound/usb/line6/snd-usb-variax.ko
  LD [M]  sound/usb/misc/snd-ua101.ko
  LD [M]  sound/usb/snd-usb-audio.ko
  LD [M]  sound/usb/snd-usbmidi-lib.ko
  LD [M]  sound/usb/usx2y/snd-usb-us122l.ko
  LD [M]  sound/usb/usx2y/snd-usb-usx2y.ko
  LD [M]  sound/virtio/virtio_snd.ko
  LD [M]  sound/x86/snd-hdmi-lpe-audio.ko
  LD [M]  sound/xen/snd_xen_front.ko
  LD [M]  virt/lib/irqbypass.ko
make[2]: *** [debian/rules:7: build-arch] Error 2
dpkg-buildpackage: error: debian/rules binary subprocess returned exit status 2
make[1]: *** [scripts/Makefile.package:77: deb-pkg] Error 2
make: *** [Makefile:1539: deb-pkg] Error 2
hcilab@hcilab-G7-7590:~/Downloads/linux-5.17