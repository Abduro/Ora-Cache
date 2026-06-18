/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jun-2026 at 13:10:47.144, UTC+4, Batumi, Sunday;
	This is OpenGL drawable shape base interface implementation file.
*/
#include "shape.base.h"

using namespace ::open_gl::shapes;

#pragma region cls::CBase{}

CBase::CBase (void) {}

const
CMove&  CBase::Move (void) const { return this->m_move; }
CMove&  CBase::Move (void)       { return this->m_move; }
const
CRotate& CBase::Rotate (void) const { return this->m_rotate; }
CRotate& CBase::Rotate (void)       { return this->m_rotate; }
const
CScale& CBase::Scale (void) const { return this->m_scale; }
CScale& CBase::Scale (void)       { return this->m_scale; }

#pragma endregion