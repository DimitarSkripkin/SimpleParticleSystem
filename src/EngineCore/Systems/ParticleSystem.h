#pragma once

#include "SystemBase.h"

#include "EngineCore/Rendering/BatchRecorder.h"
#include "EngineCore/Utils/Math.h"

namespace EngineCore::Systems {
    struct EmitParticleProps {
        glm::vec3 initialPosition;
        glm::vec3 initialVelocity;
        glm::vec4 initialColor = glm::vec4(1.0f);
        glm::vec4 endColor = glm::vec4(1.0f);
        float initialSize = 0.0f;
        float endSize = 1.0f;
        float lifeTime = 1.0f;
        Ref<Sprite> sprite;
    };

    class ParticleSystem;

    class Emitter {
    public:
        Emitter(ParticleSystem* particleSystem)
            : particleSystem(particleSystem)
        {}

        EmitParticleProps particleProps;

        // glm::vec3 velocityVariation;
        // float sizeVariation;
        float particlesPerSecond = 1.0f;

        void Update(float deltaTime);

    private:
        ParticleSystem* particleSystem;
        float cooldown = 0.0f;

        EngineCore::Math::Random rnd;
    };

    class ParticleSystem : public SystemBase {
    public:
        ParticleSystem();

        Ref<Emitter> GetEmitter();

        virtual void Update(float deltaTime) override;
        void AppendParticleData(BatchRecorder &batchRecorder);

        void EmitParticle(EmitParticleProps particleProps);
    private:
        struct ParticleData {
            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec4 initialColor;
            glm::vec4 endColor;
            float rotation = 0.0f;
            float initialSize = 0.0f;
            float endSize = 1.0f;
            float lifeTime = 5.0f;
            float lifeRemaining = 0.0f;
            Ref<Sprite> sprite;
        };

        std::vector<Ref<Emitter>> emitters;

        std::vector<ParticleData> particlePool;
        uint32_t particlePoolIndex = 0;
    };
} // EngineCore::Systems
