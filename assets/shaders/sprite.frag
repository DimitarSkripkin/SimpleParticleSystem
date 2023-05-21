#version 330 core

uniform sampler2D spriteSampler;

in VS_OUT {
    vec4 color;
    vec2 uv;
} fs_in;

out vec4 fragColor;

void main() {
    vec4 textureColor = texture(spriteSampler, fs_in.uv);
    fragColor = fs_in.color * textureColor;

    float textureColorLen = length(vec3(textureColor));
    fragColor.a = textureColorLen;

    float cutoff = 0.1;
    if (fragColor.a < cutoff) discard;

    // fragColor = fs_in.color * vec4(fs_in.uv, 1, 1);
}
