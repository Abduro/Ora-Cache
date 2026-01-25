#ifndef _GL_BUFFER_H_INCLUDED
#define _GL_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:58:20.910, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "vertex\gl_vertex_data.h"
#include "buffer\gl_procs_buffer.h"
#include "buffer\gl_procs_buf.mem.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace data {
	class CTarget : private no_copy {
	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	private: CTarget (void) = default; ~CTarget (void) = default;
	public:
		static CString To_str (const e_bind_targets);
	};

	class CCfg : private no_copy {
	public:
		CCfg (void); ~CCfg (void) = default;

		uint32_t Count (void) const;              // returns how many vertices must be drawn;
		bool     Count (const uint32_t);          // returns 'true' in case of count number of vertices is changed;

		uint32_t Primitive (void) const;          // returns the draw mode value, i.e. what type of primitives must be drawn; procs::CPrimitives::e_others::e_points is default;
		bool     Primitive (const uint32_t);      // returns 'true' in case of draw mode value is changed;

		uint32_t StartAt (void) const;            // returns the vertex arrey index to start from for drawing;
		bool     StartAt (const uint32_t _u_ndx); // returns 'true' in case of start index value change;

	private:
		uint32_t m_count_ndx;
		uint32_t m_prim_mode;
		uint32_t m_start_ndx;
	};
}
	/* note: each buffer for one set of data: for example, setting a position and a color through different sets of data will require two buffers;
	   https://gamedev.stackexchange.com/questions/90471/should-unbind-buffers << explanation of the correct order of creation and use of the drawing pipeline;
	*/
	class CBuffer_Base {
	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	using CCfg = data::CCfg;
	public:
#if (0)
		class CBinder { // https://dictionary.cambridge.org/dictionary/english/binder ;
		public:  CBinder (CBuffer_Base&); ~CBinder (void);
		private: CBinder (void) = delete; CBinder (const CBinder&) = delete; CBinder (CBinder&&) = delete;
		private: CBinder& operator = (const CBinder&) = delete;  CBinder& operator = (CBinder&&) = delete;
			mutable
			CError   m_error;
			CBuffer_Base& m_buffer;
		public:
			err_code BindTo (const e_bind_targets);
			TError&  Error (void) const;
		};
#endif
	public:
		CBuffer_Base (void); CBuffer_Base (const CBuffer_Base&) = delete; CBuffer_Base (CBuffer_Base&&) = delete; ~CBuffer_Base (void);
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
		err_code BindTo (const e_bind_targets);  // the excerpt from the doc: ...buffer set to zero effectively unbinds any buffer object previously bound...;
		err_code Create (void);                  // generates the buffer identifier, nothing more;
		err_code Delete (void);

		const
		CCfg& Cfg (void) const;
		CCfg& Cfg (void) ;

		TError&  Error (void) const;
		uint32_t GetId (void) const;
		static
		uint32_t Get_size (const e_bind_targets, CError&);
		uint32_t Get_size (void) const;
		static
		bool  Is_bound (const uint32_t _buffer_id, CError&);
		bool  Is_bound (void) const; // https://stackoverflow.com/questions/22123222/what-are-the-effects-of-unbinding-opengl-buffers ;
		static
		bool  Is_valid (const uint32_t _buffer_id, CError&);
		bool  Is_valid (void) const; // checks the reference of the buffer identifier to buffer object; in case of failure the error status is updated;

		e_bind_targets Target (void) const;
		const bool     Target (const e_bind_targets); // it can be used by the child class before calling its 'Bind' procedure; returns 'true' in case of change 'target' value;

#if (0)
		err_code Unbind (void) ;
#else
		static
		err_code Unbind (const procs::e_bind_targets, CError&);
#endif

	protected:
		CBuffer_Base& operator = (const CBuffer_Base&) = delete; CBuffer_Base& operator = (CBuffer_Base&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_buf_id;
		CCfg     m_cfg;
		e_bind_targets m_target;
	};

namespace vertex {
	class CBuffer : public CBuffer_Base { typedef CBuffer_Base TBase;
	private: CBuffer (const CBuffer&) = delete; CBuffer (CBuffer&&) = delete;
	public : CBuffer (void); ~CBuffer (void);

		err_code Bind (void);                // binds this buffer to the already predefined target, i.e. GL_ARRAY_BUFFER;
		err_code SetData (const TVertData&); // sets vertex data vector directly; not recommended;

	private: CBuffer& operator = (const CBuffer&) = delete;  CBuffer& operator =  (CBuffer&&) = delete;
	};
}}}}
#endif/*_GL_BUFFER_H_INCLUDED*/