#ifndef _GRID_LAYOUT_H_INCLUDED
#define _GRID_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2026 at 08:42:49.539, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' gview grid layout interfce declaration file;
*/
#include "grid.pers.h"

namespace open_gl { namespace views {
namespace grid {

	struct s_point_2d {
		float m_x, m_y;

		s_point_2d (const float _x = 0.0f, const float _y = 0.0f);
		s_point_2d (const s_point_2d&);

		bool Set (const float _x, const float _y); // returns 'true' in case a value of 'x' or/and 'y' change;
		bool Set (const s_point_2d&);              // returns 'true' in case a value of 'x' or/and 'y' change;

		s_point_2d& operator = (const s_point_2d&);

		CString To_str (void) const;
	};

	struct s_point_3d : public s_point_2d { typedef s_point_2d base_t;
		float m_z;

		s_point_3d (const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f);
		s_point_3d (const s_point_2d&, const float _z = 0.0f);
		s_point_3d (const s_point_3d&);

		CString To_str (void) const;

		s_point_3d& operator = (const s_point_3d&);
		s_point_3d& operator <<(const s_point_2d&);
		const
		s_point_2d& operator ()(void) const;
		s_point_2d& operator ()(void) ;

		operator const s_point_2d& (void) const;
		operator       s_point_2d& (void) ;
	};

	typedef s_point_2d pt_2d_t;
	typedef s_point_3d pt_3d_t;

	struct s_line_2d { enum e_points : uint32_t { e_begin = 0x0, e_end };
		s_point_2d  m_points[e_points::e_end + 1];

		s_line_2d (void) = default;
		s_line_2d (const s_line_2d&); s_line_2d (s_line_2d&&);
		s_line_2d (const s_point_2d& _begin, const s_point_2d& _end); ~s_line_2d (void) = default;

		const
		s_point_2d& Begin (void) const;
		s_point_2d& Begin (void) ;
		const
		s_point_2d& End (void) const;
		s_point_2d& End (void) ;
		const
		s_point_2d& Get (const e_points) const;
		s_point_2d& Get (const e_points) ;

		CString To_str (void) const;

		s_line_2d&  operator = (const s_line_2d&);
		s_line_2d&  operator = (s_line_2d&&);
		const
		s_point_2d& operator [](const e_points) const;
		s_point_2d& operator [](const e_points) ;
	};

	typedef ::std::vector<s_line_2d> lines_t;

	using CPers = CPersistent;

	class CLayout {
	public:
		CLayout (const CPers&);
		CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete; ~CLayout (void) = default;

		TError& Error (void) const;

		const lines_t& Calc (void);          // uses cached rectangle for calculating grid lines;
		const lines_t& Calc (const t_rect&); // calculates how many lines are required to draw the grid; grid's row and cols numbers are used;
		const lines_t& Get  (void) const;    // returns the reference to lines' set calculated by this::Calc();

		CLayout& operator <<(const t_rect&); // sets the grid rectangle;

	private:
		CLayout& operator = (const CLayout&) = delete; CLayout& operator = (CLayout&&) = delete;
		const
		CPers&  m_pers ;
		lines_t m_lines;
		CError  m_error;
		t_rect  m_rect ;  // cached rectangle that is available for grid;
	};
}
}}
#endif/*_GRID_LAYOUT_H_INCLUDED*/