#ifndef _GL_PROCS_DEPTH_H_INCLUDED
#define _GL_PROCS_DEPTH_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 01:24:38.204, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 depth wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace ver_1_1 {

	enum e_criteria : uint32_t {
		// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthfunc ;
		/*   compare condition | description       |
		+----------------------+-------------------+*/
		e_always  = GL_ALWAYS  , // always passes;
		e_equal   = GL_EQUAL   , // passes if the incoming z value is equal to the stored z value;
		e_greater = GL_GREATER , // passes if the incoming z value is greater than the stored z value;
		e_gr_eq   = GL_GEQUAL  , // passes if the incoming z value is greater than or equal to the stored z value;
		e_lt_eq   = GL_LEQUAL  , // passes if the incoming z value is less than or equal to the stored z value;
		e_less    = GL_LESS    , // passes if the incoming z value is less than the stored z value; this is the *default* value;
		e_never   = GL_NEVER   , // never passes;
		e_not_eq  = GL_NOTEQUAL, // passes if the incoming z value is not equal to the stored z value;
	};

	class CDepth : public CBasic { typedef CBasic TBase;
	public:
		// https://en.wikipedia.org/wiki/Comparator ;
		// https://www.allacronyms.com/comparator/abbreviated >> 'comp' ;
		class CComparator : public CBasic { typedef CBasic TBase;
		public:
			CComparator (void); CComparator (const CComparator&) = delete; CComparator (CComparator&&) = delete; ~CComparator (void) = default;

			err_code Condition  (const e_criteria);      // specifies the value used for depth-buffer comparisons;

			bool     Is_enabled (void) const;            // returns current state of depth comparator; the error state is set if necessary;
			err_code Is_enabled (const bool _yes_or_no); // sets depth comparator state to enabled or disabled;

			CComparator& operator <<(const e_criteria);
			CComparator& operator <<(const bool _yes_or_no); // sets comparator state to enabled/disabled;
			CComparator& operator >>(bool& _yes_or_no);      // gets comparator state;

		private:
			CComparator& operator = (const CComparator&) = delete; CComparator& operator = (CComparator&&) = delete;
		};
		using CComp = CDepth::CComparator;
	public:
		CDepth (void); CDepth (const CDepth&) = delete; CDepth (CDepth&&) = delete; ~CDepth (void) = default;

		err_code Clear (const float _f_value);                    // specifies the clear value for the depth buffer;
		err_code Range (const float _f_near, const float _f_far); // specifies the mapping of z values from normalized device coordinates to window coordinates;
		const
		CComp&   Comp (void) const;
		CComp&   Comp (void) ;

	private:
		CDepth& operator = (const CDepth&) = delete; CDepth& operator = (CDepth&&) = delete;
		CComparator m_comp;
	};

}}}

#endif/*_GL_PROCS_DEPTH_H_INCLUDED*/