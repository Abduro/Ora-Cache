#ifndef _COLOR_NAMED_H_INCLUDED
#define _COLOR_NAMED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Sep-2021 at 9:28:02.883 pm, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX named color interface declaration file.
*/
#include <map>
#include "color.rgb.h"

namespace ex_ui { namespace color { namespace rgb {
	// https://en.wikipedia.org/wiki/Lists_of_colors ;
	class CNamed {
	public:
		 CNamed (void);
		 CNamed (const CNamed&);
		 CNamed (const CColor&, _pc_sz _p_name);
		 CNamed (CNamed&&) = delete;
		~CNamed (void);

	public: // attributes;
		const
		CColor&  Color (void) const;
		CColor&  Color (void)      ;
		_pc_sz   Name  (void) const;
		bool     Name  (_pc_sz)    ;

	public:
		const bool Is (void) const ; // returns true if name and color are defined;
#if defined(_DEBUG)
		enum e_print {
			e_all = 0, // outputs complete information of this class object: its name, color value (hex), color's name;
			e_req = 1, // outputs color value (hex), color's name;
		};
		CString  Print (const e_print = e_print::e_req) const;
#endif
	public:
		CNamed&  operator = (const CNamed&);
		CNamed&  operator = (CNamed&&) = delete;
		CNamed&  operator <<(const CColor&);
		CNamed&  operator <<(_pc_sz _p_name);

	protected:
		CColor   m_color;
		CString  m_name ;
	};
}}}

typedef ex_ui::color::rgb::CNamed TNamedColor;
#if (0)
namespace ex_ui { namespace color { namespace rgb {
	/*
		https://encycolorpedia.com/named ;
		https://en.wikipedia.org/wiki/Web_colors ;
		https://en.wikipedia.org/wiki/X11_color_names ; this one enumerates all names being beneath;
		
	*/
}}}
#endif

typedef ::std::map<uint32_t, TNamedColor> TNamedClrRaw;

namespace ex_ui { namespace color { namespace rgb {

	class CNamed_Enum {
	public:
		 CNamed_Enum (void);
		 CNamed_Enum (const CNamed_Enum&) = delete; // assumes all child class(es) would create a singleton object(s) for providing its collection of named colors;
		 CNamed_Enum (CNamed_Enum&&) = delete;
		~CNamed_Enum (void);

	public:
		const
		TNamedColor&  Get (const uint32_t _u_id) const; // returns a reference to fake object;
	public:
		const
		TNamedClrRaw& Raw (void) const;

	private:
		CNamed_Enum&  operator = (const CNamed_Enum&) = delete;
		CNamed_Enum&  operator = (CNamed_Enum&&) = delete;
	};

}}}

#endif/*_COLOR_NAMED_H_INCLUDED*/