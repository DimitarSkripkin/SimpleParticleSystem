#version 330 core

uniform sampler2D albedoMap;
uniform bool hasAlbedoMap;

in VS_OUT {
    vec4 color;
    vec2 uv;
} fs_in;

out vec4 fragColor;

void main() {
    if (hasAlbedoMap) {
        vec4 textureColor = texture(albedoMap, fs_in.uv);
        fragColor = fs_in.color * textureColor;

        float textureColorLen = length(vec3(textureColor));
        fragColor.a = textureColorLen;
    } else {
        fragColor = fs_in.color;
    }

    float cutoff = 0.1;
    if (fragColor.a < cutoff) discard;

    // fragColor = fs_in.color * vec4(fs_in.uv, 1, 1);
}
