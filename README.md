# c_o_n_j_u_r

this repo is a part of [__r_e_c_u_r__] : an open diy video instrument.

r_e_c_u_r started as a video sampler / looper - using python on rpi to trigger clips via _omxplayer_. as the project grew i wanted more flexibity on how the videos were played so decided to replace _omxplayer_ with a custom _openframeworks_ app called __c_o_n_j_u_r__

c_o_n_j_u_r is the custom c++ video backend for r_e_c_u_r. they communicate via osc locally.

with an openframeworks backend it is now possible to play shaders in r_e_c_u_r, both to generate video, and to process and mix video sources - samples, live video input etc. somewhat confusingly i often refer to _c_o_n_j_u_r_ as the shader playing engine within r_e_c_u_r , although technically this repo is doing more than just shaders that was the name i gave it to start with ...

## ofxVideoArtTools

as i began to use openframeworks more for video-art projects on raspberry pi i relised there were some basic blocks i was repeating in each project. i tried to tidy this up by extracting these blocks into an extension repo called [ofxVideoArtTools]. this is a wrapper around other extensions and classes i used often. this repo, recurBOY - a pi0 spinoff- and others all use these extensions to 'patch' together different video instruments. 



[__r_e_c_u_r__]: https://github.com/langolierz/r_e_c_u_r
[ofxVideoArtTools]: https://github.com/langolierz/ofxVideoArtTools
