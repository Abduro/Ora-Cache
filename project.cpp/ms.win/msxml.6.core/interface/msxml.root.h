#ifndef _MSXML_ROOT_H_INCLUDED
#define _MSXML_ROOT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Jun-2025 at 12:40:35.559,UTC+4, Batumi;
	This is Ebo Pack MSXML document root node wrapper interface declaration file;
*/
#include "msxml.defs.h"
#include "msxml.gen.iface.h"

namespace shared { namespace xml { namespace ms {

	class CRoot {
	public:
		 CRoot (void);
		 CRoot (const TXmlElementPtr);
		~CRoot (void);

	public:
		err_code  Atts  (CNode_Atts&);  // sets input attributes to the node;

		TError&   Error (void) const ;
		bool   Is_valid (void) const ;  // check its interface pointer for nullptr;

		const
		TNodePtr& Ptr (void) const;     // gets raw interface pointer; (ro);
		TNodePtr& Ptr (void)      ;     // gets raw interface pointer; (rw);

		err_code  Kids  (CNode_Enum&);  // gets all children nodes;
		err_code  Name  (CAtlString&);  // gets this node name;
		err_code  Text  (CAtlString&);  // gets this node text;

	public:
		CRoot& operator << (const TXmlElementPtr);  // sets node COM-pointer;
		CRoot& operator << (const CNode_Atts&)   ;  // sets node attributes ;

		const
		TNodePtr& operator ()(void) const;
		TNodePtr& operator ()(void)      ;

	private:
		CError   m_error;
		TNodePtr m_ptr;
	};

}}}

#endif/*_MSXML_ROOT_H_INCLUDED*/