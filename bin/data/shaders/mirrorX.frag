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
    vec2 st = texCoordVarying;
    // outputColor = texture(u_tex0, st + vec2(0, .5));
   //FRAG_COLOR = TEXTURE(tex0, texCoordVarying);
   vec4 image;
   // image = TEXTURE(u_tex0, abs(st*sin(u_time)));
   if(st.x > .5){st.x = 1.0 - st.x;}
   image = TEXTURE(u_tex0, st);
   // image = TEXTURE(u_tex0, vec2(abs( st.x - .5 ), st.y));
   // FRAG_COLOR = image;
   FRAG_COLOR = image; // vec4(1., 0., 0., 1.); // ) - image; // vec4(1. - image.r, 1. - image.g, 1.,  .2); // this looks cool
   // FRAG_COLOR = vec4(1.);
    // FRAG_COLOR = vec4(1., 0., 1., 1.);

    // FRAG_COLOR = vec4(imager.r);
    outputColor = FRAG_COLOR;
}
