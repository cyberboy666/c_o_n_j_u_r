# notes on intergration with rpi camera and piCaptureSd1.

currently i am using a python package called [picamera] to intergrate the raspi camera/ [capture device] with recur. this works quite well for standand preview / recording. 

in order to run processing shaders on the live input i would need to put the camera input into a texture in openframeworks. there is an openframeworks addon called [ofxRPiCameraVideoGrabber] designed for this. 

### configuring the piCapture device:

displaying the capture input by default `raspivid -o` gives a glitchy mess: ![image1][image1] ,

it is recommended by [lintest] to use `raspivid  –md 6 –awbg 1.0,1.0 –awb off –ex off -o` which gives a nice picture: ![image2][image2],

these settings break down to the following:

- setting the sensor-mode to 6 , which sets : Size=640x480	Aspect Ratio=4:3	Frame rates=42.1-60fps	FOV=Full	Binning=2x2 plus skip. this is the only way i can set to control these settings (besides size which can be manually set by `-w` and `-h`)
- awbgains to 1.0 , 1.0 (the blue and gains when awb is off)
- auto white balance off
- auto exposure off

picamera, the python package i was using has the ability to change these settings when piCapture is being used , giving a nice image to preview and record.

### the problem:

ofxRPiCameraVideoGrabber, the openframeworks addon does have a number of camera settings that can be configured (including turning off auto exposure and turning off auto white balance) however it does not include any settings for the awbg or the sensor-mode. no awbg means a very green image when awb is off. no sensor mode means the display continues to be a glitchy mess, even after setting the width/height of the of object to 640x480. ![image 3][image 3]

under the hood ofxRPiCameraVideoGrabber seems to be talking directly to OpenMax to configure these settings. this differs from the `raspivid` and `picamera` packages which seems to use the MMAL API. according to [this thread] in the rpi forums the MMAL API wraps over OpenMax so it should be possible still to access these settings although it also sounds quite difficult / beyond my knowledge.

at this stage the options i can see are:
- no real-time processing of live input in openframeworks from captureSd1 (a shame ! , although could still have the option when using the piCamera which works fine without access to these settings
- edit the ofxRPiCameraVideoGrabber addon to include control over these parameters
- somehow figure out another way to get texture objects from the camera into openframeworks (this seems even futher beyond me !)


[capture device]: https://lintestsystems.com/products/picapture-sd1
[picamera]: https://picamera.readthedocs.io/en/release-1.13/
[ofxRPiCameraVideoGrabber]: https://github.com/jvcleave/ofxRPiCameraVideoGrabber
[lintest]: https://lintestsystems.com/documentation
[this thread]: https://www.raspberrypi.org/forums/viewtopic.php?t=71915
[image 1]: /documentation/image1.png
[image 2]: /documentation/image2.png
[image 3]: /documentation/image3.png
