#version 460

in vec3 pos_line_in;

uniform mat4 projection = mat4(1.0);
uniform mat4 model = mat4(1.0);

void main() {
	gl_Position = vec4(pos_line_in, 1.0f);
//	gl_Position = projection * model * vec4(pos_line_in, 1.0f);
}
