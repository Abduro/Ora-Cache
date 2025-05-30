#ifndef _SHAREDUIXCMPCLRSDEFINED_H_INCLUDED
#define _SHAREDUIXCMPCLRSDEFINED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@google.com) on 30-Jul-2021 at 10:17:55.666 am, UTC+7, Novosibirsk, Friday;
	This is Ebo pack generic drawing (pre-)defined complementary colors pair interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color project on 11-Oct-2021 at 10:36:14.6352254 pm, UTC+7, Novosibirsk, Monday;
*/
#include "color.compl.h"

namespace ex_ui { namespace color { namespace complementary {

	// the class below is the default one and is acceptable for the time being;
	class CPredefined : public CSet_Enum { typedef CSet_Enum TBase;
	public:
		// if two words consist of the name that means: dark colour and light one;
		// otherwise: dark, medium and light one again; :)
		enum _index : uint32_t {
			e_Black_n_Orange  ,
			e_Black_n_Red     ,
			e_Black_n_White_n_Red,
			e_Black_n_Yellow  ,          // cool! because it is the classic;
			e_Blue_n_Green    ,          // nice;
			e_Blue_n_Pink     ,
			e_Blue_n_Turquoise,          // for very persistent aims or desires: a turtle does aleays slowly go ahead;
			e_Blue_n_White    ,          // cool! because it is the classic;
			e_Charcoal_n_Burnt_Orange,   // exotic;
			e_Grey_n_Yellow   ,          // so-so; but sometimes for making not attrective, but useful, notes;
			e_Grey_n_Red      ,          // so-so; just exotic; what attraction may it make? no contrast - no feelings, no desire;
			e_Orange_n_Blue   ,          // so-so, is not for attractive design; attractive - means to force a user to take further steps, exactly for an action;
			e_Orange_n_Purple ,          // nothing at all, for young girls;
			e_Peach_n_Black   ,          // just as formal, but formal for what; nothing interesting, maybe is for babies;
			e_Pink_n_Blue     ,          // don't like smooth colors, this doen't create attrective UI;
			e_Purple_n_Pink   ,          // the same as above;
			e_Purple_n_Yellow ,          // purple is very weak colour, it is not for traders who are trying to hold a success;
			e_Red_n_Navy_n_Yellow ,      // this is a power;
			e_Turquoise_n_Marigold,
			e_Yellow_n_Green  ,
			e_Yellow_n_Red    ,
		};
	public:
		 CPredefined (void); CPredefined (const CPredefined&) = delete; CPredefined (CPredefined&&) = delete;
		~CPredefined (void) = default;

	private:
		CPredefined&  operator = (const CPredefined&) = delete;
		CPredefined&  operator = (CPredefined&&) = delete;
	};
}}}

typedef ex_ui::color::complementary::CPredefined::_index TClrPredefined;

#endif/*_SHAREDUIXCMPCLRSDEFINED_H_INCLUDED*/