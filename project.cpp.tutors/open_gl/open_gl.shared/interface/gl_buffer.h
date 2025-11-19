#ifndef _GL_BUFFER_H_INCLUDED
#define _GL_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:58:20.910, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "procs\gl_procs_buffer.h"
#include "vertex\gl_vertex_data.h"
#include "shapes\gl_shape.2d.h"
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

		TError&  Error (void) const;
		uint32_t GetId (void) const;
		static
		bool  Is_bound (const uint32_t _buffer_id, CError&);
		bool  Is_bound (void) const; // https://stackoverflow.com/questions/22123222/what-are-the-effects-of-unbinding-opengl-buffers ;
		static
		bool  Is_valid (const uint32_t _buffer_id, CError&);
		bool  Is_valid (void) const; // checks the reference of the buffer identifier to buffer object; in case of failure the error status is updated;

		e_bind_targets Target (void) const;
		const bool     Target (const e_bind_targets); // it can be used by the child class before calling its 'Bind' procedure; returns 'true' in case of change 'target' value;

		err_code Unbind (void) ;

	protected:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator =  (CBuffer&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_buf_id;

		e_bind_targets m_target;
	};

	using CTriangle = ex_ui::draw::open_gl::shapes::CTriangle;

	class CBuffer_4_vert : public CBuffer { typedef CBuffer TBase;
	private: CBuffer_4_vert (const CBuffer_4_vert&) = delete; CBuffer_4_vert (CBuffer_4_vert&&) = delete;
	public : CBuffer_4_vert (void); ~CBuffer_4_vert (void);
#if (1)
		err_code Bind (void);                // binds this buffer to the already predefined target, i.e. GL_ARRAY_BUFFER;
		err_code SetData (const CTriangle&); // sets the pointer to triangle vertex array;
#endif
	private: CBuffer_4_vert& operator = (const CBuffer_4_vert&) = delete;  CBuffer_4_vert& operator =  (CBuffer_4_vert&&) = delete;
	};
}}}
#endif/*_GL_BUFFER_H_INCLUDED*/