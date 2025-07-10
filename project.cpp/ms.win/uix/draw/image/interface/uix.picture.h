#ifndef _UIX_PICTURE_H_INCLUDED
#define _UIX_PICTURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apt-2022 at 18:16:52.257, UTC+7, Novosibirsk, Thursday;
	This is a picture related interfaces' declaration file; [this declaration is made within 'Smart Diagram' project of ARQA Technologies]
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack image wrappers' project on 09-Jul-2025 at 15:47:53.0155, UTC+4, Batumi, Wednesday;
*/
#include "uix.image.defs.h"

namespace ex_ui { namespace draw { namespace images {

	#include <olectl.h>
#pragma region __refs_4
	// https://blog.freeimages.com/post/pictures-images-and-photos-deciphering-the-differences ;
	// https://english.stackexchange.com/questions/23716/whats-the-difference-between-a-picture-and-an-image ;
	// https://www.computerhope.com/issues/ch000169.htm ;
#pragma endregion
	// https://learn.microsoft.com/en-us/windows/win32/api/ocidl/nn-ocidl-ipicture ;
	typedef ::ATL::CComPtr<IPicture> TPicturePtr;
	// https://stackoverflow.com/questions/4567875/how-would-i-load-a-png-image-using-win32-gdi-no-gdi-if-possible << needed the right answer;
	class CPicture {
	public:
		 CPicture (void); CPicture (const CPicture&); CPicture (CPicture&&) = delete;
		~CPicture (void);

	public:
		err_code  Delete(void) ;               // deletes the internal bitmap handle;
		TError&   Error (void) const;
		const
		HBITMAP   Handle(void) const;

		bool   Is_valid (void) const;

		err_code  Load  (_pc_sz _p_file_path); // loads the image from the file by input path;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		TPicturePtr&  Ptr (void) const;
		TPicturePtr&  Ptr (void) ;

		t_size    Size (void) const;

		err_code  ToBitmap(HBITMAP& _in_out) const;

	public:
		CPicture& operator = (const CPicture&);
		CPicture& operator = (CPicture&&) = delete;

		CPicture& operator <<(const TPicturePtr&) ;

	private:
		mutable
		CError  m_error;
		TPicturePtr m_pPicture;                // ToDo: this interface may be hidden;
		HBITMAP m_hBitmap;                     // the bitmap that is loaded from the file specified;
	};
}}}

#endif

#if (0)
#include "ImageStream.h"

namespace qchart { namespace drawing {

	
	{
	public:
		enum sup_type {
			e_none = 0,
			e_bmp  = 1,
			e_jpg  = 2,
		};
	public:
		HRESULT Create  (const LPSTREAM _stream);
		HRESULT Create  (LPCTSTR _lp_sz_path);

		IPicture*  Ptr(void)       ;

		HRESULT    ToBitmap(HBITMAP& _in_out) const;

	public:
		CPicture&  operator = (const CPicture&);
		CPicture&  operator <<(const LPSTREAM );

	
}}
#endif