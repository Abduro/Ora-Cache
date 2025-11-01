/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 15:29:58.463, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D shape wrapper interface implementation file;
*/
#include "gl_shape.2d.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shapes;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_4 { void __warning_lnk_4221 (void) {} static CVertex vert_inv; }}}}
using namespace _impl_4;

CTriangle:: CTriangle (void) : CShape() { CString cs_cls = TString().Format(_T("%s::%s"), CShape::m_error.Class(), (_pc_sz)__CLASS__);
	CShape::m_error.Class(cs_cls, false);
}
CTriangle::~CTriangle (void) {}

const
CVertex&    CTriangle::A (void) const { return this->m_vertices[e_vertices::e_a]; }
CVertex&    CTriangle::A (void)       { return this->m_vertices[e_vertices::e_a]; }
const
CVertex&    CTriangle::B (void) const { return this->m_vertices[e_vertices::e_b]; }
CVertex&    CTriangle::B (void)       { return this->m_vertices[e_vertices::e_b]; }
const
CVertex&    CTriangle::C (void) const { return this->m_vertices[e_vertices::e_c]; }
CVertex&    CTriangle::C (void)       { return this->m_vertices[e_vertices::e_c]; }

const
CVertex&    CTriangle::Get (const e_vertices e_vert) const {
	e_vert;
	if (e_vertices::e_a == e_vert) return this->A();
	if (e_vertices::e_b == e_vert) return this->B();
	if (e_vertices::e_c == e_vert) return this->C();
	return _impl_4::vert_inv;
}
CVertex&    CTriangle::Get (const e_vertices e_vert) {
	e_vert;
	if (e_vertices::e_a == e_vert) return this->A();
	if (e_vertices::e_b == e_vert) return this->B();
	if (e_vertices::e_c == e_vert) return this->C();
	return _impl_4::vert_inv;
}

bool  CTriangle::Is_valid (void) const { return false == this->m_cache.empty(); }

const
void* const CTriangle::Cached (void) const {
	return this->m_cache.data();
}

// https://stackoverflow.com/questions/17254425/getting-the-size-in-bytes-of-a-vector ;
uint32_t    CTriangle::Size (void) const {
	return static_cast<uint32_t>(sizeof(float) * this->m_cache.size());
}

// https://stackoverflow.com/questions/644673/is-it-more-efficient-to-copy-a-vector-by-reserving-and-copying-or-by-creating-a ;

err_code    CTriangle::Update (void) {
	CShape::m_error <<__METHOD__<<__s_ok;

	uint32_t n_req_sz_max = 0;
	for (uint32_t i_ = 0; i_ < CShape::n_min_point_count; i_++) {
		if (this->m_vertices[i_].Size() > n_req_sz_max) n_req_sz_max = this->m_vertices[i_].Size();
	}
	if (0 == n_req_sz_max)
		return CShape::m_error <<__e_inv_arg = _T("There is not a single vertex with a predefined size");

	n_req_sz_max *= CShape::n_min_point_count;

	this->m_cache.reserve(n_req_sz_max);

	try {
		for (uint32_t i_ = 0; i_ < CShape::n_min_point_count; i_++)
			::std::copy(this->m_vertices[i_].Raw().begin(), this->m_vertices[i_].Raw().end(),
				::std::back_inserter(this->m_cache));
	}
	catch (const ::std::bad_alloc&) {
		CShape::m_error <<__e_no_memory = _T("The copying vertices' data to the cache failed");
	}

	return CShape::Error();
}