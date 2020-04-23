//2-input
//written by Ben Caldwell
#pragma include "headerFrag.glsl"
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_x0;
IN vec2 texCoordVarying;

uniform float u_x1;
uniform float u_x2;
uniform float u_x3;
uniform sampler2DRect u_tex0;
uniform sampler2DRect u_tex1;
out vec4 outputColor;

void main() {
    vec2 st = texCoordVarying;
    // outputColor = texture(u_tex0, st + vec2(0, .5));
   //FRAG_COLOR = TEXTURE(tex0, texCoordVarying);
    FRAG_COLOR = vec4(.2);
    outputColor = FRAG_COLOR;
//   vec4 image1; vec4 image2;
//   image1 = TEXTURE(u_tex0, st);
//   image2 = TEXTURE(u_tex1, st);
//   FRAG_COLOR = mix(image1, vec4(0.));
//    vec3 color = vec3(0.0,0.0,0.0);
//    float mod_time = u_x0 * u_time;
//
//    vec2 pos = gl_FragCoord.xy;
//    vec2 st = gl_FragCoord.xy/u_resolution.xy;
//    st.x *= u_resolution.x/u_resolution.y;
//
//    vec2 s1 = vec2(u_resolution.x*(0.5 + 0.25*cos(mod_time)), u_resolution*(0.5 + 0.25*sin(mod_time)));
//    vec2 s2 = vec2(u_resolution.x*(0.5 + 0.25*sin(mod_time)), u_resolution*(0.5 + 0.25*cos(mod_time)));
//    vec2 s3 = vec2(u_resolution.x*0.5, u_resolution*0.5);
//    
//    float r1 = (pow(pow(pos.x-s1.x,2.0) + pow(pos.y-s1.y,2.0), 0.5))*u_x1;
//    float r2 = (pow(pow(pos.x-s2.x,2.0) + pow(pos.y-s2.y,2.0), 0.5))*u_x2;
//    float r3 = (pow(pow(pos.x-s3.x,2.0) + pow(pos.y-s3.y,2.0), 0.5))*u_x3;
//    
//    color += vec3(0.5 + 0.5*sign(sin((0.1 + 0.05*sin(mod_time+2.0))*r1 - 1.0*mod_time)), 0.0, 0.0);
//    color += vec3(0.0, 0.0, 0.5 + 0.5*sign(sin((0.1 + 0.05*sin(mod_time))*r2 - 1.2*mod_time)));
//    color += vec3(0.0, 0.5 + 0.5*sign(sin((0.1 + 0.05*sin(mod_time+0.5))*r3 - 1.1*mod_time)), 0.0);
//
//    // color = vec3(1., 0., 0.);
//    // gl_FragColor = vec4(color,1.);
//    FRAG_COLOR = vec4(color,.1);
}
