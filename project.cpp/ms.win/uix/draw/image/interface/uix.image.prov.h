#ifndef _UIX_IMAGE_PROV_H_INCLUDED
#define _UIX_IMAGE_PROV_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jul-2025 at 17:35:38.374, UTC+4, Batumi, Wednesday;
	This is Ebo Pack image lib data provider interface declaration file;
*/
#include "uix.image.defs.h"
#include "uix.image.cache.h"

namespace ex_ui { namespace draw { namespace images {

	class CResult {
	public:
		 CResult (void); CResult (const CResult&) = delete; CResult (CResult&&) = delete;
		~CResult (void);
	public:
		err_code  Attach (HBITMAP&);       // attaches the input handle, input handle is set to nullptr, there is not handle duplication;
		HBITMAP   Detach (void);           // returns encupsulated bitmap handle and set to zero of this class field;
		TError&   Error  (void) const;
		const
		HBITMAP&  Handle (void) const;     // just returns a reference to the bitmap handle;

		bool      Is_valid (void) const;   // returns 'true' in case of bitmap handle is set and is valid, and the size is not zero;
		err_code  Reset (void);            // deletes the bitmap handle of the result, if any; clears the size structure;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		t_size&   Size   (void) const;
		t_size&   Size   (void) ;

	public:
		CResult&  operator = (const CResult&) = delete; CResult& operator = (CResult&&) = delete;

	private:
		HBITMAP   m_bmp ;   // the bitmap pointer or handle that is loaded the last;
		SIZE      m_size;   // the size of the bitmap received during last loading ;
		CError    m_error;
	};

	// a data provider class does *not* manage or control life cycle of the image list, but just deal with its handle for setting data;
	class CDataProvider {
	public:
		enum e_image_fmt {  // this enumeration can be extended for new acceptable formats of the image, but this one is enough for the time being;
		     e__undef = 0x0,
		     e_bmp    = 0x1,
		     e_jpeg   = 0x2,
		     e_png    = 0x3,
		};
	public:
		 CDataProvider (void) ;  CDataProvider (const CDataProvider&); CDataProvider (CDataProvider&&) ;
		~CDataProvider (void) ;

	public:
		TError&  Error (void) const;
		err_code Load  (_pc_sz _p_file_path, const e_image_fmt = e_image_fmt::e_png);
		const
		CResult& Result(void) const;

	public:
		CDataProvider&  operator = (const CDataProvider&);
		CDataProvider&  operator = (CDataProvider&&);       // neither swap() nor move() method is used; just copying image list handle;

	private:
		CError   m_error ;
		CResult  m_result;
	};

}}}

#endif/*_UIX_IMAGE_PROV_H_INCLUDED*/