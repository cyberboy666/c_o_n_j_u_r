// this is the default.vert shader used by conjur , it ensures that the frag shaders run by glslViewer will also run in openframeworks
#pragma include "headerVert.glsl"
uniform mat4 modelViewProjectionMatrix;
IN vec4 position;
IN vec4  color;
IN vec3  normal;
IN vec2 texcoord;


OUT vec4 v_position;
OUT vec4    v_color;
OUT vec3    v_normal;
OUT vec2 tcoord;
// twice because supporting two shader formats
OUT vec2 v_texcoord;

uniform mat4 u_modelViewProjectionMatrix;

void main() {
    v_position = position;
    v_color = color;
    v_normal = normal;
    tcoord = texcoord;
    v_texcoord = texcoord;

    gl_Position = modelViewProjectionMatrix * position;

}
