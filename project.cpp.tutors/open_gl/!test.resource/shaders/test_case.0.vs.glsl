#version 460

in vec3 pos_line_in;
layout (location = 0) out vec4 clr_out;

void main() {
	gl_Position = vec4(pos_line_in, 1.0f);
	clr_out = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
