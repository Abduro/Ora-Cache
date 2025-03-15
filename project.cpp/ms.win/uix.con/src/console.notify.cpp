/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Sep-2022 at 10:08:55.9180723, UTC+7, Novosibirsk, Friday;
	This is MS Windows console generic event notification callback interfacee implementation file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:49:13pm, GMT+4, Saint-Petersburg, Sunday;
*/
#include "console.notify.h"

using namespace shared::console;

/////////////////////////////////////////////////////////////////////////////

CNotifyDefImpl:: CNotifyDefImpl (void) {}
CNotifyDefImpl::~CNotifyDefImpl (void) {}

/////////////////////////////////////////////////////////////////////////////

VOID   CNotifyDefImpl::Notify_OnEvent(const TRecordType eType, const UINT  nResId)
{
	CStringW cs_details;
	cs_details.LoadString(nResId);
	this->Notify_OnEvent(eType, cs_details.GetString());
}

VOID   CNotifyDefImpl::Notify_OnEvent(const TRecordType eType, LPCWSTR pszDetails)
{
	::ATL::CStringW cs_out;
	switch(eType)
	{
	case TRecordType::eError:   cs_out.Format(_T("\n\t[ERROR] %s"), pszDetails); break;
	case TRecordType::eInfo:    cs_out.Format(_T("\n\t[INFO]  %s"), pszDetails); break;
	case TRecordType::eWarning: cs_out.Format(_T("\n\t[WARN]  %s"), pszDetails); break;
	default:
		return;
	}
	::_tprintf(cs_out);
}

VOID   CNotifyDefImpl::Notify_OnError(const UINT nResId) {
	this->ConsoleNotify_OnEvent(TRecordType::eError, nResId);
}

VOID   CNotifyDefImpl::Notify_OnInfo (const UINT nResId) {
	this->ConsoleNotify_OnEvent(TRecordType::eInfo, nResId);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

