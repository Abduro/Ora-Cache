#ifndef _GL_SHAPE_BS_H_INCLUDED
#define _GL_SHAPE_BS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 17:52:08.453, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to OpenGL tutorials on 23-Oct-2025 at 20:56:51.657, UTC+4, Batumi, Friday;
*/
#include "gl_defs.h"
#include "gl_vertex_arr.dat.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shapes {

	using e_object = CPipeline::e_object;

	// https://simple.wikipedia.org/wiki/Shape ;
	// https://en.wikipedia.org/wiki/List_of_two-dimensional_geometric_shapes ;

	class CShape : public CPipeline {
	private: CShape (const CShape&) = delete; CShape (CShape&&) = delete;
	public : CShape (void); ~CShape (void);
	public :
		static const uint32_t n_min_vertex_count = 3; // a triangle is the simplest figure that can be considered as a shape;
		static _pc_sz Class (void);
		// virtual methods go first;
		virtual err_code Draw  (void);
		virtual err_code Prepare (void);

		TError&  Error (void) const;
		uint32_t Primitive (void) const;
		const
		CVertArray&  VertArray (void) const;
		CVertArray&  VertArray (void) ;

	private: CShape& operator = (const CShape&) = delete; CShape& operator = (CShape&&) = delete;
	protected:
		mutable
		CError   m_error;
		uint32_t m_prim_mode; // this is the primitive's draw mode that is required for how the renderer should draw this shape;
	};

	class CShape_enum {
	public:
		class CDefaults {
		public:
			CDefaults (void); CDefaults (const CDefaults&) = delete; CDefaults (CDefaults&&) = delete; ~CDefaults (void) = default;

			TError& Error (void) const;
			err_code SetTo (const e_object);  

		private:
			CDefaults& operator = (const CDefaults&) = delete; CDefaults& operator = (CDefaults&&) = delete;
			CError m_error;
		};
	public: CShape_enum (void); ~CShape_enum (void); CShape_enum (const CShape_enum&) = delete; CShape_enum (CShape_enum&&) = delete;

		const
		CDefaults& Defaults (void) const; // gets the reference to default settings of shapes; (ro)
		CDefaults& Defaults (void) ;      // gets the reference to default settings of shapes; (rw)

		TError& Error (void) const;
		const
		CShape& Get (const e_object) const;      // gets the reference to the shape that is targeted for drawing; (ro)
		CShape& Get (const e_object) ;           // gets the reference to the shape that is targeted for drawing; (rw)
		const
		CShape& Ref (const uint32_t _ndx) const; // if the index is out of range; the reference to invalid shape is returned;
		CShape& Ref (const uint32_t _ndx) ;      // if the index is out of range; the reference to invalid shape is returned;

	private:
		CShape_enum& operator = (const CShape_enum&) = delete;
		CShape_enum& operator = (CShape_enum&&) = delete;
		mutable
		CError    m_error;
		CDefaults m_defs;
	};

}}}}

typedef ex_ui::draw::open_gl::shapes::CShape_enum TShapes; TShapes&  Get_shapes (void);

#endif/*_GL_SHAPE_BS_H_INCLUDED*/