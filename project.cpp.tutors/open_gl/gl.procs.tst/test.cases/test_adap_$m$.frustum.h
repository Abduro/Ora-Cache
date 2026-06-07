#ifndef _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
#define _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:16:48.217, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum unit test adapter interface declaration file; 
*/
#include "test_case_$m$.frustum.h"
#include "test_case_$m$.matrix.h"
#include "test_case_$m$.stack.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1, i.e. for testing matrix mode and matrix stack;
	Frustum function is available in all versions of the OpenGL;
*/
namespace test { namespace open_gl { namespace frustum {

	using namespace test::open_gl::ver_1_1;
	
	__class (c_frustum) {
	public:
		c_frustum (void) = default; c_frustum (const c_frustum&) = delete; c_frustum (c_frustum&&) = delete; ~c_frustum (void) = default;

#if (0) // the below methods is not ready for testing yet;
		__method (Get_perspect); // calculates perspective projection matrix; (this is manual calculation);
		__method (Set_aspect);   // sets pre-defined surface window size;
		__method (Set_defaults); // gets default configuration values;
#endif
		/* the query to Google AI: should be used glPushMatrix and glPopMatrix when call glFrustum OpenGL?
		   https://stackoverflow.com/questions/7031842/how-do-glpushmatrix-and-glpopmatrix-keep-the-scene-the-same ;
		   Thus calling those procedures is required if transformation of the stack top matrix is used;

		   The following steps are required:
		   step #0: sets current rendering context; !required!
		   step #1: sets the matrix mode to 'projection';
		   step #2: resets the matrix to identity;
		   step #3: defines the frustum volume; << this is the step being tested!
		   step #4: if setting frustum succeeded queries the changed matrix back;
		   step #5: restores 'modelview' mode to draw objects;
		*/
		__method (Set);  // sets frustum matrix for specific clip area and planes;
	private:
		c_frustum& operator = (const c_frustum&) = delete; c_frustum& operator = (c_frustum&&) = delete;
	};
}}}

#endif/*_TEST_ADAP_$M$_FRUSTUM_H_INCLUDED*/