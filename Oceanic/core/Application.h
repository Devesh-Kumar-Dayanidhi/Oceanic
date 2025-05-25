#pragma once

#include <stdint.h>
#include <time.h>

class Application
{
public:
	virtual void Start() {}
	virtual bool Flags() { return false; }
	virtual void OnUpdate(clock_t dt) {}
	virtual void End() {}
};