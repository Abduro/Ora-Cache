#ifndef _EBO_TEST_$D$_IMG_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_IMG_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:34:11.369, UTC+4, Batumi, Thursday;
	This is Ebo Pack image wrappers' lib unit test declaration file; 
*/
#include "_log.h"

#include "uix.image.defs.h"
#include "uix.image.stream.h"
#include "uix.picture.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using namespace ebo::boo::test;

	class CTestCase {
	public:
		 CTestCase (void);
		 CTestCase (const CTestCase&) = delete; CTestCase (CTestCase&&) = delete;
		~CTestCase (void);

	public:
		TError&  Error (void) const ;

		bool  Is_valid (void) const ;

		_pc_sz   Get_path (void) const;
		err_code Set_path (void) ;       // reads the path from the registry to test folder of the images for currently selected theme;

		CString  Print (const e_print = e_print::e_all) const;

		err_code Open  (void) ;          // opens the parent/root registry key for test cases of the currently selected theme; 
		CString  Root  (void) const;     // returns the path to the root registry key of the custom/named themes;

		CString  Value (_pc_sz _p_name); // reads registry key value by name provided; if error the empty string is returned;

	protected:
		mutable
		CError   m_error;
		CString  m_path ;    // the path to test image location for the currently selected theme;
		CRegKey  m_root ;    // this is the root key for test cases, particular test case key is its child one;

	private:
		CTestCase& operator = (const CTestCase&) = delete; CTestCase& operator = (CTestCase&&) = delete;
	};

	__class (CTestCase_Root) {
	public:
		 CTestCase_Root (const bool _b_verb = false);
		~CTestCase_Root (void) = default;

	public:
		__ctor (_ctor);
		__method (Open);

	private:
		bool    m_b_verb;
		CTestCase m_root;
	};

}}}}

#pragma comment(lib, "sys.err.core_v15.lib")  // for using error object;
#pragma comment(lib, "ebo_test_$$$.lib")      // shared unit test library for common definition(s);
#pragma comment(lib, "image_v15.lib")         // this one must be tested by this unit test project;
#pragma comment(lib, "theme_v15.lib")         // the theme project is required for getting theme registry keys;

#endif/*_EBO_TEST_$D$_IMG_DEFS_H_INCLUDED*/