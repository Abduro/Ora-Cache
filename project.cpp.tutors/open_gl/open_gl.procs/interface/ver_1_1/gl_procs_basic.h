#ifndef _GL_PROCS_BASIC_H_INCLUDED
#define _GL_PROCS_BASIC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 20:04:02.817, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface declaration file;
*/
#include "shared.defs.h"
#include <gl/gl.h>       // the headers' include order is important: windows.h must go first;
#include <gl/Glu.h>
#include "gl_error.h"
/**important*:
  all functions related to legacy fixed pipeline of the OpenGL ver 1.1 does not require loading its addresses,
  because it is expected the libraries referenced below contain those functions;
*/
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
/*	taking into account the fact that there tutorials are implemented under MS Windows and OpenGL ver 1.1 is used
	the most of the reference is made to Microsoft documentation related to using OpenGL:
	https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-reference ;
*/
#include "shared.preproc.h"
#include "shared.dbg.h"

namespace open_gl { namespace procs { namespace ver_1_1 {

	using namespace shared::defs;
	using namespace ATL;

	using ::ex_ui::draw::open_gl::CError_ex;
	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

	static _pc_sz p_err_inv_oper = _T("#__e_inv_oper: called between glBegin() and glEnd()");
	static _pc_sz p_err_unk_code = _T("#__e_undef: error code 0x%04x (%d)");
	static _pc_sz p_err_inv_enum = _T("#__e_inv_enum: '_prop_id' 0x%04x (%d) is not accepted");

	class CBasic {
	public:
		TError&  Error (void) const;

	protected:
		CBasic (void); CBasic (const CBasic&) = delete; CBasic (CBasic&&) = delete; ~CBasic (void) = default;
		mutable
		CError  m_error;
	private:
		CBasic& operator = (const CBasic&) = delete; CBasic& operator = (CBasic&&) = delete;
	};

	// https://en.cppreference.com/cpp/utility/variant ;
	// this class hides the casting inside of it;
	class c_converter {
	public:
		 c_converter (void); c_converter (const float); c_converter (const double); c_converter (const c_converter&); c_converter (c_converter&&) = delete;
		~c_converter (void) = default;

		float Float (void) const;
		double Double (void) const;

		c_converter& operator = (const c_converter&); c_converter& operator = (c_converter&&) = delete;

		double operator <<(const float);
		float  operator <<(const double);

		operator float (void) const;
		operator double (void) const;

	private:
		double m_data;
	};

	/* query: difference between option and property in programming ; (Google AI)
	Key Summary:
	a 'Property' is something an object is or has (e.g., its color), while an 'Option' is a choice for how an object should act or how a tool should work;
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

#endif/*_GL_PROCS_BASIC_H_INCLUDED*/