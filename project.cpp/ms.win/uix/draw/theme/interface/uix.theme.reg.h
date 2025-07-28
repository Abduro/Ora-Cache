#ifndef _UIX_THEME_REG_H_INCLUDED
#define _UIX_THEME_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.con) on 29-Jun-2025 at 07:36:53.5666, UTC+4, Batumi, Sunday;
	This is Ebo Pack custom theme registry storage base interface declaration file;
*/
#include "uix.theme.inc.h"
#include "uix.theme.named.h"

namespace ex_ui { namespace theme { namespace storage {

	using namespace ex_ui::theme;

	class CReg_router {
	public:
		class CTestCase {
		public:
			 CTestCase (const CReg_router&); CTestCase (void) = delete; CTestCase (const CTestCase&) = delete; CTestCase (CTestCase&&) = delete;
			~CTestCase (void);
		public:
			CString Control (const uint32_t _ndx) const; // returns the registry key path for test cases of particular user control;
			CString Root (void) const; // ex_ui::theme::Get_current().Load() must be called before as least once; ToDo: light theme must be set by default;

		private:
			CTestCase& operator = (const CTestCase&) = delete; CTestCase& operator = (CTestCase&&) = delete;
		private:
			const CReg_router&  m_router;
		};

	public:
		 CReg_router (void) ; CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&);
		~CReg_router (void) ;

	public:
		const
		CCurrent&  CurrentTheme (void) const;
		CCurrent&  CurrentTheme (void) ;

		_pc_sz Element (void) const;                // composes the registry path to the UI element by using currently selected theme;
		_pc_sz Element (const TThemePalette, const TThemePart, const TThemeElement) const;
		_pc_sz Marker  (const TColorMarker&) const; // composes the registry path in accordance with input color marker;

		_pc_sz Palette (void) const;                // composes the registry path for input palette by using currently selected theme;
		_pc_sz Palette (const TThemePalette) const; // composes the registry path for input palette;

		_pc_sz Part    (void) const;                // composes the path to the part by using currently selected theme;
		_pc_sz Part    (const TThemePalette, const TThemePart) const;

		_pc_sz State   (void) const ;               // composes the path to the element state by using currently selected theme;
		_pc_sz State   (const TThemePalette, const TThemePart, const TThemeElement, const TThemeState) const;

		_pc_sz Theme   (void) const;                                     // returns the path to the theme of currently selected palette;
		_pc_sz Theme   (const TThemePalette) const;                      // returns the path to currently selected theme node;
		_pc_sz Theme   (const TThemePalette, const uint32_t _ndx) const; // returns the path of the theme node by specified index;

		HKEY   Root    (void) const;
		_pc_sz Themes  (void) const;                // this is the path to the root node of the named/custom themes; the entry point;
		_pc_sz Current (void) const;                // this is the registry key name which contains the info of currently selected theme;

		const
		CTestCase&   TestCase (void) const;

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;
	private:
		HKEY      m_root;
		CCurrent  m_current;  // the currently selected theme;
		CTestCase m_test;
	};

	CReg_router&  Get_router (void);  // returns the reference to the singleton of the router object;

	class CRegistry { // if the path is not provided to one of the functions of this class that means current theme is used;
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

	public:
		TError&  Error (void) const;
		err_code Load  (const TThemePalette, CNamed_Enum&); // loads custom themes of the palette specified;
		err_code Load  (CNamed_Enum&);

		err_code Load  (CCurrent&);                  // loads current theme data from the registry; the current theme is inteaned from router;

		err_code Node  (_pc_sz _p_path, CElement&);
		err_code Node  (TRawElements&);              // returns the error in case when no elements found for parent part node;

		err_code Node  (_pc_sz _p_path, CNamed&);    // loads the custom theme by input reqistry key path;
		err_code Node  (CNamed&);                    // loads the custom theme; the theme index is taken from currently selected theme;

		err_code Node  (CPalette&);                  // loads palette that is currently selected for getting available themes;
		err_code Node  (_pc_sz _p_path, CPalette&);
		err_code Node  (_pc_sz _p_path, CPart&);

		err_code Node  (TRawNamed&);                 // loads all registered custom themes for currently selected palette;
		err_code Node  (TRawPalettes&);              // loads all available palettes that are stored in the registry;
		err_code Node  (TRawParts&);                 // returns the error in case when no parts found for the parent palette node;

		err_code Value (_pc_sz _p_path, CState&);    // it is supposed the state identifier is already set;
		err_code Value (TRawStates&);                // gets values of all states by using currently selected theme;
		err_code Value (_pc_sz _p_path, const TThemeState, CState&);

	public:
		CRegistry& operator = (const CRegistry&) = delete;
		CRegistry& operator = (CRegistry&&) = delete;

	private:
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

typedef ex_ui::theme::storage::CRegKey_Ex TRegKeyEx;
typedef TRegKeyEx::CCache TKeyCache;
typedef TRegKeyEx::CValue TKeyValue;

#endif/*_UIX_THEME_REG_H_INCLUDED*/