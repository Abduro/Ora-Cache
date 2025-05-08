#ifndef _EBO_TEST_$G$_BASE_2D_H_INCLUDED
#define _EBO_TEST_$G$_BASE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-May-2025 at 09:43:51.849, UTC+4, Batumi, Thursday;
	This is Ebo Pack 2D space geometry base classes' unit test interface declaration file; 
*/
#include "ebo_test_$g$.2d.h"

namespace ebo { namespace boo { namespace test {

namespace outline { namespace _2D { // 'outline' namespace is declared here in order do not intercept with 'geometry' namespace;

#pragma region __points
	__class(CPoint) {
	public:
		 CPoint (const bool _b_verb = false);
		~CPoint (void) = default;

		__ctor(_ctor) ;
		__method(Operators);

	private:
		bool m_b_verb;
	};

	__class(CPoints) {
	public:
		 CPoints (const bool _b_verb = false);
		~CPoints (void) = default;

		__ctor(_ctor);

	private:
		bool m_b_verb;
	};

	using TPoint_2 =  geometry::base::_2D::CPoint_2; // this is the point class extended by marker;

	__class(CPoint_2) {
	public:
		 CPoint_2 (const bool _b_verb = false);
		~CPoint_2 (void) = default;

		__ctor(_ctor);

	private:
		bool m_b_verb;
	};
#pragma endregion
#pragma region __sizes

	__class(CSize) {
	public:
		 CSize (const bool _b_verb = false);
		~CSize (void) = default;

	public:
		__ctor (_ctor);
		__method (Operators);
	private:
		bool m_b_verb;
	};

	__class(CSizeU) {
	public:
		 CSizeU (const bool _b_verb = false);
		~CSizeU (void) = default;

	public:
		__ctor (_ctor);
		__method (Operators);

	private:
		bool m_b_verb;
	};

#pragma endregion

	__class(CMarker) {
	public:
		 CMarker (const bool _b_verb = false);
		~CMarker (void) = default;

	public:
		__ctor (_ctor);
		__method (Operators);

	private:
		bool m_b_verb;
	};

#pragma region __position

	using TAnchor = geometry::base::_2D::CAnchor;
	using TPosition = geometry::base::_2D::CPosition;

	__class(CAnchor) {
	public:
		 CAnchor (const bool _b_verb = false);
		~CAnchor (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

	__class(CPosition) {
	public:
		 CPosition (const bool _b_verb = false);
		~CPosition (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

#pragma endregion

}}

}}}
#endif/*_EBO_TEST_$G$_BASE_2D_H_INCLUDED*/