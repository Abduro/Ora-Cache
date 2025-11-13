/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:32:59.316, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' vertex data base interface implementation file;
*/
#include "gl_vertex_data.h"
#include "gl_procs.h"
#include "gl_viewport.h"
#include "procs\gl_procs_vertex.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;
using namespace ex_ui::color::rgb;

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

CVertex:: CVertex (void) { this->m_error >>__CLASS__<< __METHOD__<<__e_not_inited; }
CVertex:: CVertex (const CVertex& _src) : CVertex() { *this = _src; }
CVertex:: CVertex (CVertex&& _victim) : CVertex() { *this = _victim; }
CVertex::~CVertex (void) {}

const
CAttrArray& CVertex::Attrs (void) const { return this->m_attrs; }
CAttrArray& CVertex::Attrs (void)       { return this->m_attrs; }

TError&   CVertex::Error (void) const { return this->m_error; }

const
TVertData& CVertex::Raw (void) const { return this->m_data; }
TVertData& CVertex::Raw (void)       { return this->m_data; }

// https://stackoverflow.com/questions/64471026/does-stdvector-reserve-erase-existing-values ;
// https://medium.com/@ryan_forrester_/c-initialize-vector-with-size-how-to-guide-bf419adbc739 ;

err_code   CVertex::Update (void) {
	this->m_error <<__METHOD__<<__s_ok;
	try {
		this->m_data.resize(this->Size(), 0.0f); this->m_data.reserve(this->Size());
#if (0)
		TAttrData::const_iterator pos_b = this->Attrs().Pos().Data().begin() + 1;
		TAttrData::const_iterator pos_e = pos_b + this->Attrs().Pos().Size();

		TAttrData::iterator it_to = this->m_data.begin() + 1;

		// copies the position attribute values first;
		::std::copy(pos_b, pos_e, it_to);

		TAttrData::const_iterator clr_b = this->Attrs().Clr().Data().begin() + 1;
		TAttrData::const_iterator clr_e = clr_b + this->Attrs().Clr().Size();

		it_to += this->Attrs().Pos().Size();

		// copies the color attribute values second;
		::std::copy(clr_b, clr_e, it_to);
#else
		for (uint32_t i_ = 0; i_ < this->Size(); i_++) {
			for (uint32_t j_ = 0; j_ < this->Attrs().Pos().Size(); j_++, i_++) this->m_data.at(i_) =  this->Attrs().Pos().Data().at(j_);
			for (uint32_t j_ = 0; j_ < this->Attrs().Clr().Size(); j_++, i_++) this->m_data.at(i_) =  this->Attrs().Clr().Data().at(j_);
		}
#endif
	}
	catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }
	catch (const ::std::out_of_range&) { this->m_error << __e_inv_arg; } // the error code must be other not this one;
	return this->Error();
}

uint32_t   CVertex::Size(void) const {
	return this->Attrs().Clr().Size() + this->Attrs().Pos().Size();
}

CVertex&   CVertex::operator = (const CVertex& _src) { this->Attrs() = _src.Attrs(); this->m_data = _src.m_data;  return *this; }
CVertex&   CVertex::operator = (CVertex&& _victim) { *this = (const CVertex&)_victim; return *this; }