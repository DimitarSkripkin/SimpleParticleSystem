#pragma once

#include <cstdint>
// #include <string>
#include <memory>

#include <GL/gl3w.h>

enum class TextureColorFormat : uint16_t {
    NOT_SET = 0,
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA
};

struct RawImage {
    RawImage();
    RawImage(const std::shared_ptr<uint8_t[]> & data, int32_t width, int32_t height, int32_t componentsPerPixel);
    RawImage(const RawImage & other);
    RawImage(RawImage && other);
    RawImage(const char * path);
    ~RawImage();

    RawImage ToPowerOfTwo();

    uint8_t * GetDataRef() const;
    uint8_t * GetDataRef();
    std::shared_ptr<uint8_t[]> GetRawDataRef();

    int32_t width;
    int32_t height;
    TextureColorFormat format;

    void Clear();
private:
    bool isSTBLoaded;
    int32_t componentsPerPixel;
    std::shared_ptr<uint8_t[]> data;
};
