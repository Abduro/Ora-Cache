#ifndef _GL_BUFFER_H_INCLUDED
#define _GL_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:58:20.910, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "procs\gl_procs_buffer.h"
#include "shapes\gl_vertex.h"
namespace ex_ui { namespace draw { namespace open_gl {
namespace data {
	class CTarget : private no_copy {
	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	private: CTarget (void) = default; ~CTarget (void) = default;
	public:
		static CString To_str (const e_bind_targets);
	};
}
	/* note: each buffer for one set of data: for example, setting a position and a color through different sets of data will require two buffers;
	   https://gamedev.stackexchange.com/questions/90471/should-unbind-buffers << explanation of the correct order of creation and use of the drawing pipeline;
	*/
	class CBuffer {
	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	public:
#if (0)
		class CBinder { // https://dictionary.cambridge.org/dictionary/english/binder ;
		public:  CBinder (CBuffer&); ~CBinder (void);
		private: CBinder (void) = delete; CBinder (const CBinder&) = delete; CBinder (CBinder&&) = delete;
		private: CBinder& operator = (const CBinder&) = delete;  CBinder& operator = (CBinder&&) = delete;
			mutable
			CError   m_error;
			CBuffer& m_buffer;
		public:
			err_code BindTo (const e_bind_targets);
			TError&  Error (void) const;
		};
#endif
	public:
		CBuffer (void); CBuffer (const CBuffer&) = delete; CBuffer (CBuffer&&) = delete; ~CBuffer (void);
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
		err_code BindTo  (const e_bind_targets); // the excerpt from the doc: ...buffer set to zero effectively unbinds any buffer object previously bound...;
		err_code Create  (void);
		err_code Destroy (void);
#if (0)
		const
		TData&   Data (void) const;
		TData&   Data (void) ;
#endif
		TError&  Error (void) const;
		uint32_t GetId (void) const;
		static
		bool  Is_bound (const uint32_t _buffer_id, CError&);
		bool  Is_bound (void) const; // https://stackoverflow.com/questions/22123222/what-are-the-effects-of-unbinding-opengl-buffers ;
		static
		bool  Is_valid (const uint32_t _buffer_id, CError&);
		bool  Is_valid (void) const; // checks the reference of the buffer identifier to buffer object; in case of failure the error status is updated;

	private:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator =  (CBuffer&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_buf_id;
//		TData    m_data;

		e_bind_targets m_target;
	};
}}}
#endif/*_GL_BUFFER_H_INCLUDED*/