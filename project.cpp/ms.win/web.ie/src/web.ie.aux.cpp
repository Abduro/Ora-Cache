/*
	Createed by Tech_dog (ebontrop@gmail.com) on 08-Oct-2026 at 00:55:56.469, UTC+4, Batumi, Friday;
	This is IE browser auxiliary properties' and state classes' interface implementation file.
*/
#include "web.ie.aux.h"
#include "web.ie.accessor.h"
#include "web.ie.window.h"
#include "web.ie.browser.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::core;

#pragma region cls::CCommand{}

CCommand::CCommand (TBrwWndPtr& _p_ctrl) : m_control(_p_ctrl) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CCommand::Error (void) const { return m_error; }
bool CCommand::Is_valid (void) const {
	return (this->m_error << (nullptr != this->m_control ? __s_ok : __e_not_inited)).Is() == false;
}

err_code CCommand::Print(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false) return this->Error();

	TCmdTargetPtr pCommand;

	CAccessor acc(*this->m_control);
	this->m_error << acc.CmdTarget(pCommand);
	if (this->Error())
		return this->Error();
	else
		return this->m_error << pCommand->Exec(0, OLECMDID_PRINT, OLECMDEXECOPT_PROMPTUSER, 0, 0);
}

err_code CCommand::PrintPreview(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false) return this->Error();


	TCmdTargetPtr pCommand;

	CAccessor acc(*this->m_control);
	this->m_error << acc.CmdTarget(pCommand);

	if (this->Error())
		return this->Error();
	else
		return this->m_error << pCommand->Exec(0, OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_PROMPTUSER, 0, 0);
}

#pragma endregion
#pragma region cls::CState{}

CState::CState (CWebBrowser* _p_browser) : m_browser(_p_browser) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CState::Error (void) const { return m_error; }
bool CState::Is_valid (void) const {
	return (this->m_error << (
		nullptr != this->m_browser && nullptr != this->m_browser->Ctrl() && this->m_browser->Window().IsWindow() ? __s_ok : __e_not_inited
	)).Is() == false;
}

bool CState::Is_busy (void) const {
	
	if (this->Is_valid() == false)
		return false;

	var_bool b_valid = var_false;
	this->m_error = this->m_browser->Ctrl()->get_Busy(&b_valid);
	
	return this->Error() ? var_false : b_valid == var_true;
}

bool CState::Silent (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return false;

	var_bool v_result = var_false;
	this->m_browser->Ctrl()->get_Silent( &v_result );
	return (var_true == v_result );
}

err_code CState::Silent (const bool _yes_or_no) {
	_yes_or_no;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->Error();
#if (0)
	const bool bChanged = (this->Silent() != _yes_or_no); // it is not necessary;
	if (!bChanged)
		return this->m_error <<__s_false;
#endif
	this->m_error << this->m_browser->Ctrl()->put_Silent(_yes_or_no ? var_true : var_false);
	return  this->Error();
}

CState::operator bool (void) const { return this->Is_valid(); }

#pragma endregion