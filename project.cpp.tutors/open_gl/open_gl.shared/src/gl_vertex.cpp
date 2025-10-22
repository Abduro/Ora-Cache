/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:32:59.316, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface implementation file;
*/
#include "gl_vertex.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs.h"
#include "procs\gl_procs_vertex.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;

procs::vertex::CArray& __get_procs (void) {
	static procs::vertex::CArray procs;
	return procs;
}

vertex::CArray:: CArray (void) : m_arr_id(0) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
vertex::CArray::~CArray (void) {}

err_code vertex::CArray::Bind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (this->Is_bound()) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("the array of '_arr_id' (%u) is already bound"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}
	if (__failed(__get_procs().Bind(this->GetId()))) {
		this->m_error = __get_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(_T("The array of id = %u is bound;\n"), this->GetId());
	}
	return this->Error();
}

bool vertex::CArray::Is_bound (void) const {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	const int32_t n_result = __get_procs_param().GetInt(__gl_arr_bound);
	if (__get_procs_param().Error()) {
		this->m_error = __get_procs_param().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false;
	}
	const bool b_result = this->GetId()== static_cast<uint32_t>(n_result);
	if (false == b_result)
		__trace_info_2(_T("the array of '_arr_id' (%u) is not bound;\n"), this->GetId());

	return b_result;
}

err_code vertex::CArray::Create (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (!!this->GetId()) {
		this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(_T("#__e_inv_state: array (id = %u) already exists"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}
	if (__failed(__get_procs().GetIds(1, &this->m_arr_id))) {
		this->m_error = __get_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_impt_2(_T("The vertex array (id = %u) is created;\n"), this->m_arr_id);
	}
	return this->Error();
}

err_code vertex::CArray::Delete (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (0 == this->GetId())  // if the array is not created yet success is returned and just keeping the silence;
		return this->Error();

	if (__failed(__get_procs().Delete(1, &this->m_arr_id))) {
		this->m_error = __get_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The vertex array (id = %u) is deleted;\n"), this->m_arr_id);
		this->m_arr_id = 0;
	}
	return this->Error();
}

TError&  vertex::CArray::Error (void) const { return this->m_error; }

uint32_t vertex::CArray::GetId (void) const { return this->m_arr_id; }

err_code vertex::CArray::Unbind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (false == this->Is_bound()) {
		__trace_info_2(_T("The array id = %u is not bound;\n"), this->GetId());
		return this->Error();
	}
	if (__failed(__get_procs().Bind(0))) {
		this->m_error = __get_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else
		__trace_info_2(_T("The array id = %u is unbound;\n"), this->GetId());

	return this->Error();
}

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
#if (0)
CVertex:: CVertex (void) { this->m_error >>__CLASS__<< __METHOD__<<__e_not_inited; }
CVertex::~CVertex (void) {}

TError&  CVertex::Error (void) const { return this->m_error; }
#endif