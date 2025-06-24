#ifndef _EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 07:46:18.638, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI text output classes' unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test {

namespace text { namespace format {

	using TAlign_H = ex_ui::draw::text::format::CAlign_Horz;
	using TAlign_V = ex_ui::draw::text::format::CAlign_Vert;
	using TAlign   = ex_ui::draw::text::format::CAlign;

	using THorz_Flags = TAlign_H::e_value;
	using TVert_Flags = TAlign_V::e_value;

	__class(CAlign_H){
	public:
		 CAlign_H (const bool _b_verb = false);
		~CAlign_H (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
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
		__method (Set);
	
	private:
		bool     m_b_verb ;
		TAlign_V m_align_v;
	};

	__class(CAlign){
	public:
		 CAlign (const bool _b_verb = false);
		~CAlign (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
	private:
		bool   m_b_verb;
		TAlign m_align ;
	};

	using TCutter = ex_ui::draw::text::format::CCutter;

	__class(CCutter){
	public:
		 CCutter (const bool _b_verb = false);
		~CCutter (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
	private:
		bool    m_b_verb;
		TCutter m_cutter;
	};

	using TModifier = ex_ui::draw::text::format::CModifier;

	__class(CModifier){
	public:
		 CModifier (const bool _b_verb = false);
		~CModifier (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
	private:
		bool      m_b_verb;
		TModifier m_modifier;
	};

	using TOptimizer = ex_ui::draw::text::format::COptimizer;

	__class(COptimizer){
	public:
		 COptimizer (const bool _b_verb = false);
		~COptimizer (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
	private:
		bool       m_b_verb;
		TOptimizer m_optimazer;
	};

	using TFormat = ex_ui::draw::text::format::CFormat;

	__class(CFormat){
	public:
		 CFormat (const bool _b_verb = false);
		~CFormat (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
	private:
		bool    m_b_verb;
		TFormat m_format;
	};
}}

namespace text { namespace output {

	using TAlign_H = ex_ui::draw::text::output::CAlign_Horz;
	using TAlign_V = ex_ui::draw::text::output::CAlign_Vert;
	using TAlign   = ex_ui::draw::text::output::CAlign;

	using THorz_Flags = TAlign_H::e_value;
	using TVert_Flags = TAlign_V::e_value;

	__class(CAlign_H){
	public:
		 CAlign_H (const bool _b_verb = false);
		~CAlign_H (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);
	
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
		__method (Change);  // gets and sets alignment flags, no interacting with target device context;
		__method (GetFrom); // gets the flags of the text alignment from the real device context;
		__method (SetTo);   // sets the flags of the text alignment to the real device context;
	
	private:
		bool   m_b_verb;
		TAlign m_align ;
	};

}}

}}}

#endif/*_EBO_TEST_$D$_ZBUF_TEXT_H_INCLUDED*/