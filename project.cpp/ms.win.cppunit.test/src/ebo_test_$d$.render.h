#ifndef _EBO_TEST_$D$_RENDER_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:40:50.58, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.device.h"
#include "render.base.h"

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "render_v15.lib")       // this one must be tested by this unit test project;

#endif/*_EBO_TEST_$D$_RENDER_H_INCLUDED*/