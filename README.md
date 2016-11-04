# colegobot

## Dependencies
cd workspace/src
git clone https://github.com/ros-drivers/joystick_drivers.git
https://github.com/turtlebot/turtlebot.git

https://github.com/stevenlovegrove/Pangolin.git



## Configure wifi network
### Set static IP
```
sudo vim /etc/dhcpcd.conf
```
add the following

```
interface eth0

static ip_address=192.168.0.10/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1

interface wlan0

static ip_address=192.168.0.10/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1
```

### Configure wlan0

```
sudo vim /etc/network/interfaces
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
### USB


### Bluetooth
$ sudo bash
$ rosrun ps3joy ps3joy.py

## Launch architecture
### Station
