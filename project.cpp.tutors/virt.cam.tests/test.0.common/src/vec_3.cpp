/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2026 at 23:47:35.970, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' 3D vertex interface implementation file;
*/
#include "vec_3.h"
/*thanks to Google AI and people who made it:
  it gives a perfect and clear answers for my queries; all comments are the excerpts from the AI answers;
*/
using namespace ::test::draw::data;

#pragma region str::s_vec_3{}

s_vec_3::s_vec_3 (const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
s_vec_3::s_vec_3 (const s_vec_3& _src) : s_vec_3() { *this = _src; }

// https://www.dictionary.com/browse/intersection :
// The common abbreviations for intersection are INTXN, Int., or simply INT, while math uses the symbol 'n'.
float s_vec_3::dot (const s_vec_3& _v_n) const { return this->x * _v_n.x + this->y * _v_n.y + this->z * _v_n.z; }

bool  s_vec_3::normalize (void) {
	const
	float length = ::std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (length > 0.0f) {
		this->x /= length;
		this->y /= length;
		this->z /= length;
		return true;
	} else return false;
}

s_vec_3& s_vec_3::operator = (const s_vec_3& _src) { this->x = _src.x; this->y = _src.y; this->z = _src.z; return *this; }
s_vec_3  s_vec_3::operator + (const s_vec_3& _addend) const {
	return {this->x + _addend.x, this->y + _addend.x, this->z + _addend.z};
} // In a basic arithmetic sum expression (like A + B = C), the individual numbers or items being added are called addends, and the final result is the sum.
s_vec_3  s_vec_3::operator - (const s_vec_3& _subtrahend) const {
	return {this->x - _subtrahend.x, this->y - _subtrahend.x, this->z - _subtrahend.z};
} // In a subtraction expression like 10 - 4 = 6, the starting number is the minuend, the number you take away is the subtrahend, and the answer is the difference.
s_vec_3  s_vec_3::operator * (const s_vec_3& _factor) const {
	return {this->x * _factor.x, this->y * _factor.x, this->z * _factor.z};
} // In a basic multiplication expression like 4 * 3 = 12, the numbers being multiplied are called factors, and the answer is called the product.

#pragma endregion