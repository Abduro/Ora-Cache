#ifndef _GL_CTX_BASE_H_INCLUDED
#define _GL_CTX_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 21:32:08.562, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' base draw context interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace context { using namespace shared::defs;

	class CTarget {
	public:
		 CTarget (void);  CTarget (const HWND); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete;
		~CTarget (void);

		TError& Error (void) const; // this is the system error wrapper; that is the base for OpenGL error wrapper;
		err_code Free (void) ;      // releases the device context and sets error to '__e_not_inited', otherwise the error state of the failure;
		bool Is_valid (void) const; // validates device context handle;

		const HDC Get (void) const; // gets target window device context handle;
		err_code  Set (const HWND); // sets target window device context handle;
		// it would be better to name the following property as 'Caller' instead of 'Source';
		_pc_sz Source (void) const; // returns the window class name that is creator of the device context, i.e. the source;
		bool   Source (_pc_sz _p_cls_name); // sets the source class name; returns 'true' in case of source class name change;

		CString& Source (void);
		CTarget& operator <<(const HWND);   // invokes this::Set(...); if the device context is already obtained, it will be released first;

		operator const HWND (void) const;

	protected:
		mutable
		CError  m_error;
		CString m_cls_src;
		HDC  m_dc_src ; // this is the source device context from which the device renderer is created; it is auto-released on destroying this class instance;
		HWND m_target ; // the target window handle, it owns the source device context; this window handle is saved for releasing the HDC;
	};

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		err_code Destroy(void) ;
		TError&  Error  (void) const;

		bool   Is_valid (void) const;   // returns 'true' in case if device renderer context is not nullptr; no target object check;
		HGLRC  Renderer (void) const;

		err_code Set (const HWND _h_target);   // assines the target window handle, does*not* create the target, and checks the renderer handle first;

		const
		CTarget& Target (void) const;
		CTarget& Target (void) ;        // releasing device context directly in target object will lead to errors on operations with the renderer;

		CBase& operator <<(const HWND); // invokes this::Set(...); if the renderer context is already created, it will be destroyed first;

	protected:
		mutable // for updating the error state in 'const' methods/properties;
		CError   m_error ;
		CTarget  m_target;  // this is the object containing the target window handle and its device context one;
		HGLRC    m_drw_ctx; // rendering context that is compatible with regular GDI;
	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	};

}}}}

#endif/*_GL_CTX_BASE_H_INCLUDED*/