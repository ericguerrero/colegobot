# colegobot
Raspberry Pi 3 running Ubuntu MATE 16.04

## Dependencies
```
cd workspace/src
$ git clone git@github.com:ericguerrero/colegobot.git
$ git clone git@github.com:ericguerrero/rosberrypi_cam.git
$ git clone git@github.com:ericguerrero/ros-mpu6050-node.git
$ git clone https://github.com/ros-drivers/joystick_drivers.git
$ git clone https://github.com/turtlebot/turtlebot.git
...
```
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
