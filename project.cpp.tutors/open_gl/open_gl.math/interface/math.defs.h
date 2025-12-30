#ifndef __MATH_DEFS_H_INCLUDED
#define __MATH_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 03:10:43.568, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' geometry generic elements' interface declaration file;
*/
#include <algorithm>
#include <functional>
#include <cmath>
#include "shared.defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	using namespace shared::defs;

	namespace defs {
		static float $na = 0.0f; // the reference to this variable may be returned in cases when an index of element is out of acceptable range;
		#define __pi 3.141593f
		const float  deg_2_rad = __pi / 180.0f;
		const float  rad_2_deg = 180.0f / __pi;
		const float  f_epsilon = 0.00001f;
	}

	// https://learn.microsoft.com/en-us/cpp/cpp/numeric-boolean-and-pointer-literals-cpp ;
	// https://learn.microsoft.com/en-us/cpp/cpp/user-defined-literals-cpp ;

	typedef ::std::array<float, 2u> t_set_2;
	typedef ::std::vector<float> t_dyna_set;
#if (0) // not used;
namespace _2d {

	enum class e_index : uint32_t {
		_0 = 0,
		_1 = 1,
	};

	// the array is good for fixed size containers or data sets, but what's about inheritance: e.g. point_3d is inherited from from point_2d;
	// https://stackoverflow.com/questions/42238712/change-array-size-c ;

	class CPoint {
	public:
		CPoint (void); CPoint (const CPoint&); CPoint (CPoint&&); ~CPoint (void);
		CPoint (const float _x, const float _y);

		const float x (void) const; float& x (void); void x (const float);
		const float y (void) const; float& y (void); void y (const float);

		void  Set (const float _x, const float _y);

	public:
		CPoint& operator = (const CPoint&);
		CPoint& operator = (CPoint&&);       // no swap values operation yet, just copying;
		CPoint& operator <<(const float _x);
		CPoint& operator >>(const float _y);

		float&  operator [](const e_index);

	protected:
		float m_x, m_y;
	};
}
namespace _3d {
	class CPoint : public _2d::CPoint { typedef _2d::CPoint TBase;
	public:
		CPoint (void); CPoint (const CPoint&); CPoint (CPoint&&); ~CPoint (void);
		CPoint (const float _x, const float _y,  const float _z);

		const float z (void) const; float& z (void); void z (const float);

	public:
		CPoint& operator = (const CPoint&);
		CPoint& operator = (CPoint&&); 
		CPoint& operator ^ (const float _z);

	protected:
		float m_z;
	};
}
#endif
}}}}

#endif/*__MATH_DEFS_H_INCLUDED*/