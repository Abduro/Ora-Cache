#ifndef _ORAOLEDB_H_INCLUDED
#define _ORAOLEDB_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 20:27:37.6613548, UTC+4, Batumi, Sunday;
	This is Ebo Pack Oracle database provider interface declaration file;
*/
#include "ora.base.h"

namespace ora { namespace base { namespace oledb {

	using namespace ATL;
	using namespace shared::types;

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using CClsId = shared::sys_core::com::CClsId;
	using CProgId = shared::sys_core::com::CProgId;

	// https://github.com/MicrosoftDocs/cpp-docs/blob/main/docs/data/oledb/cenumeratoraccessor-class.md ;

	class CProv_Types {
	public:
	// ToDo: this enum element values require a clarification, .Net documentation shows different meanings of the values;
	// https://learn.microsoft.com/en-us/dotnet/api/system.data.oledb.oledbenumerator.getrootenumerator ; 
		enum _e_value : ushort {  // the element values are set from real dataset of the providers' enumeration;
			e_undef   = 0x0,  // a type of the provider is not defined; (default)
			e_regular = 0x1,  // regular data provider type;
			e_enum    = 0x2,  // this is a provider enumerator;
		};
#if (0)
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms711200(v=vs.85) ;
		enum _e_value : ushort {
			e_binder  = 0x0,  // indicates a provider binder that supports direct URL binder ;
			e_olap    = 0x1,  // this is a multidimensional (OLAP) provider (MDP) ;
			e_table   = 0x2,  // tabular data provider (TDP) ;
			e_enum    = 0x3,  // this is a provider enumerator ;
		};
#endif
	};

	// (1) https://learn.microsoft.com/en-us/windows/win32/api/oleidl/nn-oleidl-iparsedisplayname ;
	// (2) https://learn.microsoft.com/en-us/windows/win32/api/oleidl/nf-oleidl-iparsedisplayname-parsedisplayname ; 
	// (3) https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-imoniker ;

	class CProvider {
	public:
		 CProvider (void);
		 CProvider (_pc_sz _prog_id, _pc_sz _p_desc); // this constructor is for creation by ATL::CEnumeratorAccessor;
		 CProvider (const CProvider&);
		 CProvider (CProvider&&);      // vector allocator requires this move constructor;
		~CProvider (void) = default;

	public:
		const
		CClsId& ClsId (void) const;    // gets a reference to class identifier; (ra);
		CClsId& ClsId (void) ;         // gets a reference to class identifier; (rw);

		_pc_sz  Desc  (void) const;    // gets a brief description of the data provider;
		bool    Desc  (_pc_sz);        // sets a brief description; always returns true;
#if (0)
		bool    Is_enum (void) const;  // indicates this data provider has child enumeration;
		bool    Is_enum (const bool);  // sets enumeration field value; by default it is set to false;
#endif
		bool    Is_valid (void) const; // returns true in case if program identifier is set;

		const
		CProgId& ProgId(void) const;   // gets the data provider program identifier; (ra);
		CProgId& ProgId(void);         // gets the data provider program identifier; (rw);

		ushort  Type (void) const;
		bool    Type (const ushort);

#if defined(_DEBUG)
		enum e_print : uint32_t {
			e_all   = 0x0,             // prints out complete information of this class object: namespace, class name, attributes ;
			e_no_ns = 0x1,             // the same as above option, but no namespace;
			e_req   = 0x2,             // prints out this class object attribute values only;
		};
		CString Print (const e_print = e_print::e_all) const;
#endif
	public:
		CProvider&  operator = (const CProvider&);
		CProvider&  operator = (CProvider&&);          // std::vector allocator requires this 'move' operator;

		CProvider&  operator <<(_pc_sz _desc);         // sets a provider description;

		CProvider&  operator <<(const CClsId&);        // sets a class identifier;
		CProvider&  operator <<(const CProgId&);       // sets a program identifier;

		CProvider&  operator <<(const ushort _u_type);

	protected:
		CClsId  m_cls_id;
		CProgId m_prog_id;
		CString m_desc;
		bool    m_enum;
		ushort  m_type;
	};

	typedef ::std::vector<CProvider> t_raw_provs; typedef t_raw_provs TProvs;

	// https://learn.microsoft.com/en-us/cpp/data/oledb/cenumerator-class ;
	class CProvider_enum {
	public:
		 CProvider_enum (void);
		 CProvider_enum (const CProvider_enum&);
		 CProvider_enum (CProvider_enum&&) = delete; // not required yet;
		~CProvider_enum (void) = default;

	public:
		TError&  Error (void) const;
		const
		TProvs&  Get (void) const;
		err_code Set (void);  // enumerates all registered data providers; ToDo: data provider enumeration nodes are skipped;

#if defined(_DEBUG)
		CString Print (_pc_sz _pfx = _T("\t"), _pc_sz _sfx = _T("\n")) const;
#endif
		bool Registered (const _guid& _cls_id) const; // returns true if the registry contains the information of provider of given cls_id;

	public:
		CProvider_enum& operator = (const CProvider_enum&);
		CProvider_enum& operator = (CProvider_enum&&) = delete; // not required yet;

	private:
		CError m_error;
		t_raw_provs m_provs;
	};

	// https://docs.oracle.com/cd/E51173_01/win.122/e18594/intro.htm ;
	// https://docs.oracle.com/cd/E51173_01/win.122/e18594/using.htm ;
	// https://docs.oracle.com/cd/E51173_01/win.122/e18594/appxtype.htm ;

	class COraProvider : public CProvider { typedef CProvider TBase;
	public:
		 COraProvider (void); // creates this provider object with pre-defined values;
		 COraProvider (const COraProvider&) = delete; COraProvider (COraProvider&&) = delete;
		~COraProvider (void) = default;

	public:
		COraProvider& operator = (const COraProvider&);

	private:
		COraProvider& operator = (COraProvider&&);
	};

}}}

#endif/*_ORAOLEDB_H_INCLUDED*/