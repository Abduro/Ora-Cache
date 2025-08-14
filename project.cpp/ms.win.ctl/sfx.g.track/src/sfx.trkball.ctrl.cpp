/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Aug-2025 at 06:18:03.111, UTC+4, Batumi, Saturday;
	This is Ebo Pack trackball user control interface implementation file;
*/
#include "sfx.trkball.ctrl.h"
#include "sfx.trkball.wnd.h"

using namespace ex_ui::controls::sfx::track;

namespace ex_ui { namespace controls { namespace sfx { namespace track { namespace _impl { void __warning_lnk_4221 (void) {}}}}}}

#define _wnd_ptr(_pvoid)   (reinterpret_cast<CWnd*>(_pvoid))
#define _wnd_ref(_pvoid) (*(reinterpret_cast<CWnd*>(_pvoid)))

/////////////////////////////////////////////////////////////////////////////

CControl:: CControl (void) : m_ctrl_id(0), m_wnd_ptr(nullptr), m_format(*this), m_layout(*this) {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	try { m_wnd_ptr = new CWnd(*this); } catch (::std::bad_alloc&){ this->m_error << __e_no_memory; }
}
CControl::~CControl (void) {
	if (_wnd_ptr(m_wnd_ptr)) {
		try { _wnd_ptr(m_wnd_ptr)->~CWnd(); delete m_wnd_ptr; m_wnd_ptr = nullptr;} catch(...){ ATLASSERT(FALSE); }
	}
}

const
CBorders&  CControl::Borders (void) const { return m_borders; }
CBorders&  CControl::Borders (void)       { return m_borders; }

err_code   CControl::Create (const HWND hParent, const uint32_t _ctrl_id, const t_rect& _rect) {
	hParent; _ctrl_id;
	this->m_error << __METHOD__ << __s_ok;

	if (false == ::IsWindow(hParent)) return this->m_error << __e_hwnd = _T("Invalid parent window handle;");
	if (nullptr == m_wnd_ptr)         return this->m_error << __e_not_inited;
	if (::IsRectEmpty(&_rect))        return this->m_error << __e_rect;

	this->m_ctrl_id = _ctrl_id;
	t_rect  rc_area = _rect;
#if (0)
	if (false == ::GetClientRect(hParent, &rc_area)) {
		return this->m_error.Last();
	}
#endif
	const uint32_t n_style = WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	_wnd_ref(m_wnd_ptr).Create(
		hParent, rc_area, TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), n_style, 0, _ctrl_id
	);

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error.Last();

	return this->Error();
}

err_code  CControl::Destroy(void) {

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == m_wnd_ptr)
		return this->m_error << __e_pointer;

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error << __e_hwnd;

	_wnd_ref(m_wnd_ptr).SendMessage(WM_CLOSE); // ToDo: perhaps the calling ::DestroyWindow() would be better and faster?

	return this->Error();
}

TError&    CControl::Error   (void) const { return this->m_error ; }
const
CFormat&   CControl::Format (void) const { return this->m_format; }
CFormat&   CControl::Format (void)       { return this->m_format; }

uint32_t   CControl::Id (void) const { return this->m_ctrl_id; }
bool       CControl::Id (const uint32_t _u_id) {
	_u_id;
	const bool b_changed = this->Id() != _u_id; if (b_changed) this->m_ctrl_id = _u_id; return b_changed;
}

bool       CControl::Is_valid (void) const {
#if (0)
	bool b_valid = nullptr != m_wnd_ptr;
	if ( b_valid ) {
		const HWND h_wnd = _wnd_ref(m_wnd_ptr);
		b_valid = 0 != ::IsWindow(h_wnd); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-iswindow ;
	}
	return b_valid;
#else
	return nullptr != m_wnd_ptr && true == !!_wnd_ref(m_wnd_ptr).IsWindow();
#endif
}
const
CLayout&   CControl::Layout (void) const { return this->m_layout; }
CLayout&   CControl::Layout (void)       { return this->m_layout; }