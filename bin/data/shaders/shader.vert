// #version 150
#pragma include "headerVert.glsl"
// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewProjectionMatrix;

IN vec4 position;
IN vec2 texcoord;

// this is something we're creating for this shader
OUT vec2 texCoordVarying;


void main()
{
    // here we move the texture coordinates
    texCoordVarying = texcoord; // vec2(texcoord.x + mouseX, texcoord.y);

    // send the vertices to the fragment shader
	gl_Position = modelViewProjectionMatrix * position;
}
