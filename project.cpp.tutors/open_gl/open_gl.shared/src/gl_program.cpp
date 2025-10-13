/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:48:34.237, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface implementation file;
*/
#include "gl_program.h"
#include "shared.preproc.h"
#include "shared.dbg.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	procs::program::CAttr& __get_attr_procs (void) {
		static procs::program::CAttr  procs;
		return procs;
	}

}}}}

using namespace ex_ui::draw::open_gl::_impl;

CAttr::CIndex:: CIndex (const CAttr& _attr_ref) : m_attr_ref(_attr_ref) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CAttr::CIndex::~CIndex (void) {}

TError& CAttr::CIndex::Error (void) const { return this->m_error; }

int32_t CAttr::CIndex::Get (void) const { return CAttr::CIndex::Get (this->m_attr_ref.ProgId(), this->m_attr_ref.Name(), this->m_error); }
int32_t CAttr::CIndex::Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr::CIndex::_$na;
	}

	const int32_t n_ndx = __get_attr_procs().GetIndex(_prog_id, _p_att_name);
	if (0 > n_ndx) {
		_err = __get_attr_procs().Error();
	}
	return n_ndx;
}

err_code CAttr::CIndex::Set (const uint32_t _u_ndx) { return CAttr::CIndex::Set(this->m_attr_ref.ProgId(), this->m_attr_ref.Name(), _u_ndx, this->m_error); }
err_code CAttr::CIndex::Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr::CIndex::_$na;
	}

	if (__failed(__get_attr_procs().SetIndex(_prog_id, _p_att_name, _u_ndx)))
		_err = __get_attr_procs().Error();
	return _err;
}

/////////////////////////////////////////////////////////////////////////////

CAttr:: CAttr (_pc_sz _p_name) : m_index(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; if (_p_name) *this << _p_name; }
CAttr::~CAttr (void) {}

TError&  CAttr::Error (void) const { return this->m_error; }
bool     CAttr::Is_valid (void) const { return false == this->m_name.IsEmpty(); }

const
CAttr::CIndex&  CAttr::Index (void) const { return this->m_index; }
CAttr::CIndex&  CAttr::Index (void)       { return this->m_index; }

_pc_sz   CAttr::Name (void) const { return (_pc_sz)this->m_name; }
err_code CAttr::Name (_pc_sz _p_name) {
	_p_name;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_name(_p_name); cs_name.Trim(); // trimming the input name and removing whitespaces in it look like to be unnecessary;
	if (cs_name.IsEmpty())
		return this->m_error <<__e_inv_arg = _T("An attribute name cannot be empty");
	
	if (this->m_name.Compare((_pc_sz)cs_name))
		this->m_name = cs_name;
	else
		this->m_error <<__s_false;

	return this->Error();
}

const
CProgId& CAttr::ProgId (void) const { return this->m_prog_id; }
CProgId& CAttr::ProgId (void)       { return this->m_prog_id; }

CAttr&  CAttr::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CAttr&  CAttr::operator <<(const CProgId& _prog_id) { this->ProgId() << _prog_id; return *this; }

/////////////////////////////////////////////////////////////////////////////

#define __gl_curr_prog 0x8B8D // GL_CURRENT_PROGRAM ;

CProgram:: CProgram (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProgram::~CProgram (void) { this->Delete(); }

procs::CProg& CProgram::Procs (void) {
	static procs::CProg m_fn_cache;
	return m_fn_cache;
}

CString   CProgram::Class (void) { return __CLASS__; }

TError&   CProgram::Error (void) const { return this->m_error; }

err_code  CProgram::Create (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (!!this->Id())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists = TString().Format(_T("Program object (id = %u) already exists"), this->Id().Get());

	procs::CProg& procs = CProgram::Procs();
	this->Id() << procs.Create();
	if (0 == this->Id()) {
		if (procs.Error().Is())
			this->m_error = procs.Error();
		program::CLog log;
		if (__failed(log.Set(0))) {} // if the program identifier equals to zero, there is no way to get the creation error details;
	}
	else
		this->Shaders() << this->Id(); // this is very *important*, otherwise no shader attachment will succeed;

	if (this->Error()) {
	      __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
	else {__trace_impt_2(_T("The program (id = %u) is created;\n"), this->Id().Get()); }

	return this->Error();
 }

err_code  CProgram::Delete (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (false == !!this->Id())
		return this->Error();  // returns __s_ok; there is nothing to destroy;
#if (0)
	CCache(this->Id()).Detach_all(); // it is supposed the shader(s) will be destroyed later than this program, so shader(s) must be detached first;
#endif
	procs::CProg& procs = CProgram::Procs();

	if (__failed(procs.Delete(this->Id())))
		return this->m_error = procs.Error();

	this->Id().Reset();
	return this->Error();
}

const
CProgId& CProgram::Id (void) const { return this->m_prog_id; }
CProgId& CProgram::Id (void)       { return this->m_prog_id; }

bool CProgram::Is_valid (void) const {
	return CProgram::Is_valid(this->Id(), this->m_error<<__METHOD__<<__s_ok);
}

bool CProgram::Is_valid (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	static _pc_sz p_sz_pat_err = _T("'_u_prog_id' (%u) is invalid");

	if (0 == _u_prog_id) {
		return false == (_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id)).Is();
	}
	procs::CParam param;

	const uint32_t n_curr_prog = param.GetInt(__gl_curr_prog); // if a negative result is returned, the input '_u_prog_id' will still be different;

	if (0 == n_curr_prog) {
		if (param.Error())
			return false == (_err = param.Error()).Is(); // Error.Is() returns 'true' in such case, thus 'false == true' is valid return result;
	}
	else if (_u_prog_id != n_curr_prog) {
		_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id);
	}

	return false == _err.Is();
}

err_code CProgram::Link (void) {
	this->m_error<<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_lnk = _T("The program (id=%u) is linked;\n");

	CStatus prog_status(this->Id());
	CLinker linker(this->Id());

	if ( __failed(linker.Link()) ) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) linker.Error().Print(TError::e_print::e_req)); this->m_error = linker.Error(); }
	else __trace_impt_2(pc_sz_pat_lnk, linker.ProgId());

	// just checks the program link status;
	const bool b_linked = prog_status.Is_linked();
	if ( prog_status.Error() ) {
		__trace_err_2(_T("%s\n"), (_pc_sz) prog_status.Error().Print(TError::e_print::e_req));}
	else {
		__trace_info_2(_T("Program (id=%u) link status is '%s';\n"), linker.ProgId(), TString().Bool(b_linked));
		if (false == b_linked) {
			program::CLog log;
			if (__failed( log.Set(this->Id()))) {
			    __trace_err_2(_T("%s\n"), (_pc_sz) log.Error().Print(TError::e_print::e_req)); }
			else {
				__trace_warn_2(_T("%s\n"), _T("Link log:"));
			    __trace_err(_T("%s"), log.Get());
			}
		}
	}
	return this->Error();
}

const
program::CCache& CProgram::Shaders (void) const { return this->m_shaders; }
program::CCache& CProgram::Shaders (void)       { return this->m_shaders; }

err_code CProgram::Validate (void) {
	this->m_error<<__METHOD__<<__s_ok;

	procs::CProg& procs = CProgram::Procs();

	if (__failed(procs.Validate(this->Id()))) {
	    __trace_err_2(_T("%s\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req));
		this->m_error = procs.Error();
	}
	else __trace_info_2(_T("Program (id=%u) is validated;\n"), this->Id().Get());
	return this->Error();
}

CProgram& CProgram::operator <<(const CProgId& _prog_id) { this->Id() << _prog_id; return *this; }