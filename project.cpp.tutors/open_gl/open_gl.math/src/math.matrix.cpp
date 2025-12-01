/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:25:16.417, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface implementation file;
*/
#include "math.matrix.h"

using namespace ex_ui::draw::open_gl::math;

CMat2x2:: CMat2x2 (void) {}
CMat2x2:: CMat2x2 (const CMat2x2& _src) : CMat2x2() { *this = _src; }
CMat2x2:: CMat2x2 (CMat2x2&& _victim) : CMat2x2() { *this = _victim; }
CMat2x2::~CMat2x2 (void) {}


CMat2x2&  CMat2x2::operator = (const CMat2x2& _src) { _src; return *this; }
CMat2x2&  CMat2x2::operator = (CMat2x2&& _victim) { _victim; return *this; }