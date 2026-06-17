#ifndef _GL_PROCS_VIEWPORT_H_INCLUDED
#define _GL_PROCS_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2026 at 17:44:00.482, UTC+4, Batumi, Saturday;
	This is OpenGL v.1.1 viewport related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "gl_procs_params.h"

/*taking into account that glViewport() function is supported in OpenGL from ver 1.1 to 4.6, there is no need to use it in ::ver_1_1 namespace only;
  https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml >> supported versions of OpenGL;
  https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport << sets view port Size and position; (that is used in these tutorials)
  https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange << mapping of z values from normalized device coordinates to window coordinates;
*/
namespace open_gl { namespace procs {
namespace viewport {
	using namespace ::open_gl::procs::ver_1_1;
	/* i_set_4 << 0: x-Offset; 1: y-Offset; 2: width; 3: height;
	*/
	enum e_param_ndx : uint32_t {
		e_x_off = 0x0, e_y_off, e_width, e_height
	};

	struct i_values : public i_set_4 { typedef i_set_4 base_t;

		i_values (void) : base_t() {}
		i_values (const i_values& _src) : base_t() { *this = _src; }
		i_values (const t_point& _offset, const t_size_u& _size) {
			*this << _offset << _size;
		}
		i_values (const base_t& _src) : base_t() { (base_t&)*this = _src; }

		operator i_set_4& (void){ return (base_t&)*this; }

		operator t_point  (void) const { return {base_t::at(0), base_t::at(1)}; }
		t_point  Offset   (void) const { return {base_t::at(0), base_t::at(1)}; }
		t_size_u Size     (void) const { return t_size_u(base_t::at(2), base_t::at(3)); }

		i_values& operator = (const i_values& _src) { (base_t&)*this = (const base_t&)_src; return *this; }
		i_values& operator <<(const t_point& _offset) { base_t::at(0) = _offset.x; base_t::at(1) = _offset.y; return *this; }
		i_values& operator <<(const t_size_u& _size) { base_t::at(2) = _size.cx; base_t::at(3) = _size.cy; return *this; }

		const
		i_set_4& operator ()(void) const { return (i_set_4&)*this; }
		i_set_4& operator ()(void)       { return (i_set_4&)*this; }
	};

	class CParams : public CBasic { typedef CBasic TBase;
	public:
		CParams (void); CParams (const CParams&) = delete; CParams (CParams&&) = delete; ~CParams (void) = default;

		static
		err_code  Get (i_values&, CError&); // gets viewport params;
		err_code  Get (void);               // gets viewport params;
		static
		err_code  Get (t_point& _offset, t_size_u& _size, CError&);

		static
		err_code  Is_valid (const i_values&, CError&); // checks given param values;
		err_code  Is_valid (void);                     // checks internal value set;
		static
		err_code  Is_valid (const t_point & _offset, const t_size_u& _size, CError&);

		static
		err_code  Set (const i_values&, CError&); // sets input params to viewport;

		err_code  Set (const t_point & _offset, const t_size_u& _size, CError&);
		err_code  Set (const i_values&);          // sets input params to viewport; in case of success, internal values are updated by input ones;
		err_code  Set (void);          // sets viewport params by applying internal data set;
		const
		t_size_u& Size (void) const;   // gets the reference to viewport Size params; (ro);
		t_size_u& Size (void) ;        // gets the reference to viewport Size params; (rw);

		const
		i_values& Value (void) const;  // gets the reference to parameters' value array; (ro);
		i_values& Value (void) ;       // gets the reference to parameters' value array; (rw);

		static _pc_sz To_str (const i_values&);
		static _pc_sz To_str (const t_point& _offset, const t_size_u&);

		CParams& operator <<(const t_point& _offset);
		CParams& operator <<(const t_size_u& _size);

	private:
		CParams& operator = (const CParams&) = delete; CParams& operator = (CParams&&) = delete;
		i_values m_values;
	};

}
	using ::open_gl::procs::viewport::CParams;
	using namespace ::open_gl::procs::ver_1_1;

	class CViewport : public CBasic { typedef CBasic TBase;
	public:
		CViewport (const uint32_t _u_width = 0, const uint32_t _u_height = 0); CViewport (const CViewport&) = delete;
		CViewport (CViewport&&) = delete; ~CViewport (void) = default;
		const
		t_size_u& Get (void) const; // returns the reference to 'unsigned' Size structure; (ro);
		
		float   Get_X (const int32_t _n_x) const; // converts x-coord value from screen to normalized one;
		float   Get_Y (const int32_t _n_x) const; // converts y-coord value from screen to normalized one;

		int32_t Get_X (const float _f_x) const;   // converts x-normalized value to screen coordinate;
		int32_t Get_Y (const float _f_y) const;   // converts y-normalized value to screen coordinate;

		static
		bool Is_valid (const t_size_u&, CError&); // it is assumed the width and height both do not equal to 0, otherwise 'false';
		bool Is_valid (void) const;               // it is assumed the width and height both do not equal to 0, otherwise 'false';

		const
		CParams& Params (void) const;
		CParams& Params (void) ;

		// the conversion of screen coordinates is made for x|y values, z-coord has always 0.0f value;
		static err_code To_pos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, f_set_3& _pos_out, CError&);

	private:
		CViewport& operator = (const CViewport&) = delete; CViewport& operator = (CViewport&&) = delete;
		t_size_u m_size ;
		t_point  m_offset; // this is Offset of viewport from top-left corner of the window client area; by default it is (0|0);
		CParams  m_params;
	};

}}

#endif/*_GL_PROCS_VIEWPORT_H_INCLUDED*/