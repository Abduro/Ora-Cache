#ifndef _GL_PROCS_BASE_H_INCLUDED
#define _GL_PROCS_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 14:25:53.097, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL functions' loader base interface declaration file;
*/
#include "shared.defs.h"
#include <gl/gl.h>       // the headers' include order is important: windows.h must go first;
#include "gl_error.h"

#pragma comment(lib, "opengl32.lib")
/*
	https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-reference ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/state-variables ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/gl-functions ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/glu-functions ;
*/
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
	// https://www.khronos.org/opengl/wiki/OpenGL_Type ;

	using namespace shared::defs;
	using namespace ATL;

	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

	typedef ::std::map<CString, PROC> TProcCache;  // the key is the procedure name, the value is the pointer to the address of procefure function/method;
	/**important*:
	if original function of the OpenGL returns 'void' the wrapper will return 'err_code' for indicating 'success' or 'failure' of loading a function pointer;
	*/
	// ToDo: it would be better in case if the cache is global and static for all functions; it looks very like OpenGL functions do not have the same names;
	class CBase { // not thread safe yet;
	public:
		CBase (void) ; CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

		err_code Erase (void);       // clears the cached function pointers; it may be required on current context change; ToDo: must be thread-safe;

		TError&  Error (void) const;
		PROC     Get (_pc_sz _p_fun_name); // https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;
		err_code Get_all (void);     // get all functions pointers; in this base class it does nothing, must be implemented in a child class if necessary;

		CString  Print (void) const; // enumerates all loaded function(s); the output string is formatted for message box (i.e. multilined);

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;

	protected:
		mutable
		CError m_error;
		TProcCache m_cached; // every child class will have its own cache of the functions pointers;
	};

}}}}
#endif/*_GL_PROCS_BASE_H_INCLUDED*/