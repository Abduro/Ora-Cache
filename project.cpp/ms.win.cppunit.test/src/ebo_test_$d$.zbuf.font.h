#ifndef _EBO_TEST_$D$_ZBUF_FONT_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_FONT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 23:43:09.114, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI generic fonts' unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	using TFond_Base =  ex_ui::draw::CFont_Dbg;

	__class(CFont_Dbg){
	public:
		 CFont_Dbg (const bool _b_verb = false);
		~CFont_Dbg (void) = default;

	public:
		__ctor (_ctor);
	
	private:
		bool     m_b_verb ;
		TFond_Base m_font ;
	};


	using TFont = ex_ui::draw::CFont;

	__class(CFont){
	public:
		 CFont (const bool _b_verb = false);
		~CFont (void) = default;

	public:
		__ctor (_ctor);
		__method (Create);
	
	private:
		bool  m_b_verb ;
		TFont m_font ;
	};

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_FONT_H_INCLUDED*/