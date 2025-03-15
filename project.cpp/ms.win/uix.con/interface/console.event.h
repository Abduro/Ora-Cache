#ifndef _CONSOLE_EVENT_H_INCLUDED
#define _CONSOLE_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2022 at 01:15:36.7151607, UTC+7, Novosibirsk, Monday;
	This is MS Windows console event handler interface declaration file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:29:53pm, GMT+4, Saint-Petersburg, Sunday;
*/
#include <atlbase.h>
#include <vector>

#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"

// https://learn.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions ;
// https://learn.microsoft.com/en-us/windows/console/handlerroutine ;
typedef BOOL (__stdcall *pfn_ConsoleEvents)(DWORD dwEvent);

namespace shared { namespace console {

	using namespace shared::types;

	// https://stackoverflow.com/questions/18291284/handle-ctrlc-on-win32 >> handling CTRL + C;
	// https://learn.microsoft.com/en-us/windows/console/handlerroutine   >> handler routine interface;
	class CEvents
	{
	public:
		enum Id : dword
		{
			eAbort    = CTRL_C_EVENT        ,  // https://www.lifewire.com/what-is-ctrl-c-used-for-2625834 ; 
			eBreak    = CTRL_BREAK_EVENT    ,  // https://learn.microsoft.com/en-us/windows/console/ctrl-c-and-ctrl-break-signals
			eClose    = CTRL_CLOSE_EVENT    ,
			eLogoff   = CTRL_LOGOFF_EVENT   ,
			eShutdown = CTRL_SHUTDOWN_EVENT ,
		};
	};
	// it very looks like this interface is not used; must be reviewed; there must be implemented a container of registered handler(s);
	interface IConsole_EventListener
	{
		virtual HRESULT  Console_OnEvent(const CEvents::Id) = 0; // S_OK means TRUE, otherwise FALSE;
	};

	typedef ::std::vector<IConsole_EventListener*> TListeners;
	// is not thread safe, it is assumed that everything is performed in main thread of the process;
	class CListeners
	{
	public:
		enum _ndx : int32_t {
			e_not_found = -1,
		};
	public:
		 CListeners (void);
		 CListeners (const CListeners&);
		~CListeners (void);

	public:
		err_code  Add (IConsole_EventListener*);        // adds a listener pointer;
		int32_t   Has (IConsole_EventListener*) const;  // returns an index of the element found, otherwise e_not_found;
		err_code  Out (IConsole_EventListener*);        // removes a listener pointer;

	public:
		const
		TListeners&  Raw (void) const;
		TListeners&  Raw (void)      ;

	public:
		CListeners&  operator  = (const CListeners&);
		CListeners&  operator += (IConsole_EventListener*);
		CListeners&  operator -= (IConsole_EventListener*);

	private:
		TListeners  m_listeners;
	};

	// https://learn.microsoft.com/en-us/windows/console/setconsolectrlhandler ;

	class CHandler {
	public:
		 CHandler (void);
		 CHandler (const CHandler&);  // does not care about function pointer set/remove operations;
		~CHandler (void);

	public:
		err_code  Disable (void);     // removes handler function from console event handling;
		err_code  Install (void);     // sets the current handler funtion to usage of console event handling;
		bool      IsActive(void) const;

	public:
		err_code  Set (pfn_ConsoleEvents);

	public:
		const
		CListeners& Listeners (void) const;
		CListeners& Listeners (void)      ;

	public:
		CHandler& operator = (const CHandler&);
		CHandler& operator <<(pfn_ConsoleEvents);
		CHandler& operator <<(TListeners);

	protected:
		bool m_bInstalled           ; // the flag indicates this handler is installed, or custom function of the handler is applied;
		pfn_ConsoleEvents   m_events; // is set to default function pointer when this class instance being created;
		CListeners       m_listeners; // not thread safe yet;
	};

}}

#endif/*_CONSOLE_EVENT_H_INCLUDED*/