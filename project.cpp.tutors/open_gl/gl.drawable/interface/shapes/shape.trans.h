#ifndef _GL_TRANS_BASE_H_INCLUDED
#define _GL_TRANS_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 06:05:25.734, UTC+4, Batumi, Monday;
	This is OpenGL drawable shape geometric transformation related interface declaration file.
*/
#include "drawable.defs.h"
#include "matrix\gl_procs_mtx.oper.h"

namespace open_gl { namespace shapes { namespace transfer {

	using namespace ::shared::drawable;  // this is required for using mouse CEvent interface that is included in this namespace;
	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::matrix::ver_1_1;
	using f_set_3 = ::open_gl::procs::f_set_3;
	using c_angle = ::open_gl::views::c_angle;

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
		mutable
		CError m_error;
		bool   m_changed;
		COpers m_opers;
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

	/* a movement of an object occurs: [Shift] key is held, left button of the mouse is pressed and mouse cursor changes its position;
	*/
	class CMove : public COper_Base { typedef COper_Base TBase;
	public:
		CMove (void); CMove (const CMove&) = delete; CMove (CMove&&) = delete; ~CMove (void) = default;

		f_set_3  Get (void) const;
		err_code Set (const CEvent&); // returns __s_ok: handled; __s_false: out of interest; otherwise: error code;

		bool  Is_accepted (const CEvent&) const; // checks required virtual key and mouse button are pressed;

		void Update (void);

	private:
		CMove& operator = (const CMove&) = delete; CMove& operator = (CMove&&) = delete;
		f_set_3  m_where;
		t_point  m_cursor; // the previous position of the cursor is necessary for calculating a delta or a shift of the mouse cursor;

	static constexpr float f_sens = 1.0f;
	};

	/* a rotation of an object occurs: [Ctrl] key is held, left button of the mouse is pressed and mouse cursor changes its position;
	*/
	class CRotate : public COper_Base { typedef COper_Base TBase;
	public:
		enum e_around : uint32_t { e_x = 0, e_y, e_z };
		CRotate (void); CRotate (const CRotate&) = delete; CRotate (CRotate&&) = delete; ~CRotate (void) = default;

		err_code Apply (void); // calls glRotate function;

		bool  Is_accepted (const CEvent&) const; // checks required virtual key and mouse button are pressed;
		const
		c_angle& Get (const e_around) const; // returns a rotation angle around given axis;
		err_code Set (const CEvent&);        // returns __s_ok: handled; __s_false: out of interest; otherwise: error code;

	private:
		CRotate& operator = (const CRotate&) = delete; CRotate& operator = (CRotate&&) = delete;
		c_angle  m_angles[3]; // angles around each axis;
		t_point  m_curs_prev; // the previous cursor coordinates;

	static constexpr float f_sens = 0.5f; // a sensitivity factor; https://stackoverflow.com/questions/2454019/why-arent-static-const-floats-allowed ;
	};
}}}

#endif/*_GL_TRANS_BASE_H_INCLUDED*/