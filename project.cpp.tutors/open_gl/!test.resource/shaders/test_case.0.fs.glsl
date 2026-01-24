#version 460

uniform vec4 clr_line_in;
out vec4     clr_line_out;

void main() {
	clr_line_in = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	clr_line_out = clr_line_in;
}
