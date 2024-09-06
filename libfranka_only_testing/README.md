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


he following packages were automatically installed and are no longer required:
  adium-theme-ubuntu command-not-found-data cython cython3 dh-python evemu-tools evtest example-content fltk1.3-doc fluid fwupdate geoip-database gir1.2-goa-1.0
  gir1.2-gtksource-3.0 gir1.2-mutter-2 gnome-software-common gnome-user-guide guile-2.0-libs hddtemp ifupdown imagemagick-6-common iputils-arping joystick libaccinj64-9.1
  libappstream-glib8 libapt-pkg-perl libargon2-0 libarmadillo8 libart-2.0-2 libasan0 libassimp4 libb-hooks-op-check-perl libboost-atomic1.65.1 libboost-container1.65.1
  libboost-context1.65.1 libboost-coroutine1.65.1 libboost-date-time1.65.1 libboost-filesystem1.65.1 libboost-locale1.65.1 libboost-math1.65.1 libboost-python1.65.1
  libboost-serialization1.65.1 libboost-stacktrace1.65.1 libboost-system1.65.1 libboost-test1.65.1 libboost-thread1.65.1 libboost-type-erasure1.65.1 libboost-wave1.65.1
  libbrlapi0.6 libc++1 libc++abi1 libcapture-tiny-perl libcdio17 libcgi-fast-perl libcgi-pm-perl libcharls1 libclang1-6.0 libclass-method-modifiers-perl
  libclass-xsaccessor-perl libclone-perl libcrystalhd3 libcublas9.1 libcudart9.1 libcuinj64-9.1 libcurand9.1 libcusparse9.1 libdevel-size-perl libdns-export1100 libdns1100
  libdrm-dev libemail-valid-perl libevemu3 libevent-2.1-6 libexempi3 libexporter-tiny-perl libfcgi-perl libfile-copy-recursive-perl libfile-find-rule-perl libfltk-cairo1.3
  libfltk-forms1.3 libfltk-gl1.3 libfltk-images1.3 libfltk1.3 libfltk1.3-dev libfont-ttf-perl libfreenect-dev libfreenect0.5 libgcc-4.8-dev libgeoip1 libgeos-3.6.2
  libgfortran4 libgl2ps-dev libglvnd-core-dev libgmime-3.0-0 libgnome-desktop-3-17 libgtksourceview-3.0-1 libgtksourceview-3.0-common libgutenprint2 libgvc6-plugins-gtk
  libgweather-3-15 libhogweed4 libhunspell-1.6-0 libhwloc5 libicu-le-hb-dev libicu-le-hb0 libicu60 libiculx60 libignition-cmake-dev libignition-common
  libignition-fuel-tools1-1 libignition-math4 libilmbase12 libindicator3-7 libio-pty-perl libio-string-perl libip4tc0 libipc-run-perl libiptc0 libisc-export169 libisc169
  libisl19 libjs-jquery-ui libjs-sphinxdoc libjson-c3 liblist-compare-perl libllvm10:i386 liblouis14 libminiupnpc10 libmng2 libmutter-2-0 libmysofa0 libnet-dns-perl
  libnet-dns-sec-perl libnet-domain-tld-perl libnet-ip-perl libnetcdf-cxx-legacy-dev libnetpbm10 libnettle6 libnppc9.1 libnppial9.1 libnppicc9.1 libnppicom9.1 libnppidei9.1
  libnppif9.1 libnppim9.1 libnppisu9.1 libnppitc9.1 libnpps9.1 libnss-myhostname libntfs-3g88 libnumber-compare-perl libnvblas9.1 libnvrtc9.1 liboauth0 libogg-dev
  libopenal-dev libopencv-core3.2 libopencv-flann3.2 libopencv-imgproc3.2 libopencv-shape3.2 libopencv-video3.2 libopenni-dev libopenni0 libopenni2-0 libopenni2-dev
  libpackage-stash-xs-perl libpath-tiny-perl libpciaccess-dev libpcl-apps1.10 libpcl-common1.10 libpcl-common1.8 libpcl-dev libpcl-features1.10 libpcl-filters1.10
  libpcl-io1.10 libpcl-kdtree1.10 libpcl-keypoints1.10 libpcl-ml1.10 libpcl-ml1.8 libpcl-octree1.10 libpcl-octree1.8 libpcl-outofcore1.10 libpcl-outofcore1.8
  libpcl-people1.10 libpcl-recognition1.10 libpcl-registration1.10 libpcl-sample-consensus1.10 libpcl-sample-consensus1.8 libpcl-search1.10 libpcl-segmentation1.10
  libpcl-stereo1.10 libpcl-stereo1.8 libpcl-surface1.10 libpcl-tracking1.10 libpcl-visualization1.10 libperl4-corelibs-perl libperlio-gzip-perl libplymouth4 libpococrypto50
  libpocofoundation50 libpocojson50 libpoconet50 libpocoredis50 libpocoxml50 libpoppler73 libprotobuf-lite10 libprotobuf10 libprotoc10 libpython-all-dev libqpdf21
  libqt5designercomponents5 libqt5positioning5 libqt5quickparticles5 libqt5quickshapes5 libqt5quicktest5 libqt5quickwidgets5 libqt5sensors5 libqt5webchannel5 libqt5webkit5
  libqt5webkit5-dev libqtpropertybrowser4 libraw16 libreadonly-perl libref-util-xs-perl libreoffice-avmedia-backend-gstreamer librole-tiny-perl libruby2.5 libsane1
  libsdformat6 libsdl1.2debian libsereal-decoder-perl libsereal-encoder-perl libsereal-perl libspnav-dev libstrictures-perl libstruct-dumb-perl
  libsub-exporter-progressive-perl libsub-quote-perl libtest-refcount-perl libtext-glob-perl libtext-levenshtein-perl libtheora-dev libtinfo5:i386 libturbojpeg
  libturbojpeg0-dev libtype-tiny-xs-perl libusbmuxd4 libvariable-magic-perl libvpx5 libvtk7-dev libvtk7-java libvtk7-jni libvtk7-qt-dev libvtk7.1p libvtk7.1p-qt
  libx11-xcb-dev libx264-152 libxcb-glx0-dev libxcb-randr0-dev libxdamage1:i386 libxdot4 libxml-namespacesupport-perl libxml-sax-base-perl libxml-writer-perl libxmlb1
  libxshmfence-dev libxss-dev libxxf86vm-dev libyaml-libyaml-perl libzeitgeist-2.0-0 libzip4 linux-headers-5.15.0-15.1-liquorix-amd64 linux-headers-generic-hwe-18.04
  linux-image-5.15.0-15.1-liquorix-amd64 linux-image-generic-hwe-18.04 mesa-common-dev netpbm patchutils pppconfig pppoeconf python-all python-all-dev python-asn1crypto
  python-attr python-backports.functools-lru-cache python-cairo python-catkin-pkg-modules python-cbor python-cffi-backend python-colorama python-concurrent.futures
  python-configparser python-constantly python-crypto python-cycler python-dateutil python-dbus python-defusedxml python-entrypoints python-enum34 python-gnupg
  python-hyperlink python-idna python-incremental python-ipaddress python-keyring python-matplotlib python-matplotlib-data python-nacl python-netifaces python-nose
  python-numpy python-opengl python-osrf-pycommon python-pam python-psutil python-pyasn1 python-pyasn1-modules python-pycryptodome python-pydot python-pyparsing
  python-qrcode python-rosdep-modules python-rosdistro-modules python-rospkg-modules python-sip python-six python-snappy python-subprocess32 python-talloc python-trollius
  python-twisted-bin python-tz python-ubjson python-wheel python-wsaccel python-xdg python-yaml python-zope.interface python3-asn1crypto python3-attr python3-autobahn
  python3-automat python3-cbor python3-constantly python3-cycler python3-hamcrest python3-hyperlink python3-incremental python3-kiwisolver python3-lz4 python3-matplotlib
  python3-mpi4py python3-oauth python3-opengl python3-png python3-psutil python3-pyasn1 python3-pyasn1-modules python3-pydot python3-pyqrcode python3-pyqt5.qtopengl
  python3-pyqt5.qtwebkit python3-service-identity python3-snappy python3-trie python3-twisted python3-twisted-bin python3-txaio python3-u-msgpack python3-ubjson
  python3-vtk7 python3-wsaccel python3-zope.interface python3.6-minimal qdoc-qt5 qhelpgenerator-qt5 qt5-assistant qtattributionsscanner-qt5 qtdeclarative5-dev
  qtdeclarative5-dev-tools qttools5-dev qttools5-dev-tools qttools5-private-dev ros-noetic-boost-sml ros-noetic-camera-calibration-parsers ros-noetic-cmake-modules
  ros-noetic-common-msgs ros-noetic-diagnostic-msgs ros-noetic-diagnostic-updater ros-noetic-eigen-conversions ros-noetic-gl-dependency ros-noetic-image-geometry
  ros-noetic-pcl-conversions ros-noetic-pcl-msgs ros-noetic-qt-dotgraph ros-noetic-qt-gui ros-noetic-qt-gui-py-common ros-noetic-qwt-dependency ros-noetic-rosboost-cfg
  ros-noetic-roscpp-core ros-noetic-roscpp-tutorials ros-noetic-roslang ros-noetic-roslint ros-noetic-rosmake ros-noetic-self-test ros-noetic-smach ros-noetic-smach-msgs
  ros-noetic-stage ros-noetic-stereo-msgs ros-noetic-urdf-parser-plugin ros-noetic-vision-opencv ros-noetic-visualization-marker-tutorials ros-noetic-webkit-dependency
  ruby2.5 sbcl sdformat-sdf shim t1utils tcl-dev tcl-vtk7 tcl8.6-dev tk-dev tk8.6-dev ubuntu-system-service vtk7 x11proto-composite-dev x11proto-damage-dev
  x11proto-fixes-dev x11proto-scrnsaver-dev x11proto-xf86vidmode-dev xserver-xorg-core-hwe-18.04 xserver-xorg-hwe-18.04 xserver-xorg-input-all-hwe-18.04
  xserver-xorg-input-libinput-hwe-18.04 xserver-xorg-input-wacom-hwe-18.04 xserver-xorg-video-all-hwe-18.04 xserver-xorg-video-amdgpu-hwe-18.04
  xserver-xorg-video-ati-hwe-18.04 xserver-xorg-video-intel-hwe-18.04 xserver-xorg-video-nouveau-hwe-18.04 xserver-xorg-video-qxl-hwe-18.04
  xserver-xorg-video-vesa-hwe-18.04 xserver-xorg-video-vmware-hwe-18.04 zeitgeist-core
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 14 not upgraded.