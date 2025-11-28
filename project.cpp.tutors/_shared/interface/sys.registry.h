#ifndef _SYS_REGISTRY_H_INCLUDED
#define _SYS_REGISTRY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Nov-2025 at 13:30:08.417, UTC+4, Batumi, Sunday;
	This is Ebo Pack system registry storage wrapper interface class declaration file;
	-----------------------------------------------------------------------------
	The registry storage wrapper interface is adopted extraction from Ebo Pack custom theme registry interface;
*/
#include "shared.defs.h"
namespace shared { namespace sys_core { namespace storage {
	using namespace shared::defs;
	using CRegKey = ::ATL::CRegKey;

	class CReg_router {
	public:
		class CRoot {
		public:
			enum e_renderer : uint32_t { // the renderer identifier changes the root path of the tutorials;
			     e_direct_x = 0x0,
				 e_open_gl  = 0x1,       // default value for this version of the implementation;
			};
		public:
			CRoot (void); CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

			const
			HKEY    Key  (void) const;
			_pc_sz  Path (void) const;              // returns the root path without renderer identifier;
			CString Path (const e_renderer) const;  // returns the root path to the renderer key by input renderer value;

			e_renderer Renderer (void) const;       // returns currently set renderer identifier;
			const bool Renderer (const e_renderer); // sets current renderer identifier; returns 'true' in case of value change;

		private:
			CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
		};

		class CShaders {
		public:
			// https://en.wikipedia.org/wiki/Shader ;
			enum e_types : uint32_t { // this enumeration is an abstraction from the constant values of OpenGL and DirectX shader types;
			e__undef    = 0x0,
			e_fragment  = 0x2, // fragment shaders, also known as pixel shaders, compute color and other attributes of each 'fragment' (a single output pixel);
			e_vertex    = 0x6, // transforms each vertex's 3D position in virtual space to the 2D coordinate at which it appears on the screen;
			};
		public:
			CShaders (void) ; CShaders (const CShaders&) = delete; CShaders (CShaders&&) = delete; ~CShaders (void) = default;

			CString  Path (const e_types) const;    // returns the path to specified type of shader;
			_pc_sz   Root (void) const;             // gets root key path for all shader types;

		private:
			CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
		};

		class CTheme {
		public:
			enum e_element : uint32_t {
			e_bkgnd  = 0x0, // background color;
			e_border = 0x1, // border color (any state of the control that the border belongs to);
			};
			CTheme (void) ; CTheme (const CTheme&) = delete; CTheme (CTheme&&) = delete; ~CTheme (void) = default;

			CString Path (const e_element) const; // returns the registry path to the color value of the element specified;
			_pc_sz  Root (void) const;

			static
			_pc_sz  To_str (const e_element);

		private:
			CTheme& operator = (const CTheme&) = delete; CTheme& operator = (CTheme&&) = delete;
		};

	public:
		 CReg_router (void) ; CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&);
		~CReg_router (void) ;

		const
		CRoot&  Root (void) const;
		CRoot&  Root (void) ;
		const
		CShaders& Shaders (void) const;
		CShaders& Shaders (void) ;
		const
		CTheme& Theme (void) const;
		CTheme& Theme (void) ;

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;

		CRoot    m_root;
		CShaders m_shaders;
		CTheme   m_theme;
	};

	class CRegistry {
	using e_shaders = CReg_router::CShaders::e_types;
	using e_element = CReg_router::CTheme::e_element;
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

		TError&  Error (void) const;

		CString  Value (const e_element&) const;  // returns color value (hex) of element specified; 
		CString  Value (const e_shaders, _pc_sz _p_name) const; // if empty string is returned, the error occurs;

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

shared::sys_core::storage::CReg_router&  Get_reg_router (void); // returns the reference to the singleton of the router object;
shared::sys_core::storage::CRegistry&  Get_registry (void); // returns the reference to the singleton of the registry object;

#endif/*_SYS_REGISTRY_H_INCLUDED*/