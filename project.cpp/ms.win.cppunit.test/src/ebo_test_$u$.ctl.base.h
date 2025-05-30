#ifndef _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
#define _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2025 at 11:59:19.796, UTC+4, Batumi, Sunday;
	This is Ebo Pack user control base wrapper lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "ctl.base.defs.h"
#include "ctl.base.lyt.h"
#include "ctl.base.border.h"

namespace ebo { namespace boo { namespace test { namespace ctl { namespace base {

	using TMargin = ex_ui::controls::layout::CMargin;

	__class (CMargin) {
	public:
		 CMargin (const bool _b_verb = false);
		~CMargin (void) = default;

	public:
		__method (_ctor);

	private:
		bool m_b_verb;
		TMargin m_margin;
	};

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

}}}}}

#pragma comment(lib, "color_v15.lib")        // to colorize everything;
#pragma comment(lib, "ctl.base_v15.lib")     // this one must be tested by this unit test project;
#pragma comment(lib, "geometry.2d_v15.lib")  // this is for user control placement;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "win.popup_v15.lib")    // this is window popup lib that provides window message handlers;

#endif/*_EBO_TEST_$U$_CTL_BASE_H_INCLUDED*/