//1-input
#pragma include "headerFrag.glsl"
uniform sampler2D u_tex0;

IN vec2 v_texcoord;
uniform float u_time;
uniform vec2 u_resolution;

    void main(){
        vec4 image;
        image = TEXTURE(u_tex0, v_texcoord.xy);
        FRAG_COLOR = vec4(1. - image.r, 1. - image.g, 1. - image.b, 1.0);
    }
