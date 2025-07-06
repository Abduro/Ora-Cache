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

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_create ;
	// https://learn.microsoft.com/en-us/windows/win32/controls/ilc-constants ;
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_destroy ;
	using HImgList = HIMAGELIST;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_copy ;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_getimageinfo ;
	// https://learn.microsoft.com/en-us/windows/win32/api/commoncontrols/ns-commoncontrols-imageinfo ;
	
	using SImgInfo = IMAGEINFO;

	class CList {
	public:
		 CList (void); CList (const CList&); CList (CList&&) = delete;
		~CList (void);

	public:
#if (0)
		err_code  CopyTo  (HImgList&);           // copies this image list to the input handle of other image list;
#endif
		err_code  Create  (const t_size& _img_size, const uint16_t _n_count = 1, const uint16_t _n_delta = 1);
		err_code  Create  (const uint16_t _n_width, const uint16_t _n_height, const uint16_t _n_count = 1, const uint16_t _n_delta = 1);
		err_code  Destroy (void);

		err_code  DuplicateTo (HImgList&) const; // https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_duplicate ;

		uint16_t  Count (void) const;            // returns the count number of how much images the image list has;

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