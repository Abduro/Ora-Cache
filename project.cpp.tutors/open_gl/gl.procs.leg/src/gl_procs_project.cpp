/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 09:24:11.246, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 projection related function set wrapper interface implementation file;
*/
#include "gl_procs_project.h"

using namespace ::open_gl::procs::projection::ver_1_1;

#pragma region str::s_pers_args{}

s_pers_args::s_pers_args (void) : _fov_y(0.0f), _aspect(0.0f), _near(0.0f), _far(0.0f) {}
s_pers_args::s_pers_args (const float _f_fov_y, const float _f_aspect, const float _f_near, const float _f_far)
			: _fov_y(_f_fov_y), _aspect(_f_aspect), _near(_f_near), _far(_f_far) {
}

CString s_pers_args::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("vert fov = %.2f (deg); aspect = %.7f; near = %.7f; far = %.7f;");
	CString cs_out; cs_out.Format(pc_sz_pat, this->_fov_y, this->_aspect, this->_near, this->_far);
	return  cs_out;
}

#pragma endregion
#pragma region cls::CPerspect{}

CPerspect::CPerspect (void) : TBase() { TBase::m_error >>__CLASS__; }

#define gl_project_mat GL_PROJECTION_MATRIX
static _pc_sz p_err_inv_enum_el = _T("#__e_inv_arg: enum element (%04u) is not accepted");
static _pc_sz p_err_proj_mode = _T("#__e_state: matrix stack is not in projection mode");
const
f_seq_4x4& CPerspect::Ref (void) const { return this->m_pers; }

err_code  CPerspect::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CMatrix matrix;
	if (__failed(matrix.Get(e_mat_type::e_project, this->m_pers)))
		TBase::m_error = matrix.Error();

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/gluperspective ;
err_code  CPerspect::Set (const float _fov_y, const float _f_aspect, const float _f_near, const float _f_far) {
	_fov_y; _f_aspect; _f_near; _f_far;
	TBase::m_error <<__METHOD__<<__s_ok;
	/* query: what result is expected when gluPerspective is called but GL_PROJECTION mode is not set in opengl (to Google AI);
	when gluPerspective is called while GL_MODELVIEW (or another mode) is active instead of GL_PROJECTION,
	the perspective matrix is multiplied onto the active model-view stack instead. This causes several unintended visual issues:
	(1) Distorted, inverted, or Offset geometry: 3D models will undergo camera-like transformations while they are being modeled, severely warping their scale and position;
	(2) Camera tracking issues: any subsequent operations (like glTranslate or glRotate) will treat the perspective matrix as if it were a regular model transformation,
	    breaking the standard rendering pipeline.
	*/
	if (false == this->Mode().Is_project())
		return TBase::m_error <<(err_code)TErrCodes::eExecute::eState = p_err_proj_mode;

	CMatrix matrix;
	if (__failed(matrix.To_self())) // resets any previous projections;
		return TBase::m_error = matrix.Error();

	::gluPerspective(var(_f_aspect), var(_f_aspect), var(_f_near), var(_f_far));
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	if (u_err_code) {
		TBase::m_error = TString(gluErrorStringWIN(u_err_code));
	}

	return TBase::Error();
}

err_code  CPerspect::Set (const s_pers_args& _args) {
	return this->Set(_args._fov_y, _args._aspect, _args._near, _args._far);
}
const
f_seq_4x4& CPerspect::operator <<(const s_pers_args& _args) {
	_args;
	if (__succeeded(this->Set(_args)))
		this->Get();

	return this->Ref();
}

const
CMode& CPerspect::Mode (void) const { return this->m_mode; }
CMode& CPerspect::Mode (void)       { return this->m_mode; }

#pragma endregion
#pragma region cls::CProject{}

CProject::CProject (void) : TBase() { TBase::m_error >>__CLASS__; }

/* query: gluperspective function in opengl how to use example c++ (to Google AI);
	The gluPerspective function is used in OpenGL to create a perspective projection matrix,
	which simulates how we see the world: objects farther away appear smaller than objects closer to the camera.
	Usage example:
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
*/

#pragma endregion