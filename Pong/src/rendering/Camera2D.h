#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rendering {
	class Camera2D
	{
	private:
		float ScreenWidth;
		float ScreenHeight;
		glm::vec3 Position;
		float NearDist;
		float FarDist;
	public:
		Camera2D(float screenWidth, float screenHeight, float nearDist, float farDist);
		glm::mat4 GetMatrix();
	};
}

