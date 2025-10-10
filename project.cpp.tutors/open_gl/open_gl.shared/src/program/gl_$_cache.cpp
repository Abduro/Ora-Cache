/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:50:53.142, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface implementation file;
*/
#include "gl_$_cache.h"
#include "gl_program.h"
#include "procs\gl_procs_prog.h"
#include "procs\gl_procs_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

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
CCache::~CCache (void) { this->Detach_all(); }

err_code  CCache::Attach (const uint32_t _u_shader_id) {
	return CCache::Attach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code  CCache::Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::program::CShaders procs;
	if (__failed( procs.Attach(_u_prog_id, _u_shader_id)))
		return _err = procs.Error();
	// ToDo: no error is expected, but in any case if the error occurs the shader was attached to the program and in this case the storage cannot be reliable;
	if (__failed(__get_stg().Insert(_u_prog_id, _u_shader_id))) 
		_err = __get_stg().Error();

	return _err;
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

	if (__failed(__get_stg().Remove(_u_prog_id, _u_shader_id)))
		_err = __get_stg().Error();

	return _err;
}
// https://community.khronos.org/t/correct-way-to-delete-shader-programs/69742 ;
// https://stackoverflow.com/questions/27937285/when-should-i-call-gldeletebuffers ;
err_code  CCache::Delete_all (void) {
	return CCache::Delete_all (this->ProgId(), this->m_error);
}

err_code  CCache::Delete_all (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (__failed(CCache::Detach_all(_u_prog_id, _err)))
		return _err;

	TRawCache::iterator prog = __get_stg().Prog(_u_prog_id);
	if (__get_stg().Error())
		return _err = __get_stg().Error();

	procs::CShader procs;

	TShaderIds& shaders = prog->second;

	for (TShaderIds::iterator it_ = shaders.begin(); it_ != shaders.end(); ++it_) {
		if (__failed(procs.Delete(*it_))) {
			_err = procs.Error(); break;
		}
	}

	return _err;
}

err_code  CCache::Detach_all (void) {
	return  CCache::Detach_all(this->ProgId(), this->m_error);
}

err_code  CCache::Detach_all (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	procs::program::CShaders procs;

#if (0)
	static const uint32_t u_max_count = 32; // Todo: the initial value must be explained;

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
 
TError&  CCache::Error (void) const { return this->m_error; }

uint32_t CCache::ProgId (void) const { return this->m_prog_id; }   
err_code CCache::ProgId (const uint32_t _prog_id) {
	_prog_id;
	if (0 == _prog_id) return this->m_error <<__e_inv_arg;
	this->m_prog_id = _prog_id;

	return this->Error();
}

CCache& CCache::operator <<(const uint32_t _prog_id) { this->ProgId(_prog_id); return *this; }

CCache&  CCache::operator +=(const uint32_t _u_shader_id) {
	this->Attach(_u_shader_id);
	return *this;
}

CCache&  CCache::operator -=(const uint32_t _u_shader_id) {
	this->Detach(_u_shader_id);
	return *this;
}