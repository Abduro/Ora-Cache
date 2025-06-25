/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2023 at 12:13:57.5818053, UTC+7, Novosibirsk, Monday;
	This is Process Prying Eyes project system process interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack system shell lib project on 25-06-2025 on 15:39:45.225, UTC+4, Batumi;
*/
#include "sys.procs.list.h"

using namespace shared::sys_core::shell;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace shell { namespace _impl {

}}}}
using namespace shared::sys_core::shell::_impl;
/////////////////////////////////////////////////////////////////////////////

CProcess:: CProcess (void) : m_id(0) {}
CProcess:: CProcess (const CProcess& _ref) : CProcess() { *this = _ref; }
CProcess:: CProcess (CProcess&& _victim) : CProcess() { *this = _victim; }
CProcess::~CProcess (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TCertInfo& CProcess::Cert (void) const { return this->m_cert; }
dword      CProcess::Id   (void) const { return this->m_id; }
bool       CProcess::Is   (void) const { return this->Id() > 0 /*&& CGenericPath(this->Path()).Exists()*/; }
_pc_sz     CProcess::Name (void) const { return this->m_name.GetString(); }
_pc_sz     CProcess::Path (void) const { return this->m_path.GetString(); }

#if defined(_DEBUG)
CString    CProcess::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {id=%u;name=%s;path=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {id=%u;name=%s;path=%s}");
	static _pc_sz pc_sz_pat_r = _T("{id=%u;name=%s;path=%s}");

	CString cs_name = this->m_name.IsEmpty() ? _T("#undef") : this->Name();
	CString cs_path = this->m_path.IsEmpty() ? _T("#undef") : this->Path();

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) cs_name, (_pc_sz) cs_path);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) cs_name, (_pc_sz) cs_path);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_a,
		this->Id(), (_pc_sz) cs_name, (_pc_sz) cs_path);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

const
TModules&  CProcess::Modules (void) const { return this->m_dlls; }
TModules&  CProcess::Modules (void)       { return this->m_dlls; }

/////////////////////////////////////////////////////////////////////////////

CProcess&  CProcess::operator = (const CProcess& _ref) { *this << _ref.Id() << _ref.Name() >> _ref.Path() << _ref.Cert() << _ref.Modules(); return *this; }

CProcess&  CProcess::operator <<(const TCertInfo& _cert) { this->m_cert = _cert; return *this; }
CProcess&  CProcess::operator <<(dword _id) { this->m_id = _id; return *this; }

CProcess&  CProcess::operator <<(_pc_sz _name) { this->m_name = _name; return *this; }
CProcess&  CProcess::operator >>(_pc_sz _path) { this->m_path = _path; return *this; }

CProcess&  CProcess::operator <<(const TModules& _dlls) { this->Modules() = _dlls; return *this; }

/////////////////////////////////////////////////////////////////////////////

CProcess_List:: CProcess_List (void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProcess_List:: CProcess_List (const CProcess_List& _ref) : CProcess_List() { *this = _ref; }
CProcess_List::~CProcess_List (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CProcess_List::Error (void) const { return this->m_error; }

err_code CProcess_List::Get_It(void) {

	m_error << __METHOD__ << __s_ok;

	if (m_procs.empty() == false)
		m_procs.clear();

#define dw_how_many_procs (1024)

	dword dw_proc_ids[dw_how_many_procs] = {0};
	dword dw_proc_req = 0;
	dword dw_proc_got = 0;

	// https://learn.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes ;
	// https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocesses;
	if (false == !!::EnumProcesses(dw_proc_ids, sizeof(dw_proc_ids), &dw_proc_req))
		return this->m_error.Last();
#if (0)
	// gets a list of all available devices ;
	// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-querydosdevicew ;
	dword d_size = 1024;
	TRawData raw_data;
	while (true)
	{
		if (__s_ok != raw_data.Append(nullptr, d_size * sizeof(t_char))) {
			this->m_error = raw_data.Error(); break;
		}
		dword d_copied = ::QueryDosDevice(nullptr, (t_char*)raw_data.GetData(), raw_data.GetSize() / sizeof(t_char));
		if ( d_copied == 0) {
			m_error.Last();
			if (ERROR_INSUFFICIENT_BUFFER != m_error.Get())
				break;
			d_size *= 2;
		}
		else
			break;
	}
	if (false == (bool)m_error) {
		::std::vector<string_t> volumes = shared::sys_core::_split((LPTSTR)raw_data.GetData(), _T('\0'));
	}
#endif
	dw_proc_got = dw_proc_req / sizeof (DWORD);

	for (dword i_ = 0; i_ < dw_proc_got; i_++) {
		if (0 != dw_proc_ids[i_]) {
			// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess ;
			CAutoHandle h_proc; h_proc.Attach(::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dw_proc_ids[i_]));
			if (false == h_proc.Is()) {
				m_error.Last();
				continue;
			}

			HMODULE h_module = nullptr;
			dword dw_require = 0; // *attention*: value in bytes ;
			// https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocessmodules ; this function is for 32-bit app;
			// https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocessmodulesex ; this function is for 64-bit app;
			if (false == !!::EnumProcessModulesEx(h_proc, &h_module, sizeof(h_module), &dw_require, 0))
				continue;
#if (0)
			dw_require /= sizeof(HMODULE);

			HMODULE* p_modules = nullptr;
			try {
				p_modules = new HMODULE[dw_require];
			}
			catch (const ::std::bad_alloc&)
			{ continue; }

			if (false == !!::EnumProcessModules(h_proc, p_modules, dw_require, &dw_require))
			{
				delete p_modules; p_modules = nullptr;
				continue;
			}
#endif
			::std::vector<CString> v_mod_paths;
#if (0)
			for (size_t j_ = 0; j_ < dw_require / sizeof(HMODULE); j_++) {

				t_char mod_path[_MAX_PATH] = {0};
				dword  d_qry_size = _countof(mod_path);
				// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew ;
				if (false == !!::GetModuleFileNameEx(h_proc, p_modules[j_], mod_path, _countof(mod_path)) &&
					// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-queryfullprocessimagenamea
					false == !!::QueryFullProcessImageName(h_proc, 0, mod_path, &d_qry_size)) {
						m_error.Last();
						continue;
				}
				else {
					v_mod_paths.push_back(string_t(mod_path));
				}
				// suspended processes;
				// https://devblogs.microsoft.com/oldnewthing/20150716-00/?p=45131#comments ; great article written by Raymond Chen;
			}
			delete p_modules;
#else
			t_char mod_path[_MAX_PATH] = {0};
			dword d_qry_size = _countof(mod_path);

			if (false == !!::QueryFullProcessImageName(h_proc, 0, mod_path, &d_qry_size)) {
				m_error.Last();
				continue;
			}
			else {
				v_mod_paths.push_back(CString(mod_path));
			}
#endif
			t_char proc_path[_MAX_PATH] = {0};
			// https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getprocessimagefilenamew  ;
			if (false == !!::GetProcessImageFileName(h_proc, proc_path, _countof(proc_path))) {
				m_error.Last();
				continue;
			}

			// https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulebasenamew ;
			t_char proc_name[_MAX_PATH] = {0};
			if (false == !!::GetModuleBaseName(h_proc, h_module, proc_name, _countof(proc_name)))
				continue;
#if (0)                 // the checking certificate of the process is not required yet;
			TCertProvider cert_prov;

			if (false == cert_prov.Is_Trusted(v_mod_paths[0].c_str()))
				m_error = cert_prov.Error();
#endif
			CProcess proc;
			proc << dw_proc_ids[i_] << proc_name >> (v_mod_paths.empty() ? proc_path :  (_pc_sz) v_mod_paths[0]) << TCertInfo() << v_mod_paths;
#if (0)
			m_procs.insert(::std::make_pair(dw_proc_ids[i_], proc));
#else
			this->m_list.push_back(proc);
#endif
		};
	}
#if (0)
	proc::perform::reg::CPerf_Pdh counters;
	counters.Enumerate();
#elif (true == false)
	proc::perform::reg::CPerformance perf;
	perf.Get();
#else
	// the checking performance of GPU and CPU is not required yet;
#endif
	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString   CProcess_List::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s%s}");

        CString  cs_list;

	for (TProc_map::const_iterator it_ = m_procs.begin(); it_ != this->m_procs.end(); ++it_) {

		const dword proc_id  = it_->first ;
		const CProcess& proc = it_->second;

		cs_list += _p_sfx;
		cs_list += _p_pfx;

		cs_list += proc.Print(e_print::e_req);

		const TModules& dlls = proc.Modules();
		if (dlls.empty())
			continue;
#if (0)
		s_result += _T("\n\t\tModules");

		for (size_t j_ = 0; j_ < dlls.size(); j_++) {
			s_result += CFormatter().Accept(_T("\n\t\t%s"), dlls[j_].c_str());
		}
#endif
	}
	if (cs_list.IsEmpty())
		cs_list.Format (_T("%s%s#empty"), _p_sfx, _p_pfx);

	CString  cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_list, _p_sfx, _p_pfx); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_list, _p_sfx, _p_pfx); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_list, _p_sfx, _p_pfx); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return   cs_out;
}
#endif

const
TRaw_List&  CProcess_List::List (void) const { return this->m_list; }
const
TProc_map&  CProcess_List::Raw (void) const { return this->m_procs; }

/////////////////////////////////////////////////////////////////////////////

CProcess_List&  CProcess_List::operator = (const CProcess_List& _ref) { this->m_procs = _ref.m_procs; return *this; }