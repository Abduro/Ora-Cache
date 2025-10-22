#ifndef _COLOR_ALPHA_H_INCLUDED
#define _COLOR_ALPHA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2021 at 1:45:38.8392778 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color alpha value interface declaration file;
*/
#include "color._defs.h"

#define _Opaque rgb_val_max

namespace ex_ui { namespace color { namespace rgb {

	using TPercent = TPct_Flt;
		
	// https://en.wikipedia.org/wiki/Blend_modes ;
	// https://en.wikipedia.org/wiki/Alpha_compositing ;
	class CAlpha {
	public:
		class COpacity {  // alpha value resizes to the range [0..255]; thus, an alpha value for particular percentage is rounded up;
		public:
			static rgb_value Get (const rgb_color _color); // gets a transparency value of input color; 
			static rgb_value Get (const TPercent&);        // gets a value of transparency for given input percent of color light intensity;
			static rgb_value Get (const uint8_t _percent); // gets a value of transparency for input value of color light intensity percent;
		};
#if defined(_DEBUG)
		static CString Print (const TPercent& _percent);   // prints alpha/transparency value for given input percent;
		static CString Print (const rgb_value, const e_print = e_print::e_all);
#endif
	};

}}}

typedef ex_ui::color::rgb::CAlpha  TAlpha;
typedef ex_ui::color::rgb::CAlpha::COpacity TOpecity;

#endif/*_COLOR_ALPHA_H_INCLUDED*/