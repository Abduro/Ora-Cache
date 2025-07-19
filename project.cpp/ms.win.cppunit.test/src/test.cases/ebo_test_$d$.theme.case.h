#ifndef _EBO_TEST_$D$_THEME_CASE_H_INCLUDED
#define _EBO_TEST_$D$_THEME_CASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 23:04:42.206, UTC+4, Batumi, Friday;
	This is Ebo Pack custom color theme test cases' interface declaration file; 
*/
#include "_log.h"

namespace ebo { namespace boo { namespace test { namespace cases {

	using namespace ebo::boo::test;

	class CBase {
	public:
		class CRoot { // this class takes into account the currently selected custom/named theme;
		public:
			 CRoot (void); CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete;
			~CRoot (void);
		public:
			_pc_sz   Get (void) const;    // gets the path to the root folder of the theme test cases;
			err_code Set (void);          // sets, strickly speaking, reads the path to the theme test cases from the registry;

			TError&  Error (void) const;
			bool  Is_valid (void) const;  // returns 'true' in case if the path to the root folder of the theme test cases is already set, i.e. not empty;

		private:
			CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
			CError  m_error;
			CString m_path ;
		};
	public:
		 CBase (void);
		 CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);
	public:
		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		CRoot  m_root;
	};

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

#if (0)
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
#endif

	// the class below is inteanded to load status bar control images;
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

#endif/*_EBO_TEST_$D$_THEME_CASE_H_INCLUDED*/