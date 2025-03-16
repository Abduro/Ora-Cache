/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Sep-2022 at 23:23:51.5673324, UTC+7, Novosibirsk,Tuesday;
	This is MS Windows console event handler interface implementation file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class implemented on 14-Jan-2014 at 8:13:26pm, GMT+4, Saint-Petersburg, Sunday;
*/
#include "console.event.h"

using namespace shared::console;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace console { namespace _impl {

	// https://learn.microsoft.com/en-us/windows/console/handlerroutine ;

	static BOOL __stdcall Event_Handler_Func_Default(const DWORD dwCtrlType)
	{
		switch (dwCtrlType)
		{
		case CTRL_C_EVENT:
			{
				::_tprintf(_T("The CTRL+C keys have been pressed; ignoring...\n")); return TRUE;
			} break;
		case CTRL_BREAK_EVENT:
			{
				::_tprintf(_T("The CTRL+Break keys have been pressed; ignoring...\n")); return TRUE;
			} break;
		case CTRL_CLOSE_EVENT:
			{
				const INT nResult = ::MessageBox(
					::GetActiveWindow(), _T("Do you really want to exit the application?"), _T("Close Event Handler"), MB_OKCANCEL|MB_ICONQUESTION|MB_APPLMODAL
				);
				return (nResult != IDOK);
			} break;
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			{
			}
		default:;
		}
		return FALSE;
	}

}}}
using namespace shared::console::_impl;
/////////////////////////////////////////////////////////////////////////////

CListeners:: CListeners (void) {}
CListeners:: CListeners (const CListeners& _ref) : CListeners() { *this = _ref; }
CListeners::~CListeners (void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT      CListeners::Add (IConsole_EventListener* _p_listener)
{
	HRESULT hr_ = S_OK;

	if (nullptr == _p_listener)
		return (hr_ = E_POINTER);

	if (CListeners::e_not_found != this->Has(_p_listener))
		return (hr_ = HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS));

	try
	{
		this->m_listeners.push_back(_p_listener);
	}
	catch (const ::std::bad_alloc&)
	{
		hr_ = E_OUTOFMEMORY;
	}

	return  hr_;
}

INT          CListeners::Has (IConsole_EventListener* _p_listener) const
{
	INT n_ndx = CListeners::e_not_found;
	if (nullptr == _p_listener)
		return n_ndx;

	for (size_t i_= 0; i_ < m_listeners.size(); i_++)
		if (_p_listener == m_listeners[i_])
		{
			n_ndx = static_cast<INT>(i_);
			break;
		}

	return n_ndx;
}

HRESULT      CListeners::Out (IConsole_EventListener* _p_listener)
{
	HRESULT hr_ = S_OK;

	if (nullptr == _p_listener)
		return (hr_ = E_INVALIDARG);

	const INT ndx_ = this->Has(_p_listener);

	if (CListeners::e_not_found == ndx_)
		return (hr_ = HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

	try
	{
		this->m_listeners.erase(this->m_listeners.begin() + ndx_);
	}
	catch (...)
	{
		hr_ = E_OUTOFMEMORY;
	}

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////
const
TListeners&  CListeners::Raw (void) const { return this->m_listeners; }
TListeners&  CListeners::Raw (void)       { return this->m_listeners; }
/////////////////////////////////////////////////////////////////////////////

CListeners&  CListeners::operator = (const CListeners& _ref)
{
	this->Raw() = _ref.Raw();
	return *this;
}

CListeners&  CListeners::operator += (IConsole_EventListener* _p_listener) { this->Add(_p_listener); return *this; }
CListeners&  CListeners::operator -= (IConsole_EventListener* _p_listener) { this->Out(_p_listener); return *this; }

/////////////////////////////////////////////////////////////////////////////

CHandler:: CHandler (void) : m_bInstalled(false), m_events(nullptr) {}
CHandler:: CHandler (const CHandler& _ref) : CHandler() { *this = _ref; }
CHandler::~CHandler (void) { if (this->IsActive()) this->Disable(); }

/////////////////////////////////////////////////////////////////////////////

HRESULT    CHandler::Disable (void)
{
	HRESULT hr_ = S_OK;

	if (false == this->IsActive())
		return (hr_ = S_FALSE);

	const BOOL bResult = ::SetConsoleCtrlHandler(this->m_events, FALSE);
	if (FALSE == bResult)
		hr_  = HRESULT_FROM_WIN32(::GetLastError());

	if (SUCCEEDED(hr_))
		m_bInstalled = false;

	return  hr_;
}

HRESULT    CHandler::Install (void)
{
	HRESULT hr_ = S_OK;

	if (this->IsActive())
		return hr_;

	if (this->m_events == nullptr)
		this->m_events = Event_Handler_Func_Default;

	const BOOL bResult = ::SetConsoleCtrlHandler(this->m_events, TRUE);
	if (FALSE == bResult)
		hr_ =  HRESULT_FROM_WIN32(::GetLastError());

	if (SUCCEEDED(hr_))
		m_bInstalled = true;

	return  hr_;
}

bool       CHandler::IsActive (void) const
{
	return (this->m_bInstalled);
}  

/////////////////////////////////////////////////////////////////////////////

HRESULT    CHandler::Set (pfn_ConsoleEvents _p_func)
{
	HRESULT hr_ = S_OK;

	if (nullptr == _p_func)
		return (hr_ = E_INVALIDARG);

	if (this->IsActive())
		hr_ = this->Disable();

	if (SUCCEEDED(hr_))
	{
		this->m_events = _p_func;
		hr_ = this->Install();
	}

	return  hr_;
}


/////////////////////////////////////////////////////////////////////////////
const
CListeners& CHandler::Listeners (void) const { return this->m_listeners; }
CListeners& CHandler::Listeners (void)       { return this->m_listeners; }

/////////////////////////////////////////////////////////////////////////////

CHandler&   CHandler::operator = (const CHandler& _ref) { *this << _ref.m_events << _ref.Listeners().Raw(); return *this; }
CHandler&   CHandler::operator <<(pfn_ConsoleEvents _p_fn) { this->Set(_p_fn); return *this; }
CHandler&   CHandler::operator <<(TListeners _listeners) { this->Listeners().Raw() = _listeners; return *this; }