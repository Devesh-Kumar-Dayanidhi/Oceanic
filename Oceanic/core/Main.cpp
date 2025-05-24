#include "Application.h"

extern Application* FetchApplication();

int main()
{
	Application* app = FetchApplication();

	app->Start();
	while (!app->Flags())
	{
		app->OnUpdate(0.01f);
	}

	app->End();
	delete app;
}