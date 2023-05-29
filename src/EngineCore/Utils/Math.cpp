#include "Math.h"

namespace EngineCore::Math {
    Random & Random::Instance() {
        static Random instance;
        return instance;
    }
} // EngineCore::Math
