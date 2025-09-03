/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Sep-2025 at 02:13:46.166, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL version wrapper interface implementation file;
*/
#include "gl_version.h"
#include "gl_context.h"

#include "shared.dbg.h"           // using Print() function is perhaps useful, but it looks like need to be reviewed;
#include "open_gl_tutor.0.fake.h" // for getting fake message-only window interface that is used for creating device context renderer of the OpenGL;

using namespace ex_ui::draw::open_gl;
#if (0) // fake window is not used directly, it is assumed the context is already created and selected before calling this version API;
#pragma comment(lib, "gl.tutor.0.fake.lib") 
#endif
namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	using namespace shared::defs;

	class CVer_Att_Fmt {
	public:
		CVer_Att_Fmt (const CVer_Att& _att) : m_att_ref(_att) {}
		CVer_Att_Fmt (void) = delete; CVer_Att_Fmt (const CVer_Att_Fmt&) = delete; CVer_Att_Fmt (CVer_Att_Fmt&&) = delete; ~CVer_Att_Fmt (void) {}

		CString Id (void) const {
			switch (this->m_att_ref.Id()) {
				case CVersion::e_atts::e_render : return CString(_T("e_render"));
				case CVersion::e_atts::e_shader : return CString(_T("e_shader"));
				case CVersion::e_atts::e_vendor : return CString(_T("e_vendor"));
				case CVersion::e_atts::e_version: return CString(_T("e_version"));
				default:
					return CString(_T("#unknown"));
			}
		}

		CString Name (void) const {
			switch (this->m_att_ref.Id()) {
				case CVersion::e_atts::e_render : return CString(_T("GL_RENDERER"));
				case CVersion::e_atts::e_shader : return CString(_T("GL_SHADING_LANGUAGE_VERSION"));
				case CVersion::e_atts::e_vendor : return CString(_T("GL_VENDOR"));
				case CVersion::e_atts::e_version: return CString(_T("GL_VERSION"));
				default:
					return CString(_T("#undef"));
			}
		}

	private:
		CVer_Att_Fmt& operator = (const CVer_Att_Fmt&) = delete; CVer_Att_Fmt& operator = (CVer_Att_Fmt&&) = delete;
		const CVer_Att& m_att_ref;
	};

}}}}
using namespace ex_ui::draw::open_gl::_impl;

/////////////////////////////////////////////////////////////////////////////
/*
	https://registry.khronos.org/OpenGL/api/GL/glext.h ;

	GL_SHADING_LANGUAGE_VERSION is defined in glext.h, like this:
	#define GL_SHADING_LANGUAGE_VERSION 0x8b8c ;
*/

CVer_Att:: CVer_Att (const uint32_t _n_id/* = 0*/, _pc_sz _p_name/* = _T("#undef")*/, _pc_sz _p_value/* = _T("#unset")*/) {
	*this << _n_id << _p_name >> _p_value;
}
CVer_Att:: CVer_Att (const CVer_Att& _src) : CVer_Att() { *this = _src; }
CVer_Att:: CVer_Att (CVer_Att&& _victim) : CVer_Att() { *this = _victim; }

uint32_t CVer_Att::Id (void) const { return this->m_n_id; }
bool     CVer_Att::Id (const uint32_t _n_id) {
	_n_id;
	const bool b_changed = this->Id() != _n_id || 0 == _n_id; // ToDo: default value on the creating this object is initialized by 0;
	if (b_changed) {
		this->m_n_id = _n_id;
		this->Name(CVer_Att_Fmt(*this).Name());
	}
	return b_changed;
}

_pc_sz CVer_Att::Name (void) const { return (_pc_sz) this->m_name; }
bool   CVer_Att::Name (_pc_sz _p_name) {
	_p_name;
	const bool b_changed = !!this->m_name.Compare(_p_name);
	if (b_changed)
		this->m_name = _p_name;
	return b_changed;
}

_pc_sz CVer_Att::Value(void) const { return (_pc_sz) this->m_value; }
bool   CVer_Att::Value(_pc_sz _p_value) {
	_p_value;
	const bool b_changed = !!this->m_value.Compare(_p_value);
	if (b_changed)
		this->m_value = _p_value;
	return b_changed;
}

CString  CVer_Att::Print (const e_print _e_opt/* = e_print::e_all*/, const bool _b_trace/* = true*/) const {
	_e_opt; _b_trace;
	static _pc_sz pc_pat_a = _T("cls::[%s::%s] >> {id=%u(%s);name=%s;value=%s}");
	static _pc_sz pc_pat_n = _T("cls::[%s] >> {id=%u(%s);name=%s;value=%s}");
	static _pc_sz pc_pat_r = _T("id=%u(%s);name=%s;value=%s");

	CString cs_name = this->m_name.IsEmpty() ? _T("#unset") : this->Name ();
	CString cs_val = this->m_value.IsEmpty() ? _T("#unset") : this->Value();
	CString cs_out;
	if (e_print::e_all == _e_opt)   { cs_out.Format (pc_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) CVer_Att_Fmt(*this).Id(), (_pc_sz) cs_name, (_pc_sz) cs_val);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_pat_n,  (_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) CVer_Att_Fmt(*this).Id(), (_pc_sz) cs_name, (_pc_sz) cs_val);
	}
	if (e_print::e_req == _e_opt)   { cs_out.Format (pc_pat_r, this->Id(), (_pc_sz) CVer_Att_Fmt(*this).Id(), (_pc_sz) cs_name, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty()) {
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
		if (_b_trace)
			__trace_err(_T("%s"), (_pc_sz) cs_out);
	}
	else if (_b_trace)
		__trace_info(_T("%s"), (_pc_sz) cs_out);

	return  cs_out;
}

CVer_Att& CVer_Att::operator = (const CVer_Att& _src) { *this << _src.Id() << _src.Name() >> _src.Value(); return *this; }
CVer_Att& CVer_Att::operator = (CVer_Att&& _victim) { *this = (const CVer_Att&)_victim; return *this; }
CVer_Att& CVer_Att::operator <<(const uint32_t _n_id) { this->Id(_n_id); return *this; }
CVer_Att& CVer_Att::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CVer_Att& CVer_Att::operator >>(_pc_sz _p_value) { this->Value(_p_value); return *this; }

CVer_Att& CVer_Att::operator >>(const char* _p_value) { this->m_value = _p_value; return *this; }

#ifndef GL_SHADING_LANGUAGE_VERSION
#define GL_SHADING_LANGUAGE_VERSION 0x8b8c
#endif

CVersion:: CVersion (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetstring ;
#if (0)
	TFakeWnd wnd; // message-only window (aka fake) is created in its constructor;
	if (wnd.Is_valid() == false) {
		this->m_error = wnd.Error(); return;
	}

	context::CDevice ctx_dev(wnd);
	if (ctx_dev.Error()) {
		this->m_error = ctx_dev.Error(); return;
	}
#endif
	this->m_atts[e_atts::e_render ] << e_atts::e_render  >> reinterpret_cast<const char*>(::glGetString(GL_RENDERER));
	this->m_atts[e_atts::e_shader ] << e_atts::e_shader  >> reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION));
	this->m_atts[e_atts::e_vendor ] << e_atts::e_vendor  >> reinterpret_cast<const char*>(::glGetString(GL_VENDOR));
	this->m_atts[e_atts::e_version] << e_atts::e_version >> reinterpret_cast<const char*>(::glGetString(GL_VERSION));
	this->m_error << __s_ok;
}

CVersion::~CVersion (void) {}

TError&    CVersion::Error (void) const { return this->m_error; }
const
CVer_Att&  CVersion::GetAtt (const e_atts _e_att) const {
	_e_att;
	switch (_e_att) {
	case e_atts::e_render : case e_atts::e_shader : case e_atts::e_vendor : case e_atts::e_version: return this->m_atts[_e_att]; break; // ;)
	default:
		static CVer_Att inv_att;
		return  inv_att;
	}
}

CString  CVersion::Print (const e_print _e_opt/* = e_print::e_all*/, _pc_sz _p_pfx/* = _T("")*/, _pc_sz _p_sfx/* = _T(";")*/, const bool _b_trace/* = true*/) const {
	_e_opt; _p_pfx; _p_sfx; _b_trace;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s}");

	CString cs_atts;
	for (uint32_t i_ = 0; i_ < CVersion::n_atts_count; i_++) {
		cs_atts += _p_pfx;
		cs_atts += this->m_atts[i_].Print(e_print::e_req, false);
		cs_atts += _p_sfx;
	}

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _p_sfx, (_pc_sz) cs_atts);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, _p_sfx, (_pc_sz) cs_atts); }
	if (e_print::e_req == _e_opt)   { cs_out.Format (pc_sz_pat_r, _p_sfx, (_pc_sz) cs_atts); }

	if (cs_out.IsEmpty()) {
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
		if (_b_trace)
			__trace_err(_T("%s"), (_pc_sz) cs_out);
	}
	else if (_b_trace)
		__trace_info(_T("%s"), (_pc_sz) cs_out);

	return cs_out;
}