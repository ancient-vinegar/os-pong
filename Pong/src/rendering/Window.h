#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace rendering {
	class Window
	{
	private:
		GLFWwindow* window = nullptr;
		int width = 0;
		int height = 0;
	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* GetWindow() { return window; }

		void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
		void Clear();
		void EndFrame();
		inline bool WindowShouldClose() { return glfwWindowShouldClose(window); }

		void ImGui_Init();
		void ImGui_Start();
		void ImGui_End();
	};
}
