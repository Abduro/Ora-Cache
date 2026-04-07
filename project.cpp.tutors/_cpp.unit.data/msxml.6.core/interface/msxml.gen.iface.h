#ifndef _SHAREDXMLGENIFACE_H_INCLUDED
#define _SHAREDXMLGENIFACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Aug-2019 at 7:41:45a, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack shared lite generic XML data elements interface declaration file.
*/
#include "msxml.defs.h"

namespace shared { namespace xml { namespace ms {

	class CAttr {
	public:
	    CAttr (void);
	   ~CAttr (void);

	public:
		const bool   Is    (void) const;
		_pc_sz       Name  (void) const;
		err_code     Name  (_pc_sz)    ;
		CString&  Name_Ref (void)   ;
		const
		_variant_t&  Value (void) const;
		_variant_t&  Value (void)      ;

	public:
		const bool   ToBool (const bool _b_def) const;
		err_code     ToBool (const bool);
		const LONG   ToLong (const LONG _l_def) const;
		err_code     ToLong (const LONG);
		CString      ToText (void) const;
		err_code     ToText (_pc_sz)    ;
#if defined(_DEBUG)
		CString   Print (_pc_sz _lp_sz_sep) const;
#endif
	public:
		operator CString (void) const;
		operator const bool (void) const;
		operator const LONG (void) const;

	public:
		const bool operator== (const bool) const;
		const bool operator== (_pc_sz _lp_sz_name) const;
	private:
		_variant_t   m_value; // actually, attribute value is just a text, but for convenience of data conversion a variant is used;
		CString   m_name ;
	};

	typedef ::std::map<CString, CAttr> TAttributes;

	class CAttr_Mode {
	public:
	    CAttr_Mode (void);
	   ~CAttr_Mode (void);

	public:
		const bool&  AutoCreate(void) const;
		      bool&  AutoCreate(void)      ;
		const
		CString&  LastName  (void) const;
		CString&  LastName  (void)      ;

	public:
		operator const bool    (void) const;
		operator const
		           CString& (void) const;
	public:
		CAttr_Mode& operator = (const bool _b_auto_create);
		CAttr_Mode& operator = (_pc_sz  _lp_sz_last_name );
	private:
		bool         m_b_auto_create;   // if true, an attribute is automatically created in cases when it does not exist;
		CString   m_the_last;        // the last name of selected attribute if any;
	};

	class CAttr_Enum {

	public:
	    CAttr_Enum (void) ;
	   ~CAttr_Enum (void) ;

	public:
		err_code     Add (const CAttr&);
		err_code     Add (_pc_sz lp_sz_name, const _variant_t& _val);
		err_code     Del (_pc_sz lp_sz_name);
		const
		CAttr&  Get (_pc_sz lp_sz_name) const;
		CAttr&  Get (_pc_sz lp_sz_name)      ;
		bool         Has (_pc_sz lp_sz_name) const;
		const
		CAttr_Mode&  Mode(void) const;
		CAttr_Mode&  Mode(void)      ;
		const
		TAttributes& Ref (void) const;
#if defined(_DEBUG)
		CString   Print (_pc_sz _lp_sz_sep) const;
#endif
	public:
		CAttr_Enum&  operator += (const CAttr&) ;        // adds an attribute provided to the set;
		CAttr_Enum&  operator -= (_pc_sz lp_sz_name) ;        // removes attribute from the set by attribute name specified;
		CAttr_Enum&  operator <= (const bool _b_auto_create); // sets attribute auto-creation mode;
		CAttr_Enum&  operator <= (_pc_sz  _lp_sz_last_name ); // sets/selects the last name of attribute;
		CAttr_Enum&  operator << (const bool _bl_new_value ); // sets a bool value to the last selected attribute;
		CAttr_Enum&  operator << (const LONG _ln_new_value ); // sets a long value to the last selected attribute;
		CAttr_Enum&  operator << (_pc_sz _lp_sz_new_value );  // sets a string value to the last selected attribute;
	public:
		operator const CAttr_Mode& (void) const;
		operator       CAttr_Mode& (void)      ;
	private:
		CAttr_Mode   m_mode;
		TAttributes  m_atts;
	};

	typedef CAttr_Enum CNode_Atts;

	class CNode_Enum;
	class CNode {
	public:
	    CNode (void) ;
	    CNode (const CNode&);
	   ~CNode (void) ;

	public:
		const
		CAttr&  Att (_pc_sz lp_sz_name) const;
		const
		CNode_Atts&  Attributes(void) const;
		CNode_Atts&  Attributes(void)      ;
		const
		CNode&       Child     (_pc_sz _lp_sz_name) const;
		const
		CNode_Enum*  Children  (void) const;
		bool         Is        (void) const;
		bool         Is        (_pc_sz _lp_sz_name) const;
		_pc_sz       Name      (void) const;
		err_code     Name      (_pc_sz)    ;
		CString&  Name_Ref  (void)      ;
		_pc_sz       Text      (void) const;
		err_code     Text      (_pc_sz)    ;
		CString&  Text_Ref  (void)      ;
#if defined(_DEBUG)
		CString   Print     (_pc_sz  _lp_sz_sep) const;
#endif
	public:
		bool operator == (_pc_sz lp_sz_name) const; // compares a node name with provided one;
	public:
		CNode& operator= (const CNode&);  // copy constructor for creating new kids' pointer and copying data;
	private:
		CString   m_text;
		CString   m_name;
		CNode_Atts   m_atts;
		CNode_Enum*  m_kids;
	};

	typedef ::std::vector<CNode> TNodes;

	class CNode_Enum {
	public:
	    CNode_Enum (void) ;
	    CNode_Enum (const CNode_Enum&);
	   ~CNode_Enum (void) ;

	public:
		err_code      Add   (const CNode&);
		const TNodes  Filter(_pc_sz _lp_sz_name) const; // multiple node names can be provided, like this: {name_1;name_2};
		const CNode&  Find  (_pc_sz _lp_sz_name) const;
		const TNodes& Raw   (void) const  ;
#if defined(_DEBUG)
		CString    Print (_pc_sz _lp_sz_sep ) const;
#endif
	public:
		CNode_Enum& operator = (const CNode_Enum&); // copy constructor for creating new nodes and preserving their dynamic data;
	private:
		TNodes   m_nodes;
	};
}}}

typedef shared::xml::ms::CAttr       TXmlAtt  ;
typedef shared::xml::ms::CAttr_Enum  TXmlAtts ;
typedef shared::xml::ms::CAttr_Mode  TXmlMode ; // it looks like not good typedef name; it is possibly much better to set TXmlAttMode;
typedef shared::xml::ms::CNode       TXmlNode ;
typedef shared::xml::ms::CNode_Enum  TXmlNodes;

#endif/*_SHAREDXMLGENIFACE_H_INCLUDED*/