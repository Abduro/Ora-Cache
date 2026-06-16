#ifndef _GL_TRANS_BASE_H_INCLUDED
#define _GL_TRANS_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 06:05:25.734, UTC+4, Batumi, Monday;
	This is OpenGL drawable shape geometric transformation related interface declaration file.
*/
#include "drawable.defs.h"
#include "matrix\gl_procs_mtx.oper.h"

namespace open_gl { namespace shapes { namespace transfer {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::matrix::ver_1_1;
	using f_set_3 = ::open_gl::procs::f_set_3;

	/* the query to Google AI: how to name such operations as movement, rotation and scaling in opengl?
	In OpenGL, operations that change an object's position, orientation, or size are collectively known as geometric transformations.
	Specifically, they are referred to as:
	(1) Translation: Moving an object along the x, y, and z axes;
	(2) Rotation: Turning an object around a specified axis or pivot point;
	(3) Scaling: Resizing an object by enlarging or shrinking it along the axes.
	*/
	
	class COper_Base {
	protected:
		COper_Base (void); COper_Base (const COper_Base&) = delete; COper_Base (COper_Base&&) = delete; ~COper_Base (void) = default;
	public:
		TError& Error (void) const;

		bool Is_changed (void) const;
		void Is_changed (const bool);

	protected:
		COper_Base& operator = (const COper_Base&) = delete; COper_Base& operator = (COper_Base&&) = delete;
		bool m_changed;
		CError m_error;
	};

	/* the query to Google AI: what scale factor should be set in order to change draw object a little smaller opengl?
	   To make an OpenGL object slightly smaller, set the scale factor to a value slightly less than 1.0
	   (e.g., 0.9 for 10%) smaller, 0.95 for 5% smaller) using the glScalef(x, y, z) function.
	Key Details:
	(1) Scale Factor Range: values between 0.0 and 1.0 shrink the object, while values greater than 1.0 magnify it;
	(2) Uniform vs. non-uniform: Use the same value for x, y, z (e.g., 0.9, 0.9, 0.9) to shrink proportionally without distortion;
	(3) Implementation: call glScalef() before issuing the draw commands for your object;
	(4) Order Matters: to avoid unexpected positioning, translate the object to the origin (0,0,0), apply the scale, and then translate back;
	*/
	static const float f_delta = 0.08f;
	static const float f_def_scale = 1.0f;
	// this class is thread safe;
	class CScale : public COper_Base { typedef COper_Base TBase;
	public:
		CScale (void); CScale (const CScale&) = delete; CScale (CScale&&) = delete; ~CScale (void) = default;

		float Get (void) const;              // gets the factor value;
		void  Set (const int32_t _n_factor); // sets the factor value; this is uniform scale;

	private:
		CScale& operator = (const CScale&) = delete; CScale& operator = (CScale&&) = delete;
		float   m_factor;
	};

	class CTranslate : public COper_Base { typedef COper_Base TBase;
	public:
		CTranslate (void); CTranslate (const CTranslate&) = delete; CTranslate (CTranslate&&) = delete; ~CTranslate (void) = default;

		f_set_3 Get (void) const;
		void Update (void);

	private:
		CTranslate& operator = (const CTranslate&) = delete; CTranslate& operator = (CTranslate&&) = delete;
		f_set_3  m_trans;
		t_point  m_prevs; // the previous position of the cursor is necessary for calculating a delta or a shift of the mouse cursor;
	};

}}}

#endif/*_GL_TRANS_BASE_H_INCLUDED*/