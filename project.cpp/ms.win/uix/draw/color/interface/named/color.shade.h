#ifndef _COLOR_SHADE_H_INCLUDED
#define _COLOR_SHADE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Apr-2024 at 09:48:58.9145177, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack X11 Windows system color shade enumeration interface declaration file; 
*/
#include <vector>
#include "color.named.h"

namespace ex_ui { namespace color { namespace rgb { namespace shade {

	using CNamed_Enum = ex_ui::color::rgb::CNamed_Enum;
	/*
		Blue  >> https://en.wikipedia.org/wiki/Shades_of_blue  << e_AliceBlue << e_Aqua;
		Cyan  >> https://en.wikipedia.org/wiki/Shades_of_cyan  << e_AliceBlue << e_Aqua << e_Aquamarine;
		Green >> https://en.wikipedia.org/wiki/Shades_of_green << e_Aqua << e_Aquamarine;
		White >> https://en.wikipedia.org/wiki/Shades_of_white << e_AliceBlue << e_AntiqueWhite;
	*/

	// https://htmlcolorcodes.com/colors/shades-of-blue/ ;
	class CBlue : public CNamed_Enum { typedef CNamed_Enum TBase;
	public:
		enum _ids : uint32_t {
			e__undef   = 0,
			e_Blurple     , // wiki >> #5865f2; ( 88, 101, 242); Blurple is a vivid purplish blue hue ;
			e_Crayola     , // wiki >> #1F75FE; ( 31, 117, 254); https://en.wikipedia.org/wiki/Crayola ;
			e_Egyptian    , // _r_g_b(0x14, 0x34, 0xa4) ; wiki >> #1034A6; ( 16, 52, 166); Egyptian blue is a pigment that was used in Ancient Egypt;
			e_Electric    , // _r_g_b(0x7d, 0xf9, 0xff) ;
			e_Glaucous    , // _r_g_b(0x60, 0x82, 0xb6) ;
			e_Jade        , // _r_g_b(0x00, 0xa3, 0x6c) ;
			e_Indigo      , // _r_g_b(0x3f, 0x00, 0xff) ;
			e_Iris        , // _r_g_b(0x5d, 0x3f, 0xd3) ;
			e_Light       , // _r_g_b(0xad, 0xd8, 0xe6) ;
			e_Midnight    , // _r_g_b(0x19, 0x19, 0x70) ;
			e_Munsell     , // wiki >> #00DEFF; (  0, 222, 255); The Munsell color system: hue, value (lightness), and chroma (color purity);
			e_Navy        , // _r_g_b(0x00, 0x00, 0x80) ;
			e_NCS         , // wiki >> #0087BD; (  0, 135, 189); The color defined as blue in the NCS or Natural Color System is an azure-like color;
			e_Neon        , // _r_g_b(0x1f, 0x51, 0xff) ; wiki >> #4D4DFF; (  77,  77, 255); Neon blue is a vivid purplish blue ;
			e_Pantone     , // wiki >> #0018A8; (  0,  24, 168); is the color that is called blue in Pantone; https://en.wikipedia.org/wiki/Pantone; 
			e_Pastel      , // _r_g_b(0xa7, 0xc7, 0xe7) ;
			e_Periwinkle  , // _r_g_b(0xcc, 0xcc, 0xff) ; Periwinkle flower is commonly referred to as a tone of light blue;
			e_Powder      , // _r_g_b(0xb6, 0xd0, 0xe2) ;
			e_Robin_Egg   , // _r_g_b(0x96, 0xde, 0xd1) ;
			e_Royal       , // _r_g_b(0x41, 0x69, 0xe1) ;
			e_Sapphire    , // _r_g_b(0x0f, 0x52, 0xba) ;
			e_Seafoam     , // _r_g_b(0x9f, 0xe2, 0xbf) ;
			e_Sky         , // _r_g_b(0x87, 0xce, 0xeb) ;
			e_Steel       , // _r_g_b(0x46, 0x82, 0xb4) ;
			e_Teal        , // _r_g_b(0x00, 0x80, 0x80) ;
			e_Turquoise   , // _r_g_b(0x40, 0xe0, 0xd0) ;
			e_Ultramarine , // _r_g_b(0x04, 0x37, 0xf2) ; wiki >> #120A8F; ( 18, 10, 143);
			e_Verdigris   , // _r_g_b(0x40, 0xb5, 0xad) ;
			e_Zaffre      , // _r_g_b(0x08, 0x18, 0xa8) ;
		};

	public:
		 CBlue (void);
		 CBlue (const CBlue&) = delete; CBlue (CBlue&&) = delete;
		~CBlue (void);

	public:
		CBlue& operator = (const CBlue&) = delete;
		CBlue& operator = (CBlue&&) = delete;
	};
}}}}

typedef ex_ui::color::rgb::shade::CBlue   TRgbShades;

#endif/*_COLOR_SHADE_H_INCLUDED*/