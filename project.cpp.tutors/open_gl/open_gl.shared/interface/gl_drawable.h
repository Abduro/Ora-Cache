#ifndef _GL_DRAWABLE_H_INCLUDED
#define _GL_DRAWABLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:49:12.456, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface declaration file;
*/
#include "gl_defs.h"
#include "color.rgb.h"
typedef
struct {
	uint32_t cx = 0;
	uint32_t cy = 0;
} t_size_u;

namespace ex_ui { namespace draw { namespace open_gl {

	class CBkgnd : private no_copy {
	public:
		CBkgnd (void); ~CBkgnd (void);

		err_code Draw  (void);
		TError&  Error (void) const;

	private:
		CError m_error;
	};

	using namespace ex_ui::color;
	using e_rgba   = rgb::e_rgba;
	using e_object = CPipeline::e_object;

	// ToDo: it looks very like this class or its functionality needs to be moved to the rgb.color shared library project;
	class CClr_flt : public rgb::CFloat { typedef rgb::CFloat TBase;
	public:
		CClr_flt (void); ~CClr_flt (void);

		TError& Error (void) const;

		err_code Get (const e_object);  // loads the color for the draw pipeline component from the registry;

		// sets color as float value; if the value is out of range [0.0...1.0], the value is set to min or max value of the range;
		void Set (const float _r, const float _g, const float _b, const float _a = 1.0f);
		void Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a = 0xff);

	public:
		const
		rgb::CFloat&  operator ()(void) const; // gets the reference to the base class; (ro)
		rgb::CFloat&  operator ()(void) ;      // gets the reference to the base class; (rw)

	private:
		CError m_error;
	};

namespace view {
	// this grid classes uses the program, vertex array object and vertex array data which are managed by draw scene of the renderer object;
	class CGrid : private no_copy {
	public:
		class CCell : private no_copy {
		public:
			CCell (void); ~CCell (void);

			uint32_t H (void) const;     uint32_t Height (void) const;
			bool     H (const uint32_t); bool     Height (const uint32_t); // returns 'true' in case if height of the cell is changed;

			uint32_t W (void) const;     uint32_t Width  (void) const;
			bool     W (const uint32_t); bool     Width  (const uint32_t); // returns 'true' in case if width  of the cell is changed;

			static
			bool   Is_valid (const t_size_u&, CError&); // validates the input size for emptiness;
			bool   Is_valid (void) const;               // returns 'true' if the height and the width of the cell does not equal to zero (0);

			const
			t_size_u& Get (void) const;
			bool      Set (const uint32_t _u_width, const uint32_t _u_height); // returns 'true' if either cell width ot cell height is changed;

		private:
			t_size_u m_size;
		};
	public:
		CGrid (void); ~CGrid (void);

		const
		CCell& Cell (void) const;
		CCell& Cell (void) ;

		const
		CClr_flt&  Clr (void) const;
		CClr_flt&  Clr (void) ;

		err_code Create  (void);
		err_code Destroy (void);
#if (0)
		void Default (void); // sets default values for grid size, draw step and grid color;
#endif
		err_code Draw  (void);
		TError&  Error (void) const;

		err_code Update(const t_size_u&); // recalculates all vertices for input size of the draw area;

	private:
		CCell    m_cell ;    // cell dimensions: height|width;
		CError   m_error;
		CClr_flt m_color;
	};
}

}}}

#endif/*_GL_DRAWABLE_H_INCLUDED*/