// Source https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Math/Math.h

#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <random>

namespace EngineCore::Math {
    class Random {
    public:
        Random() = default;

        static Random & Instance();

        template <typename T = int32_t>
        T Int() {
            std::uniform_int_distribution<T> uniformDistribution;
            return uniformDistribution(generator);
        }

        template <typename T = int32_t>
        T Int(T maxValue) {
            std::uniform_int_distribution<T> uniformDistribution(maxValue);
            return uniformDistribution(generator);
        }

        template <typename T = int32_t>
        T Int(T minValue, T maxValue) {
            std::uniform_int_distribution<T> uniformDistribution(minValue, maxValue);
            return uniformDistribution(generator);
        }

        template <typename T = uint64_t>
        T Int64() {
            std::uniform_int_distribution<T> uniformDistribution;
            return uniformDistribution(generator64);
        }

        template <typename T = uint64_t>
        T Int64(T maxValue) {
            std::uniform_int_distribution<T> uniformDistribution(maxValue);
            return uniformDistribution(generator64);
        }

        template <typename T = uint64_t>
        T Int64(T minValue, T maxValue) {
            std::uniform_int_distribution<T> uniformDistribution(minValue, maxValue);
            return uniformDistribution(generator64);
        }

        template <typename T = float>
        T Float(T minValue, T maxValue) {
            std::uniform_real_distribution<T> uniformDistribution(minValue, maxValue);
            return uniformDistribution(generator);
        }

        float Random01() {
            static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
            return distribution(generator);
        }

        glm::vec3 RandomInUnitSphere() {
            while (true) {
                auto p = glm::vec3(Float(-1.0f, 1.0f), Float(-1.0f, 1.0f), Float(-1.0f, 1.0f));
                if (glm::length2(p) > 1) {
                    continue;
                }

                return p;
            }
        }

        glm::vec3 RandomInHemisphere(const glm::vec3 &normal) {
            auto inUnitSphere = RandomInUnitSphere();
            if (glm::dot(inUnitSphere, normal) > 0) { // in the same hemisphere as the normal
                return inUnitSphere;
            } else {
                return -inUnitSphere;
            }
        }

        glm::vec3 RandomInDirection(const glm::vec3 &normal, float spread = 0.2f) {
            while (true) {
                auto inUnitSphere = RandomInUnitSphere();
                if (glm::dot(inUnitSphere, normal) > (1 - spread)) {
                    return inUnitSphere;
                }
            }
        }

    private:
        std::default_random_engine generator;
        std::mt19937_64 generator64;
    };
} // EngineCore::Core
