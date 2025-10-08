#ifndef _GL_PROCS_BUFFER_H_INCLUDED
#define _GL_PROCS_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Oct-2025 at 21:49:52.645, (UTC+4), Batumi, Tuesday;
	This is Ebo Pack OpenGL vertex buffer functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
	enum class e_bind_targets : uint32_t {
	e_array    = 0x8892, // GL_ARRAY_BUFFER; a vertex attributes;
	e_counter  = 0x92C0, // GL_ATOMIC_COUNTER_BUFFER; atomic counter storage; ver: 4.2 or greater;
	e_read     = 0x8F36, // GL_COPY_READ_BUFFER; buffer copy source;
	e_write    = 0x8F37, // GL_COPY_WRITE_BUFFER; buffer copy destination;
	e_disp     = 0x90EE, // GL_DISPATCH_INDIRECT_BUFFER; indirect compute dispatch commands; ver: 4.3 or greater;
	e_draw     = 0x8F3F, // GL_DRAW_INDIRECT_BUFFER; indirect command arguments;
	e_el_arr   = 0x8893, // GL_ELEMENT_ARRAY_BUFFER; vertex array indices;
	e_pxl_pk   = 0x88EB, // GL_PIXEL_PACK_BUFFER; pixel read target;
	e_pxl_unpk = 0x88EC, // GL_PIXEL_UNPACK_BUFFER; texture data source;
	e_query    = 0x9192, // GL_QUERY_BUFFER; query result buffer; ver: 4.4 or greater;
	e_$_stg    = 0x90D2, // GL_SHADER_STORAGE_BUFFER; read-write storage for shaders; ver: 4.3 or greater;
	e_texture  = 0x8C2A, // GL_TEXTURE_BUFFER; texture data buffer;
	e_trans    = 0x8C8E, // GL_TRANSFORM_FEEDBACK_BUFFER; transform feedback buffer;
	e_uniform  = 0x8A11, // GL_UNIFORM_BUFFER; uniform block storage;
	};

	bool is_bind_target(const uint32_t _u_tgt_type);
	/* ToDo: the enumeration of below can be separated to the following enums:
		the excerpt from https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
		(1) freaquency access:
			(1.a) the stream  - data is modified once and used at most a few times;
			(1.b) the static  - data is modified once and used many times;
			(1.c) the dynamic - data is modified repeatedly and used many times;
		(2) operation type:
			(2.a) to draw - data is used as the source for drawing and image spec cmds; data is modified by app;
			(2.b) to read - data is returned as result of the query to data store; data is modified by reading;
			(2.c) to copy - data is used as the source for drawing and image spec cmds; data is modified by reading;
	*/
	enum class e_buf_usage : uint32_t {
	e_stream_draw = 0x88E0, // GL_STREAM_DRAW ;
	e_stream_read = 0x88E1, // GL_STREAM_READ ;
	e_stream_copy = 0x88E2, // GL_STREAM_COPY ;
	e_static_draw = 0x88E4, // GL_STATIC_DRAW ;
	e_static_read = 0x88E5, // GL_STATIC_READ ;
	e_static_copy = 0x88E6, // GL_STATIC_COPY ;
	e_dyna_draw   = 0x88E8, // GL_DYNAMIC_DRAW;
	e_dyna_read   = 0x88E9, // GL_DYNAMIC_READ;
	e_dyna_copy   = 0x88EA, // GL_DYNAMIC_COPY;
	};

	bool is_buf_usage(const uint32_t _u_oper_type);

	/**question*: what is the reason to use 'signed int' data type for 'count' and do not expect negative value or even '0'?
	*/

	// https://www.abbreviations.com/abbreviation/Target >> tgt ;
	// https://www.allacronyms.com/buffer/abbreviated >> buf ;
	class CBuffer : public CBase {
	typedef void    (__stdcall *pfn_Bind)  (uint32_t _u_tgt_id, uint32_t _u_buf_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
	typedef void    (__stdcall *pfn_Data)  (uint32_t _u_tgt_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	typedef void    (__stdcall *pfn_Delete) (int32_t _n_count, const uint32_t* _p_buffers); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml ;
	typedef void    (__stdcall *pfn_GenIds) (int32_t _n_count, uint32_t* _p_buf_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml ;
	typedef int32_t (__stdcall *pfn_IsBuf) (uint32_t _u_buf_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsBuffer.xhtml [
	typedef void    (__stdcall *pfn_Named) (uint32_t _u_buf_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	public:
		CBuffer (void); ~CBuffer (void) = default;

		err_code Bind (const uint32_t _u_tgt_id, const uint32_t _u_buf_id); // binds a buffer object to the specified buffer binding point ;
		err_code Data (const uint32_t _u_tgt_id, const ptrdiff_t _n_size, const void* _p_data, const uint32_t _u_usage); // creates and initializes a buffer object's data store currently bound to target is used ;
		err_code Delete (const int32_t  _n_count, const uint32_t* _p_buffers); // deletes _n_count buffer objects named by the elements of the array _p_buffers ;
		err_code GenerateIds (const int32_t _n_count, uint32_t* _p_buf_ids); // returns _n_count buffer object names in _p_names array ;
		bool  Is_Buffer(const uint32_t _u_buf_id) ;
		err_code Named (const uint32_t _u_buf_id, const ptrdiff_t _n_size, const void* _p_data, const uint32_t _u_usage);  // creates and initializes a buffer object associated with ID specified by the caller in buffer will be used instead ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator = (CBuffer&&) = delete;
	};
}}}}

#endif/*_GL_PROCS_BUFFER_H_INCLUDED*/