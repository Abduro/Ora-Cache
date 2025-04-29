/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Apr-2025 at 16:30:54.136, UTC+4, Batumi, Tuesday;
	This is Ebo Pack MS DirectX wrapper base interface implementation file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"

using namespace ex_ui::draw::direct_x;
using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	class CMode_Fmt {
	public:
		 CMode_Fmt (void) = default; CMode_Fmt (const CMode_Fmt&) = delete; CMode_Fmt (CMode_Fmt&&) = delete;
		~CMode_Fmt (void) = default;

	public:
		// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173064(v=vs.85) ;
		CString  Format(const TModeDesc& _mode) const {
		/*
			UINT Width;
			UINT Height;
			DXGI_RATIONAL RefreshRate; https://learn.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_rational ;
			DXGI_FORMAT Format;        https://learn.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format   ;
			DXGI_MODE_SCANLINE_ORDER ScanlineOrdering; https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173067(v=vs.85) ;
			DXGI_MODE_SCALING Scaling; https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173066(v=vs.85) ;
		*/
			static _pc_sz pc_sz_pat = _T("w=%dpx;h=%dpx;rate=%d;fmt=%s;scan=%s;scale=%s");

			CString cs_fmt   = CClrBits().Print(_mode.Format);
			CString cs_order = this->_order_to_str(_mode.ScanlineOrdering);
			CString cs_scale = this->_scale_to_str(_mode.Scaling);

			CString cs_out;
			cs_out.Format(
				pc_sz_pat, _mode.Width, _mode.Height, _mode.RefreshRate.Numerator, (_pc_sz)cs_fmt, (_pc_sz)cs_order, (_pc_sz)cs_scale);
			return  cs_out;
		}

	private:
		CString _order_to_str (const DXGI_MODE_SCANLINE_ORDER _n_order) const {
			CString cs_out;
			switch (_n_order) {
			case DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST: cs_out = _T("low_first"); break;
			case DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:       cs_out = _T("progress"); break;
			case DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:       cs_out = _T("unspec"); break;
			case DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST: cs_out = _T("up_first"); break;
			default:
				cs_out = _T("#unknown");
			}
			return  cs_out;
		}
		CString _scale_to_str (const DXGI_MODE_SCALING _n_scale) const {
			CString cs_out;
			switch (_n_scale) {
			case DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED   : cs_out = _T("center"); break;
			case DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED  : cs_out = _T("stretch"); break;
			case DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED: cs_out = _T("unspec"); break;
			default:
				cs_out = _T("#unknown");
			}
			return  cs_out;
		}

	private:
		CMode_Fmt& operator = (const CMode_Fmt&) = delete;
		CMode_Fmt& operator = (CMode_Fmt&&) = delete;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

CDisplay:: CDisplay (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError&  CDisplay::Error (void) const { return this->m_error; }

err_code CDisplay::Get (void) {
	this->m_error << __METHOD__ << __s_ok;

	const POINT ptZero = {0};
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
	const HMONITOR hMonitor = ::MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

	MONITORINFO mInfo  = {0};
	mInfo.cbSize = sizeof(MONITORINFO) ; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-monitorinfo ;
	if (!
	::GetMonitorInfo(hMonitor, &mInfo))  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmonitorinfoa ;
	return this->m_error << __e_fail;

	this->m_rez.H(mInfo.rcWork.bottom - mInfo.rcWork.top);
	this->m_rez.W(mInfo.rcWork.right - mInfo.rcWork.left);

	return this->Error();
}

bool     CDisplay::Is_valid (void) const { return false == this->Rez().Is_zero(); }

#if defined(_DEBUG)
CString  CDisplay::Print(const TModeDesc& _mode) {
	return  CMode_Fmt().Format(_mode);
}
CString  CDisplay::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{rez=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{rez=%s}");
	static _pc_sz pc_sz_pat_r = _T("{rez=%s}");

	CString cs_size  = this->Rez().Print(::e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_size); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_size); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_size); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
CSize_U& CDisplay::Rez (void) const { return this->m_rez; }