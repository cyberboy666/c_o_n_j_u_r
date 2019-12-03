
# c_o_n_j_u_r



an alternative openframeworks backend for my video sampler [r_e_c_u_r]

this is WIP, currently working towards feature parity with the existing omxplayer backend, and then experimenting with adding glsl shader playback/interaction (digital video synthesis) both standalone and as video processing/effects

## setup (note - its pretty buggy atm)

- download and install [openframeworks10] for raspberry pi following the [setup instructions] for dependacies and compiling
- ~(not sure if this is needed ?) sudo raspi-config -> advanced -> gl driver -> legacy~
- installing additional python packages `pip3 install python-osc` and `pip3 install threading`
(there will be more of these now - update this list !)
- navigate to apps : `cd ~/openFrameworks/apps/myApps/` and clone this repo `git clone https://github.com/langolierz/c_o_n_j_u_r.git`
- while in this dir (`cd ~/openFrameworks/apps/myApps/c_o_n_j_u_r`) compile the code `make`
- navigate to r_e_c_u_r (`cd ~/r_e_c_u_r`) and checkout the c_o_n_j_u_r branch `git fetch; git checkout c_o_n_j_u_r` 
- start r_e_c_u_r and switch the `VIDEO_BACKEND` setting

## progress

as a proof of concept i started by creating a simple openframework app that listens for OpenSoundControl messages locally and uses these to control 3 ofVideoPlayers. it then sends OSC messages back with player status and position info. the modified recur code replaces any calls to the omx dbus with messages over OSC.

this worked suprisingly well, there is currently one black frame between loops although i hope to close this. i figured out how to control the opacity of these players and some things like seeking and loading seems faster than omx. i have noticed that the framerate drops when playing large file (and i imagine also when heavy shaders/ effects are chained)

### updated: some things to do/try:

- ~try getting no black frame between videos~ of loops videos seamlessly although does lag for >sd it seems
- ~passing start and stop info from python to the player~
- ~testing/passing the various video_settings regarding how the players interact~ havnt really been priotizing this although some will just work , others will not...
- ~setting the background colour ?~ wont do for now...
- ~seeing if fill/letterbox/strech modes are possible~ wont do for now
- ~tryi intergrating playback speed settings~ tried this and it worked sometimes but also caused the of app to crash a lot. might be possible with specific file types...
- ~getting rpi-camera / capture working on openframeworks (the addon wasnt compiling last i tried)~ this inocent suggestion has been a huge timesink over the last few weeks! it is compiling (although i still have no idea why it wasnt then..) but i needed to mod the addon to improve the picapture playback (with some success , some things pending) also currently running of capture and playing video causes a lot of lag..
- ~a pipe for loading/playing shaders , passing through parameter values and adding shader-effects to the players~ yay this is done !

### some things still to do.try

- seeing if a different video can be played on the lcd screen ?
- experimenting with projection mapping of addon




[r_e_c_u_r]: https://github.com/langolierz/r_e_c_u_r
[openframeworks10]: https://openframeworks.cc/versions/v0.10.0/of_v0.10.0_linuxarmv6l_release.tar.gz
[setup instructions]: https://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started/

