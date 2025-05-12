/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 23:49:36.644, UTC+4, Batumi, Saturday;
	This is Ebo Pack GDI gradient shading functionality wrapper interface implementation file;
*/
#include "uix.gdi.shade.h"

using namespace ex_ui::draw::shade;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace shade { namespace _impl {

	bool operator != (const t_point& _lhv, const t_point& _rhv) {
		return (_lhv.x != _rhv.x || _lhv.y != _rhv.y);
	}

}}}}
using namespace ex_ui::draw::shade::_impl;
/////////////////////////////////////////////////////////////////////////////

CRectMesh:: CRectMesh (const uint32_t _n_left_top, const uint32_t _n_right_bottom) : m_mesh{_n_left_top, _n_right_bottom} {}
CRectMesh:: CRectMesh (const CRectMesh& _src) : CRectMesh() { *this = _src; }
CRectMesh:: CRectMesh (const TRectMesh& _mesh) : CRectMesh() { *this << _mesh; }

CRectMesh:: CRectMesh (CRectMesh&& _victim) : CRectMesh() { *this = _victim; }

CRectMesh::~CRectMesh (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t   CRectMesh::LeftTop (void) const { return this->Raw().UpperLeft; }
bool       CRectMesh::LeftTop (const uint32_t _n_ndx) {
	const bool b_changed = this->LeftTop() != _n_ndx;
	if (b_changed) 
		this->Raw().UpperLeft = _n_ndx;
	return b_changed;
}

uint32_t   CRectMesh::RightBottom (void) const { return this->Raw().LowerRight; }
bool       CRectMesh::RightBottom (const uint32_t _n_ndx) {
	const bool b_changed = this->RightBottom() != _n_ndx;
	if (b_changed) 
		this->Raw().LowerRight = _n_ndx;
	return b_changed;
}

#if defined (_DEBUG)
CString    CRectMesh::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> indices={left-top=%u;right_bottom=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> indices={left-top=%u;right_bottom=%u}");
	static _pc_sz pc_sz_pat_r = _T("{left-top=%u;right_bottom=%u}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->LeftTop(), this->RightBottom());
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->LeftTop(), this->RightBottom()); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->LeftTop(), this->RightBottom()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TRectMesh& CRectMesh::Raw (void) const { return this->m_mesh; }
TRectMesh& CRectMesh::Raw (void)       { return this->m_mesh; }

bool CRectMesh::Set (const uint32_t _n_left_top, const uint32_t _n_right_bottom) {

	bool b_changed = false;

	if (this->LeftTop(_n_left_top)) b_changed = true;
	if (this->RightBottom(_n_right_bottom)) b_changed = true;

	return b_changed;
}

bool CRectMesh::Set (const TRectMesh& _mesh) {
	return this->Set(_mesh.UpperLeft, _mesh.LowerRight);
}

/////////////////////////////////////////////////////////////////////////////
CRectMesh& CRectMesh::operator = (const CRectMesh& _src) { *this << _src.Raw(); return *this; }
CRectMesh& CRectMesh::operator = (CRectMesh&& _victim) { *this = (const CRectMesh&)_victim; return *this; }

CRectMesh& CRectMesh::operator <<(const TRectMesh& _mesh) { this->Set(_mesh);  return *this; }
CRectMesh& CRectMesh::operator <<(const uint32_t _n_left_top)     { this->LeftTop(_n_left_top); return *this; }
CRectMesh& CRectMesh::operator >>(const uint32_t _n_right_bottom) { this->RightBottom(_n_right_bottom); return *this; }

CRectMesh::operator const TRectMesh& (void) const { return this->Raw(); }
CRectMesh::operator       TRectMesh& (void)       { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////

CTriMesh:: CTriMesh (void) : m_mesh{0}{}
CTriMesh:: CTriMesh (const CTriMesh& _src) : CTriMesh() { *this = _src; }
CTriMesh:: CTriMesh (const TTriMesh& _mesh) : CTriMesh() { *this << _mesh; }

CTriMesh:: CTriMesh (CTriMesh&& _victim) : CTriMesh() { *this = _victim; }

CTriMesh::~CTriMesh (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t   CTriMesh::Index (const e_corner _n_vertex) const {
	switch (_n_vertex) {
	case e_corner::e_vert_a: return this->Raw().Vertex1;
	case e_corner::e_vert_b: return this->Raw().Vertex2;
	case e_corner::e_vert_c: return this->Raw().Vertex3;
	}
	return 0;
}

const bool CTriMesh::Index (const e_corner _n_vertex, const uint32_t _n_value) {
	bool b_changed = false;
	switch (_n_vertex) {
	case e_corner::e_vert_a: { b_changed = (_n_value != this->Raw().Vertex1); if (b_changed) this->Raw().Vertex1 = _n_value; } break;
	case e_corner::e_vert_b: { b_changed = (_n_value != this->Raw().Vertex2); if (b_changed) this->Raw().Vertex2 = _n_value; } break;
	case e_corner::e_vert_c: { b_changed = (_n_value != this->Raw().Vertex3); if (b_changed) this->Raw().Vertex3 = _n_value; } break;
	}
	return b_changed;
}

#if defined(_DEBUG)
CString    CTriMesh::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> indices={vert-1=%u;vert-2=%u;vert-3=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> indices={vert-1=%u;vert-2=%u;vert-3=%u}");
	static _pc_sz pc_sz_pat_r = _T("{vert-1=%u;vert-2=%u;vert-3=%u}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->m_mesh.Vertex1, this->m_mesh.Vertex2, this->m_mesh.Vertex3);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->m_mesh.Vertex1, this->m_mesh.Vertex2, this->m_mesh.Vertex3);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r, this->m_mesh.Vertex1, this->m_mesh.Vertex2, this->m_mesh.Vertex3);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TTriMesh&  CTriMesh::Raw (void) const { return this->m_mesh; }
TTriMesh&  CTriMesh::Raw (void)       { return this->m_mesh; }

/////////////////////////////////////////////////////////////////////////////

CTriMesh&  CTriMesh::operator = (const CTriMesh& _src) { *this << _src.Raw(); return *this; }
CTriMesh&  CTriMesh::operator = (CTriMesh&& _victim) { *this = (const CTriMesh&)_victim; return *this; }

CTriMesh&  CTriMesh::operator <<(const TTriMesh& _mesh) { this->Raw() = _mesh; return *this; }

/////////////////////////////////////////////////////////////////////////////

CVertex:: CVertex (void) : m_vertex{0} {}
CVertex:: CVertex (const CVertex& _src) : CVertex() { *this= _src; }
CVertex:: CVertex (CVertex&& _victim) : CVertex() { *this = _victim; }
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
CVertex&  CVertex::operator = (CVertex&& _victim) { *this = (const CVertex&)_victim; return *this; }

CVertex&  CVertex::operator <<(const t_point& _pt) { this->Point(_pt); return *this; }
CVertex&  CVertex::operator <<(const TVertex& _vertex) { this->Raw() = _vertex; return *this; }

CVertex::operator const TVertex& (void) const { return this->Raw(); }
CVertex::operator       TVertex& (void)       { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////
CShader:: CShader (const uint32_t _n_vert_count) {

	if (_n_vert_count && _n_vert_count < CShader::_n_vert_max + 1) {
		try {
			for (uint32_t i_ = 0; i_ < _n_vert_count; i_++) {
				this->Vertices().push_back(CVertex());
			}
		} catch (const ::std::bad_alloc&) {}
	}
}

#if defined(_DEBUG)
CString     CShader::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%svertices={%s%s%s}}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%svertices={%s%s%s}}");
	static _pc_sz pc_sz_pat_r = _T("%s%svertices={%s%s%s}");

	CString cs_vertices;

	for (size_t i_ = 0; i_ < this->Vertices().size(); i_++) {
		const CVertex& vertex = this->Vertices().at(i_);
	//	if (cs_vertices.IsEmpty() == false) {
			cs_vertices += _p_sfx;
			cs_vertices += _p_pfx;
	//	}
		cs_vertices += vertex.Print(e_print::e_req);
	}
	if (cs_vertices.IsEmpty()) {
		cs_vertices += _p_sfx;
		cs_vertices += _p_pfx;
		cs_vertices += _T("#not_set");
	}
	CString cs_out;
	
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			_p_sfx, _p_pfx, (_pc_sz)cs_vertices,
			_p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			_p_sfx, _p_pfx, (_pc_sz)cs_vertices,
			_p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r,
			_p_sfx, _p_pfx, (_pc_sz)cs_vertices,
			_p_sfx, _p_pfx);
	}
	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
TVertices   CShader::RawVertices (void) const {
	TVertices vertices;
	try {
		for (size_t i_ = 0; i_ < this->Vertices().size(); i_++) {
			const CVertex vertex = this->Vertices().at(i_);
			vertices.push_back(vertex);
		}
	} catch (const ::std::bad_alloc&) {}
	return vertices;
}
const
TVertexSet& CShader::Vertices (void) const { return this->m_vertices; }
TVertexSet& CShader::Vertices (void)       { return this->m_vertices; }

/////////////////////////////////////////////////////////////////////////////

using eMode_R = CRectShader::e_mode;

CRectShader:: CRectShader (void) : TBase(0), m_mode(e_mode::e_horz) {}
CRectShader::~CRectShader (void) {}

/////////////////////////////////////////////////////////////////////////////

void  CRectShader::Default(void) {
	
	if (this->Meshes().empty() == false) this->Meshes().clear();
	if (TBase::Vertices().empty() == false) TBase::Vertices().clear();

	try {
		TBase::Vertices().push_back(CVertex());
		TBase::Vertices().push_back(CVertex());

		this->Meshes().push_back(CRectMesh(0, 1));

	} catch (const ::std::bad_alloc&) {}

}

const
TRectMeshSet& CRectShader::Meshes (void) const { return this->m_meshes; }
TRectMeshSet& CRectShader::Meshes (void)       { return this->m_meshes; }

eMode_R CRectShader::Mode (void) const { return this->m_mode; }
bool    CRectShader::Mode (const e_mode _mode) {

	const bool b_changed = this->Mode() != _mode;
	if (b_changed)
		this->m_mode = _mode;

	return b_changed;
}

#if defined(_DEBUG)
CString CRectShader::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%smeshes={%s%s%s}%s;%s%smode=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%smeshes={%s%s%s}}");
	static _pc_sz pc_sz_pat_r = _T("{%s%smeshes={%s%s%s}}");

	CString cs_meshes;

	for (size_t i_ = 0; i_ < this->Meshes().size(); i_++) {
		const CRectMesh& mesh = this->Meshes().at(i_);
		if (cs_meshes.IsEmpty() == false) {
			cs_meshes += _p_sfx;
			cs_meshes += _p_pfx;
		}
		cs_meshes += mesh.Print(e_print::e_req);
	}
	if (cs_meshes.IsEmpty()) {
		cs_meshes += _p_sfx;
		cs_meshes += _p_pfx;
		cs_meshes += _T("#not_set");
	}

	CString cs_mode;
	if (e_mode::e_horz == this->Mode()) cs_mode = TStringEx().Format(_T("%d(horizontal)"), this->Mode());
	if (e_mode::e_vert == this->Mode()) cs_mode = TStringEx().Format(_T("%d(vertical)"), this->Mode());

	CString cs_vertices = TBase::Print(e_print::e_req);
	CString cs_out;
	
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			_p_sfx, _p_pfx, (_pc_sz)cs_meshes,
			_p_sfx, _p_pfx, (_pc_sz)cs_vertices,
			_p_sfx, _p_pfx, (_pc_sz)cs_mode);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			_p_sfx, _p_pfx, (_pc_sz)cs_meshes,
			_p_sfx, _p_pfx);
	}
	if (e_print::e_req == _e_opt) {
		cs_out.Format(pc_sz_pat_r,
			_p_sfx, _p_pfx, (_pc_sz)cs_meshes,
			_p_sfx, _p_pfx);
	}
	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

TRectMeshes   CRectShader::RawMeshes (void) const {
	TRectMeshes meshes;
	for (size_t i_ = 0; i_ < this->Meshes().size(); i_++) {
	}
	return meshes;
}

/////////////////////////////////////////////////////////////////////////////

using eMode_T = CTriShader::e_mode;

CTriShader:: CTriShader (void) : TBase(0), m_mode(e_mode::e_triangle) {}
CTriShader::~CTriShader (void) {}

/////////////////////////////////////////////////////////////////////////////

void  CTriShader::Default(void) {

	if (this->Meshes().empty() == false) this->Meshes().clear();
	if (TBase::Vertices().empty() == false) TBase::Vertices().clear();

	try {
		TBase::Vertices().push_back(CVertex());
		TBase::Vertices().push_back(CVertex());
		TBase::Vertices().push_back(CVertex());

		CTriMesh mesh;
		mesh.Raw().Vertex1 = 0;
		mesh.Raw().Vertex2 = 1;
		mesh.Raw().Vertex3 = 2;

		this->Meshes().push_back(mesh);

	} catch (const ::std::bad_alloc&) {}

}

const
TTriMeshSet& CTriShader::Meshes (void) const { return this->m_meshes; }
TTriMeshSet& CTriShader::Meshes (void)       { return this->m_meshes; }

eMode_T CTriShader::Mode (void) const { return this->m_mode; }
bool    CTriShader::Mode (const e_mode _mode) {

	const bool b_changed = this->Mode() != _mode;
	if (b_changed)
		this->m_mode = _mode;

	return b_changed;
}

TTriMeshes   CTriShader::RawMeshes (void) const {
	TTriMeshes meshes;
	for (size_t i_ = 0; i_ < this->Meshes().size(); i_++) {
	}
	return meshes;
}

/////////////////////////////////////////////////////////////////////////////

CRenderer:: CRenderer (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CRenderer::~CRenderer (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CRenderer::Error (void) const { return this->m_error; }

err_code CRenderer::Draw (const HDC _hdc, const CRectShader& _shader) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _hdc)
		return this->m_error << (err_code) TErrCodes::eObject::eHandle = _T("Input device context handle is invalid;");

	/*const*/ TRectMeshes meshes = _shader.RawMeshes();
	/*const*/ TVertices vertices = _shader.RawVertices();

	if (meshes.empty())
		return this->m_error << __e_inv_arg = _T("No meshes;");
	if (vertices.empty())
		return this->m_error << __e_inv_arg = _T("No vertex;");
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill ;
	if (!::GradientFill(
		_hdc, vertices.data(), (uint32_t)vertices.size(), meshes.data(), (uint32_t)meshes.size(), _shader.Mode()
	)) this->m_error.Last();

	return this->Error();
}

err_code CRenderer::Draw (const HDC _hdc, const CTriShader& _shader) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _hdc)
		return this->m_error << (err_code) TErrCodes::eObject::eHandle = _T("Input device context handle is invalid;");

	/*const*/ TTriMeshes meshes  = _shader.RawMeshes();
	/*const*/ TVertices vertices = _shader.RawVertices();

	if (meshes.empty())
		return this->m_error << __e_inv_arg = _T("No meshes;");
	if (vertices.empty())
		return this->m_error << __e_inv_arg = _T("No vertex;");
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill ;
	if (!::GradientFill(
		_hdc, vertices.data(), (uint32_t)vertices.size(), meshes.data(), (uint32_t)meshes.size(), _shader.Mode()
	)) this->m_error.Last();

	return this->Error();
}