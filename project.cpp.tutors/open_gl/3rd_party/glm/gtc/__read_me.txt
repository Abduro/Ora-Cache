GTC stands for: GLM Technical Core (often referred to as Stable Extensions)

Purpose:
It extends the core GLSL functionality provided in the root glm/ directory with specialized, common graphics tools like matrix transformations, matrix inversion, and data type pointers.

Usage:
You include them by using #include <glm/gtc/filename.hpp>

Common GTC Header Files

<glm/gtc/matrix_transform.hpp>:
Used to generate common transformation matrices, such as
glm::translate, glm::rotate, glm::scale, glm::lookAt, glm::perspective, and glm::ortho.

<glm/gtc/type_ptr.hpp>:
Provides functions to convert matrices and vectors into a const float* (pointer),
which is necessary for sending data to OpenGL shaders using glUniformMatrix4fv or glUniform3fv.

<glm/gtc/matrix_inverse.hpp>:
Contains functions for calculating the inverse of matrices (e.g., inverseTranspose).

<glm/gtc/quaternion.hpp>:
Provides support for quaternions for rotations.