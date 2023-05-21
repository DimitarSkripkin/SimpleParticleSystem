#include "AssetManager.h"

namespace EngineCore::Core {
    AssetManager & AssetManager::Instance() {
        static AssetManager instance;
        return instance;
    }

    Ref<Texture> AssetManager::LoadCachedImageFile(const char * path) {
        std::string pathStr(path);
        if (cachedTextures.find(pathStr) == cachedTextures.end()) {
            auto texture = LoadImageFile(path);
            cachedTextures.insert({ pathStr, texture });
            return texture;
        }

        return cachedTextures[pathStr];
    }

    Ref<Texture> AssetManager::LoadImageFile(const char * path) {
        RawImage rawImage(path);
        auto texture = CreateRef<Texture>();
        texture->UploadToGPU(rawImage);
        return texture;
    }

    Ref<Texture> AssetManager::LoadImageFile(const std::string & path) {
        return LoadImageFile(path.c_str());
    }
} // EngineCore::Core