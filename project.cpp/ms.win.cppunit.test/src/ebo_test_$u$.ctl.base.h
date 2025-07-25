#ifndef _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
#define _EBO_TEST_$U$_CTL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2025 at 11:59:19.796, UTC+4, Batumi, Sunday;
	This is Ebo Pack user control base wrapper lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"
#include "color.compl.predefs.h"
#include "uix.theme.h"       // this include requires the reference to the sys.shell project;

#include "ctl.base.defs.h"
#include "ctl.base.border.h"
#include "ctl.base.format.h"
#include "ctl.base.layout.h"
#include "ctl.base.props.h"
#include "ctl.base.pane.h"
#include "ctl.base.image.h"

namespace ebo { namespace boo { namespace test { namespace ctl {

namespace base {}

}}}}

#pragma comment(lib, "color_v15.lib")        // to colorize everything;
#pragma comment(lib, "ctl.base_v15.lib")     // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "ebo_test_$$t.case.draw.lib")  // test cases of draw helpers: loading image and fake window for example;
#pragma comment(lib, "ebo_test_$$t.case.theme.lib") // test cases for theme project of getting the path to image files;

#pragma comment(lib, "geometry.2d_v15.lib")  // this is for user control placement;
#pragma comment(lib, "image_v15.lib")        // image cache for user controls;

#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "sys.shell_v15.lib")    // this is system shell wrapper;

#pragma comment(lib, "theme_v15.lib")        // this is the color theme;
#pragma comment(lib, "win.popup_v15.lib")    // this is window popup lib that provides window message handlers;

#endif/*_EBO_TEST_$U$_CTL_BASE_H_INCLUDED*/