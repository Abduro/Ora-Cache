/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2026 at 14:30:48.038, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL extension wrapper interface implementation file;
*/
#include "gl_procs_ext.h"
#include "gl_context.h"

#include "shared.preproc.h"
#include "shared.wnd.fake.h"

using namespace ex_ui::draw::open_gl::procs;
using s_bits = ex_ui::draw::open_gl::format::s_bits;
using CSelector = ex_ui::draw::open_gl::context::CSelector;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	class CExt_Helper {
	public:
		CExt_Helper (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
		CExt_Helper (const CExt_Helper&) = delete; CExt_Helper (CExt_Helper&&) = delete; ~CExt_Helper (void) = default;

		TError& Error (void) const { return this->m_error; }
		err_code Load (ext_items_t& _items) {
			_items;
			this->m_error <<__METHOD__<<__s_ok;

			if (_items.empty() == false)
				_items.clear();

			// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetString.xhtml ;
			this->m_cache = reinterpret_cast<const char*>(::glGetString(GL_EXTENSIONS));

			const
			uint32_t u_err_code = CErr_ex().Get_code();
			switch ( u_err_code ){
			case GL_INVALID_ENUM: this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_type' (%04u) is invalid"), GL_EXTENSIONS); break;
			default:
				if (!!u_err_code)
					this->m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%04d)"), u_err_code, u_err_code);
			}

			if (false == this->Error()) {
				const TParts v_names = TString(this->Cached()).Split(_T(" "), false);
				for (uint32_t i_ = 0; i_ < v_names.size(); i_++) {
					_items.push_back(CExt_Item(v_names.at(i_)));
				}
			}
				
			return this->Error();
		}

		const
		CString& Cached (void) const { return this->m_cache; }

	private:
		CExt_Helper& operator = (const CExt_Helper&) = delete; CExt_Helper& operator = (CExt_Helper&&) = delete;
		CError  m_error;
		CString m_cache;
	};
}}}} using namespace ex_ui::draw::open_gl::_impl;

#pragma region cls::CExt_Item{}

CExt_Item::CExt_Item (_pc_sz _p_name) { if (_p_name) *this << _p_name; }
CExt_Item::CExt_Item (const CExt_Item& _src) : CExt_Item() { *this = _src; }
CExt_Item::CExt_Item (CExt_Item&& _victim) : CExt_Item() { *this = _victim; }

bool CExt_Item::Is_valid (void) const { return nullptr != this->Name(); }

_pc_sz CExt_Item::Name (void) const { return (_pc_sz) this->m_name; }
void   CExt_Item::Name (_pc_sz _p_name) {
	_p_name;
	this->m_name = _p_name; if (this->m_name.IsEmpty() == false) this->m_name.Trim();
}

CExt_Item&  CExt_Item::operator = (const CExt_Item& _src) { *this << _src.Name(); return *this; }
CExt_Item&  CExt_Item::operator = (CExt_Item&& _victim) { *this = (const CExt_Item&)_victim; return *this; }
CExt_Item&  CExt_Item::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CExt_Item&  CExt_Item::operator <<(const CString& _cs_name) { this->Name((_pc_sz) _cs_name); return *this; }

#pragma endregion
#pragma region cls::CExtension{}

CExt_Enum::CExt_Enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

TError& CExt_Enum::Error (void) const { return this->m_error; }
const
ext_items_t& CExt_Enum::Get (void) const { return this->m_items; }

bool CExt_Enum::Is_remote (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	procs::CBase base;
	const PROC p_proc = base.Get(_T("wglGetExtensionsStringARB"));
	if (base.Error())
		this->m_error << (err_code) base.Error() = base.Error().Desc();

	return nullptr == p_proc;
}

err_code CExt_Enum::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	// (1) to create message-only window (aka fake) and to get context device from it;
	TFakeWnd fk_wnd;
	if (fk_wnd.Error()) return this->m_error = fk_wnd.Error();
	// (2) to find pixel format descriptor by required params: color, stencil, z-axis (depth) bits;
	CFormat format; format << fk_wnd.Get_ctx();
	uint32_t u_index = 0;

	s_bits bits_req; bits_req.m_u_clr = 32; bits_req.m_u_depth = 24; bits_req.m_u_stencil = 8;

	if (__failed(format.Find(bits_req, u_index)))
		 return this->m_error = format.Error();
	// (3) to set the context defice to the found pixel format;
	if (__failed(format.Set()))
		return this->m_error = format.Error();

	CSelector select(fk_wnd.Get_ctx());
	if (select.Error())
		return this->m_error = select.Error();

	CExt_Helper helper;
	if (__failed(helper.Load(this->m_items)))
		this->m_error = helper.Error();

	return this->Error();
}

#pragma endregion

TProcExtEnum&  ::Get_ProcExt (void) {
	static
	TProcExtEnum proc_ext_enum;
	return proc_ext_enum;
}