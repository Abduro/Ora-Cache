#ifndef _EBO_TEST_$D$_ZBUF_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 13:12:52.885, UTC+4, Batumi, Wednesday;
	This is Ebo Pack WinAPI GDI in-memory draw renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"

#include "uix.gdi.defs.h"
#include "uix.gdi.blend.h"
#include "uix.gdi.object.h"
#include "uix.gdi.shade.h"
#include "uix.gdi.text.h"
#include "uix.gdi.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	// https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference ;
	// https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp ;

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	using CWindow = ::ATL::CWindow;
	// this is the same class of message-only window that is taken from the renderer test cases' project; copy-paste is okay for now;
	// this fake window class is necessary to get the pseudo device context, otherwise some test cases cannot be passed;
	class CFake_Wnd : public ::ATL::CWindowImpl<CFake_Wnd> { typedef ::ATL::CWindowImpl<CFake_Wnd> TBase;
	public:
		  CFake_Wnd (const bool _b_verb = false); CFake_Wnd (const CFake_Wnd&) = delete; CFake_Wnd (CFake_Wnd&&) = delete;
		 ~CFake_Wnd (void);

	public:
		DECLARE_EMPTY_MSG_MAP();
		const
		HDC&     Ctx   (void) const;
		TError&  Error (void) const;

		operator const HDC& (void) const;

	private:
		CFake_Wnd& operator = (const CFake_Wnd&) = delete;
		CFake_Wnd& operator = (CFake_Wnd&&) = delete;

	private:
		bool    m_verb ;
		CError  m_error;
		HDC     m_h_dc ;
	};

	using TMode = ex_ui::draw::memory::CMode;

	__class(CMode){
	public:
		 CMode (const bool _b_verb = false);
		~CMode (void) = default;

	public:
		__ctor (_ctor);
		__method (Get);
		__method (Set);

	private:
		bool m_b_verb;
		TMode  m_mode;
	};

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "gdi.zbuf_v15.lib")     // this one must be tested by this unit test project;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;

#endif/*_EBO_TEST_$D$_ZBUF_H_INCLUDED*/