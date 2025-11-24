#version 460
    in  vec4 fragementColor;  // error(#5) extension: "explicit attribute location in fragment shader is only supported for the out storage qualifier";
    out vec4 color;           // writes its output to the color buffer at index 0 ;

    void main() {
        color = fragementColor;
    }