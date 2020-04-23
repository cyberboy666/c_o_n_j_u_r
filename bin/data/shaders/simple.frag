//1-input
// #version 150

#pragma include "headerFrag.glsl"
uniform vec2 u_resolution;
IN vec2 texCoordVarying;
out vec4 outputColor;
// uniform sampler2DRect u_tex0;
uniform float u_time; // u_tex0;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
     // vec2 st = texCoordVarying;
     // float red = step(.45, st.x) * step(st.x, .55);
    float red = ceil(mod(100.*abs(sin(u_time)), 100.*st.x)); //  step(.45, st.x) * step(st.x, .55);
     float green = 1. - red;
     // FRAG_COLOR = TEXTURE(u_tex0, u);
    // vec4 green = vec4(0., st.x+.5, 0., 1.);
    // FRAG_COLOR = green;
    // FRAG_COLOR = TEXTURE(u_tex0, u.xy);
    // vec4 e = vec4(red, abs(sin(u_time))* green, 0., 1.);
    vec4 e = vec4(red, green, 0., 1.);
    outputColor = e;
    FRAG_COLOR = e;



}


