
#include "rendering/Window.h"



int main() {

	rendering::Window window(640, 480, "Pong");

	while (!window.WindowShouldClose()) {
		window.Clear();


		window.EndFrame();
	}

	return 0;
}