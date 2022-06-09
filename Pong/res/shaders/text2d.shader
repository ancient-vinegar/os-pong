#shader vertex
#version 460

layout(location = 0) in vec2 posit;
layout(location = 1) in vec2 texCo;

out vec2 v_texCo;

uniform mat4 view;
uniform vec2 model;

void main() {
	gl_Position = view * vec4(posit.x + model.x, posit.y + model.y, 0.0f, 1.0f);
};

#shader fragment
#version 460

in vec2 v_texCo;

out vec4 fragColour;

uniform sampler2D u_Texture;

void main() {
	fragColour = texture(u_Textures, v_texCo);
};