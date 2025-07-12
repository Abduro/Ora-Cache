#ifndef _EBO_TEST_$D$_PICTURE_H_INCLUDED
#define _EBO_TEST_$D$_PICTURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:41:01.085, UTC+4, Batumi, Thursday;
	This is Ebo Pack component object picture wrapper unit test declaration file; 
*/
#include "ebo_test_$d$.image.defs.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using TPicture = ex_ui::draw::images::CPicture;

	__class (CPicture) {
	public:
		 CPicture (const bool _b_verb = false);
		~CPicture (void) = default;

	public:
		__ctor (_ctor);
		__method (Load_file);

	private:
		bool  m_b_verb;
		TPicture m_picture;
	};

	// the class below is inteanded to load status bar control images;
	class CTestCase_0 {
	public:
		enum e_images : uint32_t {
		     e_no_0 = 0,
		     e_no_1,
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

#endif/*_EBO_TEST_$D$_PICTURE_H_INCLUDED*/