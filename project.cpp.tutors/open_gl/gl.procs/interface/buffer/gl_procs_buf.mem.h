#ifndef _GL_PROCS_BUF_MEM_H_INCLUDED
#define _GL_PROCS_BUF_MEM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 21:19:58.639, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer memory accessor interface declaration file;
*/
#include "gl_procs_base.h"
#include "gl_procs_buf.prop.h"
#include "sys.mem.heap.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace buffer {

	using e_bnd_tgts = e_bind_targets;

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBufferRange.xhtml ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUnmapBuffer.xhtml ;
	enum class e_data_access : uint32_t {
	/* alias     | value    | OpenGL symbolic def | description
	-------------+----------+---------------------+---------------------------*/
	e_read       = 0x88B8, // GL_READ_ONLY        | indicates that the returned pointer may be used to read buffer object data;
	e_read_write = 0x88BA, // GL_READ_WRITE       | indicates that the returned pointer may be used to read and to modify buffer object data;
	e_write      = 0x88B9, // GL_WRITE_ONLY       | indicates that the returned pointer may be used to modify buffer object data;
	};

	class CData_Accessor : public CBase {
	typedef void* (__stdcall *pfn_Map) (const uint32_t _u_target, const uint32_t _e_access); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ;
	typedef void* (__stdcall *pfn_Map_nm) (const uint32_t _u_buf_id, const uint32_t _e_access); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ; v4.5;
	typedef void* (__stdcall *pfn_Range) (const uint32_t _u_target, const ptrdiff_t _l_offset, const ptrdiff_t _l_length, const uint32_t _u_acc_flags); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBufferRange.xhtml ;
	typedef void* (__stdcall *pfn_Range_nm) (const uint32_t _u_buf_id, const ptrdiff_t _l_offset, const ptrdiff_t _l_length, const uint32_t _u_acc_flags); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBufferRange.xhtml ;
	typedef void* (__stdcall *pfn_Unmap) (const uint32_t _u_target); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUnmapBuffer.xhtml ;
	typedef void* (__stdcall *pfn_Unmap_nm) (const uint32_t _u_buf_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUnmapBuffer.xhtml ;

	public:
		CData_Accessor (void); ~CData_Accessor (void) = default;

		err_code Get_all (void); // loads all function pointers to the cache;

		err_code Get_Ptr (const e_bnd_tgts e_target, const e_data_access e_access, TRawData&); // gets pointer to data of the bound buffer by target enumeration;
		err_code Get_Ptr (const uint32_t _u_buf_id, const e_data_access e_access, TRawData&);  // gets pointer to data of the named buffer, i.e. queries by buffer identifier;

		static uint32_t Get_Size (const e_bind_targets, CError&);      // gets buffer size in bytes by the target which the buffer is *bound* to, no bound buffer - no size;
		static uint32_t Get_Size (const uint32_t _u_buf_id, CError&);  // gets buffer size in bytes by the buffer identifier;

		static bool Is_mapped (const e_bind_targets, CError&);     // checks buffer bound to given target is currently mapped or not;
		static bool Is_mapped (const uint32_t u_buf_id, CError&);  // checks buffer with given identifier is currently mapped or not;

		// these two procs will be automatically called after copying buffer data to local data container;
		err_code Unmap (const e_bnd_tgts e_target); // releases the mapping to the graphics card memory by given target type the buffer is bound to;
		err_code Unmap (const uint32_t _u_buf_id);  // releases the mapping to the graphics card memory by given buffer identifier;

	private:
		CData_Accessor& operator = (const CData_Accessor&) = delete; CData_Accessor& operator = (CData_Accessor&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::buffer::CData_Accessor TBufAccessor; TBufAccessor& __get_buf_acc_procs (void);

#endif/*_GL_PROCS_BUF_MEM_H_INCLUDED*/