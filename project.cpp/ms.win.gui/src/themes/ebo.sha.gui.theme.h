#ifndef _EBOSHAGUITHEME_H_INCLUDED
#define _EBOSHAGUITHEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 7:50:01.682 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack UM test project on 14-Jan-2021 at 12:03:27.717 pm, UTC+7, Novosibirsk, Thursday;
	Adopted to Ebo Pack render project desktop GUI app on 26-Apr-2025 at 22:49:56.695, UTC+4, Batumi, Saturday; 
*/
#include "win.gui.inc.h"
#include "ebo.sha.dwm.wrap.h"

namespace ebo { namespace sha { namespace theme { namespace colors {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using namespace ex_ui::color::rgb;
	using namespace ex_ui::theme::colors;

}}}}

namespace ebo { namespace sha { namespace theme {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using namespace ex_ui::color::rgb;
	using namespace ex_ui::theme;

}}}

namespace ebo { namespace sha { namespace theme { namespace direct_x {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using CFloat = ex_ui::color::rgb::CFloat;
	using namespace ex_ui::theme::direct_x;

}}}}

#endif/*_EBOSHAGUITHEME_H_INCLUDED*/