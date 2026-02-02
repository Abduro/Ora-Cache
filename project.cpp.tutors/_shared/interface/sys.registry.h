#ifndef _SYS_REGISTRY_H_INCLUDED
#define _SYS_REGISTRY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Nov-2025 at 13:30:08.417, UTC+4, Batumi, Sunday;
	This is Ebo Pack system registry storage wrapper interface class declaration file;
	-----------------------------------------------------------------------------
	The registry storage wrapper interface is adopted extraction from Ebo Pack custom theme registry interface;
*/
#include "shared.defs.h"
#include "sys.reg.router.h"

namespace shared { namespace sys_core { namespace storage {
	using namespace shared::defs;
	using CRegKey = ::ATL::CRegKey;

	class CRegistry {
	using e_shaders = route::CShaders::e_types;
	using e_element = route::CTheme::e_element;
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

		TError&  Error (void) const;

		CString  Value (const e_element) const;  // returns color value (hex) of element specified; 
		CString  Value (_pc_sz _p_object, const e_shaders) const; // returns the path to the shader source file; if empty string is returned, the error occurs;

		CRegistry& operator = (const CRegistry&) = delete;
		CRegistry& operator = (CRegistry&&) = delete;

	private:
		mutable
		CError   m_error;
	};

	class CRegKey_Ex {
	public:
		class CCache {
		public:
			CCache (_pc_sz _p_path = 0, _pc_sz _name = 0) ; CCache (const CCache&) = delete; CCache (CCache&&) = delete; ~CCache (void) = default;
			bool   Is   (void) const; // returns 'true' in case if trimmed registry key is not null or empty;
			_pc_sz Name (void) const;
			_pc_sz Path (void) const;
			bool   Name (_pc_sz);     // returns 'true' in case of name value change; the input value is trimmed; null or empty name is accepted;
			bool   Path (_pc_sz);     // returns 'true' in case of key path change; the input value is trimmed; neither null nor emptiness is accepted;
			bool   Set  (_pc_sz _p_key_path, _pc_sz _p_value_name); // returns 'true' in case if value name or key path is changed;
			CCache& operator << (_pc_sz _p_path); // calls this->Path(_p_name);
			CCache& operator >> (_pc_sz _p_name); // calls this->Name(_p_name);
			CCache& operator =  (const CCache& ) = delete; CCache& operator = (CCache&&) = delete;
			operator bool (void) const; // returns result of this->Is();
		private:
			CString  m_name; // a name of the key value; empty string is accepted;
			CString  m_path; // a path to the registry key; empty string is not accepted;
		};
		class CValue {
		public:
			 CValue (CRegKey_Ex& _the_key); CValue (void) = delete; CValue (const CValue&) = delete; CValue (CValue&&) = delete;
			~CValue (void) = default;
		public:
			const
			CCache& Cache (void) const;
			CCache& Cache (void) ;

			uint32_t GetDword (_pc_sz _p_name);
			uint32_t GetDword (_pc_sz _p_key_path, _pc_sz _p_name);

			CString GetString (_pc_sz _p_name); // it is assumed the key is already open; empty value name means (default);
			CString GetString (_pc_sz _p_key_path, _pc_sz _p_name)/* const*/; // returns empty string in case of error;

		public:
			CValue& operator = (const CValue&) = delete; CValue& operator = (CValue&&) = delete;
			const
			CCache& operator ()(void) const;   // gets the reference to cache field value; (ro)
			CCache& operator ()(void);         // gets the reference to cache field value; (rw)

			operator _pc_sz  (void) /*const*/; // gets registry value by cached key path and value name; if error occurs, empty string is returned;

		private:
			CRegKey_Ex& m_the_key;
			CCache  m_cache;
		};

	public:
		 CRegKey_Ex (void); CRegKey_Ex (const CRegKey_Ex&) = delete; CRegKey_Ex (CRegKey_Ex&&) = delete;
		~CRegKey_Ex (void);

	public:
		TError& Error (void) const;
		const
		CValue& Value (void) const;
		CValue& Value (void) ;

	public:
		CRegKey_Ex& operator = (const CRegKey_Ex&) = delete;
		CRegKey_Ex& operator = (CRegKey_Ex&&) = delete;

		TError&  operator [](const long _not_used) const; // returns the reference to the error object of this class; (ro)
		CError&  operator [](const long _not_used) ;      // returns the reference to the error object of this class; (rw)

		CRegKey& operator ()(void); // returns the reference to the CRegKey member of this class;

		const
		CValue&  operator [](_pc_sz _not_used) const;
		CValue&  operator [](_pc_sz _not_used) ;

	private:
		mutable
		CError  m_error;
		CValue  m_value;
		CRegKey m_key  ;
		friend class CValue;
	};
}}}

typedef shared::sys_core::storage::CRegKey_Ex TRegKeyEx;
typedef TRegKeyEx::CCache TKeyCache;
typedef TRegKeyEx::CValue TKeyValue;

shared::sys_core::storage::CRegistry&  Get_registry (void); // returns the reference to the singleton of the registry object;

#endif/*_SYS_REGISTRY_H_INCLUDED*/