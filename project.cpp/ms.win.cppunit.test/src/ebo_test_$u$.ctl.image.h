#ifndef _EBO_TEST_$U$_CTL_IMAGE_H_INCLUDED
#define _EBO_TEST_$U$_CTL_IMAGE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jul-2025 at 12:16:09.873, UTC+4, Batumi, Thursday;
	This is Ebo Pack user control image list unit test interface declaration file; 
*/
#include "ebo_test_$u$.ctl.base.h"

namespace ebo { namespace boo { namespace test { namespace ctl {

	using TImages = ex_ui::controls::CImages;

	__class (CImages) {
	public:
		 CImages (const bool _b_verb = false);
		~CImages (void) = default;

	public:
		__method (Set);

	private:
		bool  m_b_verb;
		TImages m_images;
	};
}}}}
#endif/*_EBO_TEST_$U$_CTL_IMAGE_H_INCLUDED*/