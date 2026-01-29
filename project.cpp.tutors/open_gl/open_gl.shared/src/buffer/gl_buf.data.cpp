/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jan-2026 at 17:49:54.373, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL vertex buffer data wrapper interface implementation file;
*/
#include "gl_buf.data.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::buffer;

#pragma region buffer::cls::CData{}

CData::CData (const e_object _target) : TPipe(_target),  m_bound_to(e_bnd_tgts::e__undef), m_buf_id(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
const
CTarget& CData::BoundTo (void) const { return this->m_bound_to; }
CTarget& CData::BoundTo (void)       { return this->m_bound_to; }

uint32_t CData::BufferId (void) const { return this->m_buf_id; }
bool     CData::BufferId (const uint32_t _u_buf_id) {
	_u_buf_id;
	const bool b_changed = this->BufferId() != _u_buf_id; if (b_changed) this->m_buf_id = _u_buf_id; return b_changed;
}

TError& CData::Error (void) const { return this->m_error; }
const
TRawData& CData::Get (void) const { return this->m_data; }

bool CData::Is_valid (void) const {
	return !!this->BufferId() && this->BoundTo() != e_bnd_tgts::e__undef;
}

err_code CData::Query (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid()) {
		this->m_error << __e_not_inited;
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); return this->Error();
	}

	if (__failed(::__get_buf_acc_procs().Get_Ptr(this->BufferId(), e_data_access::e_read, this->m_data))) {
		this->m_error = ::__get_buf_acc_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req));
	}

	return this->Error();
}

CData& CData::operator <<(e_bnd_tgts _target) { this->BoundTo() << _target; return *this; }
CData& CData::operator <<(const uint32_t _buf_id) { this->BufferId(_buf_id); return *this; }

#pragma endregion