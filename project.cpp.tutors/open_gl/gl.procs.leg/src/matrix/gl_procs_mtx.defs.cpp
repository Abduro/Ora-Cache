/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jun-2026 at 22:49:02.286, UTC+4, Batumi, Saturday;
	This is OpenGL matrix related procedures' common definitions' file;
*/
#include "gl_procs_mtx.defs.h"

using namespace ::open_gl::procs::matrix::ver_1_1;

#pragma region cls::CEnum{}

CEnum::CEnum (void) : m_mode(e_stk_mode::e_modelview), m_type(e_mat_type::e_modelview) {}
CEnum::CEnum (const e_mat_type _from) : CEnum() { this->m_mode = *this << _from; }
CEnum::CEnum (const e_stk_mode _from) : CEnum() { this->m_type = *this << _from; }

e_stk_mode CEnum::Get (const e_mat_type _from) const {
	this->m_type = _from;
	switch (_from) {
	case e_mat_type::e_project: return this->m_mode = e_stk_mode::e_project;
	case e_mat_type::e_texture: return this->m_mode = e_stk_mode::e_texture;
	default: return this->m_mode = e_stk_mode::e_modelview;
	}
}
e_mat_type CEnum::Get (const e_stk_mode _from) const {
	this->m_mode = _from;
	switch (_from) {
	case e_stk_mode::e_project: return this->m_type = e_mat_type::e_project;
	case e_stk_mode::e_texture: return this->m_type = e_mat_type::e_texture;
	default: return this->m_type = e_mat_type::e_modelview;
	}
}

e_stk_mode CEnum::operator <<(const e_mat_type _from) const { return this->Get(_from); }
e_mat_type CEnum::operator <<(const e_stk_mode _from) const { return this->Get(_from); }

_pc_sz CEnum::To_str (const e_mat_type _type) {
	_type;
	static  CString cs_out;
	switch (_type){
	case e_mat_type::e_project: cs_out = _T("e_project"); break;
	case e_mat_type::e_texture: cs_out = _T("e_texture"); break; default: cs_out = _T("e_modelview");
	}
	return (_pc_sz) cs_out;
}
_pc_sz CEnum::To_str (const e_stk_mode _mode) {
	_mode;
	static  CString cs_out;
	switch (_mode){
	case e_stk_mode::e_project: cs_out = _T("e_project"); break;
	case e_stk_mode::e_texture: cs_out = _T("e_texture"); break; default: cs_out = _T("e_modelview");
	}
	return (_pc_sz) cs_out;
}

CEnum::operator e_stk_mode (void) const { return this->m_mode; }
CEnum::operator e_mat_type (void) const { return this->m_type; }

#pragma endregion