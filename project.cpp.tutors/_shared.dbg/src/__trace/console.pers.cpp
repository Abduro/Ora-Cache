/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 09:27:52.973, UTC+4, Batumi, Wednesday;
	This is system console registry persistency interface implementation file;
*/
#include "console.pers.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "sys.registry.h"
#include "win.gui.wnd.h"

using namespace shared::console;
using namespace shared::console::persistent;

namespace shared { namespace console { namespace _impl {

	class CAccessor {
	public:
		 CAccessor (void) = default;  CAccessor (const CAccessor&) = delete; CAccessor (CAccessor&&) = delete;
		~CAccessor (void) = default;

		HWND operator ()(void) const {

			const HWND h_wnd = ::GetConsoleWindow();
			if (0 == h_wnd) {
				CError error(__CLASS__, __METHOD__, (err_code)TErrCodes::eExecute::eState);
				error = _T("There is *no* association with console process");
				__trace_err_ex_3(error);
			}
			return h_wnd;
		}

	private:
		CAccessor& operator = (const CAccessor&) = delete; CAccessor& operator = (CAccessor&&) = delete;
	};

}}} using namespace shared::console::_impl;

#pragma region cls::CBase{}

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBase::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CPin{}

static _pc_sz  p_sz_pin_name = _T("Pinned");

CPin::CPin (void) : m_pinned(true) { TBase::m_error >>__CLASS__; }

bool CPin::Is_pinned (void) const { return this->m_pinned; }
void CPin::Is_pinned (const bool _on_or_off) { this->m_pinned = _on_or_off; }

err_code CPin::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	TRegKeyEx the_key;
	this->m_pinned = !!the_key.Value().GetDword((_pc_sz) ::Get_reg_router().Trace().Root(), p_sz_pin_name);
	if (the_key.Error()) {
		TBase::m_error = the_key.Error();
		__trace_err_2(TBase::m_error);
	}
	else {
		__trace_impt_2(_T("Pinned state is: '%s'\n"), TString().Bool(this->m_pinned));
	}

	return TBase::Error();
}

err_code CPin::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	TRegKeyEx the_key;
	if (__failed(the_key.Value().Set((_pc_sz)::Get_reg_router().Trace().Root(), p_sz_pin_name, (dword)this->Is_pinned()))) {
		TBase::m_error = the_key.Error();
		__trace_err_2(TBase::m_error);
	}
	else {
		__trace_impt_2(_T("Pinned state is set to '%s'\n"), TString().Bool(this->Is_pinned()));
	}
	return TBase::Error();
}

CString  CPin::To_str (const e_print _e_opt/* = e_print::e_all*/) {
	_e_opt;
	static _pc_sz p_sz_pat_a = _T("cls::[%s::$s] >> {pinned='%s'}");
	static _pc_sz p_sz_pat_n = _T("cls::[$s] >> {pinned='%s'}");
	static _pc_sz p_sz_pat_r = _T("pinned='%s'");

	CString cs_out;
	if (false) {}
	else if (e_print::e_all == _e_opt)   { cs_out.Format(p_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TString().Bool(this->Is_pinned())); }
	else if (e_print::e_no_ns == _e_opt) { cs_out.Format(p_sz_pat_n, (_pc_sz)__CLASS__, TString().Bool(this->Is_pinned())); }
	else if (e_print::e_req == _e_opt)   { cs_out.Format(p_sz_pat_r, TString().Bool(this->Is_pinned())); }
	else
		cs_out.Format(_T("cls::[$s].%s() >> #__e_undef: e_print = %d"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

CPin& CPin::operator <<(const bool _b_on_or_off) { this->Is_pinned(_b_on_or_off); return *this; }

#pragma endregion
#pragma region cls::CPosition{}

CPosition:: CPosition (void) : TBase(), m_rc_pos{0} { TBase::m_error >>__CLASS__; }
CPosition::~CPosition (void) {}

static CString cs_pos_key = TString().Format(_T("%s\\Position"), (_pc_sz) ::Get_reg_router().Trace().Root());

CString  _rect_to_str (const t_rect& _rect) {
	_rect;
	static _pc_sz p_rect_pat = _T("{l=%d;t=%d;r=%d;b=%d}");

	CString cs_out; cs_out.Format(p_rect_pat, _rect.left , _rect.top , _rect.right, _rect.bottom);
	return  cs_out;
}

const
t_rect&  CPosition::Get (void) const { return this->m_rc_pos; }
err_code CPosition::Set (const t_rect& _rect) {
	_rect;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (::IsRectEmpty(&_rect))
		TBase::m_error <<__e_rect = _T("#__e_inv_arg: input rect is empty");

	TRegKeyEx the_key;
	if (__failed(the_key.Value().Set((_pc_sz) cs_pos_key, _rect))) {
		TBase::m_error = the_key.Error();
		__trace_err_2(TBase::Error());
	} else {
		this->m_rc_pos = _rect;
		__trace_impt_2(_T("Position is saved at rect >> %s\n"), (_pc_sz) ::_rect_to_str(this->m_rc_pos));
	}
	return TBase::Error();
}

err_code CPosition::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	using namespace ex_ui::popup::layout;

	TRegKeyEx the_key;
	this->m_rc_pos = the_key.Value().GetRect((_pc_sz) cs_pos_key);

	if (::IsRectEmpty(&this->m_rc_pos)) { // the position of the console window is not saved yet;

		t_size_u size = CPrimary().Default();
		this->m_rc_pos = CPrimary().Centered(size);

	     __trace_warn_2(_T("Using default rect at << %s\n"), (_pc_sz) ::_rect_to_str(this->m_rc_pos)); }
	else __trace_impt_2(_T("Position is restored at rect << %s\n"), (_pc_sz) ::_rect_to_str(this->m_rc_pos));

	return this->Error();
}

err_code CPosition::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowrect ;
	t_rect rc_ = {0};

	if (false == !!::GetWindowRect(CAccessor()(), &rc_))
		return TBase::m_error.Last();

	return this->Set(rc_);
}

CString  CPosition::To_str (const e_print _e_opt/* = e_print::e_all*/) {
	_e_opt;
	static _pc_sz p_sz_pat_a = _T("cls::[%s::$s] >> {rect=%s}");
	static _pc_sz p_sz_pat_n = _T("cls::[$s] >> {rect=%s}");
	static _pc_sz p_sz_pat_r = _T("rect=%s");

	CString cs_out;
	if (false) {}
	else if (e_print::e_all == _e_opt)   { cs_out.Format(p_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)::_rect_to_str(this->Get())); }
	else if (e_print::e_no_ns == _e_opt) { cs_out.Format(p_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)::_rect_to_str(this->Get())); }
	else if (e_print::e_req == _e_opt)   { cs_out.Format(p_sz_pat_r, (_pc_sz)::_rect_to_str(this->Get())); }
	else
		cs_out.Format(_T("cls::[$s].%s() >> #__e_undef: e_print = %d"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

#pragma endregion
#pragma region cls::CPersistent{}

using CPin = persistent::CPin;
using CPos = persistent::CPosition;

CPersistent:: CPersistent (void) { TBase::m_error >>__CLASS__; }
CPersistent::~CPersistent (void) {}

err_code CPersistent::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Pin().Load())) {
		TBase::m_error = this->Pin().Error();
	}
	if (__failed(this->Pos().Load())) {
		TBase::m_error = this->Pos().Error();
	}

	return TBase::Error();
}

err_code CPersistent::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Pin().Save())) {
		TBase::m_error = this->Pin().Error();
	}
	if (__failed(this->Pos().Save())) {
		TBase::m_error = this->Pos().Error();
	}

	return TBase::Error();
}

const
CPin&   CPersistent::Pin (void) const { return this->m_pin; }
CPin&   CPersistent::Pin (void)       { return this->m_pin; }
const
CPos&   CPersistent::Pos (void) const { return this->m_pos; }
CPos&   CPersistent::Pos (void)       { return this->m_pos; }

#pragma endregion
#pragma region cls::CShow{}

CShow::CShow (void) : TBase(), m_visible(true) { TBase::m_error >>__CLASS__; }

err_code CShow::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;


	return TBase::Error();
}

err_code CShow::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;


	return TBase::Error();
}

bool CShow::Is_visible (void) const { return this->m_visible; }

#pragma endregion

TConPers&  ::Get_ConPers (void) {
	static TConPers con_pers;
	return con_pers;
}