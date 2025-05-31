#ifndef _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
#define _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2025 at 11:59:19.796, UTC+4, Batumi, Sunday;
	This is Ebo Pack user control base wrapper lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "ctl.base.defs.h"
#include "ctl.base.border.h"
#include "ctl.base.layout.h"

namespace ebo { namespace boo { namespace test { namespace ctl { namespace base {

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

}}}}}

#pragma comment(lib, "color_v15.lib")        // to colorize everything;
#pragma comment(lib, "ctl.base_v15.lib")     // this one must be tested by this unit test project;
#pragma comment(lib, "geometry.2d_v15.lib")  // this is for user control placement;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "win.popup_v15.lib")    // this is window popup lib that provides window message handlers;

#endif/*_EBO_TEST_$U$_CTL_BASE_H_INCLUDED*/