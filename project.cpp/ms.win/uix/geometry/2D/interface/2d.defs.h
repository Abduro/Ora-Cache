#ifndef _2D_DEFS_H_INCLUDED
#define _2D_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2025 at 18:23:06.473, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry common declaration file.
*/
#include <map>
#include <cmath> // https://en.cppreference.com/w/cpp/numeric/math/pow ; https://en.cppreference.com/w/cpp/numeric/math/sqrt ;

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"

#include "color.rgb.h"

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/math-constants ;
// https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html ;
// https://en.wikipedia.org/wiki/Pi ~ 3.14159 is enough for graphics ;
#ifndef M_PI
#define M_PI (3.14159F)
#endif

namespace geometry { namespace base { using namespace shared::types; }}

#endif/*_D_DEFS_H_INCLUDED*/