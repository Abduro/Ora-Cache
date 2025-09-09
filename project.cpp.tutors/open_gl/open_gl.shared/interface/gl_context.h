#ifndef _GL_CONTEXT_H_INCLUDED
#define _GL_CONTEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_error.h"
#include "gl_procs.h"

namespace ex_ui { namespace draw { namespace open_gl {

	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

namespace context {

	class CTarget {
	public:
		 CTarget (void);  CTarget (const HWND); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete;
		~CTarget (void);

		TError& Error (void) const; // this is the system error wrapper; that is the base for OpenGL error wrapper;
		err_code Free (void) ;      // releases the device context and sets error to '__e_not_inited', otherwise the error state of the failure;
		bool Is_valid (void) const; // validates device context handle;

		const HDC Get (void) const; // gets target window device context handle;
		err_code  Set (const HWND); // sets target window device context handle;

		CTarget& operator <<(const HWND);  // invokes this::Set(...); if the device context is already obtained, it will be released first;

	protected:
		mutable
		CError m_error;
		HDC  m_dc_src ; // this is the source device context from which the device renderer is created; it is auto-released on destroying this class instance;
		HWND m_target ; // the target window handle, it owns the source device context; this window handle is saved for releasing the HDC;
	};

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		 TErr_ex&  Error (void) const;   // this is the OpenGL error wrapper;
		 err_code Destroy(void) ;

		 bool   Is_valid (void) const;   // returns 'true' in case if device renderer context is not nullptr; no target object check;
		 HGLRC  Renderer (void) const;

		 err_code Set (const HWND _h_target);   // assines the target window handle, does*not* create the target, and checks the renderer handle first;

		 const
		 CTarget& Target (void) const;
		 CTarget& Target (void) ;        // releasing device context directly in target object will lead to errors on operations with the renderer;

		 CBase& operator <<(const HWND); // invokes this::Set(...); if the renderer context is already created, it will be destroyed first;

	private:
		 CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	protected:
		 mutable // for updating the error state in 'const' methods/properties;
		 CError_ex m_error ;
		 CTarget   m_target;  // this is the object containing the target window handle and its device context one;
		 HGLRC     m_drw_ctx; // rendering context that is compatible with regular GDI;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	// excerpt: ...creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc... ;
	// this is the class declartion of the context compatible with regular GDI context (HDC);
	class CDevice : public CBase {
	public:
		 CDevice (void); CDevice (const HWND _h_target);
		~CDevice (void);

		err_code Create (const HWND _h_target); // creates the rendering context that is compatible with input window device context;

		CDevice& operator <<(const HWND _h_target); // invokes this::Create(...); if the renderer context is already created, it will be destroyed first;
	};
}
	/* The main idea is composed by several steps:
		(1) creates fake window;
		(2) gets renderer context that is based on regular device context handle; *important* the rendering context must be set as current one;
		(3) querying pointers to the OpenGL functions that are required for creating real draw context of OpenGL version at least 3.0;
		(4) creates new window that is expected to be surface of the drawing;
		(5) using new window device context for setting pixel format by using OpenGL functions been loaded on the previous step (#3);
		(6) creating the OpenGL draw context and making it current;
	*/

	class CContext : public context::CBase { typedef context::CBase TBase;
	public:
		 CContext (void) ;  CContext (const CContext&) = delete; CContext (CContext&&) = delete;
		~CContext (void) ;

		 err_code Create (const HWND h_target, const uint32_t _u_gl_major_ver, const uint32_t _u_gl_miner_ver);
		 const
		 procs::CContext& Cache (void) const;
		 procs::CContext& Cache (void) ;

		 err_code Destroy(void);

	private:
		 CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;

		 procs::CContext  m_fn_cache;
	};
}}}

#endif/*_GL_CONTEXT_H_INCLUDED*/