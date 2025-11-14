/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Nov-2025 at 22:24:41.965, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' generic vertex data array interface implementation file; 
*/
#include "gl_vertex_arr.dat.h"
#include "procs\gl_procs_vertex.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;

CVertArray:: CVertArray (void) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
CVertArray::~CVertArray (void) {}

uint32_t CVertArray::Count (void) const { return static_cast<uint32_t>(this->m_items.size()); }
err_code CVertArray::Count (const uint32_t _n_elems) {
	_n_elems;
	this->m_error <<__METHOD__<<__s_ok;

	try {
		if (0 == _n_elems && false == this->m_items.empty())
			this->m_items.clear();

		this->m_items.resize(_n_elems); this->m_items.reserve(_n_elems);

	} catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory; }

	return this->Error();
}

const
void*    CVertArray::GetData (void) const { return this->m_data.data(); }
#if (0)
uint32_t CVertArray::GetElements (void) const { return static_cast<uint32_t>(this->m_data.size()); }
err_code CVertArray::SetElements (const uint32_t _n_elements) {
	_n_elements;
	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	if (0 == _n_elements && false == this->m_data.empty())
		this->m_data.clear();
#endif
	try {
		this->m_data.reserve(_n_elements);
		this->m_data.assign(_n_elements, 0.0f);
	}
	catch (const ::std::length_error& _err) { this->m_error << __e_inv_arg = (_pc_sz) CString(_err.what()); }
	catch (const ::std::bad_alloc& _err) { this->m_error << __e_no_memory = (_pc_sz) CString(_err.what()); }

	return this->Error();
}
#endif
TError&  CVertArray::Error (void) const { return this->m_error; }
const
TVertices& CVertArray::Items (void) const { return this->m_items; }
TVertices& CVertArray::Items (void)       { return this->m_items; }
#if (0)
err_code CVertArray::Set_ptrs (const vertex::TRawAttrs& _attrs) {
	_attrs;
	this->m_error <<__METHOD__<<__s_ok;

	for (size_t i_ = 0; i_ < _attrs.size(); i_++) {
	}

	return this->Error();
}
#endif
err_code   CVertArray::Update (void) {
	this->m_error <<__METHOD__<<__s_ok;

	uint32_t u_req = 0;
	for (uint32_t i_ = 0; i_ < this->Count(); i_++)
		u_req += this->m_items.at(i_).Size();

	try {
		if (this->m_data.size() != u_req) {
			this->m_data.resize(u_req, 0.0f); this->m_data.reserve(u_req);
		}
	} catch (const ::std::bad_alloc& _err) { return this->m_error <<__e_no_memory = (_pc_sz) CString(_err.what()); }

	TVertData::iterator p_target = this->m_data.begin() + 1;

	for (uint32_t i_ = 0; i_ < this->Count(); i_++) {
		if (__failed(this->Items().at(i_).Update())) {
			this->m_error = this->Items().at(i_).Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req)); break;
		}
		try {
			::std::copy(this->Items().at(i_).Raw().begin() + 1,
			            this->Items().at(i_).Raw().begin() + 1 + this->Items().at(i_).Size(), p_target);
			p_target += this->Items().at(i_).Size();

		} catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory; break; }
	}

	return this->Error();
}