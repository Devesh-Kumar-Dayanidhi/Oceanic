#pragma once

#include <stdint.h>
#include <glm/glm.hpp>

#include "Utils.h"

class OceanicRenderer
{
public:
	OceanicRenderer() = default;
	OceanicRenderer(uint32_t width, uint32_t height) :
		m_ViewportWidth(width), m_ViewportHeight(height), m_CameraPosition(), m_CameraDirection()
	{
		m_ImageData = new uint32_t[width * height];
	}
	~OceanicRenderer() = default;
public:
	void Render();
	inline const uint32_t* const ImageData() const { return m_ImageData; }
private:
	void FillVerticalLine(uint32_t xStart, uint32_t xEnd, uint32_t yStart, uint32_t yEnd, const glm::vec4& color);
private:
	uint32_t m_ViewportWidth, m_ViewportHeight;
	uint32_t* m_ImageData;
	glm::vec2 m_CameraPosition, m_CameraDirection;
};