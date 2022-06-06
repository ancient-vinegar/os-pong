#shader vertex
#version 460

layout(location = 0) in vec2 posit;

uniform mat4 view;
uniform vec2 model;

void main() {
	gl_Position = view * vec4(posit.x + model.x, posit.y + model.y, 0.0f, 1.0f);
};

#shader fragment
#version 460

out vec4 fragColour;

void main() {
	fragColour = vec4(1.0f, 0.8f, 0.8f, 1.0f);
};