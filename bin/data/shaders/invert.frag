// #version 150

#pragma include "headerFrag.glsl"
// this is how we receive the texture
uniform sampler2DRect tex0;

IN vec2 texCoordVarying;

out vec4 outputColor;
 
void main()
{
    // outputColor = texture(tex0, texCoordVarying);
    FRAG_COLOR = TEXTURE(tex0, texCoordVarying);
        vec4 image;
        image = TEXTURE(tex0, texCoordVarying);
        FRAG_COLOR = vec4(1. - image.r, 1. - image.g, 1. - image.b, .1); // this looks cool
}
