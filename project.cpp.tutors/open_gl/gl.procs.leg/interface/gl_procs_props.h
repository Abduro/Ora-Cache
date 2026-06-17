#ifndef _GL_PROCS_PROPS_H_INCLUDED
#define _GL_PROCS_PROPS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jun-2026 at 23:36:47.529, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 draw object property wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace ver_1_1 {

	/* query: difference between option and property in programming ; (Google AI)
	Key Summary:
	a 'Property' is something an object is or has (e.g., its color), while an 'Option' is a choice for how an object should act or how a tool should work;
	the class below is the wrapper of ::glEnable, glDisable and glIsEnabled functions;
	*/
	// https://stackoverflow.com/questions/2074384/options-settings-properties-configuration-preferences-when-and-why ;
	class CProperty : public CBasic { typedef CBasic TBase;
	public:
		CProperty (const uint32_t _prop_id = 0); CProperty (const CProperty&) = delete; CProperty (CProperty&&) = delete; ~CProperty (void) = default;

		bool     Is_enabled (void) const;            // returns current state of input property; the error state is set if necessary;
		err_code Is_enabled (const bool _yes_or_no); // sets depth comparator state to enabled or disabled; perhaps it would be better to name it 'Enable';

		uint32_t PropId (void) const;
		err_code PropId (const uint32_t); // returns '__s_ok' if succeeded, '__s_false' if no change, otherwise error code;

		static   bool     Is_enabled (const uint32_t _prop_id, CError&);
		static   err_code Is_enabled (const uint32_t _prop_id, const bool _yes_or_no, CError&);
		static   bool     Is_valid   (const uint32_t _prop_id, CError&);

		CProperty& operator <<(const bool _yes_or_no);    // sets current state of the property;
		CProperty& operator <<(const uint32_t _prop_id);  // sets property identifier; must be called before setting/getting the property state;

		const CProperty& operator >>(bool& _yes_or_no) const;   // gets current state of the property; returns 'false' if property identifier is not set;
		const CProperty& operator >>(uint32_t& _prop_id) const; // gets current property identifier;

	private:
		CProperty& operator = (const CProperty&) = delete; CProperty& operator = (CProperty&&) = delete;
		uint32_t m_prop_id;
	};

}}}

#endif/*_GL_PROCS_PROPS_H_INCLUDED*/