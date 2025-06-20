/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2009 at 7:07:37, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack GDI+ library owner draw wrapper class(es) implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 3-May-2020 at 2:25:56a, UTC+7, Novosibirsk, Sunday;
*/
#include "uix.gen.font.h"

using namespace ex_ui::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace _impl {
#if defined (_DEBUG)
	/*
		enum _opt : ULONG {
			eNone          = 0x0000,
			eExactSize     = 0x0001,
			eRelativeSize  = 0x0002,
			eBold          = 0x0004,
			eItalic        = 0x0008,
			eUnderline     = 0x0010,
		};
	*/
	class CFontOpt_Fmt {
	using opts = CFontOptions::_opt;
	public:
		CFontOpt_Fmt (const uint32_t _u_flags = 0) : m_flags(_u_flags) {}
		CFontOpt_Fmt (const CFontOpt_Fmt&) = delete; CFontOpt_Fmt (CFontOpt_Fmt&&) = delete; ~CFontOpt_Fmt (void) = default;

	public:
		CString  ToString (void) const {
		
			CString cs_out;
			// ::std::vector may be used here;
			static const opts e_all[] = {opts::eExactSize, opts::eRelativeSize, opts::eBold, opts::eItalic, opts::eUnderline};
			static const uint32_t u_size = 5;

			CString cs_name;

			for (uint32_t i_ = 0; i_ < u_size; i_++) {

				if (0 == (this->m_flags & e_all[i_]))
					continue;

				if (cs_out.IsEmpty() == false)
					cs_out += _T("|");

				switch (e_all[i_]) {
				case opts::eExactSize   : cs_name = _T("eExactSize"); break;
				case opts::eRelativeSize: cs_name = _T("eRelativeSize"); break;
				case opts::eBold        : cs_name = _T("eBold"); break;
				case opts::eItalic      : cs_name = _T("eItalic"); break;
				case opts::eUnderline   : cs_name = _T("eUnderline"); break;
				default:
					cs_name = _T("#undef");
				}
				cs_out += TStringEx().Format(_T("0x%02x(%s)"), e_all[i_], (_pc_sz)cs_name);
			}

			if (cs_out.IsEmpty())
				cs_out.Format(_T("0x%02x(%s)"), this->m_flags, _T("#undef"));

			return  cs_out;
		}
	private:
		CFontOpt_Fmt& operator = (const CFontOpt_Fmt&) = delete;
		CFontOpt_Fmt& operator = (CFontOpt_Fmt&&) = delete;
	
	private:
		uint32_t  m_flags;
	};

#endif
}}}
using namespace ex_ui::draw::_impl;
/////////////////////////////////////////////////////////////////////////////

CFontOptions:: CFontOptions(void) : m_opts(_opt::eNone) {}
CFontOptions:: CFontOptions(const CFontOptions& _ref) : CFontOptions() { *this = _ref; }
CFontOptions:: CFontOptions(const DWORD _opts) : CFontOptions() { this->Set() = _opts; }
CFontOptions::~CFontOptions(void) {}

/////////////////////////////////////////////////////////////////////////////

DWORD   CFontOptions::Get (void) const { return m_opts; }
bool    CFontOptions::Has (const DWORD _opts) const { return 0!= (_opts & m_opts); }
DWORD&  CFontOptions::Set (void) { return m_opts; }

/////////////////////////////////////////////////////////////////////////////

bool    CFontOptions::IsBold (void) const { return (0 != (this->m_opts & _opt::eBold)); }
bool    CFontOptions::IsItalic (void) const { return (0 != (this->m_opts & _opt::eItalic)); }
bool    CFontOptions::IsUnderline (void) const { return (0 != (this->m_opts & _opt::eUnderline)); }

#if defined(_DEBUG)

CString CFontOptions::Print (const uint32_t _u_flags) {
	return CFontOpt_Fmt(_u_flags).ToString();
}

CString CFontOptions::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_flags = CFontOpt_Fmt(this->Get()).ToString();

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_flags);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_flags);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_flags); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CFontOptions&  CFontOptions::operator = (const DWORD _opts) { this->Set() = _opts; return *this; }
CFontOptions&  CFontOptions::operator = (const CFontOptions& _ref) { this->Set() = _ref.Get(); return *this; }
CFontOptions&  CFontOptions::operator+= (const DWORD _opts) { this->Set() |= _opts; return *this; }
CFontOptions&  CFontOptions::operator-= (const DWORD _opts) { this->Set() &=~_opts; return *this; }

/////////////////////////////////////////////////////////////////////////////

const bool     CFontOptions::operator == (const CFontOptions& _ref) const { return (this->Get() == _ref.Get()); }
const bool     CFontOptions::operator != (const CFontOptions& _ref) const { return (this->Get() != _ref.Get()); }

const bool     CFontOptions::operator == (const DWORD _opts) const { return (this->Has(_opts) == true ); }
const bool     CFontOptions::operator != (const DWORD _opts) const { return (this->Has(_opts) == false); }
CFontOptions::operator const DWORD (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

CFont_Base:: CFont_Base(void) : m_handle(nullptr) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CFont_Base:: CFont_Base(const CFont_Base& _ref) : CFont_Base() { *this = _ref; }
CFont_Base:: CFont_Base(const HFONT _h_font) : CFont_Base() { *this << _h_font; }
CFont_Base:: CFont_Base(CFont_Base&& _src) : CFont_Base() { *this = _src; }
CFont_Base::~CFont_Base(void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CFont_Base::Destroy(void) {
	m_error << __METHOD__ << __s_ok;

	if (!this->Is())
		return (m_error << __e_not_inited);

	if (0 == ::DeleteObject((HGDIOBJ)m_handle)) // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject ;
		m_error << (err_code) TErrCodes::eExecute::eState;
	else {
		m_error << __e_not_inited;
		m_handle = nullptr;
	}

	return this->Error();
}
HFONT     CFont_Base::Detach (void) {
	HFONT hFont = m_handle; {
		m_handle = nullptr ;
		m_error << __e_not_inited;
	}
	return hFont;
}
HFONT     CFont_Base::Handle (void) const { return m_handle; }
bool      CFont_Base::Is     (void) const { return CFont_Base::Is(m_handle); }

TErrorRef CFont_Base::Error  (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

HFONT const CFont_Base::Get (void) const { return this->Handle(); }

err_code CFont_Base::Set (const HFONT _src) {
	m_error << __METHOD__ << __s_ok;

	if (!CFont_Base::Is(_src))
		return (m_error << (err_code) TErrCodes::eObject::eHandle);
	if (this->Is())
		this->Destroy();

	if (this->Error().State() != __e_not_inited) // expects this font object has been destroyed successfully or it is not created yet;
		return m_error;

	// https://stackoverflow.com/questions/371018/create-modified-hfont-from-hfont ;
	CLogFont log_(_src);
	if (log_.Error())
		return (m_error = log_.Error());
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfontindirecta ;
	this->m_handle = ::CreateFontIndirect(&log_.Get());
	if (!this->Is())
		m_error.Last();

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CFont_Base& CFont_Base::operator = (const CFont_Base& _ref) { *this << _ref.Handle(); return *this; }
CFont_Base& CFont_Base::operator <<(const HFONT _h_font) { this->Set(_h_font); return *this; }
CFont_Base& CFont_Base::operator = (CFont_Base&& _src) {
	
	if (this->Is())
		this->Destroy();
	if (this->Error().State() != __e_not_inited)
		return *this;

	m_error << __METHOD__ << __s_ok;

	this->m_handle = _src.Detach();
	if (this->Is())
		this->m_error << __s_ok;
	else
		this->m_error << __e_not_inited;

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CFont_Base::operator const HFONT (void) const { return this->Handle(); }

/////////////////////////////////////////////////////////////////////////////

bool CFont_Base::Is (const HFONT _target) {
	return(_target && (OBJ_FONT == ::GetObjectType((HGDIOBJ)_target)));
}

/////////////////////////////////////////////////////////////////////////////

ex_ui::draw::CFont:: CFont (void) : TBase(), m_bManaged(false), m_angle(0) {
}

ex_ui::draw::CFont:: CFont (_pc_sz pszFamily, const DWORD dwOptions, const LONG lParam) : CFont() {
	this->Create(pszFamily, dwOptions, lParam);
}

ex_ui::draw::CFont::~CFont (void)
{
	if (m_bManaged) {
		TBase::Destroy();
		m_bManaged = false;
	}
}

/////////////////////////////////////////////////////////////////////////////

int16_t   ex_ui::draw::CFont::Angle (void) const { return this->m_angle; }  
bool      ex_ui::draw::CFont::Angle (const int16_t _n_degrees) {
	_n_degrees;
	int16_t n_degrees = _n_degrees; // no modulus operator is applied here;
	if (+360 < n_degrees) n_degrees = 360;
	if (-360 > n_degrees) n_degrees =-360;

	const bool b_changed = this->Angle() != n_degrees;
	if (b_changed)
		this->m_angle = n_degrees;

	return b_changed;
}

err_code  ex_ui::draw::CFont::Create(_pc_sz pszFamily, const DWORD dwOptions, const LONG lParam) {
	pszFamily; dwOptions; lParam;

	err_code n_result = __s_ok;
	LOGFONT log = {0} ; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-logfonta ; 
	                    // lfHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);

	if (this->Is())
		return n_result = TBase::m_error << (err_code)TErrCodes::eObject::eExists;

	if (::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &log, 0)) {
		if (pszFamily)
			::_tcscpy_s(log.lfFaceName, _countof(log.lfFaceName), pszFamily);
		if (0 != (CFontOptions::eExactSize & dwOptions) && lParam) {
			log.lfHeight = lParam;
		}
		else if ( 0 != (CFontOptions::eRelativeSize & dwOptions) && lParam)
		{
			if (log.lfHeight < 0) {
				log.lfHeight -= lParam;
			}
			else {
				log.lfHeight += lParam;
			}
		}
		if (TFontOpts(dwOptions).IsBold()) log.lfWeight |= FW_BOLD;
		if (TFontOpts(dwOptions).IsItalic()) log.lfItalic = TRUE;
		if (TFontOpts(dwOptions).IsUnderline()) log.lfUnderline = TRUE;

		log.lfQuality = CLEARTYPE_NATURAL_QUALITY;

		if (!!this->Angle()) {
			log.lfEscapement = this->Angle() * 10;
		}

		this->m_handle = ::CreateFontIndirect(&log); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfontindirecta ;
		if (nullptr == this->m_handle)
			n_result = (TBase::m_error << __METHOD__).Last();
		else {
			TBase::m_error << __METHOD__ << n_result; // otherwise the error of the base class object will be in error state 'not initialized';
			m_bManaged = true;
		}
	}
	else {
		m_handle = reinterpret_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT));
	}
	return n_result;
}

HFONT     ex_ui::draw::CFont::Detach(void)
{
	m_bManaged = false;
	return TBase::Detach();
}

/////////////////////////////////////////////////////////////////////////////

CFontScalable:: CFontScalable (const HDC hDC, _pc_sz lpszFontFamily, const INT nSize, const DWORD dwOptions) : TBase() {
	this->Create(hDC, lpszFontFamily, nSize, dwOptions);
}

CFontScalable::~CFontScalable (void) {
	TBase::Destroy();
}

/////////////////////////////////////////////////////////////////////////////

err_code  CFontScalable::Create(const HDC hDC, _pc_sz lpszFontFamily, const INT nSize, const DWORD dwOptions) {
	hDC; lpszFontFamily; nSize; dwOptions;

	err_code n_result = __s_ok;

	if (!hDC)
		return n_result = (err_code)TErrCodes::eObject::eHandle;
	if (this->Is())
		return n_result = (err_code)TErrCodes::eObject::eExists;

	const INT nVertScale = (::GetDeviceCaps(hDC, LOGPIXELSY) * nSize) / 72;
	const INT nHeight = -nVertScale;

	m_handle = ::CreateFont(
		nHeight,
		0,
		0,
		0,
		0 != (TFontOpts::eBold      & dwOptions) ? FW_BOLD : FW_NORMAL,
		0 != (TFontOpts::eItalic    & dwOptions),
		0 != (TFontOpts::eUnderline & dwOptions),
		0,
		DEFAULT_CHARSET    ,
		OUT_DEVICE_PRECIS  ,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY    ,
		DEFAULT_PITCH      ,
		lpszFontFamily
	);
	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

ex_ui::draw::CLogFont:: CLogFont (void) : m_log{0} { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
ex_ui::draw::CLogFont:: CLogFont (const CLogFont& _ref) : CLogFont() { *this = _ref; }
ex_ui::draw::CLogFont:: CLogFont (const HFONT _h_font) : CLogFont() { *this << _h_font; }
ex_ui::draw::CLogFont:: CLogFont (const LOGFONT& _log) : CLogFont() { *this << _log; }
ex_ui::draw::CLogFont:: CLogFont (CLogFont&& _src) : CLogFont() { *this = _src; }
ex_ui::draw::CLogFont::~CLogFont (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef  ex_ui::draw::CLogFont::Error (void) const { return this->m_error; }

const
LOGFONT&   ex_ui::draw::CLogFont::Get (void) const { return this->m_log; }
LOGFONT&   ex_ui::draw::CLogFont::Get (void)       { return this->m_log; }

HRESULT    ex_ui::draw::CLogFont::Set (void) {
	m_error << __METHOD__ << __e_not_inited;
	// https://pvs-studio.com/en/blog/posts/cpp/0360/ ;
	// https://stackoverflow.com/questions/56565539/memset-s-what-does-the-standard-mean-with-this-piece-of-text ;
	// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-rtlsecurezeromemory ;
	::RtlSecureZeroMemory ((void*)&m_log, sizeof(LOGFONT));

	// memset_s( (void*)&m_log, sizeof(LOGFONT), 0, sizeof(LOGFONT)); *!!!not found!!!*

	return m_error;
}

HRESULT    ex_ui::draw::CLogFont::Set (const LOGFONT& _log) {
	m_error << __METHOD__ << __s_ok;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s ;
	errno_t t_result = ::memcpy_s(&this->m_log, sizeof(LOGFONT), &_log, sizeof(LOGFONT));
	if (t_result)
		m_error << __e_no_memory;

	return m_error;
}

HRESULT    ex_ui::draw::CLogFont::Set (const HFONT _font, const DWORD _opts) {
	m_error << __METHOD__ << __s_ok;

	if (!CFont_Base::Is(_font))
		return (m_error << (err_code) TErrCodes::eObject::eHandle);

	// https://stackoverflow.com/questions/371018/create-modified-hfont-from-hfont ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobject ;
	LOGFONT log_ = {0};
	int n_req_sz = ::GetObject(_font, sizeof(LOGFONT), &log_);
	if (n_req_sz == 0)
		return (m_error << (err_code) TErrCodes::eExecute::eParameter);

	if (CFontOptions(_opts).IsBold()) log_.lfWeight |= FW_BOLD;
	if (CFontOptions(_opts).IsItalic()) log_.lfItalic = TRUE;
	if (CFontOptions(_opts).IsUnderline()) log_.lfUnderline = TRUE;

	*this = log_;

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

ex_ui::draw::CLogFont&  ex_ui::draw::CLogFont::operator = (const CLogFont& _ref) { *this << _ref.Get(); return *this; }
ex_ui::draw::CLogFont&  ex_ui::draw::CLogFont::operator <<(const HFONT _h_font) { this->Set(_h_font); return *this; }
ex_ui::draw::CLogFont&  ex_ui::draw::CLogFont::operator <<(const LOGFONT& _log) { this->Set(_log); return *this; }
ex_ui::draw::CLogFont&  ex_ui::draw::CLogFont::operator = (CLogFont&& _src) {
	this->Set(_src.Get()); _src.Set(); return *this;
}

/////////////////////////////////////////////////////////////////////////////

ex_ui::draw::CLogFont::operator const  LOGFONT&(void) const { return this->Get(); }
ex_ui::draw::CLogFont::operator        LOGFONT&(void)       { return this->Get(); }