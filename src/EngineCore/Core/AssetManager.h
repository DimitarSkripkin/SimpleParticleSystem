#pragma once

#include <map>
#include <string>

#include "Core.h"
#include "EngineCore/Rendering/OpenGLWrapper/Texture.h"

namespace EngineCore::Core {
    class AssetManager {
    public:
        static AssetManager & Instance();

        Ref<Texture> LoadCachedImageFile(const char * path);

    private:
        std::map<std::string, Ref<Texture>> cachedTextures;

        Ref<Texture> LoadImageFile(const char * path);
        Ref<Texture> LoadImageFile(const std::string & path);
    };
} // EngineCore::Core
