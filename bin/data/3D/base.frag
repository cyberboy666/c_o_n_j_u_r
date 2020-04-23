#version 150

in vec2 v_texcoord;
in vec3 v_normal;

out vec4 fragColor;

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform bool lightingEnabled;

void main() {
    vec3 color = texture(tex0, v_texcoord).rgb;
    
    // Directional light
    vec3 lightDirection = vec3(1.0, 1.0, -3.0);
    
    // The light intensity is proportional to the angle between the incoming light and the surface normal
    float intensity = dot(normalize(v_normal), normalize(lightDirection));
    intensity = clamp(intensity, 0.0, 1.0);
    
    if (lightingEnabled) {
        fragColor = vec4(color * intensity * lightColor, 1.0);
    } else {
        fragColor = vec4(color, 1.0);
    }
}
