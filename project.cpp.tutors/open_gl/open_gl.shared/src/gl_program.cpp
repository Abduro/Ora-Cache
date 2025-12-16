/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:48:34.237, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface implementation file;
*/
#include "gl_program.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"
#include "procs\gl_procs_prog.h"

#include "shared.preproc.h"
#include "shared.dbg.h"
#include "sys.registry.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

using CAttrArr = CProgram::CAttrArr;

/////////////////////////////////////////////////////////////////////////////

#pragma region CProgram{}
#define __gl_curr_prog 0x8B8D // GL_CURRENT_PROGRAM ;

CProgram:: CProgram (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProgram::~CProgram (void) { this->Delete(); }

const
CAttrArr&  CProgram::Attrs (void) const { return this->m_attrs; }
CAttrArr&  CProgram::Attrs (void)       { return this->m_attrs; }

CString    CProgram::Class (void) { return __CLASS__; }

TError&    CProgram::Error (void) const { return this->m_error; }

err_code   CProgram::Create (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (!!this->Id())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists = TString().Format(_T("Program object (id = %u) already exists"), this->Id().Get());

	this->Id() << __get_prog_procs().Create();
	if (0 == this->Id()) {
		if (__get_prog_procs().Error().Is())
			this->m_error = __get_prog_procs().Error();
		program::CLog log;
		if (__failed(log.Set(0))) {} // if the program identifier equals to zero, there is no way to get the creation error details;
	}
	else {
		this->Attrs() << this->Id();
		this->Shaders() << this->Id(); // this is very *important*, otherwise no shader attachment will succeed;
		this->Status() << this->Id();
	}
	if (this->Error()) { // with no brackets : error C2181: illegal else without matching if ;
	      __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
	else {__trace_impt_2(_T("The program (id = %u) is created;\n"), this->Id().Get()); }

	return this->Error();
 }

err_code   CProgram::Delete (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (false == !!this->Id())
		return this->Error();  // returns __s_ok; there is nothing to destroy;
#if (0)
	CCache(this->Id()).Detach_all(); // it is supposed the shader(s) will be destroyed later than this program, so shader(s) must be detached first;
#endif

	if (__failed(__get_prog_procs().Delete(this->Id()))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) __get_prog_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = __get_prog_procs().Error();
	}
	else
		__trace_warn_2(_T("The program (id = %u) is deleted;\n"), this->Id().Get());
	// actually the reset the prog identifier to invalid value is not so important: the all dependent objects must be deleted first;
	this->Id().Reset();

	this->Attrs().ProgId(0u);         // reset on program identifier cannot be made by derect call because the all attributes must be updated;
	this->Shaders().ProgId().Reset(); // the prog_id reset can be made in the only case: deleting the program, so shaders must be deleted first;
	this->Status().ProgId().Reset();  // the program status set to be invalid and it doesn't much matter;

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
#if (0)
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
#else
	return CProgId::Is_valid(_u_prog_id, _err);
#endif
}

err_code CProgram::Link (void) {
	this->m_error<<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_lnk = _T("The program (id = %u) is linked;\n");

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
		__trace_info_2(_T("Program (id = %u) link status is '%s';\n"), linker.ProgId(), TString().Bool(b_linked));
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
const
program::CStatus& CProgram::Status (void) const { return this->m_status; }
program::CStatus& CProgram::Status (void)       { return this->m_status; }

 err_code CProgram::Use (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Status().Is_current()) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the program (id = %u) is already used"), this->Id()());
		return this->Error();
	}

	if (__failed(__get_prog_procs().Use(this->Id()())))
		this->m_error = __get_prog_procs().Error();
	else __trace_info_2(_T("Program (id = %u) is in use;\n"), this->Id().Get());

	return this->Error();
 }

err_code  CProgram::Validate (void) {
	this->m_error<<__METHOD__<<__s_ok;

	procs::CProg& procs = __get_prog_procs();

	if (__failed(procs.Validate(this->Id()))) {
	    __trace_err_2(_T("%s\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req));
		this->m_error = procs.Error();
	}
	else __trace_info_2(_T("Program (id = %u) is validated;\n"), this->Id().Get());
	return this->Error();
}

CProgram& CProgram::operator <<(const CProgId& _prog_id) { this->Id() << _prog_id; return *this; }

#pragma endregion

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	static CProgram inv_prog;

}}}}
using namespace _impl;

using CAttrs = CProg_enum::CAttrs;

CAttrs:: CAttrs (CProg_enum* _p_progs) : m_progs(_p_progs) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CAttrs::~CAttrs (void) {}

TError&  CAttrs::Error (void) const { return this->m_error; }

err_code CAttrs::Init (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == this->m_progs)
		return this->m_error <<__e_not_inited;

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CProgram& prog = this->m_progs->Ref(i_);
#if (1)
		prog.Attrs() << prog.Id(); // ToDo: it should be not necessary;
		if (__failed(prog.Attrs().Enum_attrs())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) prog.Attrs().Error().Print(TError::e_print::e_req));
		}
#else
		// this is predefined names of attributes;
		// enumerating of the attributes is not done yet;
		static _pc_sz attr_names[] = {_T("colorIn"), _T("positionIn")};

		// these attributes' names must be coincident with vertex shader source code, possibly a parsing of the code should give an ability to get them;
		if (__failed(prog.Attrs().Clr().Name(attr_names[0]))) /*return*/ this->m_error = prog.Attrs().Clr().Error();
		if (__failed(prog.Attrs().Pos().Name(attr_names[1]))) /*return*/ this->m_error = prog.Attrs().Pos().Error();
		// the error may be set by procedure of assigning the name to attribute, just output the error to trace log;
		if (this->Error()) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}
#endif
#if (0)
		/*important:
		  the attributes' indices are set through source code of vertex shader, the same is for vertex color, it can be set in fragment shader;
		  but these indices can be applied after program linking only; they can be received by querying the program object;
		  for this tutorial another way of vertex attribute location is selected:
		  the indices are set before linking the program, it is assumed the indices are the same as in shaders' source code;
		  after linking the program the indices are checked for test purpose that they are sill have the same values;
		*/
		// sets attributes' indecise (aka location) before linking the program,
		// an index of the particular attribute must be the same as in actual vertex: 0 - position; 1 - color;
		// also, it is very important: the shader source code can change the location of the attributes and after the program linking those locations will be applied;
		if (__failed(prog.Attrs().Clr().Locate().Set(1))) /*return*/ this->m_error = prog.Attrs().Clr().Error();
		if (__failed(prog.Attrs().Pos().Locate().Set(0))) /*return*/ this->m_error = prog.Attrs().Pos().Error();
		// the same as above, the error may be set by procedure of setting the index to attribute, just output the error to trace log;
		if (this->Error()) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}

		// checks vertex attributes' indices after linking the program and deleting the shaders;
		// the indices must be the same as them were set before the linking;

		const int32_t n_clr_ndx = prog.Attrs().Clr().Locate().Get();
		const int32_t n_pos_ndx = prog.Attrs().Pos().Locate().Get();

		if (prog.Attrs().Clr().Locate().Error()) this->m_error = prog.Attrs().Clr().Locate().Error(); else {__trace_info_2(_T("The attr '%s' has the index = %d;\n"), attr_names[0], n_clr_ndx); }
		if (prog.Attrs().Pos().Locate().Error()) this->m_error = prog.Attrs().Pos().Locate().Error(); else {__trace_info_2(_T("The attr '%s' has the index = %d;\n"), attr_names[1], n_pos_ndx); }
		// the error may be set by any attribute and the error of the first attribute may be overritten by the error of the last attriboute,
		// but it is not important for this time yet;
		if (this->Error()) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}
#endif
	}

	return this->Error();
}

CProg_enum:: CProg_enum (void) : m_attrs(this) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	m_progs[0].Target(e_object::e_grid);
	m_progs[1].Target(e_object::e_tria);
}
CProg_enum::~CProg_enum (void) {}

const
CAttrs&  CProg_enum::Attrs (void) const { return this->m_attrs; }
CAttrs&  CProg_enum::Attrs (void)       { return this->m_attrs; }

err_code CProg_enum::Build (void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CProgram& prog = this->Ref(i_);

		if (__failed(prog.Shaders().Compile())) {
			this->m_error = prog.Shaders().Error(); break;
		}
		if (__failed(prog.Shaders().Attach())) {
			this->m_error = prog.Shaders().Error(); break;
		}
		if (__failed(prog.Link())) {
			this->m_error = prog.Error(); break;
		}
		if (__succeeded(prog.Validate())) { // a possible error trace is made in the procedure being called;
		}
		else {
			this->m_error = prog.Error(); break;
		}
	}

	return this->Error();
}

err_code CProg_enum::Clear (void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CProgram& prog = this->Ref(i_);
		// https://stackoverflow.com/questions/9113154/proper-way-to-delete-glsl-shader ;
		if (false) {}
		else if (__failed(prog.Shaders().Detach())) this->m_error = prog.Shaders().Error(); // the error is output to trace by the shaders' cache;
		else if (__failed(prog.Shaders().Delete())) this->m_error = prog.Shaders().Error(); // the error is output to trace by the shaders' cache;
	}

	return this->Error();
}

err_code CProg_enum::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CProgram& prog = this->Ref(i_);
		if (__failed(prog.Create())) {
			this->m_error = prog.Error(); break;
		}
		if (__failed(prog.Shaders().Create())) {
			this->m_error = prog.Shaders().Error(); break;
		}
	}

	return this->Error();
}

err_code CProg_enum::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CProgram& prog = this->Ref(i_);
#if (0) // a buffer is not program attribute anymore;
		// it is not necessary to check a binding of the buffer, it makes itself, just unbind it;
		if (prog.Buffer().Is_bound()) {
			if (__failed(prog.Buffer().Unbind()))
				this->m_error = prog.Buffer().Error(); // no break on error; just continue;
		}
		if (__failed(prog.Buffer().Destroy())) {
			this->m_error = prog.Buffer().Error();     // no break on error; just continue;
		}
#endif
#if (0) // shaders must be deleted right after linking the program;
		if (__failed(prog.Shaders().Detach()))
			return this->m_error = prog.Shaders().Error();

		if (__failed(prog.Shaders().Delete()))
			return this->m_error = prog.Shaders().Error();
#endif
		if (__failed(prog.Delete()))
			this->m_error = prog.Error(); // no break on error; just continue;
	}

	return this->Error();
}

TError&  CProg_enum::Error (void) const { return this->m_error; }
const
CProgram&   CProg_enum::Get (const e_object _u_target) const {
	_u_target;
	if (e_object::e_grid == _u_target) return this->m_progs[0];
	if (e_object::e_tria == _u_target) return this->m_progs[1];
	return _impl::inv_prog;
}

CProgram&   CProg_enum::Get (const e_object _u_target) {
	_u_target;
	if (e_object::e_grid == _u_target) return this->m_progs[0];
	if (e_object::e_tria == _u_target) return this->m_progs[1];
	return _impl::inv_prog;
}

const
CProgram&   CProg_enum::GetActive (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	const uint32_t u_prog_id = program::CStatus::GetActiveProg(this->m_error);
	if (this->Error() || 0 == u_prog_id) {
		if (this->Error())
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return _impl::inv_prog; // there is no active program or the error occurs in procedure wrapper;
	}

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++)
		if (u_prog_id == this->Ref(i_).Id().Get())
			return this->Ref(i_);

	return _impl::inv_prog; // there is no active program from existing ones;
}

err_code    CProg_enum::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	// this array size must have the same value as programs' count: each program has the entries in registry for shaders' paths;
	static _pc_sz p_object[] = {_T("grid.1"), _T("triangle.1")};

	for (uint32_t i_ = 0; i_ < _countof(this->m_progs) && i_ < _countof(p_object); i_++) {
		CProgram& prog = this->m_progs[i_];
		if (__failed(prog.Shaders().Fragment().Src().Cfg().Path(p_object[i_], prog.Shaders().Fragment().Type().Get())))
		    __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Fragment().Src().Cfg().Error().Print(TError::e_print::e_req));
		if (__failed(prog.Shaders().Vertex().Src().Cfg().Path(p_object[i_], prog.Shaders().Vertex().Type().Get())))
	        __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Vertex().Src().Cfg().Error().Print(TError::e_print::e_req));

		if (__failed(prog.Shaders().Load())) {}
	}

	return this->Error();
}

const
CProgram& CProg_enum::Ref (const uint32_t _u_ndx) const { if (_countof(this->m_progs) > _u_ndx) return this->m_progs[_u_ndx]; else return _impl::inv_prog; }
CProgram& CProg_enum::Ref (const uint32_t _u_ndx)       { if (_countof(this->m_progs) > _u_ndx) return this->m_progs[_u_ndx]; else return _impl::inv_prog; }