/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Apr-2024 at 09:19:12.8306905, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack X11 Windows system color enumeration interface implementation file; 
*/
#include "color.x11.h"

using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace rgb { namespace _impl {

	static TNamedClrRaw named_colors = {
	     { TX11_clrIds::e_AliceBlue           , TNamedColor(RGB(0xf0, 0xf8, 0xff), _T("AliceBlue")           ) },
	     { TX11_clrIds::e_AntiqueWhite        , TNamedColor(RGB(0xfa, 0xeb, 0xd7), _T("AntiqueWhite")        ) },
	     { TX11_clrIds::e_Aqua                , TNamedColor(RGB(0x00, 0xff, 0xff), _T("Aqua")                ) },
	     { TX11_clrIds::e_Aquamarine          , TNamedColor(RGB(0x7f, 0xff, 0xd4), _T("Aquamarine")          ) },
	     { TX11_clrIds::e_Azure               , TNamedColor(RGB(0xf0, 0xff, 0xff), _T("Azure")               ) },
	     { TX11_clrIds::e_Beige               , TNamedColor(RGB(0xf5, 0xf5, 0xdc), _T("Beige")               ) },
	     { TX11_clrIds::e_Bisque              , TNamedColor(RGB(0xff, 0xe4, 0xc4), _T("Bisque")              ) },
	     { TX11_clrIds::e_BeccaPurple         , TNamedColor(RGB(0x66, 0x33, 0x99), _T("BeccaPurple")         ) },
	     { TX11_clrIds::e_Black               , TNamedColor(RGB(0x00, 0x00, 0x00), _T("Black")               ) },
	     { TX11_clrIds::e_BlanchedAlmond      , TNamedColor(RGB(0xff, 0xeb, 0xcd), _T("BlanchedAlmond")      ) },
	     { TX11_clrIds::e_Blue                , TNamedColor(RGB(0x00, 0x00, 0xff), _T("Blue")                ) },
	     { TX11_clrIds::e_BlueViolet          , TNamedColor(RGB(0x8a, 0x2b, 0xe2), _T("BlueViolet")          ) },
	     { TX11_clrIds::e_Brown               , TNamedColor(RGB(0xa5, 0x2a, 0x2a), _T("Brown")               ) },
	     { TX11_clrIds::e_BurlyWood           , TNamedColor(RGB(0xde, 0xb8, 0x87), _T("BurlyWood")           ) },
	     { TX11_clrIds::e_Burlywood           , TNamedColor(RGB(0xde, 0xb8, 0x87), _T("Burlywood")           ) },
	     { TX11_clrIds::e_CadetBlue           , TNamedColor(RGB(0x5f, 0x9e, 0xa0), _T("CadetBlue")           ) },
	     { TX11_clrIds::e_Carnation           , TNamedColor(RGB(0xff, 0x5e, 0xd0), _T("Carnation")           ) },
	     { TX11_clrIds::e_Cayenne             , TNamedColor(RGB(0x8d, 0x00, 0x00), _T("Cayenne")             ) },
	     { TX11_clrIds::e_Chartreuse          , TNamedColor(RGB(0x7f, 0xff, 0x00), _T("Chartreuse")          ) },
	     { TX11_clrIds::e_Chocolate           , TNamedColor(RGB(0xd2, 0x69, 0x1e), _T("Chocolate")           ) },
	     { TX11_clrIds::e_Coral               , TNamedColor(RGB(0xff, 0x7f, 0x50), _T("Coral")               ) },
	     { TX11_clrIds::e_CornflowerBlue      , TNamedColor(RGB(0x64, 0x95, 0xed), _T("CornflowerBlue")      ) },
	     { TX11_clrIds::e_Cornsilk            , TNamedColor(RGB(0xff, 0xf8, 0xdc), _T("Cornsilk")            ) },
	     { TX11_clrIds::e_Crimson             , TNamedColor(RGB(0xdc, 0x14, 0x3c), _T("Crimson")             ) },
	     { TX11_clrIds::e_Cyan                , TNamedColor(RGB(0x00, 0xff, 0xff), _T("Cyan")                ) },
	     { TX11_clrIds::e_DeepPink            , TNamedColor(RGB(0xff, 0x14, 0x93), _T("DeepPink")            ) },
	     { TX11_clrIds::e_DeepSkyBlue         , TNamedColor(RGB(0x00, 0xbf, 0xbf), _T("DeepSkyBlue")         ) },
	     { TX11_clrIds::e_DimGray             , TNamedColor(RGB(0x69, 0x69, 0x69), _T("DimGray")             ) },
	     { TX11_clrIds::e_DimGrey             , TNamedColor(RGB(0x69, 0x69, 0x69), _T("DimGrey")             ) },
	     { TX11_clrIds::e_DodgerBlue          , TNamedColor(RGB(0x1e, 0x90, 0xff), _T("DodgerBlue")          ) },
	     { TX11_clrIds::e_Feldspar            , TNamedColor(RGB(0xd1, 0x92, 0x75), _T("Feldspar")            ) },
	     { TX11_clrIds::e_FireBrick           , TNamedColor(RGB(0xb2, 0x22, 0x22), _T("FireBrick")           ) },
	     { TX11_clrIds::e_Firebrick           , TNamedColor(RGB(0xb2, 0x22, 0x22), _T("Firebrick")           ) },
	     { TX11_clrIds::e_FloralWhite         , TNamedColor(RGB(0xff, 0xfa, 0xf0), _T("FloralWhite")         ) },
	     { TX11_clrIds::e_ForestGreen         , TNamedColor(RGB(0x22, 0x8b, 0x22), _T("ForestGreen")         ) },
	     { TX11_clrIds::e_Fuchsia             , TNamedColor(RGB(0xff, 0x00, 0xff), _T("Fuchsia")             ) },
	     { TX11_clrIds::e_Gainsboro           , TNamedColor(RGB(0xdc, 0xdc, 0xdc), _T("Gainsboro")           ) },
	     { TX11_clrIds::e_GhostWhite          , TNamedColor(RGB(0xf8, 0xf8, 0xff), _T("GhostWhite")          ) },
	     { TX11_clrIds::e_Gold                , TNamedColor(RGB(0xff, 0xd7, 0x00), _T("Gold")                ) },
	     { TX11_clrIds::e_GoldenRod           , TNamedColor(RGB(0xda, 0xa5, 0x20), _T("GoldenRod")           ) },
	     { TX11_clrIds::e_Goldenrod           , TNamedColor(RGB(0xda, 0xa5, 0x20), _T("Goldenrod")           ) },
	     { TX11_clrIds::e_Green               , TNamedColor(RGB(0x00, 0x80, 0x00), _T("Green")               ) },
	     { TX11_clrIds::e_GreenYellow         , TNamedColor(RGB(0xad, 0xff, 0x2f), _T("GreenYellow")         ) },
	     { TX11_clrIds::e_HoneyDew            , TNamedColor(RGB(0xf0, 0xff, 0xf0), _T("HoneyDew")            ) },
	     { TX11_clrIds::e_Honeydew            , TNamedColor(RGB(0xf0, 0xff, 0xf0), _T("Honeydew")            ) },
	     { TX11_clrIds::e_HotPink             , TNamedColor(RGB(0xff, 0x69, 0xb4), _T("HotPink")             ) },
	     { TX11_clrIds::e_IndianRed           , TNamedColor(RGB(0xcd, 0x5c, 0x5c), _T("IndianRed")           ) },
	     { TX11_clrIds::e_Indigo              , TNamedColor(RGB(0x4b, 0x00, 0x82), _T("Indigo")              ) },
	     { TX11_clrIds::e_Ivory               , TNamedColor(RGB(0xff, 0xff, 0xf0), _T("Ivory")               ) },
	     { TX11_clrIds::e_Khaki               , TNamedColor(RGB(0xf0, 0xe6, 0x8c), _T("Khaki")               ) },
	     { TX11_clrIds::e_Lavender            , TNamedColor(RGB(0xe6, 0xe6, 0xfa), _T("Lavender")            ) },
	     { TX11_clrIds::e_LavenderBlush       , TNamedColor(RGB(0xff, 0xf0, 0xf5), _T("LavenderBlush")       ) },
	     { TX11_clrIds::e_LawnGreen           , TNamedColor(RGB(0x7c, 0xfc, 0x00), _T("LawnGreen")           ) },
	     { TX11_clrIds::e_LemonChiffon        , TNamedColor(RGB(0xff, 0xfa, 0xcd), _T("LemonChiffon")        ) },
	     { TX11_clrIds::e_Lime                , TNamedColor(RGB(0x00, 0xff, 0x00), _T("Lime")                ) },
	     { TX11_clrIds::e_LimeGreen           , TNamedColor(RGB(0x32, 0xcd, 0x32), _T("LimeGreen")           ) },
	     { TX11_clrIds::e_Linen               , TNamedColor(RGB(0xfa, 0xf0, 0xe6), _T("Linen")               ) },
	     { TX11_clrIds::e_Magenta             , TNamedColor(RGB(0xff, 0x00, 0xff), _T("Magenta")             ) },
	     { TX11_clrIds::e_Maroon              , TNamedColor(RGB(0x80, 0x00, 0x00), _T("Maroon")              ) },
	     { TX11_clrIds::e_MidnightBlue        , TNamedColor(RGB(0x19, 0x19, 0x70), _T("MidnightBlue")        ) },
	     { TX11_clrIds::e_MintCream           , TNamedColor(RGB(0xf5, 0xff, 0xfa), _T("MintCream")           ) },
	     { TX11_clrIds::e_MistyRose           , TNamedColor(RGB(0xff, 0xe4, 0xe1), _T("MistyRose")           ) },
	     { TX11_clrIds::e_Moccasin            , TNamedColor(RGB(0xff, 0xe4, 0xb5), _T("Moccasin")            ) },
	     { TX11_clrIds::e_NavajoWhite         , TNamedColor(RGB(0xff, 0xde, 0xad), _T("NavajoWhite")         ) },
	     { TX11_clrIds::e_Navy                , TNamedColor(RGB(0x00, 0x00, 0x80), _T("Navy")                ) },
	     { TX11_clrIds::e_OldLace             , TNamedColor(RGB(0xfd, 0xf5, 0xe6), _T("OldLace")             ) },
	     { TX11_clrIds::e_Olive               , TNamedColor(RGB(0x80, 0x80, 0x00), _T("Olive")               ) },
	     { TX11_clrIds::e_OliveDrab           , TNamedColor(RGB(0x6b, 0x8e, 0x23), _T("OliveDrab")           ) },
	     { TX11_clrIds::e_Olivedrab           , TNamedColor(RGB(0x6b, 0x8e, 0x23), _T("Olivedrab")           ) },
	     { TX11_clrIds::e_Orange              , TNamedColor(RGB(0xff, 0xa5, 0x00), _T("Orange")              ) },
	     { TX11_clrIds::e_OrangeRed           , TNamedColor(RGB(0xff, 0x45, 0x00), _T("OrangeRed")           ) },
	     { TX11_clrIds::e_Orchid              , TNamedColor(RGB(0xda, 0x70, 0xd6), _T("Orchid")              ) },
	     { TX11_clrIds::e_PaleGoldenRod       , TNamedColor(RGB(0xee, 0xe8, 0xaa), _T("PaleGoldenRod")       ) },
	     { TX11_clrIds::e_PaleGoldenrod       , TNamedColor(RGB(0xee, 0xe8, 0xaa), _T("PaleGoldenrod")       ) },
	     { TX11_clrIds::e_PaleGreen           , TNamedColor(RGB(0x98, 0xfb, 0x98), _T("PaleGreen")           ) },
	     { TX11_clrIds::e_PaleTurquoise       , TNamedColor(RGB(0xaf, 0xee, 0xee), _T("PaleTurquoise")       ) },
	     { TX11_clrIds::e_PaleVioletRed       , TNamedColor(RGB(0xdb, 0x70, 0x93), _T("PaleVioletRed")       ) },
	     { TX11_clrIds::e_PapayaWhip          , TNamedColor(RGB(0xff, 0xef, 0xd5), _T("PapayaWhip")          ) },
	     { TX11_clrIds::e_PeachPuff           , TNamedColor(RGB(0xff, 0xda, 0xb9), _T("PeachPuff")           ) },
	     { TX11_clrIds::e_Peachpuff           , TNamedColor(RGB(0xff, 0xda, 0xb9), _T("Peachpuff")           ) },
	     { TX11_clrIds::e_Peru                , TNamedColor(RGB(0xcd, 0x85, 0x3f), _T("Peru")                ) },
	     { TX11_clrIds::e_Pink                , TNamedColor(RGB(0xff, 0xc0, 0xcb), _T("Pink")                ) },
	     { TX11_clrIds::e_Plum                , TNamedColor(RGB(0xdd, 0xa0, 0xdd), _T("Plum")                ) },
	     { TX11_clrIds::e_PowderBlue          , TNamedColor(RGB(0xb0, 0xe0, 0xe6), _T("PowderBlue")          ) },
	     { TX11_clrIds::e_Purple              , TNamedColor(RGB(0x80, 0x00, 0x80), _T("Purple")              ) },
	     { TX11_clrIds::e_RebeccaPurple       , TNamedColor(RGB(0x66, 0x33, 0x99), _T("RebeccaPurple")       ) },
	     { TX11_clrIds::e_Red                 , TNamedColor(RGB(0xff, 0x00, 0x00), _T("Red")                 ) },
	     { TX11_clrIds::e_RosyBrown           , TNamedColor(RGB(0xbc, 0x8f, 0x8f), _T("RosyBrown")           ) },
	     { TX11_clrIds::e_RoyalBlue           , TNamedColor(RGB(0x41, 0x69, 0xe1), _T("RoyalBlue")           ) },
	     { TX11_clrIds::e_SaddleBrown         , TNamedColor(RGB(0x8b, 0x45, 0x13), _T("SaddleBrown")         ) },
	     { TX11_clrIds::e_Salmon              , TNamedColor(RGB(0xfa, 0x80, 0x72), _T("Salmon")              ) },
	     { TX11_clrIds::e_SandyBrown          , TNamedColor(RGB(0xf4, 0xa4, 0x60), _T("SandyBrown")          ) },
	     { TX11_clrIds::e_SeaGreen            , TNamedColor(RGB(0x2e, 0x8b, 0x57), _T("SeaGreen")            ) },
	     { TX11_clrIds::e_SeaShell            , TNamedColor(RGB(0xff, 0xf5, 0xee), _T("SeaShell")            ) },
	     { TX11_clrIds::e_Seashell            , TNamedColor(RGB(0xff, 0xf5, 0xee), _T("Seashell")            ) },
	     { TX11_clrIds::e_Sienna              , TNamedColor(RGB(0xa0, 0x52, 0x2d), _T("Sienna")              ) },
	     { TX11_clrIds::e_Silver              , TNamedColor(RGB(0xc0, 0xc0, 0xc0), _T("Silver")              ) },
	     { TX11_clrIds::e_SkyBlue             , TNamedColor(RGB(0x87, 0xce, 0xeb), _T("SkyBlue")             ) },
	     { TX11_clrIds::e_SlateBlue           , TNamedColor(RGB(0x6a, 0x5a, 0xcd), _T("SlateBlue")           ) },
	     { TX11_clrIds::e_SlateGray           , TNamedColor(RGB(0x70, 0x80, 0x90), _T("SlateGray")           ) },
	     { TX11_clrIds::e_SlateGrey           , TNamedColor(RGB(0x70, 0x80, 0x90), _T("SlateGrey")           ) },
	     { TX11_clrIds::e_Snow                , TNamedColor(RGB(0xff, 0xfa, 0xfa), _T("Snow")                ) },
	     { TX11_clrIds::e_SpringGreen         , TNamedColor(RGB(0x00, 0xff, 0x7f), _T("SpringGreen")         ) },
	     { TX11_clrIds::e_SteelBlue           , TNamedColor(RGB(0x46, 0x82, 0xb4), _T("SteelBlue")           ) },
	     { TX11_clrIds::e_Tan                 , TNamedColor(RGB(0xd2, 0xb4, 0x8c), _T("Tan")                 ) },
	     { TX11_clrIds::e_Teal                , TNamedColor(RGB(0x00, 0x80, 0x80), _T("Teal")                ) },
	     { TX11_clrIds::e_Thistle             , TNamedColor(RGB(0xd8, 0xbf, 0xd8), _T("Thistle")             ) },
	     { TX11_clrIds::e_Tomato              , TNamedColor(RGB(0xff, 0x63, 0x47), _T("Tomato")              ) },
	     { TX11_clrIds::e_Turquoise           , TNamedColor(RGB(0x40, 0xe0, 0xd0), _T("Turquoise")           ) },
	     { TX11_clrIds::e_Violet              , TNamedColor(RGB(0xee, 0x82, 0xee), _T("Violet")              ) },
	     { TX11_clrIds::e_VioletRed           , TNamedColor(RGB(0xd0, 0x20, 0x90), _T("VioletRed")           ) },
	     { TX11_clrIds::e_Wheat               , TNamedColor(RGB(0xf5, 0xde, 0xb3), _T("Wheat")               ) },
	     { TX11_clrIds::e_White               , TNamedColor(RGB(0xff, 0xff, 0xff), _T("White")               ) },
	     { TX11_clrIds::e_WhiteSmoke          , TNamedColor(RGB(0xf5, 0xf5, 0xf5), _T("WhiteSmoke")          ) },
	     { TX11_clrIds::e_Yellow              , TNamedColor(RGB(0xff, 0xff, 0x00), _T("Yellow")              ) },
	     { TX11_clrIds::e_YellowGreen         , TNamedColor(RGB(0x9a, 0xcd, 0x32), _T("YellowGreen")         ) },
	};

}}}}
using namespace ex_ui::color::rgb::_impl;
/////////////////////////////////////////////////////////////////////////////

CNamed_X11:: CNamed_X11 (void) {}
CNamed_X11::~CNamed_X11 (void) {}

/////////////////////////////////////////////////////////////////////////////

const TNamedColor&  CNamed_X11::Get (const uint32_t _u_id) const {
	_u_id;
	TNamedClrRaw::const_iterator it_found = named_colors.find(_u_id);
	if (it_found == named_colors.end())
		return it_found->second;
	else
		return TBase::Get(_u_id);
}

const TNamedClrRaw& CNamed_X11::Raw (void) const { return named_colors; }

/////////////////////////////////////////////////////////////////////////////

CNamed_X11&  CNamed_X11::Ref (void) {
	static   CNamed_X11 x_11_enum; return x_11_enum;
}