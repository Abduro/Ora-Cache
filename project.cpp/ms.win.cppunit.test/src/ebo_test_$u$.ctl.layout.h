#ifndef _EBO_TEST_$U$_CTL_LAYOUT_H_INCLUDED
#define _EBO_TEST_$U$_CTL_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2025 at 09:32:14.342, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base layout unit test interface declaration file; 
*/
#include "ebo_test_$u$.ctl.base.h"

namespace ebo { namespace boo { namespace test { namespace ctl {

namespace layout {

	using TBorder = ex_ui::controls::borders::COne;

	__class (CBorder) {
	public:
		 CBorder (const bool _b_verb = false);
		~CBorder (void) = default;

	public:
		__method (_ctor);

	private:
		bool m_b_verb;
		TBorder m_border;
	};

	using TBorders = ex_ui::controls::borders::CSet;

	__class (CBorders) {
	public:
		 CBorders (const bool _b_verb = false);
		~CBorders (void) = default;

	public:
		__method (_ctor);
		__method (Modify);

	private:
		bool m_b_verb;
		TBorders m_bdrset;
	};

	using TGap = ex_ui::controls::layout::CGap;

	__class (CGap) {
	public:
		 CGap (const bool _b_verb = false);
		~CGap (void) = default;

	public:
		__ctor(_ctor);

	private:
		bool m_b_verb;
		TGap m_gap;
	};

	using TGapSet = ex_ui::controls::layout::CGaps_of_rect;

	__class (CGaps_of_rect) {
	public:
		 CGaps_of_rect (const bool _b_verb = false);
		~CGaps_of_rect (void) = default;

	public:
		__ctor (_ctor);
		__method (ApplyMargins);
		__method (ApplyPadding);

	private:
		bool    m_b_verb;
		TGapSet m_gaps;
	};
}
}}}}
#endif/*_EBO_TEST_$U$_CTL_LAYOUT_H_INCLUDED*/