/*
	Created by Tech_dog (ebontrop@google.com) on 27-May-2025 at 23:24:05.060, UTC+4, Batumi, Tuesday;
	This is Ebo pack generic drawing (pre-)defined complementary colors pair interface implementation file;
*/
#include "color.compl.predefs.h"

using namespace ex_ui::color::complementary;

/////////////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4310)

namespace ex_ui { namespace color { namespace complementary { namespace _impl {

	static CSet Predefined[] = {
		CSet(H2C(0x161C25), __clr_none     , H2C(0xF3A950), _T("Black & Orange")    ,       _T("The orange provides a dose of optimism, while the black is a professional and grounded counterpart.")),
		CSet(H2C(0x1C1A1A), __clr_none     , H2C(0xEB4D37), _T("Black & Red"   )    ,       _T("Daring and surprisingly inviting, color combination dominates and instills a sense of power and energy.")),
		CSet(H2C(0x333333), H2C(0xBA0000)  , H2C(0xE9E9E9), _T("Black, White & Red"),       _T("Black and white are one of the most popular, yet classic, colour schemes.")),
		CSet(H2C(0x2F2D29), __clr_none     , H2C(0xF9D342), _T("Black & Yellow")    ,       _T("The bright yellow and almost-black shade of grey have an air of mystery and intrigue.")),
		CSet(H2C(0x4830D4), __clr_none     , H2C(0xCBF380), _T("Blue & Green"  )    ,       _T("Blue and green are often associated with tranquility, but this electric blue and lime green exude energy and youthfulness.")),
		CSet(H2C(0x080A52), __clr_none     , H2C(0xEB2188), _T("Blue & Pink"   )    ,       _T("The vibrant pink radiates against the blue and works well for industries like beauty and blogging.")),
		CSet(H2C(0x273773), __clr_none     , H2C(0x8BD7BD), _T("Blue & Turquoise"  ),       _T("The colors are from the same color family, but are different enough to create a striking duo, with the turquoise used sparingly.")),
		CSet(H2C(0x90AFEC), __clr_none     , H2C(0xFEFEFE), _T("Blue & White"  )    ,       _T("This peaceful sky blue and white combo is a definite crowd pleaser, communicating feelings of trust and tranquility.")),
		CSet(H2C(0x34434D), __clr_none     , H2C(0xC75400), _T("Charcoal & Burnt Orange"),  _T("The best thing about charcoal and burnt orange combination is that it is gender neutral.")),
		CSet(H2C(0x585E5D), __clr_none     , H2C(0xF5CA0C), _T("Grey & Yellow" )    ,       _T("This colour combination is mostly attributed to the monochromatic feel that grey projects, and the contrasting vibrancy of yellow.")),
		CSet(H2C(0x858988), __clr_none     , H2C(0xA82B32), _T("Neutral Grey & Red"),       _T("Red is one of the best colours to use to break the monotony of neutral colours and spice things a notch or two.")),
		CSet(H2C(0x141A46), __clr_none     , H2C(0xFA935B), _T("Orange & Blue" )    ,       _T("This complementary color duo is a classic yet powerful pairing and is popular in the technology and banking sectors.")),
		CSet(H2C(0x4A274F), __clr_none     , H2C(0xFBA77D), _T("Orange & Purple")   ,       _T("This pairing of warm peach and eggplant purple is both elegant and unique.")),
		CSet(H2C(0x333333), __clr_none     , H2C(0xF27B70), _T("Peach & Black" )    ,       _T("This is a great colour combination for achieving a formal look.")),
		CSet(H2C(0x2F3C7D), __clr_none     , H2C(0xFEECEC), _T("Pink & Blue"   )    ,       _T("A delicate pink paired with navy blue gives off a playful yet trustworthy vibe.")),
		CSet(H2C(0x3D1560), __clr_none     , H2C(0xDE668B), _T("Purple & Pink" )    ,       _T("The bright pink adds a spark of energy, while the purple acts as a mature counterpart.")),
		CSet(H2C(0x3C1A5B), __clr_none     , H2C(0xFEF648), _T("Purple & Yellow")   ,       _T("Optimistic and energizing yellow with a rich purple to spark feelings of creativity.")),
		CSet(H2C(0x2B3252), H2C(0xEF5455)  , H2C(0xFAD644), _T("Red, Navy, & Yellow" ),     _T("The bright red complements the cheery yellow and regal navy, exuding power and confidence.")),
		CSet(H2C(0x5595A1), __clr_none     , H2C(0xFBEA74), _T("Turquoise & Marigold"),     _T("Turquoise and marigold are an excellent choice for colour combinations of getting extra pop.")),
		CSet(H2C(0x295F2D), __clr_none     , H2C(0xFFE67B), _T("Yellow & Green")    ,       _T("This youthful yellow brings life and energy to the otherwise calming green in this color combination.")),
		CSet(H2C(0xF86067), __clr_none     , H2C(0xFCEE77), _T("Yellow & Red"  )    ,       _T("The vibrant red and happy shade of yellow create a sense of energy and playfulness."))
	};

}}}}
using namespace ex_ui::color::complementary::_impl;

/////////////////////////////////////////////////////////////////////////////

CPredefined:: CPredefined (void) : TBase() {
	try {
		for (size_t i_ = 0; i_ < _countof(Predefined); i_++) {
			TBase::m_sets.push_back(Predefined[i_]);
		}
	}
	catch (const ::std::bad_alloc&) {}
}

namespace shared {

	const CComplPredefs&  ThemeTriplets(void) {
		static CComplPredefs triplets;
		return triplets;
	}

}