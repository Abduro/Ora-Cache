#ifndef _GDI_PLUS_ERR_H_INCLUDED
#define _GDI_PLUS_ERR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2025 at 12:41:25.128, UTC+4, Batumi, Monday;
	This is Ebo Pack GDI+ error status wrapper interface declaration file;
*/
#include "gdi_plus.defs.h"
namespace ex_ui { namespace draw { namespace gdi_pls {

	/*
		ToDo: not sure the enumeration below would be useful; it requires a review;
		The review : the enumeration below inherits the original gdi+ one, but can have additional elements for extending gdi+ status states;
	*/
	// https://learn.microsoft.com/en-us/windows/win32/api/gdiplustypes/ne-gdiplustypes-status ;
	typedef Gdiplus::Status TStatus;

	/*
		what is your name? a shorter name...
		Lilu... (c) 5th Element, (43:35);
	*/
	enum  TAlias : uint32_t {
		e_no_err      = TStatus::Ok                       ,
		e_generic     = TStatus::GenericError             ,
		e_inv_arg     = TStatus::InvalidParameter         ,
		e_no_memory   = TStatus::OutOfMemory              ,
		e_obj_busy    = TStatus::ObjectBusy               ,
		e_out_buff    = TStatus::InsufficientBuffer       ,
		e_not_impl    = TStatus::NotImplemented           ,
		e_win_err     = TStatus::Win32Error               ,
		e_inv_state   = TStatus::WrongState               ,
		e_aborted     = TStatus::Aborted                  ,
		e_no_file     = TStatus::FileNotFound             ,
		e_overflow    = TStatus::ValueOverflow            ,
		e_no_access   = TStatus::AccessDenied             ,
		e_unk_image   = TStatus::UnknownImageFormat       ,
		e_no_family   = TStatus::FontFamilyNotFound       ,
		e_no_style    = TStatus::FontStyleNotFound        ,
		e_not_ttf     = TStatus::NotTrueTypeFont          ,
		e_unsup_ver   = TStatus::UnsupportedGdiplusVersion,
		e_not_init    = TStatus::GdiplusNotInitialized    ,
		e_no_prop     = TStatus::PropertyNotFound         ,
		e_unsup_prop  = TStatus::PropertyNotSupported     ,
		e_inited      = e_unsup_prop + 1                  , // this is the status of the object being in initialized state;
		e_uninited    = e_unsup_prop + 2                  , // this is the status of extension mode, that is set after calling release/unload method; 
	};

	/*
		system error handling is not efficient for catching GDI+ errors due to this library produces its own internal errors
		that are partially somehow related to WinAPI but in the most cases they aren't;

		the main purpose of the GDI+ error adapter is to expose some description of the error state of the library;
		such approach does not require an inheritance from shared::sys_core::CError;
	*/
	// ToDo: this class and the adapter of sys error use different enums, must be re-viewed;
	class CErr_Assoc {
	public:
		 CErr_Assoc (const TAlias = TAlias::e_no_err, const err_code = TErrCodes::no_error, const bool b_is_sys = false);
		 CErr_Assoc (const CErr_Assoc&);
		 CErr_Assoc (CErr_Assoc&&) = delete;
		~CErr_Assoc (void) ;

	public: // accessr(s) and mutator(s);

		err_code   Code (void) const;      // gets syetem error code;
		const bool Code (const err_code);  // sets system error code; returns true in case of changing value;

		bool Is_sys (void) const;
		void Is_sys (const bool);

		TAlias Alias (void) const;
		bool   Alias (const TAlias);

	public:
		bool   Set (const TAlias, const err_code, const bool b_is_sys); // returns true if one of the attributes is changed;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_req) const;
#endif
	public:
		CErr_Assoc& operator = (const CErr_Assoc&);
		CErr_Assoc& operator = (CErr_Assoc&&) = delete;
		CErr_Assoc& operator <<(const err_code);
		CErr_Assoc& operator <<(const bool _is_sys);
		CErr_Assoc& operator <<(const TAlias);

	private:
		TAlias    m_status  ;
		err_code  m_err_code;   // this is associated system error handling error result;
		bool      m_b_sys   ;   // this is a flag that indicates that system information is accessible through ::FormatMessage();
	};

	class CErr_Adapter {
	public:
		 CErr_Adapter (const TAlias = TAlias::e_no_err, _pc_sz _p_desc = nullptr);
		 CErr_Adapter (const CErr_Adapter&);
		 CErr_Adapter (CErr_Adapter&&) = delete;
		~CErr_Adapter (void);

	public: // attribute(s) and mutator(s);
		_pc_sz    Desc (void) const;         // gets status description;
		bool      Desc (_pc_sz)    ;         // sets status description; returns true in case of changing value;

		TAlias    Status (void) const;       // gets status value;
		bool      Status (const TAlias);     // sets status value; returns true in case of changing the status value;
		const
		CErr_Assoc&  Sys_err (void) const;   // returns a reference to the object associated with the system error; (r-o);
		CErr_Assoc&  Sys_err (void)      ;   // returns a reference to the object associated with the system error; (r-w);

	public: // method(s);
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		bool      Set (const TAlias, _pc_sz _p_desc) ; // sets error adapter data in one call; returs true if at least one of the attributes is changed;

	public:
		CErr_Adapter& operator = (const CErr_Adapter&);
		CErr_Adapter& operator = (CErr_Adapter&&) = delete;

		CErr_Adapter& operator <<(_pc_sz _p_desc);
		CErr_Adapter& operator <<(const TAlias);

		CErr_Adapter& operator <<(const CErr_Assoc&);

	private:
		TAlias     m_status;
		CString    m_desc  ;
		CErr_Assoc m_assoc ;
	};

#if (0)
	class CErr_Adapter {
	public:
		 CErr_Adapter (void);
		 CErr_Adapter (const TStatus, _pc_sz _p_desc, const err_code, const bool _b_is_sys);
		 CErr_Adapter (const CErr_Adapter&);
		 CErr_Adapter (CErr_Adapter&&) = delete;
		 CErr_Adapter (const TStatus);
		~CErr_Adapter (void) ;

	public:
		err_code Code   (void) const;                    // gets error code; there is no set() of code due to it can be done through setting status value only;
		_pc_sz   Desc   (void) const;                    // gets the status description;
		bool     Desc   (_pc_sz)    ;                    // sets the status description; returns true in case of change, otherwise, false that indicates no change;
		bool     Is_sys (void) const;
#if defined(_DEBUG)
		CString  Print  (void) const;
#endif
		err_code Set (const TStatus, _pc_sz _p_desc, const err_code, const bool _b_is_sys);    // sets the current value of the status and its description;

		TStatus  Status (void) const;                    // gets the status code;
		bool     Status (const TStatus);                 // sets the status code;

	public:
		CErr_Adapter& operator = (const CErr_Adapter&);  // just making a copy;
		CErr_Adapter& operator = (CErr_Adapter&&) = delete;
		CErr_Adapter& operator <<(const  TStatus);       // sets the status code; if the code is predefined the error discription is updated;
		CErr_Adapter& operator <<(_pc_sz _p_desc);       // sets a description of the error status;
		CErr_Adapter& operator <<(const err_code);       // sets associated system error code;
		CErr_Adapter& operator <<(const bool _b_sys);    // sets a flag of an avalablility getting details from GetLastErros();

		CErr_Adapter& operator >>(TError&);              // takes an input error object and sets hresult error code with description to this object;

		operator err_code (void) const;
		operator TStatus  (void) const;

	protected:
		err_code  m_code;      // this is associated system api error code for this status;
		CString   m_desc;      // status description;
		bool      m_is_sys;    // indicates an accessability of getting details from the win api;
		TStatus   m_status;    // the status value;
	};
#endif

}}}

using   TStatus = ex_ui::draw::gdi_pls::TStatus;

typedef ex_ui::draw::gdi_pls::CErr_Assoc   TErrAssoc;
typedef ex_ui::draw::gdi_pls::CErr_Adapter TErrAdapt;

typedef ::std::map<uint32_t, TErrAdapt>    TRawStatus; // the key that is based on gdi+ status enumeration is intentionally replaced by plain data type;

namespace ex_ui { namespace draw { namespace gdi_pls {

	class CErr_Adapt_enum {
	public:
		 CErr_Adapt_enum (const bool _b_auto = true);       // if b_auto is true, the Set() is called up;
		 CErr_Adapt_enum (const CErr_Adapt_enum&) = delete;
		 CErr_Adapt_enum (CErr_Adapt_enum&&) = delete;
		~CErr_Adapt_enum (void);

	public:
		const TErrAdapt&  Get (const uint32_t _code) const; // returns a reference to an object specified by status code; if not found >> fake object; not-thread-safe;
		const TRawStatus& Raw (void) const;                 // returns a reference to the collection of all gdi+ status;
		
		err_code Set (void);           // fills this enumerarion by the set of predefined gdi+ status;

	public: static
		CErr_Adapt_enum&  Ref (void) ; // this is the singleton of this enumeration object;

	private:
		CErr_Adapt_enum& operator = (const CErr_Adapt_enum&) = delete;
		CErr_Adapt_enum& operator = (CErr_Adapt_enum&&) = delete;

	private:
		TRawStatus m_raw_stats;
	};
}}}

typedef ex_ui::draw::gdi_pls::CErr_Adapt_enum TErrAdapt_enum;

#endif/*_GDI_PLUS_ERR_H_INCLUDED*/