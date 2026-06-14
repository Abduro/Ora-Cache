/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2026 at 08:47:09.435, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' view grid layout interfce implementation file;
*/
#include "grid.layout.h"

using namespace open_gl::views::grid;

#pragma region str::s_point_2d{}

s_point_2d::s_point_2d (const float _x/* = 0.0f*/, const float _y/* = 0.0f*/) : m_x(_x), m_y(_y) {}
s_point_2d::s_point_2d (const s_point_2d& _src) : s_point_2d() { *this = _src; }

bool s_point_2d::Set (const float _x, const float _y) {
	const bool b_changed = (_x != this->m_x || _y != this->m_y);
	if (b_changed) {
		this->m_x = _x;
		this->m_y = _y;
	}
	return b_changed;
}
bool s_point_2d::Set (const s_point_2d& _pt) { return this->Set(_pt.m_x, _pt.m_y); }

s_point_2d& s_point_2d::operator = (const s_point_2d& _src) { this->Set(_src); return *this; }

CString s_point_2d::To_str (void) const {
	static _pc_sz p_pat = _T("x=%07.4f|y=%07.4f");
	CString cs_out; cs_out.Format(p_pat, this->m_x, this->m_y);
	return  cs_out;
}

#pragma endregion
#pragma region str::s_point_3d{}

s_point_3d::s_point_3d (const float _x/* = 0.0f*/, const float _y/* = 0.0f*/, const float _z/* = 0.0f*/) : base_t(_x, _y), m_z(_z) {}
s_point_3d::s_point_3d (const s_point_2d& _pt, const float _z/* = 0.0f*/) : s_point_3d(_pt.m_x, _pt.m_y, _z) {}
s_point_3d::s_point_3d (const s_point_3d& _src) : s_point_3d() { *this = _src; }

CString s_point_3d::To_str (void) const {
	static _pc_sz p_pat = _T("%s|z=%07.4f");
	CString cs_out; cs_out.Format(p_pat, (_pc_sz)(*this)().To_str(), this->m_z);
	return  cs_out;
}

s_point_3d& s_point_3d::operator = (const s_point_3d& _src) { (*this)() = _src(); this->m_z = _src.m_z; return *this; }
s_point_3d& s_point_3d::operator <<(const s_point_2d& _pt) { (*this)() = _pt; return *this; } // z-value is kept as it is;

const
s_point_2d& s_point_3d::operator ()(void) const { return (base_t&)*this; }
s_point_2d& s_point_3d::operator ()(void)       { return (base_t&)*this; }

s_point_3d::operator const s_point_2d& (void) const { return (base_t&)*this; }
s_point_3d::operator       s_point_2d& (void)       { return (base_t&)*this; }

#pragma endregion
#pragma region str::s_line_2d{}

s_line_2d::s_line_2d (const s_point_2d& _begin, const s_point_2d& _end) : m_points{_begin, _end} {}
s_line_2d::s_line_2d (const s_line_2d& _src) { *this = _src; }
s_line_2d::s_line_2d (s_line_2d&& _victim) { *this = _victim; }

const
s_point_2d& s_line_2d::Begin (void) const { return this->Get(e_points::e_begin); }
s_point_2d& s_line_2d::Begin (void)       { return this->Get(e_points::e_begin); }
const
s_point_2d& s_line_2d::End (void) const { return this->Get(e_points::e_end); }
s_point_2d& s_line_2d::End (void)       { return this->Get(e_points::e_end); }
const
s_point_2d& s_line_2d::Get (const e_points _e_pt) const { switch(_e_pt) { case e_points::e_begin: case e_points::e_end: return this->m_points[_e_pt]; } static s_point_2d pt_2d; return pt_2d; }
s_point_2d& s_line_2d::Get (const e_points _e_pt)       { switch(_e_pt) { case e_points::e_begin: case e_points::e_end: return this->m_points[_e_pt]; } static s_point_2d pt_2d; return pt_2d; }

CString s_line_2d::To_str (void) const {
	static _pc_sz p_pat_ln = _T("begin=[%s];end=[%s]");
	CString cs_out; cs_out.Format(p_pat_ln, (_pc_sz) this->Begin().To_str(), (_pc_sz) this->End().To_str());
	return  cs_out;
}
const
s_point_2d& s_line_2d::operator [](const e_points _e_pt) const { return this->Get(_e_pt); }
s_point_2d& s_line_2d::operator [](const e_points _e_pt)       { return this->Get(_e_pt); }

s_line_2d&  s_line_2d::operator = (const s_line_2d& _src) { this->Begin() = _src.Begin(); this->End() = _src.End(); return *this; }
s_line_2d&  s_line_2d::operator = (s_line_2d&& _victim) { *this = (const s_line_2d&)_victim; return *this; }

#pragma endregion
#pragma region cls::CLayout{}

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif
CLayout::CLayout (const CPers& _pers) : m_pers(_pers), m_rect{0} { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

const lines_t& CLayout::Calc (void) { return this->Calc(this->m_rect); }
const lines_t& CLayout::Calc (const t_rect& _rect) {
	_rect;
	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_lines.empty() == false) // it's doubtful, perhaps input rectangle must be checked for emptiness;
		this->m_lines.clear();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-isrectempty ;
	if (::IsRectEmpty(&_rect)) {
		__trace_err_ex_2(this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input rect is empty")); // justs makes the trace record, no exit;
	}
	const uint32_t u_cols = m_pers.Grid().Cols();
	const uint32_t u_rows = m_pers.Grid().Rows();

	if (0 == u_cols || 0 == u_rows) {
		__trace_err_ex_2(this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: cols=%u; rows=%u;"), u_cols, u_rows)); // traces the error and exits;
		return this->Get();
	}

	const uint32_t u_height = m_pers.Cell().Get().cy;
	const uint32_t u_width  = m_pers.Cell().Get().cx;

	if (0 == u_height || 0 == u_width) {
		__trace_err_ex_2(this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: cell={h=%u;w=%u}"), u_height, u_width)); // traces the error and exits;
		return this->Get();
	}
#if (0)
	const bool b_col_even = false == !!(u_cols % 2);
	const bool b_row_even = false == !!(u_rows % 2);
#endif
	const t_size u_center = {_rect.left + __W(_rect)/2, _rect.top + __H(_rect)/2 };
	struct {
		uint32_t u_height, u_width;
	} totals = { u_rows * u_height, u_cols * u_width};

	int32_t n_left = u_center.cx - totals.u_width / 2; while (n_left < 0) n_left += u_width ; // arranges the left x-coord to be visible;
	int32_t n_top = u_center.cy - totals.u_height / 2; while (n_top  < 0) n_top  += u_height; // arranges the top y-coord to be visible;

	int32_t n_right  = n_left + totals.u_width;  while (n_right > _rect.right) n_right -= u_width;     // arranges the right x-coord to be visible;
	int32_t n_bottom = n_top  + totals.u_height; while (n_bottom > _rect.bottom) n_bottom -= u_height; // arranges the bottom y-coord to be visible;

	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	CViewPort v_port; v_port << _rect;
	try {
		// it calculates vertical lines parallel to the Y axis;
		for (uint32_t i_ = 0; i_ < u_cols; i_++) {
			
			const s_point_2d pt_begin(v_port << (n_left + i_ * u_width), v_port >> n_top);
			const s_point_2d pt_end(pt_begin.m_x, v_port >> n_bottom);

			this->m_lines.push_back(s_line_2d(pt_begin, pt_end));
		}
		// it calculates horizontal lines parallel to the X axis;
		for (uint32_t i_ = 0; i_ < u_rows; i_++) {

			const s_point_2d pt_begin(v_port << n_left, v_port >> (n_top + i_ * u_height));
			const s_point_2d pt_end(v_port << n_right, pt_begin.m_y);

			this->m_lines.push_back(s_line_2d(pt_begin, pt_end));
		}
		// adds the most right vertical line of the grid;
		{
			const s_point_2d pt_begin(v_port << n_right, v_port >> n_top);
			const s_point_2d pt_end(v_port << n_right, v_port >> n_bottom);

			this->m_lines.push_back(s_line_2d(pt_begin, pt_end));
		}
		// adds the most bottom horizontal line of the grid;
		{
			/* query: how to convert GDI line wide to opengl line width :
			   to convert GDI line width to OpenGL line width, treat the GDI pen width as a pixel value for the OpenGL function glLineWidth();
			   using a standard GDI pen defined in pixels, the conversion is a direct 1:1 mapping;
			*/
			float f_thick = (float)this->m_pers.Line().Thick()/(float)v_port.Get().cx;
		//	::glGetFloatv(GL_LINE_WIDTH, &f_thick); // https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;

			const s_point_2d pt_begin(v_port << n_left, v_port >> n_bottom);
			const s_point_2d pt_end(v_port << n_right, (v_port >> n_bottom) + f_thick);

			this->m_lines.push_back(s_line_2d(pt_begin, pt_end));
		}
	} catch (const ::std::bad_alloc&) {}

	return this->Get();
}
const lines_t& CLayout::Get  (void) const { return this->m_lines; }

TError&  CLayout::Error (void) const { return this->m_error; }

CLayout& CLayout::operator <<(const t_rect& _rect) {
	this->m_rect = _rect; return *this;
}

#pragma endregion