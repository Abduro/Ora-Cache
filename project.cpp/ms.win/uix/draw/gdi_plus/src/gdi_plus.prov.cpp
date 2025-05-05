/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2007 at 9:59:**pm, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack owner-drawn related classe(s) implementation file.
	-----------------------------------------------------------------------------
	Adopted to Platinum project on 23-Mar-2014 at 8:53:20pm, GMT+4, Saint-Petersburg, Sunday; (https://platinumpayroll.co.nz)
	Adopted to File Guardian project on 28-May-2018 at 11:09:23p, UTC+7, Phuket, Rawai, Monday; (https://thefileguardian.com/)
	Adopted to Geometry Curve project on 17-Feb-2024 at 12:30:11.9845955, UTC+7, Novosibirsk, Saturday;
*/

#include "gdi_plus.prov.h"

using namespace ex_ui::draw::gdi_pls;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace gdi_pls { namespace _impl {

	bool       get_auto (void) {
		static volatile bool b_auto = false;
		return b_auto;
	}
	// error C2440: 'return': cannot convert from 'volatile ULONG_PTR' to 'ULONG_PTR &'
	ULONG_PTR& get_token (void) {
		static ULONG_PTR token_ = NULL;
		return token_;
	}

}}}}

using namespace ex_ui::draw::gdi_pls::_impl;

/////////////////////////////////////////////////////////////////////////////

CGuard:: CGuard(const bool _b_auto_mode) : m_auto_mode(_b_auto_mode) {

	this->m_err_ada = TErrAdapt_enum::Ref().Get(TAlias::e_uninited/*t_stat::GdiplusNotInitialized*/);

	if (m_auto_mode)
		this->Capture();
}
CGuard::~CGuard(void) {
	if (m_auto_mode)
		this->Release();
}

/////////////////////////////////////////////////////////////////////////////

bool  CGuard::Auto (void) const { return this->m_auto_mode; }

err_code CGuard::Capture (void) {

	err_code n_result = TErrCodes::no_error;
	
	if (!!get_token()) {
		this->m_err_ada  = TErrAdapt_enum::Ref().Get(TAlias::e_inv_state/*t_stat::WrongState*/);
		return (n_result = TErrCodes::eObject::eInited);
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusstartup ;
	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ns-gdiplusinit-gdiplusstartupinput ;

	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nc-gdiplusinit-debugeventproc ;
	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ne-gdiplusinit-debugeventlevel ;

	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ns-gdiplusinit-gdiplusstartupoutput ;

	Gdiplus::GdiplusStartupInput input_ = {0};
	this->m_err_ada = TErrAdapt_enum::Ref().Get(Gdiplus::GdiplusStartup(&get_token(), &input_, 0));

	return (n_result = this->m_err_ada.Sys_err().Code());
}

#if defined(_DEBUG)
CString  CGuard::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{auto=%s;inited=%s;status=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{auto=%s;inited=%s;status=%s}");
	static _pc_sz pc_sz_pat_r = _T("auto=%s;inited=%s");

	CString cs_auto = TStringEx().Bool(this->Auto());
	CString cs_seq  = TStringEx().Bool(this->Secured());
	CString cs_stat = this->Status().Print(e_print::e_all);
	CString cs_out;

	if (e_print::e_all == e_opt) {
		cs_out.Format( pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_auto, (_pc_sz) cs_seq, (_pc_sz) cs_stat);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format( pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_auto, (_pc_sz) cs_seq, (_pc_sz) cs_stat );
	}
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_auto, (_pc_sz) cs_seq); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

err_code CGuard::Release (void) {

	err_code n_result = TErrCodes::no_error;

	if (false == !!get_token()) {
		this->m_err_ada  = TErrAdapt_enum::Ref().Get(TStatus::WrongState);
		return (n_result = TErrCodes::eExecute::eState);
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusshutdown ;
	// unfortunately there is no returned result from this method; thus, the status is set to uninitialized mode; no any other suggestions yet;
	Gdiplus::GdiplusShutdown(get_token()); get_token() = 0;

	this->m_err_ada = TErrAdapt_enum::Ref().Get(TAlias::e_uninited); // the same state as it is before initializing gdi+ module;

	return n_result;
}

bool     CGuard::Secured (void) const { return (!!get_token()); }

TErr_ref CGuard::Status (void) const {
	return this->m_err_ada;
}

/////////////////////////////////////////////////////////////////////////////
#if (0)
namespace ex_ui { namespace draw { namespace _impl
{
	struct GdiPlus_ResourceInfo
	{
		PVOID   __res;
		DWORD   __size;
		GdiPlus_ResourceInfo(void) : __res(0), __size(0) {}
	};

	static HRESULT GdiPlus_GetResourcePtr(const ATL::_U_STRINGorID RID, const HMODULE hModule, GdiPlus_ResourceInfo& res__)
	{
		if (!RID.m_lpstr)
			return E_INVALIDARG;

		HRSRC hResource = ::FindResource(hModule, RID.m_lpstr, _T("PNG"));
		if (!hResource)
			return OLE_E_CANT_BINDTOSOURCE;

		res__.__size = ::SizeofResource(hModule, hResource);
		if (!res__.__size)
			return ERROR_EMPTY;

		res__.__res = ::LockResource(::LoadResource(hModule, hResource));
		if (!res__.__res)
			return STG_E_LOCKVIOLATION;
		else
			return S_OK;
	}

	class  GdiPlus_GlobalAlloca
	{
	private:
		HGLOBAL    m_hGlobal;
		HRESULT    m_hResult;
		DWORD      m_dwSize;
		PVOID      m_pVoid;
	public:
		// error C4596: '{ctor}': illegal qualified name in member declaration
		// GdiPlus_GlobalAlloca::
		GdiPlus_GlobalAlloca(const DWORD size__, const bool fixed__ = false):
			m_hGlobal(NULL),
			m_hResult(OLE_E_BLANK),
			m_dwSize(size__),
			m_pVoid(NULL)
		{
			try
			{
				m_hGlobal = ::GlobalAlloc(fixed__ ? GMEM_FIXED : GMEM_MOVEABLE, m_dwSize);
				m_hResult = (m_hGlobal != NULL ? S_OK : E_OUTOFMEMORY);
				if (S_OK == m_hResult)
				{
					m_pVoid = ::GlobalLock(m_hGlobal);
					if (!m_pVoid)
						 m_hResult = HRESULT_FROM_WIN32(::GetLastError());
				}
			}
			catch(...)
			{
				m_hResult = E_OUTOFMEMORY;
			}
		}
		// error C4596: '{dtor}': illegal qualified name in member declaration
		// GdiPlus_GlobalAlloca::
		~GdiPlus_GlobalAlloca(void)
		{
			m_pVoid = NULL;
			if (m_hGlobal)
			{
				::GlobalUnlock(m_hGlobal);
				::GlobalFree(m_hGlobal);
				m_hGlobal = NULL;
			}
		}
	public:
		HGLOBAL    GetHandle(void) const     { return m_hGlobal; }
		HRESULT    GetLastResult(void) const { return m_hResult; }
		PVOID      GetPtr(void) const        { return m_pVoid;   }
		DWORD      GetSize(void) const       { return m_dwSize;  }
	private:
		GdiPlus_GlobalAlloca(const GdiPlus_GlobalAlloca&);
		GdiPlus_GlobalAlloca& operator=(const GdiPlus_GlobalAlloca&);
	};
}}}
using namespace ex_ui::draw::_impl;
/////////////////////////////////////////////////////////////////////////////

HRESULT     TPngLoader::CreateImages(const LPVOID pRawData, const DWORD _data_sz, Gdiplus::Bitmap*& _p_bmp) {

	HRESULT hr_ = S_OK;
	if (NULL == pRawData) {
		return (hr_ = HRESULT_FROM_WIN32(ERROR_INVALID_DATA));
	}
	if (0 == _data_sz) {
		return (hr_ = E_INVALIDARG);
	}

	if (NULL != _p_bmp) {
		return (hr_ = HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED));
	}
	// https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-createstreamonhglobal;
	// The handle must be allocated as moveable and nondiscardable.
	CGlobalAlloca alloca(pRawData, _data_sz, true);
	if (alloca.IsValid() == false)
		return (hr_ = alloca.Error());

	::ATL::CComPtr<IStream> pStream;
	hr_ = ::CreateStreamOnHGlobal(alloca.Handle(), FALSE, &pStream);
	if (FAILED(hr_))
		return hr_;

	_p_bmp = Gdiplus::Bitmap::FromStream(pStream);
	if (_p_bmp)
		hr_ = CErr_drw((*_p_bmp).GetLastStatus());
	else
		hr_ = E_OUTOFMEMORY;

	return  hr_;
}

HRESULT     TPngLoader::CreateImages(const LPVOID pRawData, const DWORD _data_sz, HIMAGELIST& hImageList) {

	Gdiplus::Bitmap* pBitmap = NULL;
	HRESULT hr_ = CGdiPlusPng_Loader::CreateImages(pRawData, _data_sz, pBitmap);
	if (FAILED(hr_))
		return hr_;
	if (NULL == pBitmap)
		return (hr_ = E_UNEXPECTED);

	HBITMAP hBitmap = NULL;

	const Gdiplus::Status g_s = pBitmap->GetHBITMAP(0, &hBitmap);
	hr_ = CErr_drw(g_s);
	if (FAILED(hr_))
		goto __clean_mark__;

	hr_ = CGdiPlusPng_Loader::CreateImages(hBitmap, hImageList);

__clean_mark__:
	try {
		delete pBitmap; pBitmap = NULL;
	}
	catch(...){ hr_ = E_OUTOFMEMORY; }

	if (hBitmap)
		::DeleteObject(hBitmap);

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

HRESULT     TPngLoader::CreateImages(const ATL::_U_STRINGorID RID, const HMODULE hModule, HIMAGELIST& hImageList)
{
	HBITMAP bmp = NULL;
	HRESULT hr_ = CGdiPlusPng_Loader::LoadResource(RID, hModule, bmp);
	if (S_OK != hr_)
		return  hr_;

	hr_ = CGdiPlusPng_Loader::CreateImages(bmp, hImageList);
	if (bmp)
		::DeleteObject(bmp);
	return hr_;
}

HRESULT     TPngLoader::LoadResource(const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*& ptr_ref)
{
	if (ptr_ref)
		return HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS);

	GdiPlus_ResourceInfo res__;
	HRESULT hr = GdiPlus_GetResourcePtr(RID, hModule, res__);
	if (S_OK != hr)
		return hr;

	GdiPlus_GlobalAlloca ga__(res__.__size, false);
	if (S_OK != (hr = ga__.GetLastResult()))
		return hr;

	::CopyMemory(ga__.GetPtr(), res__.__res, res__.__size);

	::ATL::CComPtr<IStream> pStream;
	hr = ::CreateStreamOnHGlobal(ga__.GetHandle(), FALSE, &pStream);
	if (S_OK==hr)
	{
		ptr_ref = Gdiplus::Bitmap::FromStream(pStream);
		if (ptr_ref)
		{
			hr = ((*ptr_ref).GetLastStatus() == Gdiplus::Ok ? S_OK : E_OUTOFMEMORY);
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}
	}
	return hr;
}

HRESULT     TPngLoader::LoadResource(const ATL::_U_STRINGorID RID, const HMODULE hModule, HBITMAP& hBitmap)
{
	if (hBitmap)
		return HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS);
	Gdiplus::Bitmap* pBitmap = NULL;
	HRESULT hr_ = CGdiPlusPng_Loader::LoadResource(RID, hModule, pBitmap);
	if (S_OK != hr_)
		return  hr_;
	if (!pBitmap)
		return E_UNEXPECTED;
	pBitmap->GetHBITMAP(0, &hBitmap);
	try
	{
		delete pBitmap; pBitmap = NULL;
	}
	catch(...){ return E_OUTOFMEMORY; }
	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

HRESULT     TPngLoader::CreateImages(const HBITMAP& hBitmap, HIMAGELIST& hImageList) {

	HRESULT hr_ = S_OK;
	if (NULL == hBitmap)
		return (hr_ = E_HANDLE);

	if (NULL != hImageList)
		return (hr_ = HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED));

	BITMAP  bmpInfo = {0};

	if (::GetObject(hBitmap, sizeof(BITMAP), &bmpInfo)) {
		//
		// _img_sz is ignored for this version of the code;
		//
		const LONG nCount = (bmpInfo.bmWidth > bmpInfo.bmHeight ? bmpInfo.bmWidth / bmpInfo.bmHeight : 1);
		hImageList = ::ImageList_Create(bmpInfo.bmWidth / nCount, bmpInfo.bmHeight, ILC_COLOR32, nCount, 0);
		if (hImageList)
			hr_ = (-1 != ::ImageList_Add(hImageList, hBitmap, NULL) ? S_OK : E_OUTOFMEMORY);
		else
			hr_ = __HRESULT_FROM_LASTERROR();
	}
	else {  hr_ = __HRESULT_FROM_LASTERROR(); }

	return  hr_;
}

HRESULT     TPngLoader::CreateImages(const HBITMAP& _h_bmp, HIMAGELIST& _h_lst, const SIZE& _sz_frame) {

	HRESULT hr_ = S_OK;
	if (NULL == _h_bmp)
		return (hr_ = E_HANDLE);

	if (NULL != _h_lst)
		return (hr_ = HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED));

	if (_sz_frame.cx < 16 || _sz_frame.cy < 16 || _sz_frame.cx < _sz_frame.cy)
		return (hr_ = E_INVALIDARG);

	BITMAP b_i_ = {0};

	if (::GetObject(_h_bmp, sizeof(BITMAP), &b_i_)) {
		//
		// this version does not work with images that has a height greater than a width;
		//
		if (b_i_.bmWidth < b_i_.bmHeight)
			return (hr_ = E_INVALIDARG);

		const LONG nCount = (
				b_i_.bmWidth / _sz_frame.cx
			);
		_h_lst = ::ImageList_Create(_sz_frame.cx, _sz_frame.cy, ILC_COLOR32, nCount, 0);
		if (_h_lst)
			hr_ = (-1 != ::ImageList_Add(_h_lst, _h_bmp, NULL) ? S_OK : E_OUTOFMEMORY);
		else
			hr_ = __HRESULT_FROM_LASTERROR();
	}
	else {  hr_ = __HRESULT_FROM_LASTERROR(); }

	return  hr_;
}

HMODULE     TPngLoader::CurrentModule(void) {
	const HINSTANCE hInstance = ::ATL::_AtlBaseModule.GetModuleInstance();
	return hInstance;
}

/////////////////////////////////////////////////////////////////////////////

TPngLoaderLite:: CGdiPlusPng_Loader_lite(void) {}
TPngLoaderLite::~CGdiPlusPng_Loader_lite(void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT     TPngLoaderLite::LoadImage(const ATL::_U_STRINGorID RID, Gdiplus::Bitmap*& ptr_ref) {
	const HINSTANCE hInstance = ::ATL::_AtlBaseModule.GetModuleInstance();
	return this->LoadImage(RID, hInstance, ptr_ref);
}

HRESULT     TPngLoaderLite::LoadImage(const ATL::_U_STRINGorID RID, HBITMAP& _h_bit) {
	HRESULT hr_ = S_OK;
	if (_h_bit)
		return (hr_ = __DwordToHresult(ERROR_OBJECT_ALREADY_EXISTS));

	Gdiplus::Bitmap* pBitmap = NULL;
	hr_ = this->LoadImage(RID, pBitmap);
	if (FAILED(hr_))
		return hr_;

	if (NULL == pBitmap)
		return (hr_ = E_UNEXPECTED);

	pBitmap->GetHBITMAP(0, &_h_bit);
	try
	{
		delete pBitmap; pBitmap = NULL;
	}
	catch(...){ return E_OUTOFMEMORY; }
	return hr_;
}

HRESULT     TPngLoaderLite::LoadImage(const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*& ptr_ref) {
	if (ptr_ref)
		return HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS);

	GdiPlus_ResourceInfo res__;
	HRESULT hr_ = GdiPlus_GetResourcePtr(RID, hModule, res__);
	if (FAILED(hr_))
		return hr_;

	GdiPlus_GlobalAlloca ga__(res__.__size, false);
	if (FAILED(hr_ = ga__.GetLastResult()))
		return hr_;

	::CopyMemory(ga__.GetPtr(), res__.__res, res__.__size);

	::ATL::CComPtr<IStream> pStream;
	hr_ = ::CreateStreamOnHGlobal(ga__.GetHandle(), FALSE, &pStream);
	if (SUCCEEDED(hr_)) {
		ptr_ref = Gdiplus::Bitmap::FromStream(pStream);
		if (ptr_ref) {
			hr_ = ((*ptr_ref).GetLastStatus() == Gdiplus::Ok ? S_OK : E_OUTOFMEMORY);
		}
		else {
			hr_ = E_OUTOFMEMORY;
		}
	}
	return hr_;
}
#if (0)
/////////////////////////////////////////////////////////////////////////////

TGdiPlsHelper:: CGdiPlus_Helper(void) {}
TGdiPlsHelper::~CGdiPlus_Helper(void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT     TGdiPlsHelper::DrawImage(const HDC _h_dc, const RECT& _rc_area, Gdiplus::Bitmap* const _p_bmp) { HRESULT hr_ = S_OK;
	_h_dc; _rc_area; _p_bmp;
	if (NULL == _p_bmp)
		return (hr_ = E_POINTER);
	if (NULL == _h_dc || (OBJ_MEMDC != ::GetObjectType(_h_dc) && OBJ_DC != ::GetObjectType(_h_dc))) return (hr_ = E_HANDLE);
	if (::IsRectEmpty(&_rc_area)) return (hr_ = OLE_E_INVALIDRECT);

	Gdiplus::Graphics gr__(_h_dc);

	const SIZE sz_bmp = {
		static_cast<LONG>(_p_bmp->GetWidth()), static_cast<LONG>(_p_bmp->GetHeight())
	};
	const POINT pt_anchor = {
		_rc_area.left + (__W(_rc_area) - sz_bmp.cx) / 2,
		_rc_area.top  + (__H(_rc_area) - sz_bmp.cy) / 2
	};

	gr__.DrawImage(_p_bmp, pt_anchor.x, pt_anchor.y, sz_bmp.cx, sz_bmp.cy);

	return hr_;
}

HRESULT     TGdiPlsHelper::Gradient(const HDC& _h_dc, const RECT& _rc_area, _c_clr _from, _c_clr _upto, const bool _b_horz) {
	_h_dc; _rc_area; _from; _upto; _b_horz;
	HRESULT hr_ = S_OK;
	if (NULL == _h_dc)
		return (hr_ = E_HANDLE);
	if (::IsRectEmpty(&_rc_area))
		return (hr_ = OLE_E_INVALIDRECT);

	TRIVERTEX        vert[2] = {0};
	GRADIENT_RECT    gRect   = {0};
	vert [0] .x      = _rc_area.left;
	vert [0] .y      = _rc_area.top;
	vert [0] .Red    = GetRValue(_from)<<8;
	vert [0] .Green  = GetGValue(_from)<<8;
	vert [0] .Blue   = GetBValue(_from)<<8;
	vert [0] .Alpha  = 0x0000;

	vert [1] .x      = _rc_area.right;
	vert [1] .y      = _rc_area.bottom; 
	vert [1] .Red    = GetRValue(_upto)<<8;
	vert [1] .Green  = GetGValue(_upto)<<8;
	vert [1] .Blue   = GetBValue(_upto)<<8;
	vert [1] .Alpha  = 0x0000;

	gRect.UpperLeft  = 0;
	gRect.LowerRight = 1;
	::GradientFill(_h_dc, vert, 2, &gRect, 1, _b_horz ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V);

	return  hr_;
}
#endif
#endif