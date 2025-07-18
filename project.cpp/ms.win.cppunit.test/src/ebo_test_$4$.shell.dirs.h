#ifndef _EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED
#define _EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:16:48.791, UTC+4, Batumi, Friday;
	This is Ebo pack system shell generic folder wrapper library unit test declaration file; 
*/
#include "ebo_test_$4$.shell.h"

namespace ebo { namespace boo { namespace test { namespace shell {

	using TFolder = shared::user_32::ntfs::CFolder;

	__class (CFolder) {
	public:
		 CFolder (const bool _b_verb = false);
		~CFolder (void) = default;

	public:
		__ctor (_ctor);
		__method (EnumItems);

	private:
		bool     m_b_verb;
		TFolder  m_folder;
	};

	// the class below is base test case for finding path to test images; ToDo: this test case must be shard between different unit test projects;
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
	// the class below is inteanded to load status bar control images; ToDo: this test case must be shard between different unit test projects;
	class CTestCase_0 {
	public:
		enum e_images : uint32_t {
		     e_no_0 = 0,
		     e_no_1 = 1,
		};
	public:
		 CTestCase_0 (void);
		~CTestCase_0 (void) = default;

	TError&   Error  (void) const;

	CString   Get_path (const e_images) const; // returns the path to the image file; in case of error the empty string is returned;
	err_code  Set_path (void) ;                // composes the path specific for images of the status bar control;

	private:
		mutable
		CError m_error;
		CString m_folder; // this is the path to images' folder;
	};
}}}}

#endif/*_EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED*/