//0-input

#pragma include "headerFrag.glsl"
uniform vec2 u_resolution;
IN vec2 texCoordVarying;
out vec4 outputColor;
// uniform sampler2DRect u_tex0;
uniform float u_time; // u_tex0;

float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
        vec2 st = gl_FragCoord.xy/u_resolution;

    float y = st.x;

    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(0.0,1.0,0.0);

	FRAG_COLOR = vec4(color,1.0);
        outputColor = FRAG_COLOR;
}
