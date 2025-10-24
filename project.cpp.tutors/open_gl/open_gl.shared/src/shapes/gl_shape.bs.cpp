/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 22:08:22.288, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D/3D shape wrapper interface implementation file;
*/
#include "gl_shape.bs.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::data;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_3 { void __warning_lnk_4221 (void) {}}}}}

/////////////////////////////////////////////////////////////////////////////

CData:: CData (void) : m_index(0), m_normal(false), m_offset(0), m_stride(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CData::~CData (void) {}

TError& CData::Error (void) const { return this->m_error; }

uint32_t CData::Index (void) const { return this->m_index; }
bool     CData::Index (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = this->Index() != _u_ndx;
	if (b_changed)
		this->m_index = _u_ndx;
	return b_changed;
}

bool   CData::Is_normalized (void) const { return this->m_normal; }
bool   CData::Is_normalized (const bool _b_state) {
	_b_state;
	const bool b_changed =  this->Is_normalized() != _b_state;
	if (b_changed)
		this->m_normal = _b_state;

	return b_changed;
}

const
TRawData& CData::Raw (void) const { return this->m_data; }
TRawData& CData::Raw (void)       { return this->m_data; }

uint32_t  CData::Offset (void) const { return this->m_offset; }
bool      CData::Offset (const uint32_t _u_offset) {
	_u_offset;
	const bool b_changed = this->Offset() != _u_offset;
	if (b_changed)
		this->m_offset = _u_offset;
	return b_changed;
}

uint32_t  CData::Stride (void) const { return this->m_stride; }
bool      CData::Stride (const uint32_t _u_stride) {
	_u_stride;
	const bool b_changed = this->Stride() != _u_stride;
	if (b_changed)
		this->m_stride = _u_stride;
	return b_changed;
}

uint32_t  CData::Size  (void) const { return static_cast<uint32_t>(sizeof(float) * this->Raw().size()); }