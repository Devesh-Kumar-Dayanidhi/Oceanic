#include "OceanicRenderer.h"

#include <glm/glm.hpp>

#include "Utils.h"

#define RED_WALL 1
#define GREEN_WALL 2
#define BLUE_WALL 3

void OceanicRenderer::Render()
{
	uint32_t map[8][8] = {
		{1, 2, 3, 1, 2, 3, 1, 2},
		{2, 0, 0, 0, 0, 0, 0, 3},
		{3, 0, 1, 1, 3, 3, 0, 2},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{2, 0, 0, 0, 2, 0, 0, 3},
		{3, 0, 0, 0, 0, 0, 0, 2},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{2, 3, 1, 2, 3, 1, 2, 3},
	};
	uint32_t mapWidth = 8, mapHeight = 8;

	for (int i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
	{
		glm::vec4 v = glm::vec4(0.4f);
		uint32_t color = Utils::Vec4ToRGBA(v);
		m_ImageData[i] = color;
	}

	float fov = 90.0f;
	float angleStep = fov / static_cast<float>(m_ViewportWidth);
	float cameraAngle = atan2(m_CameraDirection.y, m_CameraDirection.x);

	for (int x = 0; x < m_ViewportWidth; ++x)
	{
		float angle = cameraAngle + Utils_DegToRad((x - m_ViewportWidth / 2.0f) * angleStep);

		glm::vec2 rayDirection = glm::vec2(cosf(angle), sinf(angle));
		glm::vec2 rayOrigin = m_CameraPosition;

		float t = 0.0f;
		const float maxT = 100.0f;
		const float step = 0.1f;

		glm::vec4 finalColor = glm::vec4(0.4f);

		while (t < maxT)
		{
			glm::vec2 point = rayOrigin + rayDirection * t;

			uint32_t mapX = static_cast<uint32_t>(point.x);
			uint32_t mapY = static_cast<uint32_t>(point.y);
			if (mapX >= mapWidth || mapY >= mapHeight)
				break;

			if (map[mapY][mapX] > 0)
			{
				switch (map[mapY][mapX])
				{
				case BLUE_WALL:
					finalColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case GREEN_WALL:
					finalColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case RED_WALL:
					finalColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				default:
					finalColor = glm::vec4(0.4f);
					break;
				}

				break;
			}

			t += step;
		}

		float correctedDistance = t * cos(angle - cameraAngle);
		float tileHeight = 2.0f;
		float wallHeight = (correctedDistance > 0.001f) ? (m_ViewportHeight * tileHeight) / correctedDistance : m_ViewportHeight;

		float yStart = 0.5f * (m_ViewportHeight - wallHeight);
		float yEnd = yStart + wallHeight;

		FillVerticalLine(x, x + 1.0f, yStart, yEnd, finalColor);
	}
}

void OceanicRenderer::FillVerticalLine(uint32_t xStart, uint32_t xEnd, uint32_t yStart, uint32_t yEnd, const glm::vec4& color)
{
	uint32_t rgba = Utils::Vec4ToRGBA(color);

	xStart = Utils_Clamp(xStart, 0, m_ViewportWidth);
	xEnd = Utils_Clamp(xEnd, 0, m_ViewportWidth);
	yStart = Utils_Clamp(yStart, 0, m_ViewportHeight);
	yEnd = Utils_Clamp(yEnd, 0, m_ViewportHeight);

	for (uint32_t x = xStart; x < xEnd; x++)
	{
		for (uint32_t y = yStart; y < yEnd; y++)
		{
			uint32_t index = x + y * m_ViewportWidth;
			m_ImageData[index] = rgba;
		}
	}
}
