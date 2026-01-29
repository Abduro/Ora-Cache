#ifndef _UIX_IMG_CACHE_H_INCLUDED
#define _UIX_IMG_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jul-2025 at 23:35:28.326, (UTC+4), Batumi, Friday;
	This is Ebo Pack generic 32-bits image cache interface declaration file;
*/
#include "uix.gdi.defs.h"
#include "uix.img.bitmap.h"

namespace ex_ui { namespace draw { namespace images {

	using namespace ex_ui::draw;
	using namespace ex_ui::draw::bitmaps;

	// https://learn.microsoft.com/en-us/windows/win32/controls/ilc-constants ;
	using HImgList = HIMAGELIST;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_copy ;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_getimageinfo ;
	// https://learn.microsoft.com/en-us/windows/win32/api/commoncontrols/ns-commoncontrols-imageinfo ;
	
	using SImgInfo = IMAGEINFO;
	/*
		The image list control may be created and be used through the following:
		(1) WTL CImagList class that is the wrapper over ImageList_xxx() functions of Win32 API;
		(2) COM interface IImageList: https://learn.microsoft.com/en-us/windows/win32/api/commoncontrols/nn-commoncontrols-iimagelist ;
		(3) User defined class or a set of classes, like it is made below;
	*/
	// a data provider class does *not* manage or control life cycle of the image list, but just deal with its handle for setting data;
	class CDataProvider {
	public:
		 CDataProvider (const HImgList = nullptr) ;  CDataProvider (const CDataProvider&); CDataProvider (CDataProvider&&) ;
		~CDataProvider (void);

	public:
		TError&  Error (void) const;
		bool  Is_valid (void) const;  // checks a set value of the image list handle for nullptr, nothing specific;
		HImgList List  (void) const;
		err_code List  (const HImgList&);

		err_code Load  (_pc_sz _p_file_path);

	public:
		CDataProvider&  operator = (const CDataProvider&);
		CDataProvider&  operator = (CDataProvider&&);       // neither swap() nor move() method is used; just copying image list handle;

		CDataProvider&  operator <<(const HImgList&);

	private:
		HImgList m_list;
		CError   m_error;	
	};

	class CList {
	public:
		 CList (void); CList (const CList&); CList (CList&&) = delete;
		~CList (void);

	public:
		err_code  Append  (const HBitmap);    // bitmap handle, bits per pixel and size will be checked;
		err_code  CopyTo  (HImgList&) const;  // copies this image list to the input handle of other image list;

		err_code  Create  (const t_size& _img_size, const uint16_t _n_count = 1, const uint16_t _n_delta = 1);
		err_code  Create  (const uint16_t _n_width, const uint16_t _n_height, const uint16_t _n_count = 1, const uint16_t _n_delta = 1);
		err_code  Destroy (void);

		uint16_t  Count (void) const;         // returns the count number of how much images the image list has;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		dword  Id (void) const;

		const
		HImgList& Handle(void) const;
		HImgList& Handle(void) ;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		t_size&   Size  (void) const;            // the image list item size can be change in case of the list re-creation;
	public:
		CList& operator = (const CList&);
		CList& operator = (CList&&) = delete;

	protected:
		mutable
		CError   m_error;
		t_size   m_size ;
		HImgList m_list ;
		dword    m_list_id;
	};

	typedef ::std::map<dword, CList> TRawLists;

	class CCache {
	public:
		 CCache (void); CCache (const CCache&); CCache (CCache&&) = delete;
		~CCache (void);

	public:
		TError& Error (void) const;

	public:
		CCache& operator = (const CCache&);
		CCache& operator = (CCache&&) = delete;

	protected:
		CError    m_error;
		TRawLists m_items;
	};

}}}

#endif/*_UIX_IMG_CACHE_H_INCLUDED*/