/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2026 at 19:56:50.627, UTC+4, Batumi, Thursday;
	This is drawable shape vertex interface implementation file.
*/
#include "shape.vertex.h"

using namespace ::open_gl::shapes;

#pragma region cls::CVertex{}

CVertex::CVertex (void) : m_point{0.0f}, m_color{0.0f} {}
CVertex::CVertex (const CVertex& _src) : CVertex() { *this = _src; }

const
f_set_3& CVertex::Color (void) const { return this->m_color; }
f_set_3& CVertex::Color (void)       { return this->m_color; }
const
f_set_3& CVertex::Point (void) const { return this->m_point; }
f_set_3& CVertex::Point (void)       { return this->m_point; }

CVertex& CVertex::operator = (const CVertex& _src) {  this->Color() = _src.Color(); this->Point() = _src.Point(); return *this; }

#pragma endregion