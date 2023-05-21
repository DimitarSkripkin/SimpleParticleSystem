#include "RawImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

RawImage::RawImage()
    : width(0),
    height(0),
    format(TextureColorFormat::NOT_SET),
    data(nullptr),
    componentsPerPixel(0)
{}

RawImage::RawImage(const std::shared_ptr<uint8_t[]> & data, int32_t width, int32_t height, int32_t componentsPerPixel)
    : width(width),
    height(height),
    format(TextureColorFormat::NOT_SET),
    data(std::move(data)),
    componentsPerPixel(componentsPerPixel)
{
    switch (componentsPerPixel)
    {
        case 1:
            format = TextureColorFormat::RED;
            break;
        case 2:
            format = TextureColorFormat::RG;
            break;
        case 3:
            format = TextureColorFormat::RGB;
            break;
        case 4:
            format = TextureColorFormat::RGBA;
            break;
    }
}

RawImage::RawImage(RawImage && other)
    : width(other.width),
    height(other.height),
    format(other.format),
    data(std::move(other.data)),
    componentsPerPixel(other.componentsPerPixel)
{
    other.width = 0;
    other.height = 0;
    other.format = TextureColorFormat::NOT_SET;
    other.componentsPerPixel = 0;
}

RawImage::RawImage(const RawImage & other)
    : width(other.width),
    height(other.height),
    format(other.format),
    data(other.data),
    componentsPerPixel(other.componentsPerPixel)
{}

RawImage::RawImage(const char * filePath)
    : width(0),
    height(0),
    format(TextureColorFormat::NOT_SET),
    data(nullptr),
    componentsPerPixel(0)
{
    //    int x,y,n;
    //    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    //    // ... process data if not NULL ...
    //    // ... x = width, y = height, n = # 8-bit components per pixel ...
    //    // ... replace '0' with '1'..'4' to force that many components per pixel
    //    // ... but 'n' will always be the number that it would have been if you said 0
    //    stbi_image_free(data)
    data = std::shared_ptr<uint8_t[]>(stbi_load(filePath, &width, &height, &componentsPerPixel, 0), stbi_image_free);
    switch (componentsPerPixel) {
        case 1:
            format = TextureColorFormat::RED;
            break;
        case 2:
            format = TextureColorFormat::RG;
            break;
        case 3:
            format = TextureColorFormat::RGB;
            break;
        case 4:
            format = TextureColorFormat::RGBA;
            break;
    }
}

int32_t NextPowerOfTwo(int32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

RawImage RawImage::ToPowerOfTwo() {
    RawImage newImage;
    newImage.width = NextPowerOfTwo(width);
    newImage.height = NextPowerOfTwo(height);

    if (newImage.width == width && newImage.height == height) {
        return RawImage(*this);
    }

    newImage.format = format;
    newImage.data = std::shared_ptr<uint8_t[]>(new uint8_t[newImage.width * newImage.height * componentsPerPixel], std::default_delete<uint8_t[]>());
    int offset = 0;
    for (int y = 0; y < height; ++ y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < componentsPerPixel; ++c) {
                // newImage.data.get()[(y * newImage.width + x) * componentsPerPixel + c] = data.get()[offset++];
                newImage.data[(y * newImage.width + x) * componentsPerPixel + c] = data[offset++];
            }
        }
    }

    return std::move(newImage);
}

uint8_t * RawImage::GetDataRef() const {
    return data.get();
}

uint8_t * RawImage::GetDataRef() {
    return data.get();
}

std::shared_ptr<uint8_t[]> RawImage::GetRawDataRef() {
    return data;
}

RawImage::~RawImage() {
    Clear();
}

void RawImage::Clear() {
    width = 0;
    height = 0;
    format = TextureColorFormat::NOT_SET;
}
