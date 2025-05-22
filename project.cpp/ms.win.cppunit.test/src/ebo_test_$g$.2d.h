#ifndef _EBO_TEST_$G$_2D_H_INCLUDED
#define _EBO_TEST_$G$_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 09:18:10.448, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry lib unit test common definition file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "2d.base.h"
#include "2d.base.line.h"
#include "2d.rotate.h"
#include "2d.shape.h"
#include "2d.shape.rect.h"

namespace ebo { namespace boo { namespace test { namespace _2D {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	using TMarker = geometry::_2D::CMarker;

	__class(CMarker) {
	public:
		 CMarker (const bool _b_verb = false);
		~CMarker (void) = default;

	public:
		__ctor (_ctor);
		__method (Operators);

	private:
		bool m_b_verb;
	};

	using TRotate = geometry::_2D::CRotate;
	using TLine   = geometry::_2D::base::CLine;
	using TRect   = geometry::_2D::shapes::COblong;
	using TShape  = geometry::_2D::shapes::CShape;

	__class(CRotate) {
	public:
		 CRotate (const bool _b_verb = false);
		~CRotate (void) = default;

	public:
		__ctor (_ctor);
		__method (Angle);
		__method (ApplyTo); // this is the method for testing the applying the rotation class to different shapes and a line;
		__method (DoIt);    // the is the base test case of appying rotation class to one point;

	private:
		bool m_b_verb;
		TRotate m_rotate;
	};

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "color_v15.lib")        // color management library;
#pragma comment(lib, "geometry.2d_v15.lib")  // this one must be tested by this unit test project;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the base;

#endif/*_EBO_TEST_$G$_2D_H_INCLUDED*/