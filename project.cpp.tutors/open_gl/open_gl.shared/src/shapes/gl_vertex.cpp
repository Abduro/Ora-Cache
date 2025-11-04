/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:32:59.316, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface implementation file;
*/
#include "gl_vertex.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs.h"
#include "procs\gl_procs_vertex.h"
#include "gl_viewport.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;
using namespace ex_ui::color::rgb;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;

/////////////////////////////////////////////////////////////////////////////
#if (1)
CCoord:: CCoord (const float _x, const float _y, const float _z) : m_coord{_x, _y, _z} {}
CCoord:: CCoord (const CCoord& _src) : CCoord() { *this = _src; }
CCoord:: CCoord (CCoord&& _victim) : CCoord() { *this = _victim; }

float CCoord::X (void) const { return this->m_coord[0]; } void  CCoord::X (const float _x) { this->m_coord[0] = _x; } float& CCoord::X (void) { return this->m_coord[0]; }
float CCoord::Y (void) const { return this->m_coord[1]; } void  CCoord::Y (const float _y) { this->m_coord[1] = _y; } float& CCoord::Y (void) { return this->m_coord[1]; }
float CCoord::Z (void) const { return this->m_coord[2]; } void  CCoord::Z (const float _z) { this->m_coord[2] = _z; } float& CCoord::Z (void) { return this->m_coord[2]; }

CCoord& CCoord::operator = (const CCoord& _src) { this->X() = _src.X(); this->Y() = _src.Y(); this->Z() = _src.Z(); return *this; }
CCoord& CCoord::operator = (CCoord&& _victim) { *this = (const CCoord&)_victim; return *this; } // no move or swap operation;
#endif
/////////////////////////////////////////////////////////////////////////////

// https://stackoverflow.com/questions/64471026/does-stdvector-reserve-erase-existing-values ;
// https://medium.com/@ryan_forrester_/c-initialize-vector-with-size-how-to-guide-bf419adbc739 ;
CData:: CData (TVertData& _data) :  m_data(_data), m_index(0), m_normal(false), m_offset(0), m_stride(0), m_size(4) {
	this->Stride(static_cast<uint32_t>(sizeof(float) * this->m_data.size()));
}
CData::~CData (void) {}

CString  CData::Class (void) { return __CLASS__; }

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

uint32_t  CData::Size  (void) const { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CColor:: CColor (TVertData& _data) : CData(_data) {
	CData::m_offset = 3; // it is the count of the position elements and the size of the data type;
	CData::m_size = 4; // r|g|b|a;
}
CColor::~CColor (void) {}

void CColor::Set (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	const uint32_t n_size = static_cast<uint32_t>(CData::m_data.size());
	const uint32_t n_req = CData::Offset() + this->Size();

	if (n_req > n_size)
		return;

	CData::m_data[0 + CData::Offset()] = (0.0f > _r ? 0.0f : (1.0f < _r ? 1.0f : _r));
	CData::m_data[1 + CData::Offset()] = (0.0f > _g ? 0.0f : (1.0f < _g ? 1.0f : _g));
	CData::m_data[2 + CData::Offset()] = (0.0f > _b ? 0.0f : (1.0f < _b ? 1.0f : _b));
	CData::m_data[3 + CData::Offset()] = (0.0f > _a ? 0.0f : (1.0f < _a ? 1.0f : _a));
}

void CColor::Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) {
	_r; _g; _b; _a;
	const uint32_t n_size = static_cast<uint32_t>(CData::m_data.size());
	const uint32_t n_req = CData::Offset() + this->Size();

	if (n_req > n_size)
		return;

	// the color channels' sequence: r-g-b-a;
	CData::m_data[0 + CData::Offset()] = _r;
	CData::m_data[1 + CData::Offset()] = _g;
	CData::m_data[2 + CData::Offset()] = _b;
	CData::m_data[3 + CData::Offset()] = _a;
}

void CColor::Set (const rgb_color _rgba) {
	_rgba;
	const uint32_t n_size = static_cast<uint32_t>(CData::m_data.size());
	const uint32_t n_req = CData::Offset() + this->Size();

	if (n_req > n_size)
		return;
	// the color channels' sequence: r-g-b-a;
	CData::m_data[0 + CData::Offset()] = CConvert::ToFloat(get_r_value(_rgba));
	CData::m_data[1 + CData::Offset()] = CConvert::ToFloat(get_g_value(_rgba));
	CData::m_data[2 + CData::Offset()] = CConvert::ToFloat(get_b_value(_rgba));
	CData::m_data[3 + CData::Offset()] = CConvert::ToFloat(get_a_value(_rgba));
}

CPosition:: CPosition (TVertData& _data) : CData(_data) {
	CData::m_offset = 0; // this value is set by the parent class, but for better readability it is shown here; position's elements start from the beginning of the data vector;
	CData::m_size = 3;   // x|y|z;
}
CPosition::~CPosition (void) {}

void CPosition::Set (const float _x, const float _y, const float _z) {
	_x; _y; _z;
	const uint32_t n_size = static_cast<uint32_t>(CData::m_data.size());
	const uint32_t n_req = CData::Offset() + this->Size();

	if (n_req > n_size) // the offset, elements/components' count/size and vertex vector size must be appropriate;
		return;

	CData::m_data[0 + CData::Offset()] = (-1.0f > _x ? -1.0f : (1.0f < _x ? 1.0f : _x));
	CData::m_data[1 + CData::Offset()] = (-1.0f > _y ? -1.0f : (1.0f < _y ? 1.0f : _y));
	CData::m_data[2 + CData::Offset()] = (-1.0f > _z ? -1.0f : (1.0f < _z ? 1.0f : _z));
}

void CPosition::Set (const long  _x, const long  _y) {
	_x; _y;
}

/////////////////////////////////////////////////////////////////////////////

CVertex:: CVertex (void) : m_data(7, 0.0f), m_clr(m_data), m_pos(m_data) { this->m_error >>__CLASS__<< __METHOD__<<__e_not_inited; this->m_data.reserve(7); } // not sure the 'reserve' is required;
CVertex::~CVertex (void) {}

TError&   CVertex::Error (void) const { return this->m_error; }

const
vertex::CColor& CVertex::Clr (void) const { return this->m_clr; }
vertex::CColor& CVertex::Clr (void)       { return this->m_clr; }

const
vertex::CPosition& CVertex::Pos (void) const { return this->m_pos; }
vertex::CPosition& CVertex::Pos (void)       { return this->m_pos; }

const
TVertData& CVertex::Raw (void) const { return this->m_data; }
TVertData& CVertex::Raw (void)       { return this->m_data; }

uint32_t   CVertex::Size(void) const {
	return this->Clr().Size() + this->Pos().Size();
}