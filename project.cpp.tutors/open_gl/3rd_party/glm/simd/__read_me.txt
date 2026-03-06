SIMD (Single Instruction, Multiple Data) hardware acceleration, such as SSE, AVX, or NEON

Hardware Acceleration (SIMD):
It enables GLM to use special CPU instructions to process multiple data points (like four 32-bit floats) in a single instruction, significantly speeding up math operations.

Performance Optimization:
While GLM is designed to be portable and mostly header-only, the simd folder provides highly optimized code paths for performance-critical sections of graphics code
(e.g., matrix-vector multiplication, vertex transformations).

Intrinsics:
The headers in this folder rely on compiler intrinsics (e.g., <xmmintrin.h>) that allow the code to directly use SIMD instructions.

How it's Used:
Generally, these are not intended to be called directly by the user. Instead, GLM automatically uses these specialized paths when certain preprocessor definitions are set,
such as GLM_FORCE_SSE2, GLM_FORCE_AVX, or GLM_FORCE_INTRINSICS