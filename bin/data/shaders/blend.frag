//1-input
// #version 150

#pragma include "headerFrag.glsl"
// this is how we receive the texture
uniform sampler2DRect u_tex0;
uniform vec2 u_resolution;
uniform float u_time;
IN vec2 texCoordVarying;
out vec4 outputColor;
 
void main()
{
    //vec2 st = texCoordVarying;
    vec2 st = gl_FragColor.xy/u_resolution.xy;
    //vec2 pos = gl_FragCoord.xy;
    // vec2 st = gl_FragCoord.xy/u_resolution.xy;
//    st.x *= u_resolution.x/u_resolution.y;
//
//    color += vec3(u_x0*sign(sin(0.05*pos.x - u_time + sin(0.05*pow(pos.y,(0.7 + u_x1)) - u_time))),0.,0.);
//    color += vec3(0., 0., sign(cos(0.05*pos.x*u_x2 - 2.0*u_time + 5.0*u_x3*sin(0.05*pos.y - 2.0*u_time))));

    //FRAG_COLOR = vec4(color,1.);
    // outputColor = texture(u_tex0, st + vec2(0, .5));
   //FRAG_COLOR = TEXTURE(tex0, texCoordVarying);
   vec4 behind, forward, here;
   // image = TEXTURE(u_tex0, abs(st*sin(u_time)));
   vec2 near = vec2(0.1, .0);
   here = TEXTURE(u_tex0, st);
   forward = TEXTURE(u_tex0, st + near);
   behind = TEXTURE(u_tex0, st - near);
   // FRAG_COLOR = image;
   FRAG_COLOR = mix(here, forward, vec4(.5));
    outputColor = FRAG_COLOR;
   // FRAG_COLOR = vec4(1.);
    // FRAG_COLOR = vec4(1., 0., 1., 1.);

    // FRAG_COLOR = vec4(imager.r);
}
