#include "Camera2D.h"

rendering::Camera2D::Camera2D(float screenWidth, float screenHeight, float nearDist, float farDist)
	: ScreenHeight(screenHeight), ScreenWidth(screenWidth), FarDist(farDist), NearDist(nearDist)
{
	Position = glm::vec3(0.0f);
}

glm::mat4 rendering::Camera2D::GetMatrix()
{
	glm::mat4 proj = glm::ortho(
		-(ScreenWidth / 2), ScreenWidth / 2,
		-(ScreenHeight / 2), ScreenHeight / 2,
		FarDist, NearDist
	);
	glm::mat4 view = glm::translate(
		glm::mat4(1.0f),
		Position
	);
	return proj * view;
}
