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
		 CColor (void) = default; CColor (const CColor&) = default; CColor (CColor&&) = delete;
		~CColor (void) = default;

		rgb_color Get  (const TStateValue) const;

		rgb_color Disabled (void) const;
		rgb_color Normal   (void) const;
		rgb_color Selected (void) const;

		CColor& operator = (const CColor&) = default;
		CColor& operator = (CColor&&) = delete;
	};

	class CBorder {
	public:
		 CBorder (void); CBorder (const CBorder&); CBorder (CBorder&&) = delete;
		~CBorder (void);
		const
		CColor&  Color (void) const;
		CColor&  Color (void) ;

		uint8_t  Thickness (void) const;
		bool     Thickness (const uint8_t);  // returns 'true' in case of thickness value is changed;

		CBorder& operator = (const CBorder&);
		CBorder& operator <<(const CColor&);
		CBorder& operator <<(uint8_t _u_thick);

	private:
		CBorder& operator = (CBorder&&) = delete;
		CColor   m_color;
		uint8_t  m_thick;  // equals to 1px by default, because in the most cases the border should exist, otherwise, its thickness is specified intentionly;
	};

	class CPage {
	public:
		 CPage (void); CPage (const CPage&); CPage (CPage&&) = delete;
		~CPage (void) = default;

		const
		CBorder& Border (void) const;
		CBorder& Border (void) ;

		CPage&  operator = (const CPage&);
		CPage&  operator <<(const CBorder&);

	private:
		CPage&  operator = (CPage&&) = delete;
		CBorder m_border;
	};
}
	using format::TBorderAssoc;

	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		const format::CBorder& Border (void) const;

		void      Default (void);
	
	private:
		CFormat&  operator = (const CFormat&) = delete;
		CFormat&  operator = (CFormat&&) = delete;

	private:
		CControl& m_ctrl;
		format::CBorder   m_border;
	};

}}}}

#endif/*_SFXTABSFMT_H_D9B720FB_42AC_434C_B055_2F7BC83DECE9_INCLUDED*/