/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2022 at 18:16:52.246 [the time stamp is not accurate], UTC+7, Novosibirsk, Thursday;
	This is image stream interface implementation file; [this implementation is made within 'Smart Diagram' project of ARQA Technologies]
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack image wrappers' project on 11-Jul-2025 at 22:08:27.868, UTC+4, Batumi, Friday;
*/
#include "uix.image.stream.h"

using namespace ex_ui::draw::images;

/////////////////////////////////////////////////////////////////////////////

CStream:: CStream (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CStream::~CStream (void) { if (this->Is_valid()) this->Destroy(); }

/////////////////////////////////////////////////////////////////////////////

err_code  CStream::Create (const CAlloc& _alloc) {
	_alloc;
	this->m_error <<__METHOD__<<__s_ok;
	if (_alloc.Is() == false)
		return this->m_error = _alloc.Error();

	// https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-createstreamonhglobal ;
	/*
		important: (excerpts from the above document url)
		(1) Do not free the hGlobal memory handle during the lifetime of the stream object.
		(2) Do not call GlobalReAlloc to change the size of the memory handle...
		(3) If possible, avoid accessing the memory block during the lifetime of the stream object... >> Locker is turned on;
	*/
	err_code n_result = ::CreateStreamOnHGlobal(_alloc.Handle(), true, &m_p_stream );
	if (__failed(n_result))
		this->m_error << n_result;

	return this->Error();
}

err_code  CStream::Create(_pc_sz _p_file_path) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_file_path || 0 == ::_tcslen(_p_file_path))
		return this->m_error << __e_inv_arg;

	::ATL::CAtlFile file_;
	err_code n_result = file_.Create(_p_file_path, FILE_READ_DATA, FILE_SHARE_READ, OPEN_EXISTING);
	if (__failed(n_result))
		return this->m_error << n_result;

	shared::memory::shared_flags flags;
	shared::memory::shared_data  data ;

	ULONGLONG u_size = 0;
	n_result = file_.Seek(0, FILE_BEGIN); if (__failed(n_result)) return this->m_error << n_result;
	n_result = file_.GetSize(u_size); if (__failed(n_result)) return this->m_error << n_result;

	data.n_size = (u_size & 0x0000ffff);
	// the file must be read first to shared data structure, otherwise the allocator buffer will be empty;

	if (this->m_alloc.Is())
		if (__failed(this->m_alloc.Builder().Destroy()))
			return this->m_error = this->m_alloc.Builder().Error();

	this->m_alloc << flags << data;

	if (__failed(this->m_alloc.Builder().Create()))
		return this->m_error = this->m_alloc.Builder().Error();

	if (__failed(this->m_alloc.Locker().Lock()))
		return this->m_error = this->m_alloc.Locker().Error();

	void* p_data = const_cast<void*>(this->m_alloc.Locker().Ptr());

	n_result = file_.Read(p_data, data.n_size);
	if (__failed(n_result))
		this->m_error << n_result;

	if (__failed(this->m_alloc.Locker().Unlock()))
		this->m_error = this->m_alloc.Locker().Error();  // this case will overwrite the above error state, it's necessary to make a review;

	if (this->Error())
		return this->Error();

	this->Create(this->m_alloc);	

	return this->Error();
}

err_code  CStream::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;

	IStream* p_stream = this->m_p_stream.Detach();
	if (nullptr == p_stream)
		return this->m_error << __e_pointer;

	err_code n_result = p_stream->Release();
	if (__succeeded(n_result))
		p_stream = nullptr;
	else
		this->m_p_stream.Attach(p_stream); // ToDo: stupid approach, possibly it never occurs, anyway must be reviewed;

	return this->Error();
}

TError&   CStream::Error (void) const { return this->m_error; }

#if defined(_DEBUG)
CString   CStream::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz lp_sz_pat_a = _T("cls::[%s::%s] >> {ptr=%s;valid=%s}");
	static _pc_sz lp_sz_pat_n = _T("cls::[%s] >> {ptr=%s;valid=%s}");
	static _pc_sz lp_sz_pat_r = _T("ptr=%s;valid=%s");

	CString cs_data = TString().__address_of(this->Ptr());
	CString cs_valid = TString().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (lp_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_data, (_pc_sz) cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (lp_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_data, (_pc_sz) cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (lp_sz_pat_r, (_pc_sz) cs_data, (_pc_sz) cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool   CStream::Is_valid (void) const { return this->m_p_stream != nullptr; }

const
TStreamPtr& CStream::Ptr (void) const { return this->m_p_stream; }
TStreamPtr& CStream::Ptr (void)       { return this->m_p_stream; }