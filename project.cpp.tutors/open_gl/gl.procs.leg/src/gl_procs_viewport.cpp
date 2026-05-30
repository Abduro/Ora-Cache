/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2026 at 17:45:24.752, UTC+4, Batumi, Saturday;
	This is OpenGL v.1.1 viewport related function set wrapper interface implementation file;
*/
#include "gl_procs_viewport.h"

namespace open_gl { namespace procs { namespace ver_1_1 {}}}

using namespace open_gl::procs;
using namespace open_gl::procs::ver_1_1;

#pragma region cls::CViewport{}

CViewport::CViewport (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height}, m_offset{0} { TBase::m_error >>__CLASS__; }
const
t_size_u& CViewport::Get (void) const { return this->m_size; }

err_code  CViewport::Get_Params (i_set_4& _params, CError& _error) {
	_params; _error;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
	CParam param;
	_params.fill(0);

	if (__failed(param.Get_ptr(GL_VIEWPORT, _params.data())))
		_error = param.Error();

	return _error;
}

float   CViewport::Get_X (const int32_t _n_x) const {
	_n_x;
	if (0 == this->Get().cx) // the division by zero is not defined;
		return 0.0f;
	// https://en.wikipedia.org/wiki/Division_(mathematics) ; >> Dividend / Divisor = Quotient; (Remainder) : left amount;
#if (1)
	const float f_divisor = (float)this->Get().cx;
	return 2.0f * (float)_n_x/f_divisor - 1.0f;
#else
	return 2.0f * ((float)_n_x + 0.5f)/(float)(this->Get().cx / 2) - 1.0f
#endif
}

float   CViewport::Get_Y (const int32_t _n_y) const {
	_n_y;
	if (0 == this->Get().cy) // the division by zero is not defined;
		return 0.0f;
#if (1)
	return 1.0f - 2.0f * (float)_n_y/(float)this->Get().cy;
#else
	return 1.0f - ((float)_n_y + 0.5f)/(float)(this->Get().cy / 2);
#endif
}

// https://stackoverflow.com/questions/8491247/c-opengl-convert-world-coords-to-screen2d-coords#comment43751183_8493759 ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport#remarks ;
int32_t CViewport::Get_X (const float _f_x) const {
	_f_x;
	const int32_t n_x = int32_t((_f_x + 1.0f) / 2.0f) * this->Get().cx + this->m_offset.x;
	return n_x;
}

int32_t CViewport::Get_Y (const float _f_y) const {
	_f_y;
	const int32_t n_y = int32_t((1.0f - _f_y) / 2.0f) * this->Get().cy + this->m_offset.y;
	return n_y;
}

bool CViewport::Is_valid (void) const {
	return CViewport::Is_valid(this->m_size, TBase::m_error);
}
bool CViewport::Is_valid (const t_size_u& _u_size, CError& _err) {
	_u_size; _err;
	if (0 == _u_size.cx || 0 == _u_size.cy) {
		_err <<__METHOD__<<__e_inv_arg = TString().Format(_T("#__e_inv_size: cx=0x%04x, cy=0x%04x"), _u_size.cx, _u_size.cy);
		return false;
	}
	else return true;
}

err_code  CViewport::ToPos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, f_set_3& _pos_out, CError& _err) {
	_u_size; _in_x; _in_y; _pos_out; _err;
	if (CViewport::Is_valid(_u_size, _err) == false)
		return _err;
	// ToDo: this requires testing to find out which expression works faster;
#if (1)
	// https://discourse.glfw.org/t/converting-between-screen-coordinates-and-pixels/1841/2 ; thanks @dougbinks for good answer;
	_pos_out[0] = 2.0f * (float)_in_x/(float)_u_size.cx - 1.0f; // x;
	_pos_out[1] = 1.0f - 2.0f * (float)_in_y/(float)_u_size.cy; // y;
	_pos_out[2] = 0.0f; // z;
#else
	// https://stackoverflow.com/questions/40068191/opengl-screen-to-world-coordinates-conversion ;
	_pos_out = {2.0f * ((float)_in_x + 0.5f)/(float)(_u_size.cx / 2) - 1.0f, 1.0f - ((float)_in_y + 0.5f)/(float)(_u_size.cy / 2), 0.0f};
#endif
	return _err;
}

#pragma endregion