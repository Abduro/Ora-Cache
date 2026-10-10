#ifndef _WEB_IE_SCRIPT_H_INCLUDED
#define _WEB_IE_SCRIPT_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 07-Oct-2026 at 20:14:07.784, UTC+4, Batumi, Wednesday;
	This is IE JavaScript execution engine wrapper interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768904(v=vs.85) ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768898(v=vs.85) << adds charset property;
	using IScriptElement = IHTMLScriptElement;
	typedef CComPtr<IScriptElement> TScriptElPtr;

	typedef ::std::vector<CString> func_names_t;

	class CScript {
	public:
		 CScript (void) = delete;
		 CScript (TBrwWndPtr&); CScript (const CScript&) = delete; CScript (CScript&&) = delete;
		~CScript (void);

		TError&  Error (void) const;
		err_code Evaluate (_pc_sz _p_code, CComVariant& _result) const; // uses eval() function that replaces the ScriptExec() one;
		err_code Execute (_pc_sz _p_code); // this function uses ScriptExec(), no returned result from the script executing, and it is deprecated;

		err_code Get_Object (void); // https://learn.microsoft.com/en-us/previous-versions/aa752642(v=vs.85) ; IHTMLDocument interface has this property;
		err_code Get_Names (void);  // gets function / method names;
		bool     Is_func (_pc_sz _fn_name) const; // checks given name for it is a name of java script function or mot;

	private:
		CScript& operator = (const CScript&) = delete; CScript& operator = (CScript&&) = delete;
		mutable
		CError       m_error;
		TBrwWndPtr& m_control;
		TDispatchPtr m_script;   // this is the script object dispatch pointer;
	};

	using IElementColl = IHTMLElementCollection;
	typedef CComPtr<IElementColl> TElCollPtr;

	// https://learn.microsoft.com/en-us/previous-versions/aa752604(v=vs.85) ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa703928(v=vs.85) ;
	class CScript_Collection {
	public:
		 CScript_Collection (void) = delete;
		 CScript_Collection (TBrwWndPtr&); CScript_Collection (const CScript_Collection&) = delete; CScript_Collection (CScript_Collection&&) = delete;
		~CScript_Collection (void);

		TError&  Error (void) const;

		err_code Get (void);       // gets a collection of the script items which belongs to HTML document;
		err_code Get_Items (void); // enumerates script nodes (items) by using HTML elements' collection;

	private:
		CScript_Collection& operator = (const CScript_Collection&) = delete; CScript_Collection& operator = (CScript_Collection&&) = delete;
		mutable
		CError       m_error;
		TBrwWndPtr& m_control;
		TElCollPtr   m_scripts;
	};

	using CScript_Coll = CScript_Collection;

}}}
#endif/*_WEB_IE_SCRIPT_H_INCLUDED*/