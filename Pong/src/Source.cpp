
#define _USE_MATH_DEFINES

#include "rendering/Window.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/IndexBuffer.h"
#include "rendering/Shader.h"
#include "rendering/Camera2D.h"

#include "input/Keyboard.h"

#include "glm/glm.hpp"

#include <iostream>
#include <cmath>

float player1pos = 0.0f;
float player2pos = 0.0f;
glm::vec2 ballVelocity(0.0f, 0.0f);
float ballXpos = 0.0f, ballYpos = 0.0f;
bool ballRolling = false;

void Reset() {
	ballRolling = false;
	ballVelocity = glm::vec2(0.0f, 0.0f);
	ballXpos = 0.0f;
	ballYpos = 0.0f;
	player1pos = 0.0f;
	player2pos = 0.0f;
}

glm::vec2 RotateVec2(glm::vec2 vector, float radians) {
	return glm::vec2(vector.x * std::cos(radians) - vector.y * std::sin(radians),
		vector.x * std::sin(radians) + vector.y * std::cos(radians));
}

float DegreesToRadians(float degrees) {
	return degrees * (M_PI / 180.0f);
}

int main() {

	rendering::Window window(640, 480, "Pong");
	rendering::Camera2D camera(640.0f, 480.0f, -1.0f, 1.0f);
	input::Keyboard keyboard(window.GetWindow());

	float player1Speed = 5.0f;
	float player2Speed = 5.0f;
	float ballSpeed = 5.0f;

	float playerVertices[] = {
		-5.0f, -40.0f,
		 5.0f, -40.0f,
		 5.0f,  40.0f,
		-5.0f,  40.0f
	};

	std::cout << "Player Vertices :: " << sizeof playerVertices << std::endl;

	float ballVertices[] = {
		-5.0f, -5.0f,
		 5.0f, -5.0f,
		 5.0f,  5.0f,
		-5.0f,  5.0f
	};

	std::cout << "Ball Vertices :: " << sizeof ballVertices << std::endl;

	unsigned int quadIndices[]{
		0, 1, 2,
		2, 3, 0
	};

	std::cout << "Quad Indices :: " << sizeof quadIndices << std::endl;

	rendering::VertexBuffer playerVb(playerVertices, sizeof playerVertices);
	rendering::VertexBuffer ballVb(ballVertices, sizeof ballVertices);

	rendering::VertexBufferLayout basicLayout;
	basicLayout.PushFloat(2);

	rendering::VertexArray playerArray;
	playerArray.AddBuffer(playerVb, basicLayout);
	rendering::VertexArray ballArray;
	ballArray.AddBuffer(ballVb, basicLayout);

	rendering::IndexBuffer quadBuff(quadIndices, sizeof quadIndices);

	rendering::Shader shader("res/shaders/basic.shader");
	shader.Bind();
	glm::mat4 camView = camera.GetMatrix();
	shader.SetUniformMat4f("view", camView);
	shader.SetUniform2f("model", 0.0f, 0.0f);

	while (!window.WindowShouldClose()) {
		keyboard.Update(window.GetWindow());
		
		if (keyboard.KeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}

		if (!ballRolling)
		if (keyboard.KeyPressed(GLFW_KEY_SPACE)) {
			ballVelocity = glm::vec2(ballSpeed, 0.0f);
		}

		if (keyboard.KeyPressed(GLFW_KEY_R)) {
			Reset();
		}

		if (keyboard.KeyHeld(GLFW_KEY_W)) {
			player1pos += player1Speed;
		}

		if (keyboard.KeyHeld(GLFW_KEY_S)) {
			player1pos -= player1Speed;
		}

		if (keyboard.KeyHeld(GLFW_KEY_I)) {
			player2pos += player2Speed;
		}

		if (keyboard.KeyHeld(GLFW_KEY_K)) {
			player2pos -= player2Speed;
		}

		if ((ballXpos <= -295.0f) && (ballYpos <= player1pos + 40.0f && ballYpos >= player1pos - 40.0f)) {
			float ballHitPos = player1pos - ballYpos;
			if (ballHitPos < 0.0f) {
				ballVelocity = RotateVec2(ballVelocity, DegreesToRadians(-45.0f * (ballHitPos / 40.0f)));
			}
			if (ballHitPos > 0.0f) {
				ballVelocity = RotateVec2(ballVelocity, DegreesToRadians(45.0f * (ballHitPos / 40.0f)));
			}
			ballVelocity = glm::vec2(ballVelocity.x * -1, ballVelocity.y * -1);
		}

		if ((ballXpos >= 295.0f) && (ballYpos <= player2pos + 40.0f && ballYpos >= player2pos - 40.0f)) {
			float ballHitPos = player2pos - ballYpos;
			if (ballHitPos < 0.0f) {
				ballVelocity = RotateVec2(ballVelocity, DegreesToRadians(-45.0f * (ballHitPos / 40.0f)));
			}
			if (ballHitPos > 0.0f) {
				ballVelocity = RotateVec2(ballVelocity, DegreesToRadians(45.0f * (ballHitPos / 40.0f)));
			}
			ballVelocity = glm::vec2(ballVelocity.x * -1, ballVelocity.y * -1);
		}

		if (ballYpos <= -240.0f || ballYpos >= 240.0f) {
			ballVelocity = glm::vec2(ballVelocity.x, ballVelocity.y *= -1);
		}

		if (ballXpos <= -320.0f) {
			Reset();
		}

		if (ballXpos >= 320.0f) {
			Reset();
		}

		ballXpos += ballVelocity.x;
		ballYpos += ballVelocity.y;

		window.Clear();



		shader.SetUniform2f("model", -300.0f, player1pos);
		window.Draw(playerArray, quadBuff, shader);

		shader.SetUniform2f("model", 300.0f, player2pos);
		window.Draw(playerArray, quadBuff, shader);

		shader.SetUniform2f("model", ballXpos, ballYpos);
		window.Draw(ballArray, quadBuff, shader);

		window.EndFrame();
	}

	return 0;
}