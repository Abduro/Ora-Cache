/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2025 at 20:25:12.265, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX adapter output wrapper interface implementation file;
*/
#include "direct_x.output.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CRotateMode::Print (const uint32_t _n_flag, _pc_sz _p_sep) const {
	_n_flag; _p_sep;
	CString cs_out;

	switch (_n_flag) {
	case CRotateMode::e_rotate::e_090    : cs_out = _T("rotate:090"); break;
	case CRotateMode::e_rotate::e_180    : cs_out = _T("rotate:180"); break;
	case CRotateMode::e_rotate::e_270    : cs_out = _T("rotate:270"); break;
	case CRotateMode::e_rotate::e_none   : cs_out = _T("#no_rotate"); break;
	case CRotateMode::e_rotate::e__unspec: cs_out = _T("#unspec"); break;
	default:
		cs_out = _T("#undef");
	}
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

namespace _impl {
#if defined(_DEBUG)
	class COutDesc_Fmt {
	public:
		 COutDesc_Fmt (void) = default; COutDesc_Fmt (const COutDesc_Fmt&) = delete; COutDesc_Fmt (COutDesc_Fmt&&) = delete;
		~COutDesc_Fmt (void) = default;

	public:
		CString  Format(const TModeDesc& _mode) const {
			return CDisplay().Print(_mode);
		}

		CString  Format(const TOutDesc& _desc) const {
			_desc;
		//	static
		//	_pc_sz pc_sz_pat = _T("device=%s;coords=%s;desktop=%s;rotate=%s;monitor=%s");
			static
			_pc_sz pc_sz_pat = _T("device=%s;desktop=%s;rotate=%s;monitor=%s"); // the display mode shows the size;

			CString cs_name   = _desc.DeviceName; if (cs_name.IsEmpty()) cs_name = _T("#undef");
		//	CString cs_coords = this->_rect_to_str(_desc.DesktopCoordinates);
			CString cs_desk   = TStringEx().Bool(_desc.AttachedToDesktop);
			CString cs_rotate = CRotateMode().Print(_desc.Rotation);
			CString cs_mon    = (!!_desc.Monitor ? _T("yes") : _T("no"));

		//	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)cs_name, (_pc_sz)cs_coords, (_pc_sz)cs_desk, (_pc_sz)cs_rotate, (_pc_sz)cs_mon);
			CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)cs_name, (_pc_sz)cs_desk, (_pc_sz)cs_rotate, (_pc_sz)cs_mon);
			return  cs_out;
		}

	private:
		COutDesc_Fmt& operator = (const COutDesc_Fmt&) = delete;
		COutDesc_Fmt& operator = (COutDesc_Fmt&&) = delete;
	private:
		CString _rect_to_str  (const RECT& _rect) const {
			_rect;
			static
		//	_pc_sz pc_sz_pat = _T("left=%d;top=%d;right=%d;bottom=%d");
			_pc_sz pc_sz_pat = _T("l:%d;t:%d;r:%d;b:%d");
			CString cs_out; cs_out.Format(pc_sz_pat, _rect.left, _rect.top, _rect.right, _rect.bottom);
			return  cs_out;
		}
	};
#endif
}

COutput:: COutput (void) : m_desc{0}, m_mode{0} { this->m_error >>__CLASS__ << __METHOD__ << __e_not_inited; }
COutput:: COutput (const COutput& _src) : COutput() { *this = _src; }
COutput:: COutput (COutput&& _victim) : COutput() { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////

const
TOutDesc& COutput::GetDesc (void) const { return this->m_desc; }
err_code  COutput::SetDesc (void) {
	this->m_error << __METHOD__ << __s_ok;
	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;

	this->m_error << this->m_p_out->GetDesc(&this->m_desc);

	return this->Error();
}

TError&   COutput::Error (void) const { return this->m_error; }

bool   COutput::Is_valid (void) const { return nullptr != this->Ptr(); }

#if defined(_DEBUG)
CString   COutput::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("%s;mode={%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_desc  = _impl::COutDesc_Fmt().Format(this->GetDesc());
	CString cs_mode  = _impl::COutDesc_Fmt().Format(this->GetMode());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc, (_pc_sz)cs_mode); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
TModeDesc& COutput::GetMode (void) const { return this->m_mode; }
err_code   COutput::SetMode (const uint32_t _n_format) {
	_n_format;
	this->m_error << __METHOD__ << __s_ok;
	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgioutput-getdisplaymodelist ;
	uint32_t n_count = 0;
	uint32_t n_flags = DXGI_ENUM_MODES_INTERLACED;

	this->m_error << this->m_p_out->GetDisplayModeList((DXGI_FORMAT)_n_format, n_flags, &n_count, nullptr);
	if (this->Error())
		return this->Error();

	if (0 == n_count)
		return this->m_error << (err_code) TErrCodes::eData::eNotFound;

	::std::vector<DXGI_MODE_DESC> v_modes(n_count);
	this->m_error << this->m_p_out->GetDisplayModeList((DXGI_FORMAT)_n_format, n_flags, &n_count, v_modes.data());
	if (this->Error())
		return this->Error();

	this->m_mode = v_modes.at(0);

	return this->Error();
}

const
TOutputPtr&  COutput::Ptr (void) const { return this->m_p_out; }
err_code     COutput::Ptr (const TOutputPtr& _p_out) {
	_p_out;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_out)
		return this->m_error << __e_pointer;
	else {
		this->m_p_out = _p_out;
		this->SetDesc();
		this->SetMode();
	}
	return this->Error();
}
	
/////////////////////////////////////////////////////////////////////////////

COutput&     COutput::operator = (const COutput& _src) { *this << _src.Ptr() << _src.GetDesc(); return *this; }
COutput&     COutput::operator = (COutput&& _victim) {

	*this = (const COutput&)_victim;
	return *this;
}
COutput&     COutput::operator <<(const TOutDesc& _desc) { this->m_desc = _desc; return *this; }
COutput&     COutput::operator <<(const TOutputPtr& _p_out) { this->Ptr(_p_out); return *this; }

}}}}
namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {
}}}}