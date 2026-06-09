/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:50:53.142, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface implementation file;
*/
#include "gl_$_cache.h"
#include "gl_program.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "shader\gl_compiler.h"
#include "shader\gl_shd_type.h"

#include "gl_procs_prog.h"
#include "gl_procs_shader.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

#define __gl_shader_type 0x8B4F

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	typedef ::std::map<uint32_t, TShaderIds> TRawCache;

	class CStorage {
	public:
		CStorage (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; } CStorage (const CStorage&) = delete; CStorage (CStorage&&) = delete; ~CStorage (void) {}

		TError& Error (void) const { return this->m_error; }

		TRawCache::const_iterator Prog (const uint32_t _prog_id) const {
			return this->m_cached.find(_prog_id);
		}
		TRawCache::iterator Prog (const uint32_t _prog_id) {
			return this->m_cached.find(_prog_id);
		}

		TShaderIds::const_iterator Shader (TRawCache::const_iterator _prog, const uint32_t _shader_id) const {
			if (this->m_cached.end() == _prog)
				return this->m_shader.end();
			else
				return _prog->second.find(_shader_id);
		}
		TShaderIds::iterator Shader (TRawCache::iterator _prog, const uint32_t _shader_id) {
			if (this->m_cached.end() == _prog)
				return this->m_shader.end();
			else
				return _prog->second.find(_shader_id);
		}

		bool Has (const uint32_t _prog_id) const { return this->m_cached.end() != this->m_cached.find(_prog_id); }
		bool Has (const uint32_t _prog_id, const uint32_t _shader_id) const {
			_prog_id; _shader_id;
			TRawCache::const_iterator prog = this->m_cached.find(_prog_id);
			if (this->m_cached.end() == prog)
				return false;
			TShaderIds::const_iterator shader = prog->second.find(_shader_id);
			return prog->second.end() != shader;
		}

		err_code Insert (const uint32_t _prog_id, const uint32_t _shader_id) {
			_prog_id; _shader_id;
			this->m_error <<__METHOD__<<__s_ok;

			if (0 == _prog_id)
				return this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_prog_id' (%u) is invalid"), _prog_id);

			if (0 == _shader_id)
				return this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_shader_id' (%u) is invalid"), _shader_id);

			TRawCache::iterator prog = this->m_cached.find(_prog_id);
			if (this->m_cached.end() == prog) { // it's necessary to create new element of the program;
				try {
					this->m_cached.insert(::std::make_pair(_prog_id, ::std::set<uint32_t>{_shader_id}));
				} catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory = TString().Format(_T("#__e_no_mem: insert of '_prog_id' (%u) for '_shader_id' (%u) failed"), _prog_id, _shader_id); }
			}
			else {
				try {
					prog->second.insert(_shader_id); // no check for the existance of the element in this set: the element is just being replaced;
				} catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory = TString().Format(_T("#__e_no_mem: insert '_shader_id' (%u) to '_prog_id' (%u) failed"), _shader_id, _prog_id); }
			}
			return this->Error();
		}

		err_code Remove (const uint32_t _prog_id, const uint32_t _shader_id) {
			_prog_id; _shader_id;
			this->m_error <<__METHOD__<<__s_ok;
			TRawCache::iterator prog = this->m_cached.find(_prog_id);
			if (this->m_cached.end() == prog)
				return this->m_error << (err_code) TErrCodes::eData::eNotFound = TString().Format(_T("'_prog_id' (%u) not found"), _prog_id);
			TShaderIds::iterator shader = prog->second.find(_shader_id);
			if (prog->second.end() == shader)
				return this->m_error << (err_code) TErrCodes::eData::eNotFound = TString().Format(_T("'_shader_id' (%u) not found"), _shader_id);

			prog->second.erase(shader);
 
			if (prog->second.empty())
				this->m_cached.erase(prog); // possibly it is not required and cached element of the program would be used later;

			return this->Error();
		}

		const
		TRawCache& Cached (void) const { return this->m_cached; }
		TRawCache& Cached (void)       { return this->m_cached; }

		const
		TRawCache& operator () (void) const { return this->Cached(); }
		TRawCache& operator () (void)       { return this->Cached(); }

	private:
		CStorage& operator = (const CStorage&) = delete; CStorage& operator = (CStorage&&) = delete;
		mutable CError m_error;
		TRawCache   m_cached;
		TShaderIds  m_shader; // the empty shader used for returning 'nothing' from find methods;
	};

	CStorage& __get_stg (void) {
		static CStorage stg;
		return stg;
	}
}}}}
using namespace ex_ui::draw::open_gl::_impl;

CCache:: CCache (const uint32_t _prog_id) : m_prog_id(0) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; if (!!_prog_id) *this<<_prog_id; }
CCache::~CCache (void) { /*this->Detach_all();*/ }

err_code CCache::Attach (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (0 == this->ProgId()) {
		this->m_error << (err_code)TErrCodes::eExecute::eState = _T("Program ID is not set");
		__trace_err_2(_T("%s\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	static _pc_sz pc_sz_pat_att = _T("Program (id = %u) attaches '%s' shader (id = %u);\n");

	CShader* shaders[] = { &this->Fragment(), &this->Vertex() };

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
	if ( __failed(this->Attach(shaders[i_]->Id())) ) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) shaders[i_]->Error().Print(TError::e_print::e_req)); }
	else __trace_impt_2(pc_sz_pat_att, this->ProgId().Get(), (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id());
	}

	return this->Error();
}

err_code CCache::Attach (const uint32_t _u_shader_id) {
	return CCache::Attach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code CCache::Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::program::CShaders procs;
	if (__failed( procs.Attach(_u_prog_id, _u_shader_id)))
		return _err = procs.Error();
#if (0)
	// ToDo: no error is expected, but in any case if the error occurs the shader was attached to the program and in this case the storage cannot be reliable;
	if (__failed(__get_stg().Insert(_u_prog_id, _u_shader_id))) 
		_err = __get_stg().Error();
#endif
	return _err;
}

err_code CCache::Attached (::std::vector<$Type>& _types) const {
	this->m_error <<__METHOD__<<__s_ok;
	return CCache::Attached(this->ProgId(), _types, this->m_error);
}

err_code CCache::Attached (const uint32_t _prog_id, ::std::vector<$Type>& _v_types, CError& _err) {
	_prog_id; _v_types; _err;

	static const uint32_t u_max_count = 32; // it is assumed max number of attached shaders is not grater than 32; if necessary it can be increased;

	uint32_t shader_ids[u_max_count] = {0};
	uint32_t u_count = 0;

	if (false == _v_types.empty())
		_v_types.clear();

	if (__failed(__get_$_bind_procs().Attached(_prog_id, u_max_count, &u_count, shader_ids)))
		return _err = __get_$_bind_procs().Error();

	for (uint32_t i_ = 0; i_ < u_count; i_++) {

		int32_t n_type = 0;
		err_code err_ = __get_$_procs().Params(shader_ids[i_], __gl_shader_type, &n_type);

		if (__failed(err_)) {
			_err = __get_$_procs().Error(); break;
		}
		try {
			_v_types.push_back(($Type)n_type); // doesn't care about proper conversion unsigned int to enum element this time;
		}
		catch (const ::std::bad_alloc&) { _err <<__e_no_memory; break; }
	}

	return _err;
}

err_code CCache::Compile (void) {
	this->m_error <<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_cmpl = _T("Source code of '%s' shader (id = %u) is compiled;\n");
	static _pc_sz pc_sz_pat_stat = _T("Shader '%s' (id = %u) compiled status: '%s';\n");

	shader::CCompiler cmpl;
	shader::CStatus $_status;
	// error C2234: 'shaders': arrays of references are illegal ;
	CShader* shaders[] = { &this->Vertex(), &this->Fragment() };

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
		if (shaders[i_]->Error()().Is())
			continue;
		cmpl << shaders[i_]->Id();
		if (__failed(cmpl.Compile())) { // there is no need to check compilation status of the shader source code if error already occurs;
			__trace_err_2(_T("%s\n"), (_pc_sz)cmpl.Error().Print(TError::e_print::e_req));
			__trace_warn_2(pc_sz_pat_stat, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id(), TString().Bool(false));
			continue;
		}
		else {
			__trace_info_2(pc_sz_pat_cmpl, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id()); // the compiler works;
			// checks the compile status of the shader;
			$_status << shaders[i_]->Id();
			const bool b_compiled = $_status.Is_compiled();
			if ($_status.Error()) { // the error can occur in one of the procedure wrappers;
				__trace_err_2(_T("%s\n"), (_pc_sz) $_status.Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(pc_sz_pat_stat, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id(), TString().Bool(b_compiled));
			}
		}
	}
	return this->Error();
}

err_code CCache::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CShader* shaders[] = { &this->Fragment(), &this->Vertex() };

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
		if (__failed(shaders[i_]->Create(shaders[i_]->Type().Get()))) {
			this->m_error = shaders[i_]->Error(); break;
		}
	}

	return this->Error();
}

err_code CCache::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_del = _T("'%s' shader (id = %u) is deleted;\n");

	CShader* shaders[] = { &this->Fragment(), &this->Vertex() };

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
#if (0)
		if (__succeeded(this->Delete(shaders[i_]->Id()))) // the error is caught by Delete(_u_shader_id) ;
		   __trace_warn_2(pc_sz_pat_del, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id());
#else
		if (__failed(shaders[i_]->Delete())) {
			this->m_error = shaders[i_]->Error(); // the shader Delete() operation does not output the error to trace;
			__trace_err_2(_T("%s\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req));
		}
#endif
	}

	return this->Error();
}
#if (0)
err_code CCache::Delete (const uint32_t _u_shader_id) {
	return CCache::Delete(_u_shader_id, this->m_error);
}
// https://community.khronos.org/t/correct-way-to-delete-shader-programs/69742 ;
// https://stackoverflow.com/questions/27937285/when-should-i-call-gldeletebuffers ;
err_code CCache::Delete (const uint32_t _u_shader_id, CError& _err) {
	_u_shader_id; _err;

	if (0 == _u_shader_id) {
		_err << __e_inv_arg = _T("'_u_shader_id' is zero (0)");
		__trace_err_2(_T("%s\n"), (_pc_sz)_err.Print(TError::e_print::e_req));
		return _err;
	}

	procs::CShader procs;
	
	if (__failed(procs.Delete(_u_shader_id))) {
		_err = procs.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)_err.Print(TError::e_print::e_req));
	}
	return _err;
}
#endif
err_code CCache::Detach (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (0 == this->ProgId()) {
		this->m_error << (err_code)TErrCodes::eExecute::eState = _T("Program ID is not set");
		__trace_err_2(_T("%s\n"), (_pc_sz)this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	static _pc_sz pc_sz_pat_att = _T("'%s' shader (id = %u) is detached from program (id = %u);\n");

	CShader* shaders[] = { &this->Fragment(), &this->Vertex() };

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
	if ( __failed(this->Detach(shaders[i_]->Id()))) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
	else __trace_warn_2(pc_sz_pat_att, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id(), this->ProgId().Get());
	}
	return this->Error();
}
// https://stackoverflow.com/questions/18736773/why-it-is-necessary-to-detach-and-delete-shaders-after-creating-them-on-opengl ;
err_code CCache::Detach (const uint32_t _u_shader_id) {
	return CCache::Detach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code CCache::Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::program::CShaders procs;
	if (__failed( procs.Detach(_u_prog_id, _u_shader_id)))
		return _err = procs.Error();
#if (0)
	if (__failed(__get_stg().Remove(_u_prog_id, _u_shader_id)))
		_err = __get_stg().Error();
#endif
	return _err;
}

#if (0)
err_code  CCache::Detach_all (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	procs::program::CShaders procs;

#if (0)
	static const uint32_t u_max_count = 32; // it is assumed max number of attached shaders is not grater than 32; if necessary it will be increased;

	uint32_t shader_ids[u_max_count] = {0};
	uint32_t u_count = 0;

	if (__failed(procs.Attached(_u_prog_id, u_max_count, &u_count, shader_ids)))
		return _err = procs.Error();

	for (uint32_t i_ = 0; i_ < u_count && i_ < u_max_count; i_++) {
		if (__failed(procs.Detach(_u_prog_id, shader_ids[i_]))) {
			_err = procs.Error(); break;
		}
	}
#else // it is supposed the cache works as expected: without errors in 'insert' and 'remove' operations; https://langeek.co/en/grammar/course/1821/suppose-vs-assume ;
	TRawCache::iterator prog = __get_stg().Prog(_u_prog_id);
	if (__get_stg().Error())
		return _err = __get_stg().Error();

	TShaderIds& shaders = prog->second;

	for (TShaderIds::iterator it_ = shaders.begin(); it_ != shaders.end(); ++it_) {
		if (__failed(procs.Detach(_u_prog_id, *it_))) {
			_err = procs.Error(); break;
		}
	}
#endif
	return _err;
}
#endif
const
shader::CFragment& CCache::Fragment (void) const { return this->m_$_frag; }
shader::CFragment& CCache::Fragment (void)       { return this->m_$_frag; }

TError&  CCache::Error (void) const { return this->m_error; }

err_code CCache::Load  (void) {
	this->m_error <<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_src = _T("Load source code to '%s' shader (id = %u) succeeded;\n");

	CShader* shaders[] = { &this->Fragment(), &this->Vertex()};

	for (uint32_t i_ = 0; i_ < _countof(shaders); i_++) {
		if (__failed(shaders[i_]->Src().Set())) {
			this->m_error = shaders[i_]->Src().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz) shaders[i_]->Src().Error().Print(TError::e_print::e_req));
		}
		else
			__trace_info_2(pc_sz_pat_src, (_pc_sz) shader::CType::To_str (shaders[i_]->Type()), shaders[i_]->Id());
	}
	return this->Error();
}

const
CProgId& CCache::ProgId (void) const { return this->m_prog_id; }
CProgId& CCache::ProgId (void)       { return this->m_prog_id; }
const
shader::CVertex& CCache::Vertex (void) const { return this->m_$_vert; }
shader::CVertex& CCache::Vertex (void)       { return this->m_$_vert; }

CCache& CCache::operator <<(const CProgId& _prog_id) { this->ProgId() << _prog_id; return *this; }

#if (0)
CCache&  CCache::operator +=(const uint32_t _u_shader_id) {
	this->Attach(_u_shader_id);
	return *this;
}

CCache&  CCache::operator -=(const uint32_t _u_shader_id) {
	this->Detach(_u_shader_id);
	return *this;
}
#endif