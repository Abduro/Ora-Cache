#ifndef _EBO_TEST_$D$_DRAW_CASE_H_INCLUDED
#define _EBO_TEST_$D$_DRAW_CASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jul-2025 at 19:28:25.012, UTC+4, Batumi, Thursday;
	This is Ebo Pack custom draw helpers' interface declaration file; 
*/
#include "_log.h"

namespace ebo { namespace boo { namespace test { namespace cases {

	using namespace ebo::boo::test;

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

}}}}

#endif/*_EBO_TEST_$D$_DRAW_CASE_H_INCLUDED*/