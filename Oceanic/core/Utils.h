#pragma once

#include <stdint.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

#define Utils_DegToRad(x) (x * 0.0174533f)
#define Utils_RadToDeg(x) (x * 57.2958f)
#define Utils_Max(a, b) (a >= b ? a : b)
#define Utils_Min(a, b) (a <= b ? a : b)
#define Utils_Clamp(a, b, c) (a <= b ? b : (a >= c ? c : a)) // b <= a <= c

namespace Utils
{
	uint32_t Vec4ToRGBA(const glm::vec4& color);
	glm::vec2 NDCToScreenSpace(glm::vec2 coord, uint32_t width, uint32_t height);
	glm::vec2 ScreenSpaceToNDC(glm::vec2 coord, uint32_t width, uint32_t height);
}