#ifndef _SYS_COM_SVC_H_INCLUDED
#define _SYS_COM_SVC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Mar-2011 at 1:48:50am, GMT+3, Rostov-on-Don, Monday;
	This is Row27 project COM libraries auto-initializer interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to PulsePay project on 2-May-2012 at 8:57:47am, GMT+3, Rostov-on-Don, Wednesday;
	Adopted to Platinum project on 19-Mar-2014 at 9:47:36am, GMT+4, Taganrog, Wednesday;
	Adopted to File Guardian project on 11-Jul-2018 at 10:29:00a, UTC+7, Phuket, Rawai, Wednesday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:15:18a, UTC+7, Novosibirsk, Friday;
	Adopted to Geometry Curve project on 18-Feb-2024 at 08:47:01.5887698, UTC+7, Novosibirsk, Sunday;
*/
#include "shared.defs.h"

namespace shared { namespace sys_core { using namespace shared::defs;

	// https://learn.microsoft.com/en-us/windows/win32/api/objbase/ne-objbase-coinit ;
	class c_com_init {
	public:
		enum e_flags : dword {
		/* element   |  value                    |  brief desc;                        |
		|------------+---------------------------+-------------------------------------|*/
		e_co_apart   = COINIT_APARTMENTTHREADED, // calls can arrive only at message-queue boundaries; (looks like similar to STA);
		e_co_threads = COINIT_MULTITHREADED    , // The multi-threaded apartment is intended for use by non-GUI threads, COM does not support message pump; 
		e_co_no_ole1 = COINIT_DISABLE_OLE1DDE  , // Disables DDE for OLE1 support; not used;
		e_co_fast    = COINIT_SPEED_OVER_MEMORY, // Increase memory usage in an attempt to increase performance; (it can be very interesting)
		};
		static CString To_str (const e_flags);
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-iinitializespy << very interesting;

	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializeex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-couninitialize ; // no error is thrown;

	/* important:
	   Because there is no way to control the order in which in-process servers are loaded or unloaded,
	   do *not* call CoInitialize(), CoInitializeEx(), or CoUninitialize() from the DllMain function;
	*/

	class CCoIniter {
	public:
		 CCoIniter (void); CCoIniter (const CCoIniter&) = delete; CCoIniter (CCoIniter&&) = delete;
		~CCoIniter (void) = default;

		TError&  Error (void) const; // returns error object in state: '__s_ok' - com-system is inited or '__e_not_inited', otherwise error code;
		/* there is two different modes of the com-system initialization:
		(1) STA - single thread apartment, in this mode receiving calls can be made within one thread apartment through message pumping (PeekMessage() and SendMessage());
		(2) MTA - multi-thread apartment, calls from different threads are acceptable, no message pumping, but access to shared data control by using critical sections, semaphors and so on;
		*/
		err_code Init (bool _b_STA); // if '_b_STA' is 'true' the CoInitialize(0) is called for STA mode of COM; otherwise, MTA (c_com_init::e_co_threads);
		err_code Init (const c_com_init::e_flags = c_com_init::e_co_threads);
		err_code Uninit (void);

		operator const bool (void) const; // returns 'true' if com-system was initialized, that means the error object is set to __s_ok;

	private:
		CCoIniter& operator = (const CCoIniter&) = delete; CCoIniter& operator = (CCoIniter&&) = delete;
		CError m_error;
	};

	class CCoIniter_auto : public CCoIniter { typedef CCoIniter TBase;
	public:
		 CCoIniter_auto (const c_com_init::e_flags = c_com_init::e_co_threads);
		~CCoIniter_auto (void);
	};

	/* unfortunately, 'enum class' requires casting its elements to base data type of the enumeration, otherwise
	   an element cannot be passed as argument to winapi function, but 'class {enum {}}' can;
	*/
	// https://learn.microsoft.com/en-us/windows/win32/com/com-authentication-level-constants ;
	class e_co_sec_auth {
	public: enum e_levels : dword {
	/* element    |  value                           |  brief desc;                        |
	|-------------+----------------------------------+-------------------------------------|*/
	e_default     = RPC_C_AUTHN_LEVEL_DEFAULT      , // DCOM to choose the authentication level using its normal security blanket negotiation algorithm;
	e_none        = RPC_C_AUTHN_LEVEL_NONE         , // no authentication;
	e_connect     = RPC_C_AUTHN_LEVEL_CONNECT      , // for a relationship with the server; datagram transports always use RPC_AUTHN_LEVEL_PKT instead;
	e_remote_call = RPC_C_AUTHN_LEVEL_CALL         , // for remote procedure call; datagram transports use RPC_C_AUTHN_LEVEL_PKT instead;
	e_expected    = RPC_C_AUTHN_LEVEL_PKT          , // authenticates that all data received is from the expected client;
	e_integrity   = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY, // verifies that none of the data transferred between client and server has been modified;
	e_privacy     = RPC_C_AUTHN_LEVEL_PKT_PRIVACY  , // encrypts the argument value of each remote procedure call;
	};};

	// https://learn.microsoft.com/en-us/windows/win32/com/com-impersonation-level-constants ;
	class e_co_sec_imp {
	public: enum e_levels : dword {
	/* element    |  value                     |  brief desc;                        |
	|-------------+----------------------------+-------------------------------------|*/
	e_default     = RPC_C_IMP_LEVEL_DEFAULT    , // DCOM can choose the impersonation level using its normal security blanket negotiation algorithm;
	e_anonymous   = RPC_C_IMP_LEVEL_ANONYMOUS  , // a client is anonymous to the server;
	e_identity    = RPC_C_IMP_LEVEL_IDENTIFY   , // a server can obtain the client's identity and to impersonate the client for ACL checking;
	e_impersonate = RPC_C_IMP_LEVEL_IMPERSONATE, // a server can impersonate a client's security context while acting on behalf of the client; (for local resource only);
	e_delegate    = RPC_C_IMP_LEVEL_DELEGATE   , // a server may use a client's security context on other machines to access local and remote resources as a client;
	};};

	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializesecurity ;
	class CCoSecProvider {
	public:
		 CCoSecProvider (void); CCoSecProvider (const CCoSecProvider&) = delete; CCoSecProvider (CCoSecProvider&&) = delete;
		~CCoSecProvider (void) = default;

		TError&  Error (void) const;

		err_code Init (const e_co_sec_auth::e_levels, const e_co_sec_imp::e_levels);

		err_code Default (void);     // args: e_co_sec_auth::e_defaul, e_co_sec_imp::e_impersonate ;
		err_code NoIdentity (void);  // args: e_co_sec_auth::e_none, e_co_sec_imp::e_identity ;

	protected:
		CError      m_error;
	};
}}

#endif/*_SYS_COM_SVC_H_INCLUDED*/