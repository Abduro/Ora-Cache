#ifndef _2D_ROTATE_H_INCLUDED
#define _2D_ROTATE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-May-2025 at 11:05:11.044, UTC+4, Batumi, Thursday;
	This is Ebo Pack 2D space geometry figure rotation interface declaration file.
*/
#include "2d.base.h"
#include "2d.base.line.h"
#include "2d.shape.h"
#include "2d.shape.rect.h"

namespace geometry { namespace _2D {

	using CLine  = geometry::_2D::base::CLine ;
	using CPoint = geometry::_2D::base::CPoint;
	using CShape = geometry::_2D::shapes::CShape;
	using CRect  = geometry::_2D::shapes::COblong;

	// https://stackoverflow.com/questions/2285936/easiest-way-to-rotate-a-rectangle ; good example and explanation;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/rotation ;
	// https://learn.microsoft.com/en-us/windows/win32/direct2d/how-to-rotate ; as an example of the rotation in Direct2D;
	class CRotate {
	public:
		enum e_direct : uint32_t {
		     e_cw  = 0x0, // clockwise; if the rotate angle has negative value of degrees;
		     e_ccw = 0x1, // counter-clockwise; it is just the opposition of above case: the angle has positive value of degrees;
		};
	public:
		 CRotate (void) ; CRotate (const CRotate&) = delete; CRotate (CRotate&&) = delete;
		~CRotate (void) ;

	public:
		int16_t  Angle (void) const;    // returns an angle which the rotation must be made in;
		bool     Angle (const int16_t); // returns 'true' in case of change; if the value more/less than 360 degree, it is casted to appropriate value;

		err_code ApplyTo (CLine&) const;
		err_code ApplyTo (CPoint& _vertex) const; // returns 's_okay' always;
		err_code ApplyTo (CRect&) const;
		err_code ApplyTo (CShape&) const;

		const
		CPoint&  Center (void) const;
		CPoint&  Center (void) ;
		e_direct Direct (void) const;   // it is just informative and is dependable on the sign rotate angle value;
//		bool     Direct (const e_direct); this is mostly not usefull due to: negative degree is clockwise rotation, otherwise counter-clockwise;
#if defined(_DEBUG)
		CString  DirectAsText (void) const;
#endif
		TError&  Error (void) const;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CRotate&  operator = (const CRotate&) = delete;
		CRotate&  operator = (CRotate&&) = delete;

//		CRotate&  operator <<(const e_direct);
		CRotate&  operator <<(const CPoint& _center);    // sets a center of the rotation;
		CRotate&  operator <<(const int16_t _angle);     // sets an angle of the rotation;

		CRotate&  operator >>(CLine& ) ;
		CRotate&  operator >>(CPoint&) ;
		CRotate&  operator >>(CRect& ) ;
		CRotate&  operator >>(CShape&) ;

	private:
		mutable
		CError    m_error ;
		int16_t   m_angle ;
		e_direct  m_direct;
		CPoint    m_center;
	};

}}

#endif/*_2D_BASE_H_INCLUDED*/