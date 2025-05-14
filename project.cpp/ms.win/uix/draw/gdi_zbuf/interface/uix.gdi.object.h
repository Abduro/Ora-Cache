#ifndef _UIXDRAWGDIOBJECT_H_INCLUDED
#define _UIXDRAWGDIOBJECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Oct-2010 at 1:02:30am, GMT+3, Rostov-on-Don, Tuesday;
	This is Sfx Pack project shared UIX draw library GDI wrapper interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on on 7-Feb-2015 at 10:27:49pm, GMT+3, Taganrog, Saturday;
	Adopted to v15 on 28-May-2018 at 11:08:13p, UTC+7, Phuket, Rawai, Monday;
	Adopted to FakeGPS project on 19-Apr-2020 at 3:09:08a, UTC+7, Novosibirsk, Sunday;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace memory {

	using namespace ex_ui::draw::defs;

	// https://www.grammarly.com/blog/know-your-latin-i-e-vs-e-g/
	// *IMPORTANT*
	// all images are expected to have 32-bit-color format, otherwise an error is returned;
	// it is assumed a bitmap row of image pixels is rounded to 4 bytes value, that means a stride = 4-byte * bitmap width;
	// but sometimes implement code does not check of color-bitness and it may lead to an error of memory access; this is must be checked;

	// this class does not free/delete an object that is attached;
	class CBitmapInfo : public BITMAP { typedef BITMAP TBase;
	public:
		 CBitmapInfo (void);
		 CBitmapInfo (const CBitmapInfo&);
		 CBitmapInfo (const HBITMAP hBitmap, const UINT UID = ::GetTickCount());
		~CBitmapInfo (void);

	public:
		HRESULT    Attach (const HBITMAP); // attaches to bitmap handle provided and initializes base structure fields;
		HBITMAP    Detach (void);          // returns attached handle and resets itself;
		HRESULT    Reset  (void);          // zeros this class object attributes and base structure fields;

	public:
		const
		HBITMAP    Handle (void ) const;
		UINT       ID     (void ) const;
		bool       Is     (void ) const;
		BITMAPINFO Raw    (void ) const;
		HRESULT    Size   (SIZE&) const;

	public:
		CBitmapInfo& operator = (const CBitmapInfo&);
		CBitmapInfo& operator <<(const UINT UID);
		CBitmapInfo& operator <<(const HBITMAP );

	public:
		operator const HBITMAP  (void) const;
		operator const BITMAPINFO (void) const;

	public:
		static
		bool      IsValid(const HBITMAP);
	private:
		UINT       m_UID;      // identifier of this object;
		HBITMAP    m_handle;   // attached bitmap handle;
	};

	typedef const PBYTE  PCBYTE;
	// https://docs.microsoft.com/en-us/windows/win32/gdi/storing-an-image
	class CDibSection {
	public:
		 CDibSection (void);
		 CDibSection (const CDibSection&);  CDibSection (CDibSection&&) = delete;
		 CDibSection (const HDC, const SIZE&);
		~CDibSection (void);

	public: // bitmap life cycle;
		err_code  Create  (const HDC, const SIZE&); // creates new bitmap by applying input arguments; the previous data is destroyed if any;
		err_code  Destroy (void)      ;             // returned result is dependent on current state of DC: ERROR_INVALID_HANDLE|ERROR_INVALID_STATE;
		HBITMAP   Detach  (void)      ;             // detaches from encapsulated bitmap descriptor;
		err_code  Reset   (void)      ;             // clears all variables|no destroying bitmap handle; used in const|detach;

	public: // bitmap attributes and other;
		PCBYTE    Bits    (void) const;             // gets bitmap data;
		TError&   Error   (void) const;
		HBITMAP   Handle  (void) const;             // gets a bitmap handle if success, otherwise returns NULL;
		bool      Is      (void) const;             // checks a validity of the encapsulated bitmap descriptor;
		SIZE      Size    (void) const;             // returns a size of bitmap;

	public:
		CDibSection& operator = (const CDibSection&);
		CDibSection& operator = (CDibSection&&) = delete;
		
	public:
		operator  HBITMAP (void) const;             // operator overloading, does the same as GetHandle_Safe()

	private :
		HBITMAP   m_handle;     // encapsulated bitmap descriptor;
		PBYTE     m_pData ;     // a pointer to bitmap bits;
		SIZE      m_size  ;     // bitmap size;
		CError    m_error ;
	};
}}}

#endif/*_UIXDRAWGDIOBJECT_H_INCLUDED*/