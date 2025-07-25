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
		__method (Create); // creates the image list of specified size of the image frame (24x24(px));
		__method (Draw);   // loads the specified image and tries to draw the image to device context of the fake window;
		__method (Set);    // loads the specified image from the file and adds it to the image list;

	private:
		bool  m_b_verb;
		TImages m_images;
	};
}}}}
#endif/*_EBO_TEST_$U$_CTL_IMAGE_H_INCLUDED*/