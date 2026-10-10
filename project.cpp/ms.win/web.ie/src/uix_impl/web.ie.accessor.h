#ifndef _WEB_IE_ACCESSOR_H_INCLUDED
#define _WEB_IE_ACCESSOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser object accessor class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 3:42:14p, UTC+7, Novosibirsk, Monday;
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { namespace core { using namespace ::ex_ui::web::IE::defs;

	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa752127(v=vs.85) ;
	class CAccessor {
	public:
		 CAccessor (CAxWindow& browser_ref);
		 CAccessor (void) = delete; CAccessor (const CAccessor&) = delete; CAccessor (CAccessor&&) = delete;
		~CAccessor (void) = default;

		TError&   Error (void) const;

		err_code  CmdTarget (TCmdTargetPtr& target_ref);
		err_code  Document0 (TDispatchPtr&  doc_ref); // Gets the automation object of the active document, if any;
		err_code  Document2 (TDocument2Ptr& doc_ref); // Gets information about the document, and examines and modifies the HTML elements and text in the document.
		err_code  Document3 (TDocument3Ptr& doc_ref);
		err_code  Element   (TElementPtr&   elm_ref, _pc_sz _p_el_id);

	private:
		CAccessor& operator = (const CAccessor&) = delete; CAccessor& operator = (CAccessor&&) = delete;
		CAxWindow& m_browser;
		CError     m_error;
	};

}}}}

#endif/*_WEB_IE_ACCESSOR_H_INCLUDED*/