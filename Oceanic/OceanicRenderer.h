#pragma once

#include <stdint.h>

class OceanicRenderer
{
public:
	OceanicRenderer() = default;
	OceanicRenderer(uint32_t width, uint32_t height) :
		m_ViewportWidth(width), m_ViewportHeight(height) {}
	~OceanicRenderer() = default;
public:
	void Render();
private:
	uint32_t m_ViewportWidth, m_ViewportHeight;
};