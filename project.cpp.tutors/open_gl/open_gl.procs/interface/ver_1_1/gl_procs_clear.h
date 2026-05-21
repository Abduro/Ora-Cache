#ifndef _GL_PROCS_CLEAR_H_INCLUDED
#define _GL_PROCS_CLEAR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-May-2026 at 20:04:02.817, UTC+4, Batumi, Monday;
	This is OpenGL ver.1.1 glClear* function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace ver_1_1 {

	/* query: difference between clear and clean verbs ; (Google AI)
	clear means to remove items or obstructions to create space, while clean means to remove dirt, stains, or contaminants to make something hygienic or tidy;
	you clear the table by removing dishes, but you clean the table by washing it;
	*//* query: abbreviation for clearance ; (Google AI)
	The most common abbreviations for clearance are CLR (commonly used in aviation and general contexts) or CLNC (used specifically for clearance delivery in aviation);
	*/
	typedef ::std::array<float, 0x04u> f_clr_t; // elements from 0 to 3 index: red-green-blue-alpha;

	struct s_clear_args {
		f_clr_t _f_color; // color value for clear color buffers;
		int32_t _n_index; // stensil index;
		float   _f_value; // depth value;

		s_clear_args (const f_clr_t& _color = {0.0f, 0.0f, 0.0f, 0.0f}, const int32_t _index = 0, const float _depth_value = 0.0f ) :
			_f_color(_color), _n_index(_index), _f_value(_depth_value)
		{}
	};

	class CClear : public CBasic { typedef CBasic TBase;
	public:
		CClear (void); CClear (const CClear&) = delete; CClear (CClear&&) = delete; ~CClear (void) = default;

		err_code All (const s_clear_args&);           // clears color buffers, depth buffer and stencil by given values;

		err_code Color (const f_clr_t _clr_value);    // specifies clear values for the color buffers; it must to go before glClear();
		err_code Depth (const float _f_value);        // specifies the clear value for the depth buffer;

		err_code Stencil (const int32_t _n_index);    // specifies the clear value for the stencil buffer ;

	private:
		CClear& operator = (const CClear&) = delete; CClear& operator = (CClear&&) = delete;
	};
}}}

#endif/*_GL_PROCS_CLEAR_H_INCLUDED*/