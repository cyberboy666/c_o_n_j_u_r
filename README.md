
# c_o_n_j_u_r

an alternative openframeworks backend for my video sampler [r_e_c_u_r]

this is WIP, currently working towards feature parity with the existing omxplayer backend, and then experimenting with adding glsl shader playback/interaction (digital video synthesis) both standalone and as video processing/effects

## setup (note - its pretty buggy atm)

- download and install [openframeworks10] for raspberry pi following the [setup instructions] for dependacies and compiling
- (not sure if this is needed ?) sudo raspi-config -> advanced -> gl driver -> legacy
- installing additional python packages `pip3 install python-osc` and `pip3 install threading`
- navigate to apps : `cd ~/openFrameworks/apps/myApps/` and clone this repo `git clone https://github.com/langolierz/c_o_n_j_u_r.git`
- while in this dir (`cd ~/openFrameworks/apps/myApps/c_o_n_j_u_r`) compile the code `make` and run `make run` (or set up to run on boot ... )
- navigate to r_e_c_u_r (`cd ~/r_e_c_u_r`) and checkout the c_o_n_j_u_r branch `git fetch; git checkout c_o_n_j_u_r` 
- start r_e_c_u_r and switch the `VIDEO_BACKEND` setting




[r_e_c_u_r]: https://github.com/langolierz/r_e_c_u_r
[openframeworks10]: https://openframeworks.cc/versions/v0.10.0/of_v0.10.0_linuxarmv6l_release.tar.gz
[setup instructions]: https://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started/

