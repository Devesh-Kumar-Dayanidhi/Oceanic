#pragma once

#include <stdint.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace Utils
{
	uint32_t Vec4ToRGBA(const glm::vec4& color);
}