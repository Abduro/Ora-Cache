#ifndef _GL_PROCS_BUF_PROP_H_INCLUDED
#define _GL_PROCS_BUF_PROP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jan-2026 at 09:36:11.831, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex buffer property getter interface declaration file;
*/
#include "gl_procs_base.h"
#include "gl_procs_buffer.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace buffer {

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetBufferParameter.xhtml ;
	enum class e_buf_params : uint32_t {
	/* alias     | value    | OpenGL symbolic definition (aka name)  | Description ;
	-------------+----------+----------------------------------------+---------------------------*/
	e_access     = 0x88BB, // GL_BUFFER_ACCESS                       | returns the access policy set while mapping the buffer object; glMapBuffer();
	e_acc_flags  = 0x911F, // GL_BUFFER_ACCESS_FLAGS                 | returns the access policy set while mapping the buffer object; glMapBufferRange();
	e_immutable  = 0x821F, // GL_BUFFER_IMMUTABLE_STORAGE            | returns a boolean flag indicating whether the buffer object is immutable, initial is 'false';
	e_mapped     = 0x88BC, // GL_BUFFER_MAPPED                       | returns a flag indicating whether the buffer object is currently mapped, initial is 'false';
	e_map_len    = 0x9120, // GL_BUFFER_MAP_LENGTH                   | returns the length of the mapping into the buffer object established with glMapBuffer*();
	e_map_offset = 0x9121, // GL_BUFFER_MAP_OFFSET                   | returns the offset of the mapping into the buffer object established with glMapBuffer*();
	e_size       = 0x8764, // GL_BUFFER_SIZE                         | returns the size of the buffer object, measured in bytes; initial is 0;
	e_stg_flags  = 0x8220, // GL_BUFFER_STORAGE_FLAGS                | returns a bitfield indicating the storage flags for the buffer object; glBufferStorage();
	e_usage      = 0x8765, // GL_BUFFER_USAGE                        | returns the buffer object's usage pattern; the initial value is GL_STATIC_DRAW;
	};

	bool is_buf_param (const uint32_t _u_param);

	class CProperty : public CBase {
	typedef void    (__stdcall *pfn_Get) (uint32_t _u_bound_tgt, uint32_t _e_param, int32_t* _p_result); // gets parameter value by bound target type;
	typedef void    (__stdcall *pfn_Get_nm) (uint32_t _u_buf_id, uint32_t _e_param, int32_t* _p_result); // gwts parameter value by buffer identifier;
	public:
		CProperty (void); ~CProperty (void) = default;

		err_code Get (const e_bind_targets, const e_buf_params, uint32_t& _u_value);     // returns property value of a buffer object by given parameter;
		err_code Get (const uint32_t _u_buf_id, const e_buf_params, uint32_t& _u_value); // returns property value of a buffer object by its identifier;

		err_code Get_all (void);

	private:
		CProperty& operator = (const CProperty&) = delete; CProperty& operator = (CProperty&&) = delete;
	};

}}}}} // the number of closing brackets requires the paying attention, otherwise a lot of stupid errors during the compilation process;

typedef ex_ui::draw::open_gl::procs::buffer::CProperty TBufPropProcs; TBufPropProcs& __get_buf_prop_procs (void);

#endif/*_GL_PROCS_BUF_PROP_H_INCLUDED*/