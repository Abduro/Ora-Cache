#ifndef _CONSOLE_H_INCLUDED
#define _CONSOLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Sep-2020 at 6:54:34p, UTC+7, Novosibirsk, Thursday;
	This is FakeGPS driver version 2 desktop client console interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Wanderer Path Finder project on 6-Jan-2021 at 11:42:05.633 am, UTC+7, Novosibirsk, Tuesday;
	Adopted to Yandex Wanderer project on 11-Dec-2022 at 07:38:02.6575746, UTC+7, Novosibirsk, Sunday;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.defs.h"
#include "console.content.h"
#include "console.event.h"
#include "console.layout.h"

namespace shared { namespace console {
	/* the locator class is for getting path to trace console executable in the following order:
	   (1) checking the registry for possible specifying where the console wrapper resides;
	   (2) in case if registry does not contain such path or the specified path is wrong,
	       the locator gets absolute path to the app process either tutorial app or test case dyna-lib,
	       than composes the relative path to the trace console;
	*/
	class CLocator {
	public:
		 CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete;
		~CLocator (void) = default;

		TError&  Error (void) const;
		_pc_sz   Get_path (void);    // if returned pointer to path string is null, the error object contains the error detailes;

	private:
		CLocator& operator = (const CLocator&) = delete; CLocator& operator = (CLocator&&) = delete;
		CError m_error;
	};

	/* query: how to create console process with hidden window winapi (Google AI):
	   To create a console process with a hidden window using the Win32 API,
	   the most effective method is using the CreateProcess function with specific flags;
	(1) Using CREATE_NO_WINDOW flag: no console window is created for a process. This avoids the "flicker" of a window appearing and then disappearing;
	(2) Using STARTUPINFO with SW_HIDE: { dwFlags = STARTF_USESHOWWINDOW; wShowWindow = SW_HIDE; }
	*/

	class CWrap {
	public:
		 CWrap (void); CWrap (const CWrap&) = delete; CWrap (CWrap&&) = delete;
		~CWrap (void);

		err_code Create (_pc_sz _p_path, const bool _b_visible, const bool _b_attach = true); // creates the console process through CreateProcess() procs;
		err_code Detach (void); // dettaches from the console, to close console host process the operating does it itself;
		TError&  Error  (void) const;

		bool Is_attached (void) const;

	private:
		CWrap& operator = (const CWrap&) = delete; CWrap& operator = (CWrap&&) = delete;
		CError m_error;
		void*  m_hwnd ;  // console window handle; winnt.h: typedef void* HANDLE;
	};

	enum e_cmd_ids : uint32_t {
		e__undef = 0,
		e_clear  = 6666, // clears console buffer, i.e. no text in the console window;
	};

	class CCmd_Handler {
	public:
		CCmd_Handler (void); CCmd_Handler (const CCmd_Handler&) = delete; CCmd_Handler (CCmd_Handler&&) = delete; ~CCmd_Handler (void) = default;

		TError& Error (void) const;
		bool Has_cmd (const uint32_t _u_cmd_id) const;

		err_code On_command (const uint32_t _cmd_id);

	private:
		CCmd_Handler& operator = (const CCmd_Handler&) = delete; CCmd_Handler& operator = (CCmd_Handler&&) = delete;
		CError m_error;
	};

	class CFrame {
	public:
		class CIcon {
		public:
			CIcon (void) = default; CIcon (const CIcon&) = delete; CIcon (CIcon&&) = delete; ~CIcon (void) = default;
			CIcon& operator <<(const uint16_t _res_id); // sets the frame icon; (16x16 and 32x32px);
		private:
			CIcon& operator = (const CIcon&) = delete; CIcon& operator = (CIcon&&) = delete;
		};

		CFrame (void); CFrame (const CFrame&) = delete; CFrame (CFrame&&) = delete; ~CFrame (void) = default;

		void     Caption (_pc_sz);
		CString  Caption_Dflt (const e_print = e_print::e_all) const;

		TError&  Error (void) const;
		const
		CIcon&   Icon (void) const;
		CIcon&   Icon (void) ;

		err_code OnCreate (void);

	private:
		CFrame& operator = (const CFrame&) = delete; CFrame& operator = (CFrame&&) = delete;
		CError  m_error;
		CIcon   m_icon ;
	};

	// https://learn.microsoft.com/en-us/windows/console/creation-of-a-console ;
	// https://learn.microsoft.com/en-us/windows/console/allocconsole ;
	// the excerpt from the above article: this function is primarily used by a graphical user interface (GUI) application to create a console window...;

	class CConsole {
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void);

		 err_code Create (void); // allocates new console, restores its previous position, pinned state;
		 err_code Create (const s_create_data&); // allocates console, inserts it as a child window to the parent one;
		 err_code Close  (void); // closes all IO handles; ::FreeConsole() is not used because there is no call to ::AttachConsole() was made before;

		 const
		 CFrame&  Frame  (void) const;
		 CFrame&  Frame  (void) ;

		 TError&  Error  (void) const;	
		 HWND     Handle (void) const; // returns console window handle;
		 bool  Is_valid  (void) const; // checks validity of the console window handle;

		 void*   Get_err (void) const; // gets std::error handle;
		 void*   Get_in  (void) const; // gets std::input handle;
		 void*   Get_out (void) const; // gets std::output handle;
		 
		 operator const HWND (void) const;

	private:
		 CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
		 mutable
		 CError   m_error;
		 HWND     m_con_wnd; // it is not necessary actually;
		 CFrame   m_frame;
	};
}}

typedef shared::console::CConsole con_t; static con_t _con;
typedef shared::console::CCmd_Handler TCmdHandler;  TCmdHandler&  Get_ConHandler (void);  

#endif/*_CONSOLE_H_INCLUDED*/