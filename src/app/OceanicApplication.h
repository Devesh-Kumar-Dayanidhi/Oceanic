#pragma once

#include <core/Application.h>
#include <string>

class OceanicApplication : public Oceanic::Application
{
public:
    OceanicApplication() :
		m_ViewportWidth(0), m_ViewportHeight(0), m_WindowTitle("") {}
    OceanicApplication(const std::string& title, uint32_t width, uint32_t height) :
		m_ViewportWidth(width), m_ViewportHeight(height), m_WindowTitle(title) {}
public:
	void Start() override;
	bool Flags() override;
	void OnUpdate(float dt) override;
	void End() override;
protected:
	uint32_t m_ViewportWidth, m_ViewportHeight;
	std::string m_WindowTitle;
};