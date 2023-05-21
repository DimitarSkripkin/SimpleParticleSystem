#pragma once

#include <cstdint>

#include "EngineCore/FileLoaders/RawImage.h"
#include "EngineCore/Core/Core.h"

class Texture {
public:
    Texture();
    ~Texture();

    uint32_t GetId() const;
    intptr_t GetId();

    Ref<RawImage> Source;

    virtual bool UploadToGPU(
        RawImage &rawTexture,
        TextureColorFormat internalFormat = TextureColorFormat::NOT_SET
    );
    virtual bool UploadToGPU(
        std::shared_ptr<uint8_t[]> data,
        int32_t width,
        int32_t height,
        TextureColorFormat format = TextureColorFormat::NOT_SET,
        TextureColorFormat internalFormat = TextureColorFormat::NOT_SET
    );

    virtual void Delete();

    void Bind();
    void Unbind();

    int32_t GetWidth();
    int32_t GetHeight();

protected:
    uint32_t textureId;
    int32_t width, height;
};
