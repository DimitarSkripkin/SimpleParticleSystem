#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "EngineCore/Utils/Math.h"

namespace EngineCore::Systems {
void Emitter::Update(float deltaTime) {
    cooldown -= deltaTime;
    if (cooldown <= 0.0f) {
        auto newParticleProps = particleProps;
        newParticleProps.initialVelocity *= rnd.RandomInUnitSphere();
        particleSystem->EmitParticle(newParticleProps);
        cooldown += 1.0f / particlesPerSecond;
    }
}

ParticleSystem::ParticleSystem() {
    particlePool.resize(1000);
}

Ref<Emitter> ParticleSystem::GetEmitter() {
    auto newEmitter = CreateRef<Emitter>(this);
    emitters.push_back(newEmitter);
    return newEmitter;
}

void ParticleSystem::Update(float deltaTime) {
    for (auto& emitter : emitters) {
        emitter->Update(deltaTime);
    }

    for (auto& particle : particlePool) {
        if (particle.lifeRemaining <= 0.0f) {
            continue;
        }

        particle.lifeRemaining -= deltaTime;
        particle.position += particle.velocity * deltaTime;
        particle.rotation += 0.01f * deltaTime;
    }
}

void ParticleSystem::AppendParticleData(BatchRecorder &batchRecorder) {
    for (auto& particle : particlePool) {
        float interpolationValue = 1 - (particle.lifeRemaining / particle.lifeTime);
        float size = glm::lerp(particle.initialSize, particle.endSize, interpolationValue);
        auto color = glm::lerp(particle.initialColor, particle.endColor, interpolationValue);
        if (particle.sprite) {
            particle.sprite->color = color;
            batchRecorder.Add(*particle.sprite, particle.position, particle.rotation, size / glm::vec2(particle.sprite->width, particle.sprite->height));
        } else {
            batchRecorder.Add(DrawQuad { { size, size }, color }, particle.position, particle.rotation, glm::vec2(1.0f));
        }
    }
}

void ParticleSystem::EmitParticle(EmitParticleProps particleProps) {
    ParticleData& particle = particlePool[particlePoolIndex];
    particle.position = particleProps.initialPosition;
    particle.velocity = particleProps.initialVelocity;
    particle.rotation = 0.0f;
    particle.initialColor = particleProps.initialColor;
    particle.endColor = particleProps.endColor;
    particle.initialSize = particleProps.initialSize;
    particle.endSize = particleProps.endSize;
    particle.lifeTime = particleProps.lifeTime;
    particle.lifeRemaining = particleProps.lifeTime;
    particle.sprite = particleProps.sprite;

    particlePoolIndex = (++particlePoolIndex) % particlePool.size();
}
} // EngineCore::Systems
