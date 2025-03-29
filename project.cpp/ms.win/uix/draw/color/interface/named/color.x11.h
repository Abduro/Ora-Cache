#ifndef _COLOR_X11_H_INCLUDED
#define _COLOR_X11_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Apr-2024 at 08:37:52.6939106, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack X11 Windows system color enumeration interface declaration file; 
*/
#include "color.named.h"

namespace ex_ui { namespace color { namespace rgb {

	// https://en.wikipedia.org/wiki/X11_color_names ;
	// https://learn.microsoft.com/en-us/dotnet/api/system.drawing.color ; MS also uses this color enumeration;
	class CNamed_X11 : public CNamed_Enum {
	                  typedef CNamed_Enum TBase;
	public:
		enum _ids : uint32_t {
			e__undef           = 0,
			e_AliceBlue           , // [0xf0, 0xf8, 0xff] https://en.wikipedia.org/wiki/Alice_blue ;
			e_AntiqueWhite        , // [0xfa, 0xeb, 0xd7] https://en.wikipedia.org/wiki/Shades_of_white#Antique_white ;
			e_Aqua                , // [0x00, 0xff, 0xff] https://en.wikipedia.org/wiki/Aqua_(color) ;
			e_Aquamarine          , // [0x7f, 0xff, 0xd4] https://en.wikipedia.org/wiki/Aquamarine_(color) ;
			e_Azure               , // [0xf0, 0xff, 0xff] https://en.wikipedia.org/wiki/Azure_(color) ; https://en.wikipedia.org/wiki/Shades_of_blue ; https://en.wikipedia.org/wiki/Shades_of_cyan;
			e_Beige               , // [0xf5, 0xf5, 0xdc]
			e_Bisque              , // [0xff, 0xe4, 0xc4]
			e_BeccaPurple         , // [0x66, 0x33, 0x99]
			e_Black               , // [0x00, 0x00, 0x00]
			e_BlanchedAlmond      , // [0xff, 0xeb, 0xcd]
			e_Blue                , // [0x00, 0x00, 0xff]
			e_BlueViolet          , // [0x8a, 0x2b, 0xe2]
			e_Brown               , // [0xa5, 0x2a, 0x2a]
			e_BurlyWood           , // [0xde, 0xb8, 0x87]
			e_Burlywood           , // [0xde, 0xb8, 0x87]
			e_CadetBlue           , // [0x5f, 0x9e, 0xa0]
			e_Carnation           , // [0xff, 0x5e, 0xd0]
			e_Cayenne             , // [0x8d, 0x00, 0x00]
			e_Chartreuse          , // [0x7f, 0xff, 0x00]
			e_Chocolate           , // [0xd2, 0x69, 0x1e]
			e_Coral               , // [0xff, 0x7f, 0x50]
			e_CornflowerBlue      , // [0x64, 0x95, 0xed]
			e_Cornsilk            , // [0xff, 0xf8, 0xdc]
			e_Crimson             , // [0xdc, 0x14, 0x3c]
			e_Cyan                , // [0x00, 0xff, 0xff]
			e_DeepPink            , // [0xff, 0x14, 0x93]
			e_DeepSkyBlue         , // [0x00, 0xbf, 0xbf]
			e_DimGray             , // [0x69, 0x69, 0x69]
			e_DimGrey             , // [0x69, 0x69, 0x69]
			e_DodgerBlue          , // [0x1e, 0x90, 0xff]
			e_Feldspar            , // [0xd1, 0x92, 0x75]
			e_FireBrick           , // [0xb2, 0x22, 0x22]
			e_Firebrick           , // [0xb2, 0x22, 0x22]
			e_FloralWhite         , // [0xff, 0xfa, 0xf0]
			e_ForestGreen         , // [0x22, 0x8b, 0x22]
			e_Fuchsia             , // [0xff, 0x00, 0xff]
			e_Gainsboro           , // [0xdc, 0xdc, 0xdc]
			e_GhostWhite          , // [0xf8, 0xf8, 0xff]
			e_Gold                , // [0xff, 0xd7, 0x00]
			e_GoldenRod           , // [0xda, 0xa5, 0x20]
			e_Goldenrod           , // [0xda, 0xa5, 0x20]
			e_Green               , // [0x00, 0x80, 0x00]
			e_GreenYellow         , // [0xad, 0xff, 0x2f]
			e_HoneyDew            , // [0xf0, 0xff, 0xf0]
			e_Honeydew            , // [0xf0, 0xff, 0xf0]
			e_HotPink             , // [0xff, 0x69, 0xb4]
			e_IndianRed           , // [0xcd, 0x5c, 0x5c]
			e_Indigo              , // [0x4b, 0x00, 0x82]
			e_Ivory               , // [0xff, 0xff, 0xf0]
			e_Khaki               , // [0xf0, 0xe6, 0x8c]
			e_Lavender            , // [0xe6, 0xe6, 0xfa]
			e_LavenderBlush       , // [0xff, 0xf0, 0xf5]
			e_LawnGreen           , // [0x7c, 0xfc, 0x00]
			e_LemonChiffon        , // [0xff, 0xfa, 0xcd]
			e_Lime                , // [0x00, 0xff, 0x00]
			e_LimeGreen           , // [0x32, 0xcd, 0x32]
			e_Linen               , // [0xfa, 0xf0, 0xe6]
			e_Magenta             , // [0xff, 0x00, 0xff]
			e_Maroon              , // [0x80, 0x00, 0x00]
			e_MidnightBlue        , // [0x19, 0x19, 0x70]
			e_MintCream           , // [0xf5, 0xff, 0xfa]
			e_MistyRose           , // [0xff, 0xe4, 0xe1]
			e_Moccasin            , // [0xff, 0xe4, 0xb5]
			e_NavajoWhite         , // [0xff, 0xde, 0xad]
			e_Navy                , // [0x00, 0x00, 0x80]
			e_OldLace             , // [0xfd, 0xf5, 0xe6]
			e_Olive               , // [0x80, 0x80, 0x00]
			e_OliveDrab           , // [0x6b, 0x8e, 0x23]
			e_Olivedrab           , // [0x6b, 0x8e, 0x23]
			e_Orange              , // [0xff, 0xa5, 0x00]
			e_OrangeRed           , // [0xff, 0x45, 0x00]
			e_Orchid              , // [0xda, 0x70, 0xd6]
			e_PaleGoldenRod       , // [0xee, 0xe8, 0xaa]
			e_PaleGoldenrod       , // [0xee, 0xe8, 0xaa]
			e_PaleGreen           , // [0x98, 0xfb, 0x98]
			e_PaleTurquoise       , // [0xaf, 0xee, 0xee]
			e_PaleVioletRed       , // [0xdb, 0x70, 0x93]
			e_PapayaWhip          , // [0xff, 0xef, 0xd5]
			e_PeachPuff           , // [0xff, 0xda, 0xb9]
			e_Peachpuff           , // [0xff, 0xda, 0xb9]
			e_Peru                , // [0xcd, 0x85, 0x3f]
			e_Pink                , // [0xff, 0xc0, 0xcb]
			e_Plum                , // [0xdd, 0xa0, 0xdd]
			e_PowderBlue          , // [0xb0, 0xe0, 0xe6]
			e_Purple              , // [0x80, 0x00, 0x80]
			e_RebeccaPurple       , // [0x66, 0x33, 0x99]
			e_Red                 , // [0xff, 0x00, 0x00]
			e_RosyBrown           , // [0xbc, 0x8f, 0x8f]
			e_RoyalBlue           , // [0x41, 0x69, 0xe1]
			e_SaddleBrown         , // [0x8b, 0x45, 0x13]
			e_Salmon              , // [0xfa, 0x80, 0x72]
			e_SandyBrown          , // [0xf4, 0xa4, 0x60]
			e_SeaGreen            , // [0x2e, 0x8b, 0x57]
			e_SeaShell            , // [0xff, 0xf5, 0xee]
			e_Seashell            , // [0xff, 0xf5, 0xee]
			e_Sienna              , // [0xa0, 0x52, 0x2d]
			e_Silver              , // [0xc0, 0xc0, 0xc0]
			e_SkyBlue             , // [0x87, 0xce, 0xeb]
			e_SlateBlue           , // [0x6a, 0x5a, 0xcd]
			e_SlateGray           , // [0x70, 0x80, 0x90]
			e_SlateGrey           , // [0x70, 0x80, 0x90]
			e_Snow                , // [0xff, 0xfa, 0xfa]
			e_SpringGreen         , // [0x00, 0xff, 0x7f]
			e_SteelBlue           , // [0x46, 0x82, 0xb4]
			e_Tan                 , // [0xd2, 0xb4, 0x8c]
			e_Teal                , // [0x00, 0x80, 0x80]
			e_Thistle             , // [0xd8, 0xbf, 0xd8]
			e_Tomato              , // [0xff, 0x63, 0x47]
			e_Turquoise           , // [0x40, 0xe0, 0xd0]
			e_Violet              , // [0xee, 0x82, 0xee]
			e_VioletRed           , // [0xd0, 0x20, 0x90]
			e_Wheat               , // [0xf5, 0xde, 0xb3]
			e_White               , // [0xff, 0xff, 0xff]
			e_WhiteSmoke          , // [0xf5, 0xf5, 0xf5]
			e_Yellow              , // [0xff, 0xff, 0x00]
			e_YellowGreen         , // [0x9a, 0xcd, 0x32]
		};

	public:
		 CNamed_X11 (void);
		 CNamed_X11 (const CNamed_X11&) = delete;
		 CNamed_X11 (CNamed_X11&&) = delete;
		~CNamed_X11 (void);

	public:
		const TNamedColor&  Get (const uint32_t _u_id) const; // returns a reference to an object specified by input identifier; if not found >> fake object;
		const TNamedClrRaw& Raw (void) const;                 // returns a reference to the collection of all X11 named colors ;

	public:
		static CNamed_X11&  Ref (void); // returns singleton object for avoiding a creation of predefined X11 color set each time;

	private:
		CNamed_X11& operator = (const CNamed_X11&) = delete;
		CNamed_X11& operator = (CNamed_X11&&) = delete;
	};

}}}

typedef ex_ui::color::rgb::CNamed_X11       TX11_Named ;
typedef ex_ui::color::rgb::CNamed_X11::_ids TX11_clrIds;

#endif/*_COLOR_X11_H_INCLUDED*/