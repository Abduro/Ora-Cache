#pragma once
/*
	https://english.stackexchange.com/questions/23716/whats-the-difference-between-a-picture-and-an-image
	https://www.computerhope.com/issues/ch000169.htm

	This is a picture related interfaces' declaration file;
*/
namespace ex_ui { namespace draw { namespace images {
}}}

#if (0)
#include "ImageStream.h"

namespace qchart { namespace drawing {

	class CPicture
	{
	public:
		enum sup_type {
			e_none = 0,
			e_bmp  = 1,
			e_jpg  = 2,
		};
	public:
		 CPicture (void);
		 CPicture (const CPicture&);
		~CPicture (void);

	public:
		HRESULT Create  (const LPSTREAM _stream);
		HRESULT Create  (LPCTSTR _lp_sz_path);

		bool    IsValid (void) const;

		const
		IPicture*  Ptr(void) const ;
		IPicture*  Ptr(void)       ;

		HRESULT    ToBitmap(HBITMAP& _in_out) const;

	public:
		CPicture&  operator = (const CPicture&);
		CPicture&  operator <<(const LPSTREAM );

	private:
		ATL::CComPtr<IPicture> m_picture; // copyable;
	};
}}
#endif