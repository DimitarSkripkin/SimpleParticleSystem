#include "Texture.h"

Texture::Texture() {
    textureId = 0;
};

Texture::~Texture() {
    Delete();
}

uint32_t Texture::GetId() const {
    return textureId;
}

intptr_t Texture::GetId() {
    return textureId;
}

bool Texture::UploadToGPU(RawImage &rawTexture, TextureColorFormat internalFormat) {
    return UploadToGPU(rawTexture.GetRawDataRef(), rawTexture.width, rawTexture.height, rawTexture.format, internalFormat);
}

bool Texture::UploadToGPU(
    std::shared_ptr<uint8_t[]> data,
    int32_t width,
    int32_t height,
    TextureColorFormat format,
    TextureColorFormat internalFormat
) {
    ENGINE_ASSERT_WITH_MSG(width > 0 && height > 0, "Invalid texture size");
    if (!textureId) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    if (internalFormat == TextureColorFormat::NOT_SET) {
        internalFormat = format;
    }

    this->width = width;
    this->height = height;

    glTexImage2D(GL_TEXTURE_2D,
        0, static_cast<uint16_t>(internalFormat),
        width, height,
        0, static_cast<uint16_t>(format),
        GL_UNSIGNED_BYTE, data.get());

    return true;
}

void Texture::Delete() {
    if (textureId) {
        glDeleteTextures(1, &textureId);
        textureId = 0;
        width = 0;
        height = 0;
    }
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int32_t Texture::GetWidth() {
    return width;
}

int32_t Texture::GetHeight() {
    return height;
}
