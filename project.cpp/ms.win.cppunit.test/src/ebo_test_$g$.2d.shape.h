#ifndef _EBO_TEST_$G$_2D_SHAPE_H_INCLUDED
#define _EBO_TEST_$G$_2D_SHAPE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-May-2025 at 09:31:45.786, UTC+4, Batumi, Thursday;
	This is Ebo Pack 2D space geometry shape classes' unit test interface declaration file; 
*/
#include "ebo_test_$g$.2d.h"

namespace ebo { namespace boo { namespace test { namespace _2D { namespace shapes {

#pragma region __sides

	using TSide = geometry::_2D::shapes::CSide;

	__class(CSide) {
	public:
		 CSide (const bool _b_verb = false);
		~CSide (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

	using TSides = geometry::_2D::shapes::CSides;

	__class(CSides) {
	public:
		 CSides (const bool _b_verb = false);
		~CSides (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

#pragma endregion

#pragma region __shapes

	using TRect = geometry::_2D::shapes::COblong; // TRect typedef is also applicable;

	__class(CRect) {
	public:
		 CRect (const bool _b_verb = false);
		~CRect (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

	using TShape = geometry::_2D::shapes::CShape;

	__class(CShape) {
	public:
		 CShape (const bool _b_verb = false);
		~CShape (void) = default;

	public:
		__ctor (_ctor);
		__method (Modify);

	private:
		bool m_b_verb;
		TShape m_shape;
	};

#pragma endregion
}}}}}
#endif/*_EBO_TEST_$G$_2D_SHAPE_H_INCLUDED*/