#ifndef _SFXTABSFMT_H_INCLUDED
#define _SFXTABSFMT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jul-2020 at 11:53:29p, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack Sfx tab control format interface declaration file.
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

	using namespace ex_ui::controls::sfx;
	using TBase = ex_ui::controls::format::CBase;
	using CFontSpec = ex_ui::controls::format::CFontSpec;

namespace format {

	typedef ::std::map<TStateValue, rgb_color> TVisualStateAssoc;
	typedef TVisualStateAssoc TBorderAssoc;

	class CColor {
	public:
		 CColor (void); CColor (const CColor&) = delete; CColor (CColor&&) = delete;
		~CColor (void);

		rgb_color Get  (const TStateValue) const;

	public:
		rgb_color Disabled (void) const;
		rgb_color Normal   (void) const;
		rgb_color Selected (void) const;

	public:
		CColor& operator = (const CColor&) = delete;
		CColor& operator = (CColor&&) = delete;
	};

	class CBorder {
	public:
		 CBorder (void); CBorder (const CBorder&) = delete; CBorder (CBorder&&) = delete;
		~CBorder (void);
	public:
		const
		CColor&  Color (void) const;
		CColor&  Color (void) ;

	public:
		CBorder& operator = (const CBorder&) = delete;
		CBorder& operator = (CBorder&&) = delete;
	private:
		CColor m_color;
	};

}
	using format::TBorderAssoc;

	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		const
		format::CBorder&  Border (void) const;
		void      Default(void);
	
	private:
		CFormat&  operator = (const CFormat&) = delete;
		CFormat&  operator = (CFormat&&) = delete;

	private:
		CControl& m_ctrl;
		format::CBorder   m_border;
	};

}}}}

#endif/*_SFXTABSFMT_H_D9B720FB_42AC_434C_B055_2F7BC83DECE9_INCLUDED*/