#ifndef _UIX_IMG_CACHE_H_INCLUDED
#define _UIX_IMG_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jul-2025 at 23:35:28.326, (UTC+4), Batumi, Friday;
	This is Ebo Pack generic 32-bits image cache interface declaration file;
*/
#include "uix.image.defs.h"
#include "uix.bitmap.h"

namespace ex_ui { namespace draw { namespace images {

	using namespace ex_ui::draw;
	using namespace ex_ui::draw::bitmaps;
#pragma region __refs_a
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_copy ;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_getimageinfo ;
	// https://learn.microsoft.com/en-us/windows/win32/api/commoncontrols/ns-commoncontrols-imageinfo ;
#pragma endregion
	using SImgInfo = IMAGEINFO;
	/*
		The image list control may be created and be used through the following:
		(1) WTL CImagList class that is the wrapper over ImageList_xxx() functions of Win32 API;
		(2) COM interface IImageList: https://learn.microsoft.com/en-us/windows/win32/api/commoncontrols/nn-commoncontrols-iimagelist ;
		(3) User defined class or a set of classes, like it is made below;
	*/

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
		// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_draw ;
		err_code  Draw  (const uint16_t _n_index, const HDC, const int16_t _n_x, const int16_t _n_y, const uint32_t _u_mode = ILD_NORMAL);

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
		t_size&   Size  (void) const;            // the image list item size can be changed in case of the list re-creation;
	public:
		CList& operator = (const CList&);
		CList& operator = (CList&&) = delete;

	protected:
		mutable
		CError   m_error;
		t_size   m_size ;
		HImgList m_list ;
		dword    m_list_id; // (static_cast<dword>(_n_width) << 16) | static_cast<dword>(_n_height);
	};

	typedef ::std::map<dword, CList> TRawLists;

	class CCache {
	public:
		 CCache (void); CCache (const CCache&); CCache (CCache&&) = delete;
		~CCache (void);

	public:
		err_code Append(_pc_sz _p_file_dir, const TImgFmt); // appends files with specific extension from specified directory ;
		err_code Append(const t_size&, const uint16_t _n_count = 0, const uint16_t _n_delta = 0);

		TError&  Error (void) const;

		const bool Has (const dword _n_id) const; // returns 'true' in case if the list of input identifier exists;
		const bool Has (const t_size&) const;     // returns 'true' in case if the list of input size of the image exists;
		const
		CList&   List  (const dword _n_id) const; // gets the list by the identifier; if not found the reference to fake list returned;
		CList&   List  (const dword _n_id) ;      // gets the list by the identifier; if not found the reference to fake list returned;
		const
		CList&   List  (const t_size&) const;  // gets the list by the required size of its images; if not found the reference to fake list returned;
		CList&   List  (const t_size&) ;       // gets the list by the required size of its images; if not found the reference to fake list returned;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	public:
		CCache& operator = (const CCache&);
		CCache& operator = (CCache&&) = delete;

	protected:
		mutable
		CError    m_error;
		TRawLists m_lists;
	};

}}}

#endif/*_UIX_IMG_CACHE_H_INCLUDED*/