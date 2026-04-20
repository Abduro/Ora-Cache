/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Apr-2026 on 22:21:09.706, UTC+4, Batumi, Sunday;
	This is Ebo Pack trace console command interface implementation file;
*/
#include "console.cmd.h"
#include "console.h"
#include "console.buffer.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace shared::console::cmds;

#pragma region cls::CCmd_Base{}

CCmd_Base::CCmd_Base (const uint32_t _cmd_id/* = 0*/, _pc_sz _p_name/* = nullptr*/) : m_id(_cmd_id), m_name(_p_name) {
	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited: command object is not inited yet"); }
CCmd_Base::CCmd_Base (const CCmd_Base& _src) : CCmd_Base() { *this = _src; }
CCmd_Base::CCmd_Base (CCmd_Base&& _victim) : CCmd_Base() { *this = _victim; }

TError&  CCmd_Base::Error (void) const { return this->m_error; }

uint32_t CCmd_Base::Get_id (void) const { return this->m_id; }
err_code CCmd_Base::Set_id (const uint32_t _u_id) {
	this->m_error <<__METHOD__<<__s_ok;

	if (CCmd_Handler().Has_cmd(_u_id))
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: cmd ID = (%u) is already assigned"), _u_id);

	this->m_id = _u_id;

	return this->Error();
}

bool  CCmd_Base::Is_valid (void) const { return !!this->Get_id() && !!this->Name(); }

_pc_sz   CCmd_Base::Name (void) const { return (_pc_sz) this->m_name; }
err_code CCmd_Base::Name (_pc_sz _p_name) {
	_p_name;
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_name || 0 == ::_tcslen(_p_name))
		return this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input cmd name is invalid");

	const bool b_changed = 0 == this->m_name.CompareNoCase(_p_name); if (b_changed) this->m_name = _p_name; return this->Error();
}

CString CCmd_Base::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("id = %u; name = '%s'");
	CString cs_out; cs_out.Format(pc_sz_pat, this->Get_id(), this->Name());
	return  cs_out;
}

CCmd_Base& CCmd_Base::operator = (const CCmd_Base& _src) { *this << _src.Get_id() << _src.Name(); return *this; }
CCmd_Base& CCmd_Base::operator = (CCmd_Base&& _victim) { *this = (const CCmd_Base&)_victim; return *this; }
CCmd_Base& CCmd_Base::operator <<(const uint32_t _u_id) { this->Set_id(_u_id); return *this; }
CCmd_Base& CCmd_Base::operator <<(const CString& _cs_name) { *this << (_pc_sz) _cs_name; return *this; }
CCmd_Base& CCmd_Base::operator <<(_pc_sz _p_sz_name) { this->Name(_p_sz_name); return *this; }

#pragma endregion
#pragma region cls::CCmd_Clear{}

CCmd_Clear::CCmd_Clear (void) : TBase(e_cmd_ids::e_clear, _T("Clear")) {}

err_code CCmd_Clear::Exec (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CScreenBuffer buffer;
	if (__failed( buffer.Clear()))
		TBase::m_error = buffer.Error();

	return TBase::Error();
}

#pragma endregion