#ifndef __MATH_RECT_2D_H_INCLUDED
#define __MATH_RECT_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Mar-2026 at 15:24:11.163, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' rectangular 2d shape corner points' matrix 2x4 interface declaration file;
*/
#include "math.rot.2x2.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	/* corners of a rectangle:
	   (a)+--+(b), that means: the corner top-left is 'a', top-right is 'b', bottom-right is 'c' and finally, bottom-left is 'd';
	      |  |
	   (d)+--+(c)
	   *note*: changing one corner value can destroy rectangularity of this shape;
	*/
	class c_rect {
	public:
		enum e_corners : uint32_t {
			e_a = 0x0, /*top-left;*/ e_b, /* top-right;*/ e_c, /*bottom-right;*/ e_d /*bottom-left;*/
		};
		static const uint32_t u_corners = 4;
		class c_corners { // this class is just an accessor to vector array of this rectangle shape;
		public:
			 c_corners (c_rect&); c_corners (void) = delete; c_corners (const c_corners&) = delete; c_corners (c_corners&&) = delete;
			~c_corners (void) = default;
			const vec_2&  A (void) const; /*vec_2&  A (void) ;*/ // these accessors are disabled for protecting rectangularity of this shape;
			const vec_2&  B (void) const; /*vec_2&  B (void) ;*/
			const vec_2&  C (void) const; /*vec_2&  C (void) ;*/
			const vec_2&  D (void) const; /*vec_2&  D (void) ;*/
			const
			vec_2&  Get (const e_corners) const;
			vec_2&  Get (const e_corners) ; // this reference remains be accessible, but using it without special circumstances is not recommended;

			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setrect ;

			void Set_Bottom (const float); // sets y-coord value of the following corners: C & D;
			void Set_Left (const float); // sets x-coord value of the following corners: A & D;
			/* 
			   sets left side x-coord value, this changes x-coord value of these corners: A & D;
			   sets top side y-coord value, this changes y-coord value of these corners: A & B;
			*/
			void  Set_LeftTop (const float _f_left, const float _f_top);
			void  Set_Right (const float); // sets x-coord value of the following corners: B & C;
			/*
			   sets right side x-coord value, this changes x-coord of these corners: B & C;
			   sets bottom side y-coord value, this changes y-coord of these corners: C & D;
			*/
			void  Set_RightBottom (const float _f_right, const float _f_bottom);
			void  Set_Top (const float); // sets y-coord value of the following corners: A & B;
			static
			_pc_sz  To_str (const e_corners, const vec_2);

		private:
			c_corners& operator = (const c_corners&) = delete; c_corners& operator = (c_corners&&) = delete;
			c_rect&  m_rect;
		};
	public:
		 c_rect (void); c_rect (const c_rect&); c_rect (c_rect&&) = delete;
		~c_rect (void) = default;
		/* unit square/rectangle: (x,y) notation;
		cols:    #0  #1  #2  #3
		rows: #0  0   1   1   0 >> corner 'a': (x=c0:r0;y=c0:r1); corner 'b': (x=c1:r0;y=c1:r1);
		      #1  0   0   1   1    corner 'c': {x=c2:r0;y=c2:r1}; corner 'd': {x=c3:r0;y=c3:r1};
		or in vectors as column of the matrix:
		corners:  A   B   C   D
		          v0  v1  v2  v3;
		*/
		const
		c_corners& Corners (void) const;
		c_corners& Corners (void) ;

		float Height (void) const; // gets the height of this shape; it is supposed the rectangularity is still kept;

		void  Init (void); // initializes the rectangle by default unit rectangle coordinates;

		bool  Is_empty (void) const; // sometimes the rectangle appears as a line or even a dot;
		bool  Is_valid (void) const; // opposite sides must have the same length and all corners equal to 90 degrees;

		float Width (void) const; // gets the width of this shape; it is supposed the rectangularity is still kept;

		c_rect& operator = (const c_rect&); c_rect& operator = (c_rect&&) = delete;
		const
		c_corners& operator ()(void) const;
		c_corners& operator ()(void) ;

	protected:
		vec_2  m_data[c_rect::u_corners]; friend class c_rect::c_corners;
		c_corners m_corners;
	};

	class c_rot_rect : public c_rect {
	public:
		 c_rot_rect (void); c_rot_rect (const c_rot_rect&) = delete; c_rot_rect (c_rot_rect&&) = delete;
		~c_rot_rect (void) = default;

		c_rect& Do (const float _f_angle); // rotates this shape to given angle around axes' origin;

		const
		c_rect& operator ()(void) const;
		c_rect& operator ()(void) ;

	private:
		c_rot_rect& operator = (const c_rot_rect&) = delete; c_rot_rect& operator = (c_rot_rect&&) = delete;
	};
}}}}

#endif/*__MATH_RECT_2D_H_INCLUDED*/