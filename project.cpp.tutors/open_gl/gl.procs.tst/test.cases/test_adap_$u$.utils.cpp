/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 12:59:54.484, UTC+4, Batumi, Friday;
	This is OpenGL version 1.1 GLU related procedures' wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$u$.utils.h"

using namespace ::test::open_gl::utils::ver_1_1;

#pragma region cls::c_perspect{}

/* query: gluperspective function in opengl how to use example c++ (to Google AI);
	The gluPerspective function is used in OpenGL to create a perspective projection matrix,
	which simulates how we see the world: objects farther away appear smaller than objects closer to the camera.
	Usage example:
*/
#if (0)
	void handleResize(int w, int h) {
		// 1. Prevent division by zero
		if (h == 0) h = 1;
		float aspect = (float)w / (float)h;

		// 2. Set the Viewport to cover the new window Size
		glViewport(0, 0, w, h);

		// 3. Switch to Projection Matrix mode to set up the camera lens
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); // Reset any previous projections

		// 4. Set up perspective (45 or 60 degree FOV, aspect ratio, near clip 0.1, far clip 100.0)
		gluPerspective(45.0, aspect, 0.1, 100.0);

		// 5. Switch back to Modelview Matrix for drawing objects
		glMatrixMode(GL_MODELVIEW);
	}
	void display() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// Move the camera back 5 units so we can see the object
		// (By default, the camera is at 0,0,0 looking down -Z)
		glTranslatef(0.0f, 0.0f, -5.0f);

		// Draw a simple triangle
		glBegin(GL_TRIANGLES);
			glVertex3f( 0.0f,  1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f( 1.0f, -1.0f, 0.0f);
		glEnd();

		glutSwapBuffers();
	}
#endif

void c_perspect::Get (void) { /*TCtx_Toggle();*/ CTstPerspect(true).Get(); _out()(); }
void c_perspect::Set (void) {/* TCtx_Toggle();*/

	CTstMode     stk_mode(false);
	CTstMatrix   matrix(true);
	CTstPerspect perspect(true);
	CTstViewport viewport(true);

	const uint32_t v_p_h = 683, v_p_w = 683;
	/* cls::[CError]>>{code=0x139f;result=0x8007139f;desc='#__e_state: matrix stack is not in projection mode';context=CPerspect::Set()}
	   it is not so obvious: the CPerspect{} class has its own 'stack mode' attribute and this mode is checked before querying a matrix;
	*/
	// step#1: sets the viewport;
	if (__failed(viewport.Set_Params({0,0,v_p_w,v_p_h}))) { _out()(); return; }
	// step#2: sets matrix mode to projection; setting the mode loads identity matrix for clearing previously set projection;
	if (__failed(stk_mode.Set(e_stk_mode::e_project))) { _out()(); return; }

	// step#3: sets the projection matrix;
	s_pers_args args(60.0f, float(v_p_w)/float(v_p_h), 1.0f,  10.0f);

	if (__failed(perspect.Set(args))) {}
	else if (__failed(matrix.Get(e_mat_type::e_project))) {}

	// step#4: returns back the modelview mode;
	if (__failed(stk_mode.Set(e_stk_mode::e_modelview))){}

	_out()();
}

#pragma endregion
#pragma region cls::c_vsync{}

void c_vsync::Get (void) {

	int32_t n_intervals= 0;
	CTstVSync(true).Get(n_intervals); _out()();
}
void c_vsync::Set (void) {
	CTstVSync(true).Set(1); _out()();
}

#pragma endregion