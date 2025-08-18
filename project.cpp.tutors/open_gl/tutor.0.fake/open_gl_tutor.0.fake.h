#ifndef _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:16:27.485, UTC+4, Batumi, Monday;
	This is OpenGL tutorial of the creating fake content interface declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <cstdint>    // for declareing and/or defining data types such as: uint32_t for example;

#include <gl/gl.h>
#pragma comment(lib, "opengl32.lib")

#ifndef __e_not_inited
#define __e_not_inited OLE_E_BLANK
#endif

#ifndef __DwordToHresult
#define __DwordToHresult(_dword) HRESULT_FROM_WIN32(_dword)
#endif
#define __HresultToDword(_hres) (_hres & 0x0000FFFF)
#define __LastErrToHresult()   __DwordToHresult(::GetLastError())

#ifndef __s_ok
#define __s_ok S_OK
#endif

typedef LPCTSTR _pc_sz; // since Win32 there is neither 'long' nor 'near' pointer types;
typedef LPTSTR  _p_sz ;

// https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-on-windows-nt--windows-2000--and-windows-95-98 ; << old but still valid;

namespace ebo { namespace pack { namespace draw { namespace open_gl {  namespace fake {

	struct {
		int32_t err_code;
		_pc_sz  err_desc;
	} _error = {0, 0};

	class CWnd : public ::ATL::CWindowImpl<CWnd> { typedef ::ATL::CWindowImpl<CWnd> TWindow;
	public:
		 CWnd (void); CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void);

		 static
		 const uint32_t u_style = CS_DBLCLKS | CS_OWNDC; // cs_owndc is important for creating open_gl window content;

		 DECLARE_WND_CLASS_EX(_T("open_gl::fake::CWnd"), u_style, COLOR_ACTIVECAPTION);
		 DECLARE_EMPTY_MSG_MAP();

		 int32_t Err_code (void) const;
		 bool    Is_valid (void) const;

		 const
		 HDC&    Get_ctx  (void) const; // gets the reference to device context; read-only;

		 operator const HDC& (void) const;

	private:
		 CWnd& operator = (const CWnd&) = delete; CWnd& operator = (CWnd&&) = delete;

		 HDC     m_h_dc ;
		 int32_t m_err_code; // taking into account that hresult is defined as long data type, unsigned integer cannot be used;
		 HGLRC   m_h_render; // the render context;
	};

}}}}}

#endif/*_OPEN_GL_TUTOR_0_FAKE_H_INCLUDED*/