#pragma once

class Application
{
public:
	virtual void Start() {}
	virtual bool Flags() { return false; }
	virtual void OnUpdate(float dt) {}
	virtual void End() {}
};