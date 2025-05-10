/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 10:02:47.899, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface implemetation file;
*/
#include "uix.gdi.blend.h"

using namespace ex_ui::draw::blend;

/////////////////////////////////////////////////////////////////////////////

CVertex:: CVertex (void) : m_vertex{0} {}
CVertex:: CVertex (const CVertex& _src) : CVertex() { *this= _src; }
CVertex::~CVertex (void) {}

/////////////////////////////////////////////////////////////////////////////

TRgbQuad  CVertex::Clr (void) const {
	return TRgbQuad(this->Raw().Red >> 8, this->Raw().Green >> 8, this->Raw().Blue >> 8, this->Raw().Alpha >> 8);
}

bool      CVertex::Clr (const TRgbQuad& _quad) {
	_quad;
	const bool b_changed = (this->Raw().Red != _quad.R() << 8
							|| this->Raw().Green != _quad.G() << 8
								|| this->Raw().Blue != _quad.B() << 8
									|| this->Raw().Alpha != _quad.A() << 8);
	if (b_changed) {
		this->Raw().Red   = _quad.R() << 8;
		this->Raw().Green = _quad.G() << 8;
		this->Raw().Blue  = _quad.B() << 8;
		this->Raw().Alpha = _quad.A() << 8;
	}
	return b_changed;
}
const
t_point   CVertex::Point (void) const { return t_point{this->Raw().x, this->Raw().y}; }
bool      CVertex::Point (const int32_t _x, const int32_t _y) {
	_x; _y;
	const bool b_changed = (this->Raw().x != _x || this->Raw().y != _y);
	if (b_changed) {
		this->Raw().x = _x;
		this->Raw().y = _y;
	}
	return b_changed;
}
bool      CVertex::Point (const t_point& _pt) {
	return this->Point(_pt.x, _pt.y);
}

#if defined(_DEBUG)
CString   CVertex::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {point=%s;rgba=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {point=%s;rgba=%s}");
	static _pc_sz pc_sz_pat_r = _T("{point=%s;rgba=%s}");

	CString cs_point = TStringEx().Format(_T("x:%d|y:%d"), this->Raw().x, this->Raw().y);
	CString cs_rgba  = this->Clr().Print(e_print::e_req);

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_point, (_pc_sz)cs_rgba); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_point, (_pc_sz)cs_rgba); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_point, (_pc_sz)cs_rgba); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
TVertex&  CVertex::Raw (void) const { return this->m_vertex; }
TVertex&  CVertex::Raw (void)       { return this->m_vertex; }

/////////////////////////////////////////////////////////////////////////////

CVertex&  CVertex::operator = (const CVertex& _src) { *this << _src.Raw(); return *this; }
CVertex&  CVertex::operator <<(const t_point& _pt) { this->Point(_pt); return *this; }
CVertex&  CVertex::operator <<(const TVertex& _vertex) { this->Raw() = _vertex; return *this; }

CVertex::operator const TVertex& (void) const { return this->Raw(); }
CVertex::operator       TVertex& (void)       { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////

CRectGrad:: CRectGrad (void) : m_indices{0,1} {}
CRectGrad::~CRectGrad (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TRectGrad& CRectGrad::Indices (void) const { return this->m_indices; }
TRectGrad& CRectGrad::Indices (void)       { return this->m_indices; }

const bool CRectGrad::Is_valid(void) const {
	t_rect rect_t = {
		this->LeftTop().Raw().x, this->LeftTop().Raw().y, this->RightBottom().Raw().x, this->RightBottom().Raw().y
	};
	return (!::IsRectEmpty(&rect_t));
}
const
CVertex&  CRectGrad::LeftTop (void) const { return this->m_vertices[0]; }
CVertex&  CRectGrad::LeftTop (void)       { return this->m_vertices[0]; }
const
CVertex&  CRectGrad::RightBottom (void) const { return this->m_vertices[1]; }
CVertex&  CRectGrad::RightBottom (void)       { return this->m_vertices[1]; }
#if defined(_DEBUG)
CString   CRectGrad::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%sindices=%s;%s%svertices=%s%s%svalid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {indices=%s;vertices=%s}");
	static _pc_sz pc_sz_pat_r = _T("{indices=%s;vertices=%s}");

	CString cs_indices  = TStringEx().Format(_T("left-top:%u;right-bottom:%u"), this->Indices().UpperLeft, this->Indices().LowerRight);
	CString cs_virtices = TStringEx().Format(_T("{%s%s0:%s%s%s1:%s%s%s}"),
		_p_sfx, _p_pfx, (_pc_sz) this->LeftTop().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->RightBottom().Print(e_print::e_req),
		_p_sfx, _p_pfx
	);

	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__ ,
		_p_sfx, _p_pfx, (_pc_sz)cs_indices ,
		_p_sfx, _p_pfx, (_pc_sz)cs_virtices,
		_p_sfx, _p_pfx, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__  , (_pc_sz)cs_indices, (_pc_sz)cs_virtices); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)cs_indices , (_pc_sz)cs_virtices); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CRectGrad& CRectGrad::operator <<(const CVertex& _vertex) { this->LeftTop() = _vertex; return *this; }
CRectGrad& CRectGrad::operator >>(const CVertex& _vertex) { this->RightBottom() = _vertex; return *this; }

/////////////////////////////////////////////////////////////////////////////

CTriaGrad:: CTriaGrad (void) : m_indices{0, 1, 2} {}
CTriaGrad::~CTriaGrad (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TTriGrad&   CTriaGrad::Indices (void) const { return this->m_indices; }
TTriGrad&   CTriaGrad::Indices (void)       { return this->m_indices; }

const bool  CTriaGrad::Is_valid(void) const {
	const
	bool b_valid = (
		(this->Get_A().Raw().x != this->Get_B().Raw().x) && (this->Get_A().Raw().x != this->Get_C().Raw().x) &&
		(this->Get_B().Raw().x != this->Get_C().Raw().x) &&
		(this->Get_A().Raw().y != this->Get_B().Raw().y) && (this->Get_A().Raw().y != this->Get_C().Raw().y) &&
		(this->Get_B().Raw().y != this->Get_C().Raw().y)
	);
	return b_valid;
}
const
CVertex&    CTriaGrad::Get_A (void) const { return this->m_vertices[0]; }
CVertex&    CTriaGrad::Get_A (void)       { return this->m_vertices[0]; }
const
CVertex&    CTriaGrad::Get_B (void) const { return this->m_vertices[1]; }
CVertex&    CTriaGrad::Get_B (void)       { return this->m_vertices[1]; }
const
CVertex&    CTriaGrad::Get_C (void) const { return this->m_vertices[2]; }
CVertex&    CTriaGrad::Get_C (void)       { return this->m_vertices[2]; }
#if defined(_DEBUG)
CString     CTriaGrad::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%sindices=%s;%s%svertices=%s%s%svalid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {indices=%s;vertices=%s}");
	static _pc_sz pc_sz_pat_r = _T("{indices=%s;vertices=%s}");

	CString cs_indices  = TStringEx().Format(_T("0:%u;1:%u;2:%u"), this->Indices().Vertex1, this->Indices().Vertex2, this->Indices().Vertex3);
	CString cs_virtices = TStringEx().Format(_T("{%s%sA:%s%s%sB:%s%s%sC:%s%s%s}"),
		_p_sfx, _p_pfx, (_pc_sz) this->Get_A().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->Get_B().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->Get_C().Print(e_print::e_req),
		_p_sfx, _p_pfx
	);

	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__ ,
			_p_sfx, _p_pfx, (_pc_sz)cs_indices ,
			_p_sfx, _p_pfx, (_pc_sz)cs_virtices,
			_p_sfx, _p_pfx, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__  , (_pc_sz)cs_indices, (_pc_sz)cs_virtices); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)cs_indices , (_pc_sz)cs_virtices); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CRenderer:: CRenderer (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CRenderer::~CRenderer (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CRenderer::Error (void) const { return this->m_error; }