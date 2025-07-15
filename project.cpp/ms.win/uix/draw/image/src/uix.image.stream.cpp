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
CStream::~CStream (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CStream::Create(_pc_sz _p_file_path) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_file_path || 0 == ::_tcslen(_p_file_path))
		return this->m_error << __e_inv_arg;

	::ATL::CAtlFile file_;
	err_code n_result = file_.Create(_p_file_path, FILE_READ_DATA, FILE_SHARE_READ, OPEN_EXISTING);
	if (__failed(n_result))
		return this->m_error << n_result;

	ULONGLONG u_size = 0;
	n_result = file_.Seek(0, FILE_BEGIN); if (__failed(n_result)) return this->m_error << n_result;
	n_result = file_.GetSize(u_size); if (__failed(n_result)) return this->m_error << n_result;

	return this->Error();
}

TError&   CStream::Error (void) const { return this->m_error; }