#version 460

in vec3 pos_line_in;

void main() {
	gl_Position = vec4(pos_line_in, 1.0f);
}
