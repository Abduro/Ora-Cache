/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:56:20.572, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface implementation file; 
*/
#include "gl_px_format_arb.h"
#include "gl_context.h"
#include "gl_procs_ctx.h"

using namespace open_gl;
using namespace open_gl::arb;
using namespace open_gl::arb::format;

#pragma region cls::CPxFormat{}

static _pc_sz p_err_fmt_not_init = _T("#__e_state: pixel format is not inited");

CPxFormat::CPxFormat (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_fmt_not_init; }

TError& CPxFormat::Error (void) const { return this->m_error; }

err_code CPxFormat::Find  (const format::s_bits_ex& _bits) {
	_bits;
	this->m_error <<__METHOD__<<__s_ok;

	uint32_t u_index = 0;

	win_api::CPxFormat px_format; px_format << this->m_hdc;

	if (__failed(px_format.Find(_bits(), u_index))) {
		return this->m_error = px_format.Error();
	}

	// chooses the pixel format for ARB extension;
	CAtt_set_pixels pxl_atts(_bits); // no error check for this time yet;

	uint32_t n_count = 0;
	int32_t p_formats = 0;

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ; this file contains the function description;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ; << there is the example of how to use the function;

	const int32_t n_result = ::__get_ctx_procs().ChoosePxFormatArb(
		this->m_hdc, pxl_atts.IAtt_Get_Int_Ptr(), nullptr, 1, &p_formats, &n_count
	);

	bool b_can_go_ahead = false;

	if (0 == n_result) { // the failure has occurred: the format cannot be chosen for creating the context;
		if (__get_ctx_procs().Error()) { // checks for failure of loading the function pointer;
			this->m_error = __get_ctx_procs().Error();
		}
		else 
			this->m_error <<(err_code)TErrCodes::eData::eNotFound = _T("#__e_not_found: the requested pixel format is not found");
		__trace_err_ex_2(this->Error());
	}
	else if (nullptr != &p_formats && true == !!n_count) { b_can_go_ahead = true; }
	else { b_can_go_ahead = true; }

	if (false == b_can_go_ahead)
		return this->Error();

	return this->Error();
}

CPxFormat& CPxFormat::operator <<(const HDC& _hdc) { this->m_hdc = _hdc; return *this; }

#pragma endregion