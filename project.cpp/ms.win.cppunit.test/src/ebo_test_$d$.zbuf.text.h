#ifndef _EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 07:46:18.638, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI text output classes' unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

namespace text{ namespace vertical {

	using TAlign_H = ex_ui::draw::text::output::vertical::CAlign_Horz;
	using TAlign_V = ex_ui::draw::text::output::vertical::CAlign_Vert;
	using TAlign   = ex_ui::draw::text::output::vertical::CAlign;

	using THorz_Flags = TAlign_H::e_value;
	using TVert_Flags = TAlign_V::e_value;

	__class(CAlign_H){
	public:
		 CAlign_H (const bool _b_verb = false);
		~CAlign_H (void) = default;

	public:
		__ctor (_ctor);
	
	private:
		bool     m_b_verb ;
		TAlign_H m_align_h;
	};

	__class(CAlign_V){
	public:
		 CAlign_V (const bool _b_verb = false);
		~CAlign_V (void) = default;

	public:
		__ctor (_ctor);
	
	private:
		bool     m_b_verb ;
		TAlign_V m_align_v;
	};

	using TFnt_Sel = ex_ui::draw::memory::CFont_Selector;

	__class(CAlign){
	public:
		 CAlign (const bool _b_verb = false);
		~CAlign (void) = default;

	public:
		__ctor (_ctor);
		__method (Get);
		__method (Set);
	
	private:
		bool   m_b_verb;
		TAlign m_align ;
	};

}}

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED*/