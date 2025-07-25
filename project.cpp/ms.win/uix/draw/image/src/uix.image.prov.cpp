/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jul-2025 at 17:37:12.589, UTC+4, Batumi, Wednesday;
	This is Ebo Pack image lib data provider interface implementation file;
*/
#include "uix.image.prov.h"
#include "uix.image.stream.h"

#include "uix.bitmap.h"

using namespace ex_ui::draw::images;
using namespace ex_ui::draw::bitmaps;

#include <wincodec.h>
#pragma comment (lib, "Windowscodecs.lib")

/////////////////////////////////////////////////////////////////////////////

CResult:: CResult (void) : m_bmp(0), m_size{0} { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CResult::~CResult (void) { this->Reset(); }

/////////////////////////////////////////////////////////////////////////////

err_code  CResult::Attach (HBitmap& _h_src) {
	_h_src;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_src || OBJ_BITMAP != ::GetObjectType((HGDIOBJ)_h_src))
		return this->m_error <<(err_code) TErrCodes::eObject::eHandle;

	if (this->Is_valid())
		return this->m_error <<(err_code) TErrCodes::eObject::eExists;

	this->m_bmp = _h_src; _h_src = nullptr;

	return this->Error();
}

HBitmap   CResult::Detach (void) {

	this->m_error <<__METHOD__<<__s_ok;

	HBitmap h_bmp = this->m_bmp;
	this->m_bmp = nullptr;

	return h_bmp;
}

TError&   CResult::Error  (void) const { return this->m_error; }
const
HBitmap&  CResult::Handle (void) const { return this->m_bmp; }

bool      CResult::Is_valid (void) const {
	return (nullptr != this->Handle() && OBJ_BITMAP == ::GetObjectType((HGDIOBJ)this->Handle())); // no size check this time;
}

#if defined(_DEBUG)
CString   CResult::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {bmp=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {bmp=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("bmp=%s;size=%s;valid=%s");

	CString cs_bmp   = TStringEx().__address_of(this->Handle(), _T("0x%08x"));
	CString cs_size  = TStringEx().Format(_T("[w|h:%d|%d](px)"), this->Size().cx, this->Size().cy);
	CString cs_valid = TStringEx().Bool (this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format ( pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, 
		(_pc_sz) cs_bmp, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format ( pc_sz_pat_n, (_pc_sz)__CLASS__, 
		(_pc_sz) cs_bmp, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format ( pc_sz_pat_r,
		(_pc_sz) cs_bmp, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

err_code  CResult::Reset (void) {
	this->m_error <<__METHOD__<<__e_not_inited;
	if (this->Is_valid())
		if (!::DeleteObject((HGDIOBJ)this->m_bmp))
			return this->m_error.Last();

	this->Size().cx = this->Size().cy = 0;
	return __s_ok;
}

const
t_size&   CResult::Size  (void) const { return this->m_size; }
t_size&   CResult::Size  (void)       { return this->m_size; }

CResult&  CResult::operator = (CResult&& _victim) {
	_victim;
	if (__is_okay(this->Reset())) {

		HBitmap bmp_ = _victim.Detach();
	
		this->Attach(bmp_);
		this->Size() = _victim.Size();
	
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CDataProvider:: CDataProvider (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDataProvider:: CDataProvider (const CDataProvider& _src) : CDataProvider() { *this = _src; }
CDataProvider:: CDataProvider (CDataProvider&&  _victim ) : CDataProvider() { *this = _victim; }
CDataProvider::~CDataProvider (void) {}

//////////////////////////////////////////////////////////////////////////////

TError&  CDataProvider::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

err_code CDataProvider::Load  (_pc_sz _p_file_path, const TImgFmt _e_type) {
	_p_file_path; _e_type;

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_file_path || 0 == ::_tcslen(_p_file_path))
		return this->m_error << __e_inv_arg;

	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;

	if (false == ::PathFileExists((_pc_sz)_p_file_path))
		this->m_error << (err_code) TErrCodes::ePath::eNoFile;

	this->m_result.Reset();

#if (0)
	// ImageList_Read() creates new image list, thus the image list variable must be empty(nullptr);
	if (nullptr != this->List() || this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eInited = _T("Image list handle must equal to null");

	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-shcreatestreamonfileex ;

	ATL::CComPtr<IStream> stream;
	// tries to open file for reading, not for creating or writing data;
	this->m_error << ::SHCreateStreamOnFileEx(_p_file_path, STGM_READ, OPEN_EXISTING, false, nullptr, &stream);
	if (this->m_error)
		return this->Error();
	
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_read ;
	this->List(::ImageList_Read(stream));
	if (this->Is_valid() == false)
		this->m_error.Last();
#elif (0==1)

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;

	CPicture picture;
	if (__failed(picture.Load(_p_file_path)))
		return this->m_error = picture.Error();
#else

	CStream stream;
	if (__failed(stream.Create(_p_file_path)))
		return this->m_error = stream.Error();

	CComPtr<IWICBitmapSource>  pSource  = nullptr; // https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nn-wincodec-iwicbitmapsource  ;
	CComPtr<IWICBitmapDecoder> pDecoder = nullptr; // https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nn-wincodec-iwicbitmapdecoder ;

	GUID guid_dec = __guid_null;

	switch (_e_type) {
	case TImgFmt::e_bmp : guid_dec = CLSID_WICBmpDecoder ; break;
	case TImgFmt::e_jpg : guid_dec = CLSID_WICJpegDecoder; break;
	case TImgFmt::e_jpeg: guid_dec = CLSID_WICJpegDecoder; break;
	case TImgFmt::e_png : guid_dec = CLSID_WICPngDecoder ; break;
	default:
		return this->m_error << (err_code) TErrCodes::eData::eUnsupport;
	}

	err_code n_result = ::CoCreateInstance(guid_dec, NULL, CLSCTX_INPROC_SERVER, __uuidof(pDecoder), reinterpret_cast<void**>(&pDecoder));
	if (__failed(n_result))
		return this->m_error << n_result;
	// https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nf-wincodec-iwicbitmapdecoder-initialize ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wincodec/ne-wincodec-wicdecodeoptions ;
	n_result = pDecoder->Initialize(stream.Ptr(), WICDecodeMetadataCacheOnLoad);
	if (__failed(n_result))
		return this->m_error << n_result;
	// https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nf-wincodec-iwicbitmapdecoder-getframecount ;
	UINT nFrameCount = 0;
	n_result = pDecoder->GetFrameCount(&nFrameCount);
	if (__failed(n_result))
		return this->m_error << n_result;

	if (0 == nFrameCount)
		return this->m_error << (err_code) TErrCodes::eData::eUnsupport = _T("There is no image frame");

	CComPtr<IWICBitmapFrameDecode> pFrame = nullptr;
	// https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nf-wincodec-iwicbitmapdecoder-getframe ;
	n_result = pDecoder->GetFrame(0, &pFrame);
	if (__failed(n_result))
		return this->m_error << n_result;
	// https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nf-wincodec-wicconvertbitmapsource ;
	// https://learn.microsoft.com/en-us/windows/win32/wic/-wic-codec-native-pixel-formats ;
	// ToDo: review the available color formats;
	n_result = ::WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, pFrame, &pSource);
	if (__failed(n_result))
		return this->m_error << n_result;

	UINT u_width  = 0;
	UINT u_height = 0;
	n_result = pSource->GetSize(&u_width, &u_height);
	if (__failed(n_result))
		return this->m_error << n_result;

	this->m_result.Size().cx = static_cast<LONG>(u_width );
	this->m_result.Size().cy = static_cast<LONG>(u_height);

	HDC hdcScreen = GetDC(0);

	CDibSection dib_sec;
	n_result  = dib_sec.Create(hdcScreen, this->m_result.Size());
	::ReleaseDC(0, hdcScreen);

	if (__failed(n_result))
		return this->m_error << n_result;

	byte* p_bits = const_cast<byte*>(dib_sec.Bits());
	HBitmap h_target  = dib_sec.Detach(); 

	if (p_bits && h_target) {
		const UINT cbStride = u_width * 4;
		const UINT cbImage  = cbStride * u_height;

		n_result = pSource->CopyPixels(nullptr, cbStride, cbImage, p_bits);
		if (__failed(n_result)) {
			this->m_error << n_result;
			::DeleteObject((HGDIOBJ)h_target); // no check for error this time yet;
			h_target = 0;
		}
		else
			this->m_result.Attach(h_target);
	}

#endif
	return this->Error();
}

const
CResult&  CDataProvider::Result(void) const { return this->m_result; }

/////////////////////////////////////////////////////////////////////////////

CDataProvider&  CDataProvider::operator = (const CDataProvider& _src) { _src; return *this; }
CDataProvider&  CDataProvider::operator = (CDataProvider&& _victim ) { *this = (const CDataProvider&)_victim; return *this; }