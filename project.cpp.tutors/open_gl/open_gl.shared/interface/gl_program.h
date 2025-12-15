#ifndef _GL_PROGRAM_H_INCLUDED
#define _GL_PROGRAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:45:33.548, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_buffer.h"
#include "gl_logs.h"
#include "gl_procs.h"
#include "program\gl_$_cache.h"
#include "program\gl_prog_id.h"
#include "program\gl_prog_status.h"
#include "gl_vertex_arr.obj.h"
#include "vertex\gl_vertex_attr.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {
}
	using e_object = CPipeline::e_targets;

	class CProgram : public CPipeline {
	public:
	using CAttrArr = vertex::CAttrArray;
	using CCache   = program::CCache ;
	using CProgId  = program::CProgId;
	using CStatus  = program::CStatus;
	public:
		 CProgram (void) ;  CProgram (const CProgram&) = delete; CProgram (CProgram&&) = delete;
		~CProgram (void) ;

		 const
		 CAttrArr& Attrs (void) const; // gets the reference to the attribute array that is dependable on program shaders; (ro)
		 CAttrArr& Attrs (void) ;      // gets the reference to the attribute array that is dependable on program shaders; (rw)

		 static CString  Class (void); // returns this class name for debug purposes;

		 err_code Create (void);
		 err_code Delete (void);       // deletes the attribute object first afterwards the program object itself;

		 TError&  Error (void) const;

		 const
		 CProgId& Id (void) const;
		 CProgId& Id (void) ;

		 /* the validation of a program is determined by the target that is required to be valid:
			(a) program identifier (aka symbolic name); glIsProgram() is used by CProgId::Is_valid();
			(b) program status; glGetProgramiv() is used by CStatus::Get();
		 */
		 static
		 bool Is_valid (const uint32_t _prog_id, CError&); // there is not way to check program identifier as it can be made for shader; the comment must be clarified;
		 bool Is_valid (void) const; // checks the identifier that stored in this class object;

		 err_code Link (void) ;      // it is assumed all attached shaders is already compiled; this method calls CLinker::Link(this->Prog_id());

		 const
		 CCache&   Shaders (void) const;
		 CCache&   Shaders (void) ;
		 const
		 CStatus&  Status (void) const;
		 CStatus&  Status (void) ;

		 err_code  Use (void);       // sets this program to be current in draw pipeline;
		 err_code  Validate (void);  // mimics the validation operation that OpenGL implementations must perform when rendering commands are issued ;

		 CProgram& operator <<(const CProgId&);

	private:
		 CProgram& operator = (const CProgram&) = delete; CProgram& operator = (CProgram&&) = delete;
		 mutable
		 CError    m_error;
		 CAttrArr  m_attrs;
		 CCache    m_shaders;
		 CProgId   m_prog_id;
		 CStatus   m_status ;
	};

	class CProg_enum {
	public:
		class CAttrs : private no_copy {
		public: using CProgs = CProg_enum;
		public:
			CAttrs (CProgs* = 0); ~CAttrs (void);

			TError&  Error (void) const;
			err_code Init  (void); // after getting program build success, program shaders' attributes must be initialized;

		private:
			CError   m_error;
			CProgs*  m_progs;
		};
	public:
		CProg_enum (void); CProg_enum (const CProg_enum&) = delete; CProg_enum (CProg_enum&&) = delete; ~CProg_enum (void);

		const
		CAttrs&   Attrs (void) const;
		CAttrs&   Attrs (void);

		err_code  Build (void);    // builds the programs: compiles shaders and links the each program of this enumeration;
		err_code  Clear (void);    // detaches shaders and delets them;

		err_code  Create (void);   // creates program objects;
		err_code  Delete (void);   // deletes program objects;
		TError&   Error  (void) const;

		const
		CProgram& Get (const e_object) const; // gets the reference to the program by target object enum; (ro)
		CProgram& Get (const e_object) ;	  // gets the reference to the program by target object enum; (rw)

		err_code  Load (void); // loads shaders' source files by paths which specified in the registry;
		const
		CProgram& Ref (const uint32_t _u_ndx) const; // if the input index is out of range the reference to invalid program object is returned; (ro)
		CProgram& Ref (const uint32_t _u_ndx) ;      // if the input index is out of range the reference to invalid program object is returned; (rw)

	private:
		CProg_enum& operator = (const CProg_enum&) = delete;
		CAttrs   m_attrs;
		CError   m_error;
		CProgram m_progs[CPipeline::u_tgt_count];
	};
}}}

#endif/*_GL_PROGRAM_H_INCLUDED*/