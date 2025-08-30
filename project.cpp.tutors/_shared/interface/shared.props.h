#ifndef _SHARED_PROPS_H_INCLUDED
#define _SHARED_PROPS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 04:39:42.954, UTC+4, Batume, Saturday;
	This is Ebo Pack generic property interface declaration file;
*/
#include "shared.defs.h"
#include "shared.dbg.h"

namespace shared { namespace common {

	using namespace shared::types;

	interface IProperty_Events
	{
		virtual bool IProperty_IsChanged (void) { return false; }
	};

	// for this time a property has DWORD value and cannot have other data type; it looks like a template must be created for flexibility;
	class CProperty {
	public:
		CProperty (const uint32_t _n_value = 0, _pc_sz _p_name = _T("#prop"), IProperty_Events* = nullptr);
		CProperty (const CProperty& );
		CProperty (CProperty&&) = delete; // not required yet;
		virtual ~CProperty (void);

	public:
		bool     Has   (const uint32_t) const;
		bool     Modify(const uint32_t, const bool _bApply); // returns true in case when the value is changed;

		_pc_sz   Name  (void) const;
		bool     Name  (_pc_sz) ;     // returns 'true' in case of changig the name value; case sensitive; no check for null or whitespaces;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		uint32_t& Value (void) const;
		uint32_t& Value (void)      ; // callee callback event cannot be invoked;

	public:
		uint32_t Get (void) const;
		bool     Set (uint32_t _value);  // returns true if value is changed;

		IProperty_Events* Events (void) const;
		HRESULT           Events (IProperty_Events*);// always return true, even in case the pointer is null; may cause a deadlock in case of recursion;

	public:
		operator const uint32_t  (void)  const;
		CProperty&   operator  = (const CProperty&); // property event callback is copied too, but potentially it may be dangerous;
		CProperty&   operator << (const uint32_t);
		CProperty&   operator += (const uint32_t);
		CProperty&   operator -= (const uint32_t);
		CProperty&   operator << (IProperty_Events*);
		CProperty&   operator << (_pc_sz _p_name);

	public: // Event callback pointer is not taken into account;
		bool operator != (const CProperty&) const;
		bool operator == (const CProperty&) const;
		bool operator != (uint32_t  _value) const;
		bool operator == (uint32_t  _value) const;

	protected:
		uint32_t m_value;           // this is not just a numeric value, but OR-ed flags set in the most cases;
		IProperty_Events* m_callee; // the pointer to the callback interface;
		CString  m_name ;           // the name of this property, just for informative print out;
	};
}}

#endif/*_SHARED_PROPS_H_INCLUDED*/