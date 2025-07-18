#ifndef _UIX_BITMAP_H_INCLUDED
#define _UIX_BITMAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Oct-2010 at 1:02:30am, GMT+3, Rostov-on-Don, Tuesday;
	This is Sfx Pack project shared UIX draw library GDI wrapper interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on on 7-Feb-2015 at 10:27:49pm, GMT+3, Taganrog, Saturday;
	Adopted to v15 on 28-May-2018 at 11:08:13p, UTC+7, Phuket, Rawai, Monday;
	Adopted to FakeGPS project on 19-Apr-2020 at 3:09:08a, UTC+7, Novosibirsk, Sunday;
*/
#include "uix.image.defs.h"

namespace ex_ui { namespace draw { namespace bitmaps {

	using namespace ex_ui::draw::images;
	using HBitmap = HBITMAP;

	// https://www.grammarly.com/blog/know-your-latin-i-e-vs-e-g/
	// *IMPORTANT*
	// all images are expected to have 32-bit-color format, otherwise an error is returned;
	// it is assumed a bitmap row of image pixels is rounded to 4 bytes value, that means a stride = 4-byte * bitmap width;
	// but sometimes implement code does not check of color-bitness and it may lead to an error of memory access; this is must be checked;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getdibits ;
	using TBmpHeader = BITMAPINFOHEADER;
	class CBmpHeader {
	public:
		 CBmpHeader (void) = default; CBmpHeader (const CBmpHeader&) = delete; CBmpHeader (CBmpHeader&&) = delete;
		~CBmpHeader (void) = default;

	public:
		static err_code  Get (const HBitmap& _from, TBmpHeader& _to);
#if defined(_DEBUG)
		static CString Print (const TBmpHeader&, const e_print = e_print::e_all);
#endif

	public:
		CBmpHeader&  operator = (const CBmpHeader&) = delete;
		CBmpHeader&  operator = (CBmpHeader&&) = delete;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmap ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo ;

	using TBmpInfo = BITMAPINFO;
	using TBitmap  = BITMAP;

	// this class does *not* free/delete an object that is attached;
	class CBitmapInfo : public TBitmap { typedef TBitmap TBase;
	public:
		 CBitmapInfo (void);
		 CBitmapInfo (const CBitmapInfo&);
		 CBitmapInfo (const HBitmap hBitmap, const UINT UID = ::GetTickCount());
		~CBitmapInfo (void);

	public:
		err_code   Attach (const HBitmap); // attaches to bitmap handle provided and initializes base structure fields;
		HBitmap    Detach (void);          // returns attached handle and resets itself;
		err_code   Reset  (void);          // zeros this class object attributes and base structure fields;

	public:
		const
		HBitmap    Handle (void ) const;
		UINT       ID     (void ) const;
		bool       Is     (void ) const;
		TBmpInfo   Raw    (void ) const;
		err_code   Size   (t_size&) const;
#if defined(_DEBUG)
		CString    Print  (const e_print = e_print::e_all) const;
#endif
	public:
		CBitmapInfo& operator = (const CBitmapInfo&);
		CBitmapInfo& operator <<(const UINT UID);
		CBitmapInfo& operator <<(const HBitmap );

	public:
		operator const HBitmap  (void) const;
		operator const TBmpInfo (void) const;

	public:
		static
		bool      IsValid(const HBitmap);
	private:
		UINT       m_UID;      // identifier of this object;
		HBitmap    m_handle;   // attached bitmap handle;
	};

	typedef const _byte* _pc_byte;
	// https://docs.microsoft.com/en-us/windows/win32/gdi/storing-an-image
	class CDibSection {
	public:
		 CDibSection (void);
		 CDibSection (const CDibSection&);  CDibSection (CDibSection&&) = delete;
		 CDibSection (const HDC, const t_size&);
		~CDibSection (void);

	public: // bitmap life cycle;
		err_code  Create  (const HDC, const SIZE&); // creates new bitmap by applying input arguments; the previous data is destroyed if any;
		err_code  Destroy (void)      ;             // returned result is dependent on current state of DC: ERROR_INVALID_HANDLE|ERROR_INVALID_STATE;
		HBitmap   Detach  (void)      ;             // detaches from encapsulated bitmap descriptor;
		err_code  Reset   (void)      ;             // clears all variables|no destroying bitmap handle; used in const|detach;

	public: // bitmap attributes and other;
		_pc_byte  Bits    (void) const;             // gets the pointer to bitmap data; (ro)
		_byte*    Bits    (void)      ;             // gets the pointer to bitmap data; (rw)
		TError&   Error   (void) const;
		HBitmap   Handle  (void) const;             // gets a bitmap handle if success, otherwise returns NULL;
		bool      Is      (void) const;             // checks a validity of the encapsulated bitmap descriptor;
		t_size    Size    (void) const;             // returns a size of bitmap;
#if defined(_DEBUG)
		CString   Print   (const e_print = e_print::e_all) const;
#endif
	public:
		CDibSection& operator = (const CDibSection&);
		CDibSection& operator = (CDibSection&&) = delete;
		
	public:
		operator  HBitmap (void) const;             // operator overloading, does the same as GetHandle_Safe()

	private :
		HBitmap   m_handle;     // encapsulated bitmap descriptor;
		PBYTE     m_pData ;     // a pointer to bitmap bits;
		SIZE      m_size  ;     // bitmap size;
		CError    m_error ;
	};
}}}

#endif/*_UIX_BITMAP_H_INCLUDED*/