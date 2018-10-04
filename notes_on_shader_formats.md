# notes on shader formats and conventions

when intergrating my custom shader support i will need to decide on some conventions. This document will track and explain these desisions and conventions to help you understand/write/modify your own shaders for this device.

## uniforms

the conjur app is written to take uniforms in the same format as described in [The Book of Shaders], a great resource for anyone wanting to learn from the beginning.

- a conjur shader is expecting uniform vec2 `u_resolution` and uniform float `u_time` passed in from openframeworks

## shader type

although the distinction is somewhat arbitary in practice, i want the recur interface to differenate between shaders that __generate__ and shaders that __process__.

- a _gen-shader_ dictates the output on its own. it does not need info about the videoplayer(/framebuffer) to run. by default the current-video should pause when a _gen-shader_ is started, and unpause when it is stopped (in the same way the video pauses when the capture-preview is enabled)
- a _pro-shader_ takes input from the framebuffer and uses this to create the final output. the videoplayers do not pause when these are started.
- a conjur _pro-shader_ is expecting a uniform `tex0 (sampler2D)` passed in from openframeworks _NOTE: this should be changed to u_tex0 to be inline with what i wrote above ??_

so the interface can differenate between the types, it will look for `//gen-shader` or `//pro-shader` in the .frag file. if niether is found the default will be _processing_...

## parameters

some shaders already take in parameters in the form of uniform `u_mouse (vec2)` etc. others could quite easily be made more dynamic by injecting params into the calculations. a conjur shader will allow up to 4 parameters (although this is arbitry) to be used in each shader.

- to accept params into a shader create float uniforms called: `u_x0`, `u_x1`, `u_x2`, `u_x3`, 
- these params will __always__ range from 0-1 . scaling of these will need to be done inside the shader code (ie multiply by `u_resolution.x` to replace the `u_mouse.x` etc)
- switches can also be created using these params ie: 
```
if(u_x < 0.5){
colour = (0,0,1);
}
else{
colour = (1,0,1)
}
```
- the recur sampler will search the shader code for the lines `uniform float u_x0;` and then `uniform float u_x1;` and so on. note that if _u_x0_ is not found, it will not find a param called _u_x1_ etc

## file extensions and non-frag shaders

from what i understand the file extension for shader files is arbitry since openframeworks loads shaders by reading plain text. however the recur interface wants to only display shader files to make browsing easier. by default it will display files with the following extensions: _.frag, .shader, .glsl, .glslf, .fsh_ although these can easily be modified.

for now my interest/knowledge of shaders is limited to frag shaders. for this reason a default.vert shader is hardcoded to the load in conjur. it would be easy to make this accessable if desired (probably with the convention to load the matching `.vert, .glslg, .vsh` if exists otherwise use the default) 

## compadiblity on other os/versions of gl_es etc

for now my main prioty is writing shaders that run on the raspberry pi - this is also probably where i would choose to _create_ them (so tex0/u_x0 etc conventions would just work). however ultimately it would be nice if a shader written on your mac/pc could be seamlessly ported to the pi. i have seen some examples of this around - to look in to !

[The Book of Shaders]:https://thebookofshaders.com/
