#ifndef _COM_SVC_BASE_H_INCLUDED
#define _COM_SVC_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Mar-2011 at 1:48:50am, GMT+3, Rostov-on-Don, Monday;
	This is Row27 project COM libraries auto-initializer interface declaration file. [the first project that is gained through odesk.com]
	-----------------------------------------------------------------------------[this section shows all significant projects gained through upwork.com]
	Adopted to PulsePay project on 2-May-2012 at 8:57:47am, GMT+3, Rostov-on-Don, Wednesday;
	Adopted to Platinum project on 19-Mar-2014 at 9:47:36am, GMT+4, Taganrog, Wednesday;
	Adopted to File Guardian project on 11-Jul-2018 at 10:29:00a, UTC+7, Phuket, Rawai, Wednesday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:15:18a, UTC+7, Novosibirsk, Friday;
	-----------------------------------------------------------------------------[this volunteer project]
	Adopted to Stroke Over project on 14-Aug-2024 at 22:35:25.6522707, UTC+4, Batumi, Wednesday;
*/
#include "com.def.base.h"

// https://learn.microsoft.com/en-us/windows/win32/api/objbase/ne-objbase-coinit ;
namespace none {
	#define co_apartment COINIT_APARTMENTTHREADED // apartment-threaded object concurrency ;
	#define co_threaded  COINIT_MULTITHREADED     // multithreaded object concurrency      ;
	#define co_ole_1_dde COINIT_DISABLE_OLE1DDE   // disabling DDE for OLE1 support        ;
	#define co_speed_up  COINIT_SPEED_OVER_MEMORY // increasing memory usage for high performance ;
}

namespace shared { namespace sys_core { namespace com {

	using namespace shared::types;

	using shared::sys_core::CError;
	
	using TError  = const CError&;
	using TString = TStringEx;

	class CCoMode {
	public:
		 CCoMode (void);
		 CCoMode (const CCoMode&);
		 CCoMode (CCoMode&&);
		 CCoMode (dword _code, _pc_sz _p_alias, _pc_sz _p_desc);
		~CCoMode (void);

	public:
		_pc_sz Alias(void) const;   // gets this mode alias value;
		bool   Alias(_pc_sz);       // sets this mode alias ; returns true in cas of change;

		void   Clear(void)  ;       // clears this class object, i.e. resets all its attributes to initial state;

		dword  Code (void) const;   // gets the code, in other words, actually this is one of the values of COINIT enumeration;
		bool   Code (dword) ;       // sets the code, returns true in case of change;

		_pc_sz Desc (void) const;   // gets a brief description of this mode;
		bool   Desc (_pc_sz) ;      // sets a brief description of this mode; returns true in case of change;

		void   Set  (dword _code, _pc_sz _p_alias, _pc_sz _p_desc); // sets all atts together or at once; no interest is in return result;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_req) const;
#endif
	public:
		CCoMode& operator = (const CCoMode&);
		CCoMode& operator = (CCoMode&&);        // makes copying the input objects and clears it; no move operation is made;
		CCoMode& operator >>(_pc_sz _p_alias);  // sets an alias;
		CCoMode& operator <<(dword _code);      // sets a code;
		CCoMode& operator <<(_pc_sz _p_desc );  // sets a description;

	private:
		dword   m_code ;
		CString m_alias;
		CString m_desc ;
	};
}}}

using shared::types::dword;

typedef shared::sys_core::com::CCoMode  TCoMode;
typedef ::std::map<dword, TCoMode> TCoMode_raws; // a key is COINIT enum's element; a value - the element wrapper class;
typedef TCoMode_raws TRawModes;                  // makes the typedef name is little bit shorter;

namespace shared { namespace sys_core { namespace com {

	class CCoMode_enum {
	public:
		enum e_available : dword {
			e_apart    = co_apartment,  // for GUI apps; due to GUI requires message pump that is not provided by COM;
			e_default  = co_threaded ,
			e_threaded = co_threaded ,  // multi-threaded for performing tasks concurrently, for multi-processor architecture usage;
			e_ole_1    = co_ole_1_dde,  // the legacy code disbling;
			e_speed    = co_speed_up ,  // increasing memory usage for making a performance of the COM calls faster;
			e_the_fake = (dword)-1
		};
	public:
		 CCoMode_enum (void);
		 CCoMode_enum (const CCoMode_enum&) = delete; CCoMode_enum (CCoMode_enum&&) = delete;
		~CCoMode_enum (void);

	public:
		const
		TRawModes& Get (void) const;     // gets the reference to mode mapped collection ;
		err_code   Set (void) ;          // adds a predefined concurrency mode classes;

		bool Has (dword) const;          // returns true in case when predefined mode collection has the object of such code;
		const
		TCoMode& Find (dword) const;     // returns found mode object, otherwise fake object is returned;
#if defined(_DEBUG)
		CString Print (_pc_sz _pfx = _T("\t"), _pc_sz _sfx = _T("\n")) const;
#endif
	public:
		static CCoMode_enum& Ref (void); // returns singleton object for avoiding a creation of predefined concurrency modes' set each time;

	private:
		CCoMode_enum& operator = (const CCoMode_enum&) = delete;
		CCoMode_enum& operator = (CCoMode_enum&&) = delete;

	private:
		TRawModes m_modes;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializeex ;
	// this class is a simple wrapper for the concurrency model that is assigned during initialization of a COM service or libraries;
	class CCoModel {
	public:
		enum _cfg_4 {
			e_none = 0x0, // no configuration >> no accepted modes; but by default co-init flag equals to zero; that means the cfg fo multi-threading env;
			e_gui  = 0x1, // this is the configuration for running in single/apartment thread environment, due to message pump is required;
			e_task = 0x2, // for multi-processor hardware architecture, running in multi-threaded apps with no gui; *default* cfg for COM init;
			e_fast = 0x3, // the same as above configure + more intensive usage of memory for making COM to work faster;
		};
	public:
		 CCoModel (_cfg_4 = _cfg_4::e_task); // no special method is created for filling acceptable mode set up; this constructor makes it;
		 CCoModel (const CCoModel&);
		 CCoModel (CCoModel&&) = delete;
		~CCoModel (void);

	public:
		const
		TRawModes& Accepted(void) const;
		TRawModes& Accepted(void) ;
		dword      CoInit  (void) const; // gets COINIT flags' value that is calculated from accepted modes;

		_cfg_4     Cfg(void) const;      // returns the config value that is used for creating set of accepted modes;
#if defined(_DEBUG)
		CString Print (void) const;
#endif
	public:
		CCoModel&  operator = (const CCoModel&);
		CCoModel&  operator = (CCoModel&&) = delete;

		operator dword (void) const;

	protected:
		TRawModes  m_accepted;
		_cfg_4     m_cfg;      // this stores the configuration option that is used for composing init-modes for specific requirements;
	};
}}}

typedef shared::sys_core::com::CCoMode_enum TCoMode_enum; using TCoModes = TCoMode_enum;
typedef shared::sys_core::com::CCoMode_enum::e_available  TModeAccept;

typedef shared::sys_core::com::CCoModel TCoModel;
typedef shared::sys_core::com::CCoModel::_cfg_4 TCoModelCfg; typedef TCoModelCfg TCo_Cfg; // just making name shorter;

namespace shared { namespace sys_core { namespace com {
#pragma region __refs_9
	// https://stackoverflow.com/questions/17884290/cappmodule-vs-catlexemodulet-getting-the-application-message-loop;
	// https://learn.microsoft.com/en-us/cpp/atl/catlservicemodulet-servicemain-function ;
	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlservicemodulet ;
	// possibly it would be better to use ATL::CAtlExeModuleT::InitializeCom(); but for the sake of keeping things simple, this class is declared ;
#pragma endregion	
	class CCoGuard {
	public:
		 CCoGuard (bool _b_dbg = true); // creates this class object, no co-init operation is performed; for debug purpose only;
		 CCoGuard (TCo_Cfg);            // sets acceptable mode(s) of concurrency model right before making init;
		 CCoGuard (const CCoGuard&) = delete;
		 CCoGuard (CCoGuard&&) = delete;
		~CCoGuard (void);               // if com-init operation was successfull, it automatically calls co-un-init winapi method;

	public:
		TError    Error (void) const; // no comment ;)
		bool      Is    (void) const; // returns true in case if COM init succeeded successfully;
		const
		TCoModel& Model (void) const; // just letting know what model is applied for the inits;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_req) const;
#endif
	private:
		CCoGuard& operator = (const CCoGuard&) = delete;
		CCoGuard& operator = (CCoGuard&&) = delete;
	public:
		operator const bool (void) const;

	protected:
		err_code  OnCreate (void); // calls co-init method; it is called from appropriate constructor; [for debug purpose];
		err_code  OnDestroy(void); // calls co-un-init method; it is called from deconstructor of this class; [for debug purpose];

	protected:
		bool     m_auto ; // this flags controls the auto invocation such methods as co-init and co-un-init;
		CError   m_error;
		CCoModel m_model;
	};
#if (0)
	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/initializing-the-com-library ; it is clear enough what type of COM initialization is required;
	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box ;
	// https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/begin/LearnWin32/OpenDialogBox ;
	class CCoApartment : public CCoGuard { typedef CCoGuard TBase; public: CCoApartment(void); };
	class CCoThreaded  : public CCoGuard { typedef CCoGuard TBase; public: CCoThreaded (void); };
#endif
}}}

typedef shared::sys_core::com::CCoGuard TCoGuard;

#endif/*_COM_SVC_BASE_H_INCLUDED*/