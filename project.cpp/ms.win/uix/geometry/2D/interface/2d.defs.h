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
#include "sys.error.h"

#include "color.rgb.h"

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/math-constants ;
// https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html ;
// https://en.wikipedia.org/wiki/Pi ~ 3.14159 is enough for graphics ;
#ifndef __pi
#define __pi (3.14159F)
#endif

namespace geometry { namespace _2D { 

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	// https://www.allacronyms.com/primitive/abbreviated ;

	class CMarker {
	public:
		 CMarker (void); 
		 CMarker (const uint32_t _u_id, _pc_sz _p_tag, const bool _b_valid); // a tag or maybe better to call it as just a name;
		 CMarker (const CMarker&);
		 CMarker (CMarker&&) = delete; // is not required yet;
		~CMarker (void);

	public:
		uint32_t  Id (void) const;
		bool      Id (const uint32_t);  // returns true in case if this marker identifier is changed;
		uint32_t& Id_ref (void);

		bool  Is_valid (void) const;   // returns true if marker identifier is equal to 0; a tag name is optional
		bool  Is_valid (const bool);   // sets a validity attribute to the input value;

		bool  Set (const uint32_t _u_id, _pc_sz _p_tag, bool _b_valid = false); // returns true in case of the marker identifier or tag value is changed;

		_pc_sz   Tag (void) const;
		bool     Tag (_pc_sz) ;        // returns true if tag text is changed, case sensitive; nullptr is acceptable;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CMarker& operator = (const CMarker&);
		CMarker& operator = (CMarker&&) = delete;   // is not required yet;

		CMarker& operator <<(const uint32_t _u_id); // error C2666: 'geometry::shape::_2D::CMarker::operator <<': 2 overloads have similar conversions ...;
		CMarker& operator <<(_pc_sz _p_tag);
		CMarker& operator <<(const bool _b_valid);

		operator _pc_sz   (void) const; // returns a pointer to tag string;
		operator uint32_t (void) const; // returns an identifier of this marker;

		bool operator == (const CMarker&) const;
		bool operator != (const CMarker&) const;

	private:
		CString  m_tag;
		uint32_t m_id ;
		bool     m_valid;
	};
}}

#endif/*_D_DEFS_H_INCLUDED*/