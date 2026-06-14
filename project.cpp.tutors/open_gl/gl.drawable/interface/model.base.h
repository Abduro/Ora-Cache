#ifndef _MODEL_BASE_H_INCLUDED
#define _MODEL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 08:40:08.947, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' model base interface declaration file;
*/
#include "drawable.defs.h"

namespace open_gl { namespace models { using namespace shared::defs;

	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;

	class CBase {
	public:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

		err_code Create (const HWND);
		err_code Destroy (void);
		TError&  Error (void) const;

		const
		c_mat4x4&  Mat_model (void) const;
		c_mat4x4&  Mat_model (void) ;

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError    m_error;
		c_mat4x4  m_model;
	};
}}

#endif/*_MODEL_BASE_H_INCLUDED*/