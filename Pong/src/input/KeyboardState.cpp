#include "KeyboardState.h"

input::KeyboardState::KeyboardState(GLFWwindow* window)
{
	Keys[32] = Key(glfwGetKey(window, 32));
	Keys[39] = Key(glfwGetKey(window, 39));
	for (int i = 44; i < 58; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	Keys[59] = Key(glfwGetKey(window, 59));
	Keys[61] = Key(glfwGetKey(window, 61));
	for (int i = 65; i < 94; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	Keys[96] = Key(glfwGetKey(window, 96));
	Keys[161] = Key(glfwGetKey(window, 161));
	Keys[162] = Key(glfwGetKey(window, 162));
	for (int i = 256; i < 270; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	for (int i = 280; i < 285; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	for (int i = 290; i < 315; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	for (int i = 320; i < 337; i++)
		Keys[i] = Key(glfwGetKey(window, i));
	for (int i = 340; i < 349; i++)
		Keys[i] = Key(glfwGetKey(window, i));
}

bool input::KeyboardState::KeyDown(unsigned int key)
{
	bool r = false;
	if (Keys.find(key) != Keys.end())
		r = Keys.at(key).IsPressed;
	return r;
}
