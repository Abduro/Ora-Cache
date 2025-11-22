/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 12:23:26.137, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL vertex related functions' loader interface implementation file;
*/
#include "gl_procs_vertex.h"
#include "gl_procs.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs_prog.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::program;
using namespace ex_ui::draw::open_gl::procs::vertex;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	class CAtt_dat_type {
	public:
		CAtt_dat_type (void) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; } ~CAtt_dat_type(void) = default;
		CAtt_dat_type (const CAtt_dat_type&) = delete; CAtt_dat_type (CAtt_dat_type&&) = delete;

		TError& Error (void) const { return this->m_error; }

		static bool  Is_float (const uint32_t _u_type) {
			return (_i_to_f(e_att_val_float::e_double) == _u_type || _i_to_f(e_att_val_float::e_float) == _u_type ||
			        _i_to_f(e_att_val_float::e_float_16bits) == _u_type);
		}

		static bool  Is_int (const uint32_t _u_type) {
			return (_i_to_u(e_att_val_int::e_byte) == _u_type || _i_to_u(e_att_val_int::e_u_byte) == _u_type || _i_to_u(e_att_val_int::e_short) == _u_type ||
			        _i_to_u(e_att_val_int::e_u_short) == _u_type || _i_to_u(e_att_val_int::e_int) == _u_type || _i_to_u(e_att_val_int::e_u_int) == _u_type ||
			        _i_to_u(e_att_val_int::e_fixed) == _u_type);
		}

	private: CAtt_dat_type& operator = (const CAtt_dat_type&) = delete; CAtt_dat_type& operator = (CAtt_dat_type&&) = delete;
	private:
		mutable CError m_error;
	};
	#define GL_BGRA 0x80E1               // from glcorearb.h ;
	#define GL_MAX_VERTEX_ATTRIBS 0x8869 // from glcorearb.h ;
	#define __gl_bgra GL_BGRA

	class CInput_Args {
	public:
		CInput_Args (void) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; } ~CInput_Args (void) = default;
		CInput_Args (const CInput_Args&) = delete; CInput_Args (CInput_Args&&) = delete;

		TError& Check (const uint32_t _u_ndx) const {
			// GL_INVALID_VALUE : the index '_u_ndx' is greater than or equal to GL_MAX_VERTEX_ATTRIBS ;
			if (_u_ndx >= GL_MAX_VERTEX_ATTRIBS)
			     return this->m_error<<__METHOD__<<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_ndx' (%u) is invalid"), _u_ndx);
			else return this->m_error<<__METHOD__<<__s_ok;
		}

		TError& Check (const uint32_t _u_ndx, const uint32_t _u_size) const {
			if (__failed(this->Check(_u_ndx))) return this->Error();
			// GL_INVALID_VALUE : the size '_n_size' is not 1, 2, 3, 4 or (for glVertexAttribPointer), GL_BGRA ;
			if (1 != _u_size && 2 != _u_size && 3 != _u_size && 4 != _u_size && GL_BGRA != _u_size)
			     return this->m_error<<__METHOD__<<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_size' (%u) is invalid"), _u_size);
			else return this->m_error<<__METHOD__<<__s_ok;
		}

		TError& Check (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type) const {
			if (__failed(this->Check( _u_ndx, _u_size))) return this->Error();
			// GL_INVALID_ENUM  : tye type '_u_type' is not an accepted value ;
			if (false == CAtt_dat_type::Is_int(_u_type) && false == CAtt_dat_type::Is_float(_u_type))
			     return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_type: '_u_type' (%u) is not acceptable"), _u_type);
			else return this->m_error<<__METHOD__<<__s_ok;
		}

		TError& Check (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const int32_t _n_stride) const {
			if (__failed(this->Check( _u_ndx, _u_size, _u_type))) return this->Error();
			// GL_INVALID_VALUE : '_n_stride' is negative value ;
			if (0 > _n_stride)
			     return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_stride' (%d) cannot be negative"), _n_stride);
			else return this->m_error<<__METHOD__<<__s_ok;
		}

		TError& Error (void) const { return this->m_error; }

	private:
		CInput_Args& operator = (const CInput_Args&) = delete; CInput_Args& operator = (CInput_Args&&) = delete;
		mutable CError m_error;
	};

	class CErr_Handler {
	public:
		CErr_Handler (void) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; } ~CErr_Handler (void) = default;
		CErr_Handler (const CErr_Handler&) = delete; CErr_Handler (CErr_Handler&&) = delete;

		TError& Error (void) const { return this->m_error; }
		// this is temporary signature of this method, otherwise input argument value cannot be referenced to;
		TError& Catch (
			const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const bool _b_normalized, const int32_t _n_stride, const uint32_t _u_offset) const {
			_u_ndx; _u_size; _u_type; _b_normalized; _n_stride; _u_offset;
			/* https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
			Error codes that may be returned:
				GL_INVALID_OPERATION : the size is GL_BGRA and type is not GL_UNSIGNED_BYTE, GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV ;
				GL_INVALID_OPERATION : the type is GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV and size is not 4 or GL_BGRA ;
				GL_INVALID_OPERATION : the type is GL_UNSIGNED_INT_10F_11F_11F_REV and size is not 3 ;
				GL_INVALID_OPERATION : the size is GL_BGRA and normalized is GL_FALSE ;
				GL_INVALID_OPERATION : zero is bound to the GL_ARRAY_BUFFER buffer object binding point and the pointer argument is not NULL ;
			*/
			switch (CErr_ex().Get_code()) {
			case GL_INVALID_ENUM :
			case GL_INVALID_VALUE: {
					this->m_error = CInput_Args().Check(_u_ndx, _u_size, _u_type, _n_stride);
					if (this->Error())
						return this->Error();
				} break;
			case GL_INVALID_OPERATION: {
				bool b_not_compatible = false;
				if (false) {}
				else if (__gl_bgra == _u_size
					&& ((uint32_t)e_att_val_int::e_u_byte == _u_type
						|| (uint32_t)e_att_val_int::e_int_2_10_10_10 == _u_type || (uint32_t)e_att_val_int::e_uint_2_10_10_10 == _u_type))
					b_not_compatible = true;
				else if (__gl_bgra != _u_size && 4 != _u_size
					&& ((uint32_t)e_att_val_int::e_int_2_10_10_10 == _u_type || (uint32_t)e_att_val_int::e_uint_2_10_10_10 == _u_type))
					b_not_compatible = true;
				else if (3 != _u_size && (uint32_t)e_att_val_int::e_int_2_10_10_10 == _u_type)
					b_not_compatible = true;
				else if (__gl_bgra == _u_size && false == _b_normalized)
					this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_size' (%u) & '_b_normalized' (%s) are not compatible with each other"), _u_size, (_pc_sz) TString().Bool(_b_normalized));
				else {
					if (0 == _u_ndx && !!_u_offset)
					this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_ndx' (%u) & '_u_offset' (%u) are not compatible with each other"), _u_ndx, _u_offset);
				}

				if (b_not_compatible)
					this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_size' (%u) & '_u_type' (%u) are not compatible with each other"), _u_size, _u_type);
			} break;
			default:; // it looks like no error has occurred, at least the last error code has not been set to a value other than 0;
			}
			return this->m_error << __s_ok; // the error object is reset, due to for removing possible error state that is set in the previous call of this function;
		}

	private:
		CErr_Handler& operator = (const CErr_Handler&) = delete; CErr_Handler& operator = (CErr_Handler&&) = delete;
		mutable CError m_error;
	};

}}}}

using namespace ex_ui::draw::open_gl::_impl;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;
#define __gl_max_attrs 0x8869 // GL_MAX_VERTEX_ATTRIBS from glcorearb.h ;

static _pc_sz arr_fun_names[] = {
	_T("glBindVertexArray"), _T("glDeleteVertexArrays"), _T("glGenVertexArrays"), _T("glIsVertexArray")
};
enum class e_arr_fun_ndx : uint32_t {
	e_bind = 0x0, e_delete = 0x1, e_get_ids = 0x2, e_is_array = 0x3,
};

vertex::CArray:: CArray (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
err_code vertex::CArray::Bind (const uint32_t _arr_id) {
	_arr_id;
	// GL_INVALID_OPERATION : _arr_id is not zero or is the same with previously returned from a call to glGenVertexArrays ;
	CBase::m_error << __METHOD__ << __s_ok;
#if (0)
	if (0 == _arr_id) // zero (0) is used for unbind operation;
		return CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_arr_id' (%u) is not valid"), _arr_id);
#endif
	pfn_Binding p_fun = reinterpret_cast<pfn_Binding>(CBase::Get(arr_fun_names[(uint32_t)e_arr_fun_ndx::e_bind]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			procs::CParam procs;
			const int32_t n_result = procs.GetInt(__gl_arr_bound);
			if (procs.Error())
				return CBase::m_error = procs.Error();
			if (static_cast<int32_t>(_arr_id) == n_result)
				CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the array of '_arr_id' (%u) is already bound"), _arr_id);
			else
				CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("#__e_undef_exception: code is %d"), GL_INVALID_OPERATION);
		} break;
	default:;
	}
	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
err_code vertex::CArray::Delete (uint32_t _n_count, const uint32_t* _p_arrays) {
	_n_count; _p_arrays;
	// ToDo: what does it occur if _p_arrays equal to nullptr?
	// GL_INVALID_VALUE : _n_count is negative; it cannot occur because the '_n_count' data type is intentionally changed to 'unsigned';
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(arr_fun_names[(uint32_t)e_arr_fun_ndx::e_delete]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_arrays);
	// useless, but is saved for the implementation style only;
	switch (CErr_ex().Get_code()) {
	case GL_INVALID_VALUE: CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_count' has %u invalid value"), _n_count); break;
	default:;
	}
	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
err_code vertex::CArray::GetIds (const uint32_t _n_count, uint32_t* _p_ids) {
	_n_count; _p_ids;
	// GL_INVALID_VALUE is generated if _n_count is negative ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_GetIds p_fun = reinterpret_cast<pfn_GetIds>(CBase::Get(arr_fun_names[(uint32_t)e_arr_fun_ndx::e_get_ids]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_ids);
	// useless because the data type of the '_n_count' is intentionally changed to 'unsigned';
	switch(CErr_ex().Get_code()) {
	case GL_INVALID_VALUE : 
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_n_count' (%d) has negative value"), _n_count); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml ;
bool vertex::CArray::Is_array (const uint32_t _arr_id) {
	_arr_id;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (0 == _arr_id)
		return false == (CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_arr_id' (%u) is not valid"), _arr_id)).Is();

	pfn_IsArr p_fun = reinterpret_cast<pfn_IsArr>(CBase::Get(arr_fun_names[(uint32_t)e_arr_fun_ndx::e_is_array]));
	if (nullptr == p_fun) {
		return false;
	}

	int32_t n_result = p_fun(_arr_id);
	if (!!n_result)
		return true;
	// this function does not set the error code in case of its failure, but returns 'false' only;
	// it's necessary to check the array object of which '_arr_id' refers to, otherwise the input array identifier is not valid;
	procs::CParam procs;
	n_result = procs.GetInt(__gl_arr_bound); // https://community.khronos.org/t/get-the-currently-bound-vao/69025/2 ;
	if (procs.Error()) {
		CBase::m_error = procs.Error(); return false;
	}
	if (n_result != static_cast<int32_t>(_arr_id))
		CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the object '_arr_id' (%u) refers to is not bound"), _arr_id);
	
	return n_result == static_cast<int32_t>(_arr_id);
}

err_code vertex::CArray::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(arr_fun_names); i_++) {
		if (nullptr == CBase::Get(arr_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TVertArrProcs&  ::__get_arr_procs (void) {
	static TVertArrProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz attr_fun_names[] = {
	_T("glDisableVertexArrayAttrib"), _T("glEnableVertexArrayAttrib"), _T("glGetActiveAttrib"), _T("glGetAttribLocation"), _T("glBindAttribLocation")
};
enum class e_attr_fun_ndx : uint32_t {
	e_disable = 0x0, e_enable = 0x1, e_get_active = 0x2, e_get_ndx = 0x3, e_set_ndx = 0x4
};

vertex::CAttr:: CAttr (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// basically it's a copy of disabling the attribute array, but for this version of the implementation it's fine;
err_code vertex::CAttr::Disable (const uint32_t _arr_id, const uint32_t _u_ndx) {
	_arr_id; _u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Disable p_fun = reinterpret_cast<pfn_Disable>(CBase::Get(attr_fun_names[(uint32_t)e_attr_fun_ndx::e_disable]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id, _u_ndx);
	// the same check of error code is kept as it was made for disabling an attribute's array;
	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			procs::CParam procs;
			const int32_t n_result = procs.GetInt(__gl_arr_bound);
			if (procs.Error())
				return CBase::m_error = procs.Error();
			if (0 == n_result)
				CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the array of '_arr_id' (%u) is not bound"), _arr_id);
		} break;
	case GL_INVALID_VALUE : 
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_ndx' (%u) is beyond the max acceptable value"), _u_ndx); break;
	default:;
	}

	return CBase::Error();
}
// basically it's a copy of enabling the attribute array, but for this version of the implementation it's fine;
err_code vertex::CAttr::Enable (const uint32_t _arr_id, const uint32_t _u_ndx) {
	_arr_id; _u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Enable p_fun = reinterpret_cast<pfn_Enable>(CBase::Get(attr_fun_names[(uint32_t)e_attr_fun_ndx::e_enable]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id, _u_ndx);
	// the same check of error code is kept as it was made for enabling an attributes' array;
	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			procs::CParam procs;
			const int32_t n_result = procs.GetInt(__gl_arr_bound);
			if (procs.Error())
				return CBase::m_error = procs.Error();
			if (0 == n_result)
				CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the array of '_arr_id' (%u) is not bound"), _arr_id);
		} break;
	case GL_INVALID_VALUE : 
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_ndx' (%u) is beyond the max acceptable value"), _u_ndx); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveAttrib.xhtml ;
err_code CAttr::GetActive(const uint32_t _prog_id, const uint32_t _n_ndx, uint32_t& _u_size, uint32_t& _u_type, CString& _name) {
	_prog_id; _n_ndx; _u_size; _u_type;
	/* Possible error codes:
	GL_INVALID_OPERATION : '_prog_id' does not refer to program object;
	GL_INVALID_VALUE     : '_prog_id' is not a value generated by OpenGL;
	GL_INVALID_VALUE     : '_n_ndx' is greater than or equal to the number of active attribute variables in program;
	GL_INVALID_VALUE     : '_u_buf_size' is less than 0; by this possible error reason, the buffer data type is 'unsigned';
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	char sz_buffer[64] = {0}; // local buffer for getting the name of an attribute;
	uint32_t n_length  =  0 ; // this is the lenght of the attribute name, zero terminator is excluded from the returned value;

	pfn_Active p_fun = reinterpret_cast<pfn_Active>(CBase::Get(attr_fun_names[(uint32_t)e_attr_fun_ndx::e_get_active]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _n_ndx, sizeof(sz_buffer), &n_length, (int32_t*)&_u_size, &_u_type, sz_buffer);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION :
	case GL_INVALID_VALUE : {
		if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' cannot be 0"));
			else if (false == CProg().IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program"), _prog_id);
			else if (sizeof(sz_buffer) < 0) { /*this is impossible error case;*/}
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_n_ndx' (%u) is out of active vars number"), _n_ndx);
		} break;
	default:;
	}

	if (false == CBase::Error() && !!n_length) {
		_name = sz_buffer; // CString makes the conversion to unicode; it is assumed that this project is configured for using wchar_t;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
int32_t  CAttr::GetIndex (const uint32_t _prog_id, _pc_sz _p_att_name) {
	_prog_id; _p_att_name;
	/* Possible errors, the one error code is for several specific cases:
		GL_INVALID_OPERATION : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : the object of _prog_id is not a program object ;
		GL_INVALID_OPERATION : the program of _prog_id has not been successfully linked ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	static const int32_t n_err_result = -1; // the same value is used in CAttr::CIndex;

	int32_t n_result = n_err_result;

	pfn_GetIndex  p_fun = reinterpret_cast<pfn_GetIndex>(CBase::Get(attr_fun_names[(uint32_t)e_attr_fun_ndx::e_get_ndx]));
	if (nullptr == p_fun)
		return n_result;

	CStringA cs_name(_p_att_name);

	n_result = p_fun(_prog_id, cs_name.GetString());

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' cannot be 0"));
			else if (false == CProg().IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program"), _prog_id);
			else CBase::m_error << (err_code) TErrCodes::eExecute::eOperate = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) is not linked"), _prog_id);
		} break;
	default:;
	}
	return n_result;
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml ;
err_code CAttr::SetIndex (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx) {
	_prog_id; _p_att_name; _u_ndx;
	/* Possible error codes:
	GL_INVALID_VALUE     : '_u_ndx' is greater than or equal to GL_MAX_VERTEX_ATTRIBS;
	GL_INVALID_OPERATION : '_p_att_name' starts with the reserved prefix "gl_";
	GL_INVALID_VALUE     : '_prog_id' is not a value generated by OpenGL;
	GL_INVALID_OPERATION : '_prog_id' does not refer to a program object;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_SetIndex  p_fun = reinterpret_cast<pfn_SetIndex>(CBase::Get(attr_fun_names[(uint32_t)e_attr_fun_ndx::e_set_ndx]));
	if (nullptr == p_fun)
		return CBase::Error();

	CStringA cs_name(_p_att_name);

	p_fun(_prog_id, _u_ndx, cs_name.GetString());

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			if (false == CProg().IsProg(_prog_id)) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program"), _prog_id);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_p_att_name' (%s) is invalid"), _p_att_name);
		} break;
	case GL_INVALID_VALUE : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) has invalid value"), _prog_id);
			else if (GL_MAX_VERTEX_ATTRIBS <= _u_ndx) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_ndx' (%u) is out of range"), _u_ndx);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid"), _prog_id);
		} break;
	default:;
	};

	return CBase::Error();
}

err_code vertex::CAttr::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(attr_fun_names); i_++) {
		if (nullptr == CBase::Get(attr_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TVertAttrProcs&  ::__get_attr_procs (void) {
	static TVertAttrProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz attr_arr_fun_names[] = {
	_T("glDisableVertexAttribArray"), _T("glEnableVertexAttribArray")
};
enum class e_attr_arr_fun_ndx : uint32_t {
	e_disable = 0x2, e_enable = 0x3
};

CAttrArray::CAttrArray (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
err_code CAttrArray::Disable (const uint32_t _u_ndx) {
	_u_ndx;
	/* the error codes:
	GL_INVALID_OPERATION : no vertex array object is bound;
	GL_INVALID_OPERATION : '_u_ndx' does not refer to existing vertex array object;
	GL_INVALID_VALUE     : '_u_ndx' is greater than or equal to GL_MAX_VERTEX_ATTRIBS;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Disable p_fun = reinterpret_cast<pfn_Disable>(CBase::Get(attr_arr_fun_names[(uint32_t)e_attr_arr_fun_ndx::e_disable]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			procs::CParam procs;
			const int32_t n_result = procs.GetInt(__gl_arr_bound);
			if (procs.Error())
				return CBase::m_error = procs.Error();
			if (0 == n_result)
				CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the object by '_u_ndx' (%u) is not bound"), _u_ndx);
		} break;
	case GL_INVALID_VALUE : 
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_ndx' (%u) is beyond the max acceptable value"), _u_ndx); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
// ToDo: it is mostly the copy and paste, requires review this approach due to it is not good;
err_code CAttrArray::Enable (const uint32_t _u_ndx) {
	_u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Enable p_fun = reinterpret_cast<pfn_Enable>(CBase::Get(attr_arr_fun_names[(uint32_t)e_attr_arr_fun_ndx::e_enable]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : {
			procs::CParam procs;
			const int32_t n_result = procs.GetInt(__gl_arr_bound);
			if (procs.Error())
				return CBase::m_error = procs.Error();
			if (0 == n_result)
				CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the object by '_u_ndx' (%u) is not bound"), _u_ndx);
		} break;
	case GL_INVALID_VALUE : 
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_u_ndx' (%u) is beyond the max acceptable value"), _u_ndx); break;
	default:;
	}

	return CBase::Error();
}

err_code CAttrArray::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(attr_arr_fun_names); i_++) {
		if (nullptr == CBase::Get(attr_arr_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TAttrArrProcs&  ::__get_attr_arr_procs (void) {
	static TAttrArrProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz att_ptr_fun_names[] = {
	_T("glVertexAttribPointer"), _T("glVertexAttribIPointer"), _T("glVertexAttribLPointer")
};
enum class e_att_ptr_fun_ndx : uint32_t {
	e_set_uni = 0x0, e_set_int = 0x1, e_set_float = 0x2,
};

CAttrPtr:: CAttrPtr (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code CAttrPtr::Set (
	const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const bool _b_normalized, const uint32_t _u_stride, const uint32_t _u_offset){
	_u_ndx; _u_size; _u_type; _b_normalized; _u_stride; _u_offset;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr p_fun = reinterpret_cast<pfn_AttPtr>(CBase::Get(att_ptr_fun_names[(uint32_t)e_att_ptr_fun_ndx::e_set_uni]));
	if (nullptr == p_fun)
		return CBase::Error();

	CBase::m_error = CInput_Args().Check(_u_ndx, _u_size, _u_type, _u_stride);
	if (CBase::Error())
		return CBase::Error();

	p_fun(_u_ndx, (int32_t)_u_size, _u_type, int32_t(_b_normalized ? 1 : 0), _u_stride, (const void*)(const LONG_PTR)_u_offset);

	CBase::m_error = CErr_Handler().Catch(_u_ndx, _u_size, _u_type, _b_normalized, _u_stride, _u_offset);

	return CBase::Error();
}

err_code CAttrPtr::Set_I (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset) {
	_u_ndx; _u_size; _u_type; _u_stride; _u_offset;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr_I p_fun = reinterpret_cast<pfn_AttPtr_I>(CBase::Get(att_ptr_fun_names[(uint32_t)e_att_ptr_fun_ndx::e_set_int]));
	if (nullptr == p_fun)
		return CBase::Error();

	if (false == CAtt_dat_type::Is_int(_u_type)) // it will be called again in CInput_Args::Check(...) but it is not important for now;
		return CBase::m_error << __e_inv_arg = TString().Format(_T("#__err_dat_type: '_u_type' (%u) is not integer data type"), _u_type);

	CBase::m_error = CInput_Args().Check(_u_ndx, _u_size, _u_type, _u_stride);
	if (CBase::Error())
		return CBase::Error();

	p_fun(_u_ndx, (int32_t)_u_size, _u_type, _u_stride, (const void*)(const LONG_PTR)_u_offset);

	CBase::m_error = CErr_Handler().Catch(_u_ndx, _u_size, _u_type, false, _u_stride, _u_offset);

	return CBase::Error();
}

err_code CAttrPtr::Set_L (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset) {
	_u_ndx; _u_size; _u_type; _u_stride; _u_offset;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr_L p_fun = reinterpret_cast<pfn_AttPtr_L>(CBase::Get(att_ptr_fun_names[(uint32_t)e_att_ptr_fun_ndx::e_set_float]));
	if (nullptr == p_fun)
		return CBase::Error();

	if (false == CAtt_dat_type::Is_float(_u_type)) // it will be called again in CInput_Args::Check(...) but it is not important for now;
		return CBase::m_error << __e_inv_arg = TString().Format(_T("#__err_dat_type: '_u_type' (%u) is not float data type"), _u_type);

	CBase::m_error = CInput_Args().Check(_u_ndx, _u_size, _u_type, _u_stride);
	if (CBase::Error())
		return CBase::Error();

	p_fun(_u_ndx, (int32_t)_u_size, _u_type, _u_stride, (const void*)(const LONG_PTR)_u_offset);

	CBase::m_error = CErr_Handler().Catch(_u_ndx, _u_size, _u_type, false, _u_stride, _u_offset);

	return CBase::Error();
}

err_code vertex::CAttrPtr::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(att_ptr_fun_names); i_++) {
		if (nullptr == CBase::Get(att_ptr_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TVertAttrPtrProcs&  ::__get_attr_ptr_procs (void) {
	static TVertAttrPtrProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}