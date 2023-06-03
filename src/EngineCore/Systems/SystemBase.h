#pragma once

namespace EngineCore::Systems {
    class SystemBase {
    public:
        virtual void Update(float deltaTime) = 0;
    };
} // EngineCore::Systems
