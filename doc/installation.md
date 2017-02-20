# colegobot
## Hardware
Raspberry Pi 3
Dual VNH3SP30 Motor Driver Carrier MD03A



## Install Raspbian
Used the 2016-09-23-raspbian-jessie.img from https://www.raspberrypi.org/downloads/raspbian/

Installed following https://www.raspberrypi.org/documentation/installation/installing-images/linux.md




## Install ROS

Follow the steps detailed in http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Kinetic%20on%20the%20Raspberry%20Pi




## Configure wifi network
### Set static IP
```
$ sudo vim /etc/dhcpcd.conf
```
add the following

```
interface eth0

static ip_address=192.168.1.31/24
static routers=192.168.1.1
static domain_name_servers=192.168.1.1

interface wlan0

static ip_address=192.168.1.31/24
static routers=192.168.1.1
static domain_name_servers=192.168.1.1
```

### Configure wlan0

```
$ sudo vim /etc/network/interfaces
```
add the following

```
auto lo
iface lo inet loopback
iface eth0 inet dhcp

allow-hotplug wlan0
auto wlan0

iface wlan0 inet dhcp
   wpa-ssid "Your Network SSID"
   wpa-psk "Your Password"
```




## Video
### calibration

### rosberrypi_cam
```
$ cd catkin_ws/src
$ git clone git@github.com:ericguerrero/rosberrypi_cam.git
```
Install raspicam following the instructions indicated
Check if works running the node








## Teleoperation PS3joy
### Bluetooth
```
$ sudo bash
$ rosrun ps3joy ps3joy.py
```

In a new terminal, confirm that the joystick is sending data to your computer. You can test this with jstest:
```
$ sudo jstest /dev/input/js?
```

## Launch architecture
### Station
Add the correct serial port used by the ps3_joy in the launch file and run.
```
$ roslaunch colegobot station.launch 
```

### Station

```
$ roslaunch colegobot robot.launch 
```
