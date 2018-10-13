# notes on shader formats and conventions

when intergrating my custom shader support i will need to decide on some conventions. This document will track and explain these desisions and conventions to help you understand/write/modify your own shaders for this device.

## uniforms

the conjur app is written to take uniforms/varyings in the same format as described in [The Book of Shaders], a great resource for anyone wanting to learn from the beginning.

- a conjur shader is expecting uniform vec2 `u_resolution` and uniform float `u_time` passed in from openframeworks

## shader type

although the distinction is somewhat arbitary in practice, i want the recur interface to differenate between shaders that __generate__ and shaders that __process__.

- a _gen-shader_ dictates the output on its own. it does not need info about the videoplayer(/framebuffer) to run. by default the current-video should pause when a _gen-shader_ is started, and unpause when it is stopped (in the same way the video pauses when the capture-preview is enabled)
- a _pro-shader_ takes input from the framebuffer and uses this to create the final output. the videoplayers do not pause when these are started.
- a conjur _pro-shader_ is expecting a uniform `u_tex0 (sampler2D)` passed in from openframeworks

so the interface can differenate between the types, it will look for `//gen-shader` or `//pro-shader` in the .frag file. if neither is found the default will be _processing_...

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

## how to dev shaders on the pi

one way is  to write/edit a shader file and then run the recur program to see if it works. however this is a slow way to see the result when deving.

instead i recommend using the cmd-line shader program `glslViewer` (my inputs have been made compadable with this program)

- for creation of gen-shaders you can open a terminal and type `glslViewer ~/Shaders/my_new_shader.frag -l`. this will open the shader in a window, from which you can continue to edit the code in gedit or something (glslViewer auto updates when file is saved)
- for creation of pro-shaders you will also need to pass it a texture to be manipulated. the easiest way to do this is to load any placeholder img : `glslViewer ~/Shaders/my_new_shader.frag ~/r_e_c_u_r/documentation/splash.png -l` will process the recur splash screen for example.
- to test the param input in this mode you can type the param followed by new value into the cmd console while glslViewer is running, for example `u_x0,0.1` will set first param to 0.1.
- for a faster / more continuous test of param inputs you could use the u_mouse.x and u_mouse.y and then convert back to u_x0/u_x1 when calibrated...

## understanding different shader versions / conventions

i dont really understand all this yet but will try to update/clarify here when i do:

- currently the conjur openframeworks application is running __gles 2__ 
- the glsl-shader code for this does not need to delcare its version at top however often you will see `precision highp float;` declared at the top of gles shaders. if the shader is written to run cross platform you might see the statement:
```
#ifdef GL_ES
precision mediump float;
#endif
```
## writing compadable shaders on my mac/windows machine...

writing your shaders in gles is a way to ensure compadiblity. webgl is an example of this.

- one way to do this is to install [glslViewer] onto your machine and dev in the same way described above.
- other is to create your shaders in the webbrowser using [glslEditor]... 

- i think if you see a shader that starts with `#version 120` this is referring to glsl1.2 which is used by opengl2 an old version of opengl which is not compadible ... i think `#version 150` and higher might run gles2 which should be similar : it seems like some higher versions (some `#version 330` seems to have `out vec4 fragColor` instead of using `gl_FragColor` ... )


[The Book of Shaders]:https://thebookofshaders.com/
[glslViewer]: https://github.com/patriciogonzalezvivo/glslViewer
[glslEditor]: editor.thebookofshaders.com
