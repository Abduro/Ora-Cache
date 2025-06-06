/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2009 at 7:07:37, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack GDI+ library owner draw wrapper class(es) implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 3-May-2020 at 2:25:56a, UTC+7, Novosibirsk, Sunday;
*/
#include "uix.gen.font.h"

using namespace ex_ui::draw;

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

TFont:: CFont(LPCTSTR pszFamily, const DWORD dwOptions, const LONG lParam): TBase(), m_bManaged(false) {
	this->Create(pszFamily, dwOptions, lParam);
}

TFont::~CFont(void)
{
	if (m_bManaged) {
		TBase::Destroy();
		m_bManaged = false;
	}
}

/////////////////////////////////////////////////////////////////////////////

err_code  TFont::Create(_pc_sz pszFamily, const DWORD dwOptions, const LONG lParam) {
	pszFamily; dwOptions; lParam;

	err_code n_result = __s_ok;
	LOGFONT log = {0} ;

	if (this->Is())
		return n_result = (err_code)TErrCodes::eObject::eExists;

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
		if (CFontOptions(dwOptions).IsBold()) log.lfWeight |= FW_BOLD;
		if (CFontOptions(dwOptions).IsItalic()) log.lfItalic = TRUE;
		if (CFontOptions(dwOptions).IsUnderline()) log.lfUnderline = TRUE;

		log.lfQuality = CLEARTYPE_NATURAL_QUALITY;

		m_handle = ::CreateFontIndirect(&log);
		m_bManaged = true;
	}
	else {
		m_handle = reinterpret_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT));
	}
	return n_result;
}

HFONT     TFont::Detach(void)
{
	m_bManaged = false;
	return TBase::Detach();
}

/////////////////////////////////////////////////////////////////////////////

CFontScalable:: CFontScalable (const HDC hDC, LPCTSTR lpszFontFamily, const INT nSize, const DWORD dwOptions) : TBase() {
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

namespace ex_ui { namespace draw {

CLogFont:: CLogFont (void) : m_log{0} { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CLogFont:: CLogFont (const CLogFont& _ref) : CLogFont() { *this = _ref; }
CLogFont:: CLogFont (const HFONT _h_font) : CLogFont() { *this << _h_font; }
CLogFont:: CLogFont (const LOGFONT& _log) : CLogFont() { *this << _log; }
CLogFont:: CLogFont (CLogFont&& _src) : CLogFont() { *this = _src; }
CLogFont::~CLogFont (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef  CLogFont::Error (void) const { return this->m_error; }

const
LOGFONT&   CLogFont::Get (void) const { return this->m_log; }
LOGFONT&   CLogFont::Get (void)       { return this->m_log; }

HRESULT    CLogFont::Set (void) {
	m_error << __METHOD__ << __e_not_inited;
	// https://pvs-studio.com/en/blog/posts/cpp/0360/ ;
	// https://stackoverflow.com/questions/56565539/memset-s-what-does-the-standard-mean-with-this-piece-of-text ;
	// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-rtlsecurezeromemory ;
	::RtlSecureZeroMemory ((void*)&m_log, sizeof(LOGFONT));

	// memset_s( (void*)&m_log, sizeof(LOGFONT), 0, sizeof(LOGFONT)); *!!!not found!!!*

	return m_error;
}

HRESULT    CLogFont::Set (const LOGFONT& _log) {
	m_error << __METHOD__ << __s_ok;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s ;
	errno_t t_result = ::memcpy_s(&this->m_log, sizeof(LOGFONT), &_log, sizeof(LOGFONT));
	if (t_result)
		m_error << __e_no_memory;

	return m_error;
}

HRESULT    CLogFont::Set (const HFONT _font, const DWORD _opts) {
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

CLogFont&  CLogFont::operator = (const CLogFont& _ref) { *this << _ref.Get(); return *this; }
CLogFont&  CLogFont::operator <<(const HFONT _h_font) { this->Set(_h_font); return *this; }
CLogFont&  CLogFont::operator <<(const LOGFONT& _log) { this->Set(_log); return *this; }
CLogFont&  CLogFont::operator = (CLogFont&& _src) {
	this->Set(_src.Get()); _src.Set(); return *this;
}

/////////////////////////////////////////////////////////////////////////////

CLogFont::operator const  LOGFONT&(void) const { return this->Get(); }
CLogFont::operator        LOGFONT&(void)       { return this->Get(); }

}}