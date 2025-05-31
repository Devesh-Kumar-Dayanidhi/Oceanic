#include "Utils.h"

uint32_t Utils::Vec4ToRGBA(const glm::vec4& color)
{
	uint8_t r = (uint8_t)(color.r * 255.0f);
	uint8_t g = (uint8_t)(color.g * 255.0f);
	uint8_t b = (uint8_t)(color.b * 255.0f);
	uint8_t a = (uint8_t)(color.a * 255.0f);

	uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
	return result;
}

glm::vec2 Utils::NDCToScreenSpace(glm::vec2 coord, uint32_t width, uint32_t height)
{
	coord = 0.5f * glm::vec2(width, height) * (coord + 1.0f);
	return coord;
}

glm::vec2 Utils::ScreenSpaceToNDC(glm::vec2 coord, uint32_t width, uint32_t height)
{
	coord = (coord / glm::vec2(width, height)) * 2.0f - 1.0f;
	return coord;
}
