# notes on intergration with rpi camera.

currently i am using a python package called [picamera] to intergrate the raspi camera/capture device with recur. this works fine with the current setup my pi is running:

- rpi 3
- openframeworks version 10.0
- raspberian stretch 9

in order to run processing shaders on the live input i would need to put the camera input into a texture in openframeworks. there is an openframeworks addon called [ofxRPiCameraVideoGrabber] designed for this. however on the above setup this does dont work. when i run the master branch of the addon it fails to compile (i gather due to being incompadable with of10 ?), however when i switch to a branch called `stretch` which includes commits added to make the addon of10 compadable it doesnt error but instead hanging indefinately (i think i left it running over night once) while compiling.

i tried switching to of9.8 for comparison but that doesnt seem to compile on this version of rasbian ?

## things to try:

i will run an experiment to see what combination of rasbian and of works with the app:

flash a sd card with a fresh raspbian-lite-jessie (2017-07-05-raspbian-jessie-lite.zip) and install openframeworks9.8 with ofxRPiCameraVideoGrabber, then try with openframeworks10.0 and ofxRPiCameraVideoGrabber. finally try both combinations of of with a fresh version of raspbian-lite-stretch (2018-06-27) for comparison.

this could take some time ! if it works on jessie/of9.8 i will try the recur setup process from a fresh image on this system as a possible workaround. i have a feeling though that this will break/cause problems with other things

## the steps:

- flash sd card
- change keyboard layout `sudo raspi-config` ... and add auto login
- add wifi address : 
```
network={
  ssid="YOUR_SSID"
  psk="YOUR_PASSWORD"
}
```
- `sudo apt update` and `sudo apt upgrade` , reboot...
- mount usb and copy over openframeworks zip : 
```
sudo mkdir /media/usb
sudo chmod 775 /media/usb
sudo mount -t vfat /dev/sda1 /media/usb
```
- `mkdir openFrameworks; tar vxfz of_v0.9.8_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1`
- install dependancies ... 
- try running some openframework , shaders dont work,,, video does.
- install git `sudo apt-get git`
- install ofxRPi app... `git clone https://github.com/jvcleave/ofxRPiCameraVideoGrabber.git`
- try it owt !

### compiling and working for jessie + of9 + master(branch)

### compiling and working for jessie + of10 + stretch(branch)

[picamera]: https://picamera.readthedocs.io/en/release-1.13/
[ofxRPiCameraVideoGrabber]: https://github.com/jvcleave/ofxRPiCameraVideoGrabber
