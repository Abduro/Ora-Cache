/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Nov-2025 at 22:24:41.965, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' generic vertex data array interface implementation file; 
*/
#include "gl_vertex_arr.dat.h"
#include "gl_procs_vertex.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;

CVertex virt_vex;

using CBuffer = CVertArray::CBuffer;

CVertArray:: CVertArray (void) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
CVertArray::~CVertArray (void) {}

const
CBuffer&   CVertArray::Buffer (void) const { return this->m_buffer; }
CBuffer&   CVertArray::Buffer (void)       { return this->m_buffer; }

// https://stackoverflow.com/questions/17254425/getting-the-size-in-bytes-of-a-vector ;
uint32_t   CVertArray::Bytes (void) const {
	return static_cast<uint32_t>(sizeof(float) * static_cast<uint32_t>(this->m_data.size()));
}

uint32_t   CVertArray::Count (void) const { return static_cast<uint32_t>(this->m_items.size()); }
err_code   CVertArray::Count (const uint32_t _n_elems) {
	_n_elems;
	this->m_error <<__METHOD__<<__s_ok;

	try {
		if (0 == _n_elems && false == this->m_items.empty())
			this->m_items.clear();

		this->m_items.resize(_n_elems); this->m_items.reserve(_n_elems);

	} catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory; }

	return this->Error();
}

err_code   CVertArray::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false) {}
	else if (__failed(this->Buffer().Create())) { this->m_error = this->Buffer().Error(); }
//	else if (__failed(this->Buffer().Bind())) { this->m_error = this->Buffer().Error(); }

	return this->Error();
}

err_code   CVertArray::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Buffer().Delete())) { this->m_error = this->Buffer().Error(); }

	return this->Error();
}

const
CVertex&   CVertArray::Get (const uint32_t _u_ndx) const { if (_u_ndx < this->Count()) return this->m_items.at(_u_ndx); return ::virt_vex; }
CVertex&   CVertArray::Get (const uint32_t _u_ndx)       { if (_u_ndx < this->Count()) return this->m_items.at(_u_ndx); return ::virt_vex; }     

const
void*      CVertArray::Data_ptr (void) const { return this->m_data.data(); }
const TVertData& CVertArray::Data_ref (void) const { return this->m_data; }

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
TError&    CVertArray::Error (void) const { return this->m_error; }
const
TVertices& CVertArray::Items (void) const { return this->m_items; }
TVertices& CVertArray::Items (void)       { return this->m_items; }

bool  CVertArray::Is_valid (void) const {
	uint32_t u_req = 0;

	for (uint32_t i_ = 0; i_ < this->Count(); i_++)
		u_req += this->m_items.at(i_).Size();

	return static_cast<uint32_t>(this->m_data.size()) == u_req && u_req > 0;
}

err_code   CVertArray::Set (const uint32_t _prog_id) {
	_prog_id;
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < this->Count(); i_++) {
		CVertex& vex = this->Get(i_);
		if (__failed(vex.Attrs().ProgId(_prog_id))) {
			this->m_error = vex.Attrs().Error(); break;
		}
	}

	return this->Error();
}

err_code   CVertArray::Set_ptrs (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Items().empty()) {
		return this->m_error <<__e_not_inited = _T("#__e_inv_val: the vertex array has no items");
	}

	const vertex::CAttrArray& att_aray = this->Items().at(0).Attrs();

	for (uint32_t i_ = 0; i_ < att_aray.Count(); i_++) {
		const vertex::CAttr& attr = att_aray.Item(i_);
		if (false == attr.Is_used())
			continue;
#if defined(_DEBUG)
		const uint32_t u_locate = attr.Locate().Value(); u_locate;
		const uint32_t u_size   = attr.Size(); u_size;
		const uint32_t u_type   = attr.Type(); u_type;
		const bool b_normalized = attr.Is_normal(); b_normalized;
		const uint32_t u_stride = att_aray.Stride();
		const uint32_t u_offset = attr.Offset(); u_offset;
#endif
		if (__failed(__get_attr_ptr_procs().Set(attr.Locate().Value(), attr.Size(), attr.Type(), attr.Is_normal(), att_aray.Stride(), attr.Offset()))) {
			this->m_error = __get_attr_ptr_procs().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req)); break;
		}
		// each attribute must be enabled;
		if (__failed(::__get_attr_arr_procs().Enable(attr.Locate().Value()))) {
			this->m_error = ::__get_attr_arr_procs().Error(); break;
		}
	}

	return this->Error();
}

err_code   CVertArray::Set_ptrs (const vertex::CAttr& _attr, CError& _err) {
	_attr; _err;
	if (false == _attr.Is_valid()) return _err <<__e_inv_arg;
	if (false == _attr.Is_used()) return _err <<__e_inv_arg;

	if (__failed(__get_attr_ptr_procs().Set(_attr.Locate().Value(), _attr.Size(), _attr.Type(), _attr.Is_normal(), _attr.Stride(), _attr.Offset()))) {
	    _err = __get_attr_ptr_procs().Error();
	    __trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}

	return _err;
}

// https://stackoverflow.com/questions/644673/is-it-more-efficient-to-copy-a-vector-by-reserving-and-copying-or-by-creating-a ;
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

	TVertData::iterator p_target = this->m_data.begin() + 0;

	for (uint32_t i_ = 0; i_ < this->Count(); i_++) {

		CVertex& vex = this->Items().at(i_);

		if (__failed(vex.Update())) {
			this->m_error = vex.Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req)); break;
		}
		try {
			::std::copy(vex.Raw().begin() + 0,
			            vex.Raw().end()
			          /*vex.Raw().begin() + vex.Size()*/, p_target);
			if (this->Count() - 1 > i_)
				p_target += vex.Size();

		} catch (const ::std::bad_alloc& _err) {
			this->m_error <<__e_no_memory = CString(_err.what());
			__trace_err_2(_T("%s;\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req));
			break;
		}
	}

	return this->Error();
}

CVertArray& CVertArray::operator << (const uint32_t _prog_id) { this->Set(_prog_id); return *this; }