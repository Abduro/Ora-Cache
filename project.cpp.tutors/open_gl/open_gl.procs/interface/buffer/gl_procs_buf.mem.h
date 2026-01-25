#ifndef _GL_PROCS_BUF_MEM_H_INCLUDED
#define _GL_PROCS_BUF_MEM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 21:19:58.639, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer memory accessor interface declaration file;
*/
#include "gl_procs_base.h"
#include "gl_procs_buf.prop.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace buffer {

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ;
	enum class e_data_access : uint32_t {
	/* alias     | value    | OpenGL symbolic definition  | description
	-------------+----------+-----------------------------+---------------------------*/
	e_read       = 0x88B8, // GL_READ_ONLY                | indicates that the returned pointer may be used to read buffer object data;
	e_read_write = 0x88BA, // GL_READ_WRITE               | indicates that the returned pointer may be used to read and to modify buffer object data;
	e_write      = 0x88B9, // GL_WRITE_ONLY               | indicates that the returned pointer may be used to modify buffer object data;
	};

	class CData_Accessor : public CBase {
	typedef void* (__stdcall *pfn_Map) (const uint32_t e_target, const uint32_t e_access); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ;
	typedef void* (__stdcall *pfn_MapNamed) (const uint32_t u_buf_id, const uint32_t e_access); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ; v4.5;

	public:
		CData_Accessor (void); ~CData_Accessor (void) = default;

		err_code Get_all (void); // loads all function pointers to the cache;

		void* Get_Ptr (const uint32_t e_target, const uint32_t e_access); // gets pointer to data of the bound buffer by target enumeration;
		void* Get_Ptr_nm (const uint32_t _u_buf_id, const uint32_t e_access); // gets pointer to data of the named buffer, i.e. queries by buffer identifier;

		static uint32_t Get_Size (const e_bind_targets, CError&);         // gets buffer size in bytes by the target which the buffer is *bound* to, no bound buffer - no size;
		static uint32_t Get_Size_nm (const uint32_t _u_buf_id, CError&);  // gets buffer size in bytes by the buffer identifier;

	private:
		CData_Accessor& operator = (const CData_Accessor&) = delete; CData_Accessor& operator = (CData_Accessor&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::buffer::CData_Accessor TBufAccessor; TBufAccessor& __get_buf_acc_procs (void);

#endif/*_GL_PROCS_BUF_MEM_H_INCLUDED*/