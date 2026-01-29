/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jan-2026 at 18:28:44.530, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL vertex buffer bind target wrapper interface implementation file;
*/
#include "gl_buf.bind.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::buffer;

#pragma region cls::CTarget{}

CTarget:: CTarget (const e_bnd_tgts _bound_to) : m_bound_to(_bound_to) {}

e_bnd_tgts CTarget::Get (void) const { return this->m_bound_to; }
const bool CTarget::Set (const e_bnd_tgts _e_bound_to) {
	_e_bound_to;
	const bool b_changed = this->Get() != _e_bound_to; if (b_changed) this->m_bound_to = _e_bound_to; return b_changed;
}

CString  CTarget::To_str (const e_bnd_tgts _e_target) {
	_e_target;
	CString cs_out;
	switch (_e_target) {
	case e_bnd_tgts::e_array   : cs_out = _T("$__gl_array"); break;
	case e_bnd_tgts::e_counter : cs_out = _T("$__gl_counter"); break;
	case e_bnd_tgts::e_read    : cs_out = _T("$__gl_copy_read"); break;
	case e_bnd_tgts::e_write   : cs_out = _T("$__gl_copy_write"); break;
	case e_bnd_tgts::e_disp    : cs_out = _T("$__gl_disp_inderect"); break;
	case e_bnd_tgts::e_draw    : cs_out = _T("$__gl_draw_indirect"); break;
	case e_bnd_tgts::e_el_arr  : cs_out = _T("$__gl_element_arr"); break;
	case e_bnd_tgts::e_pxl_pk  : cs_out = _T("$__gl_pixel_pack"); break;
	case e_bnd_tgts::e_pxl_unpk: cs_out = _T("$__gl_pixel_unpack"); break;
	case e_bnd_tgts::e_query   : cs_out = _T("$__gl_query"); break;
	case e_bnd_tgts::e_$_stg   : cs_out = _T("$__gl_shader_stg"); break;
	case e_bnd_tgts::e_texture : cs_out = _T("$__gl_texture"); break;
	case e_bnd_tgts::e_trans   : cs_out = _T("$__gl_transform"); break;
	case e_bnd_tgts::e_uniform : cs_out = _T("$__gl_uniform"); break;
	default:
		cs_out = _T("#undef");
	}
	return  cs_out;
}

CTarget& CTarget::operator <<(const e_bnd_tgts _e_bound_to) { this->Set(_e_bound_to); return *this; }

CTarget::operator e_bnd_tgts (void) const { return this->Get(); }


#pragma endregion