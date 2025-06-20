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

}
	using format::TBorderAssoc;

	class CFormat : public TBase {
	friend class  CControl;
	public:
		class CBorder_Clrs {
		public:
			 CBorder_Clrs (void); CBorder_Clrs (const CBorder_Clrs&) = delete; CBorder_Clrs (CBorder_Clrs&&) = delete;
			~CBorder_Clrs (void);

		public:
			rgb_color Get (const TStateValue) const; // e_normal|e_selected are expected for this time only;

		private:
			CBorder_Clrs& operator = (const CBorder_Clrs&) = delete;
			CBorder_Clrs& operator = (CBorder_Clrs&&) = delete;

		private:
			TBorderAssoc m_colors;
		};

	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		const
		CBorder_Clrs& Border_Clrs (void) const;
		void Default (void);
	
	private:
		CFormat& operator = (const CFormat&) = delete;
		CFormat& operator = (CFormat&&) = delete;

	private:
		CControl&    m_ctrl;
		CBorder_Clrs m_border;
	};

}}}}

#endif/*_SFXTABSFMT_H_D9B720FB_42AC_434C_B055_2F7BC83DECE9_INCLUDED*/