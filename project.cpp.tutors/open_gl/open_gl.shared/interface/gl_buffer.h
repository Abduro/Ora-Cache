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
namespace buffer {

	using e_bnd_tgts = ex_ui::draw::open_gl::procs::e_bnd_tgts;
	using e_data_access = ex_ui::draw::open_gl::procs::buffer::e_data_access;

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
	/*
	the preferable way is to use the buffer identifier for getting the buffer data,
	but for comparison the old way is kept: getting by target type the buffer is bound to;
	*/
	class CData {
	public:
		CData (void); CData (const CData&) = delete; CData (CData&&) = delete; ~CData (void) = default;

		uint32_t BufferId (void) const;     // gets buffer identifier value;
		bool     BufferId (const uint32_t); // sets buffer identifier value; no check for input value validity; returns 'true' in case of value change;
		const
		TRawData& Get (void) const;
		TError& Error (void) const;

		bool Is_valid (void) const; // checks for assigning the target type and buffer identifier;

		err_code  Set (void); // retrieves data copy of the buffer object;

		e_bnd_tgts Target (void) const;       // gets buffer target type which the buffer is bound to;
		const bool Target (const e_bnd_tgts); // sets buffer target type, returns 'true' in case of target value change;

		CData& operator <<(e_bnd_tgts);       // sets the target type the buffer is bound to;
		CData& operator <<(const uint32_t _buf_id);

	private:
		CData& operator = (const CData&) = delete; CData& operator = (CData&&) = delete;
		CError m_error;
		e_bnd_tgts m_target;  // target type which the buffer is bound to;
		uint32_t   m_buf_id;
		TRawData   m_data;
	};

	class CTarget : private no_copy { using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	private: CTarget (void) = default; ~CTarget (void) = default;
	public:
		static CString To_str (const e_bind_targets);
	};
}
	/* note: each buffer for one set of data: for example, setting a position and a color through different sets of data will require two buffers;
	   https://gamedev.stackexchange.com/questions/90471/should-unbind-buffers << explanation of the correct order of creation and use of the drawing pipeline;
	*/
	class CBuffer_Base {
	using e_bnd_tgts = buffer::e_bnd_tgts;
	using CCfg = buffer::CCfg;
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
		err_code BindTo (const e_bnd_tgts);  // the excerpt from the doc: ...buffer set to zero effectively unbinds any buffer object previously bound...;
		err_code Create (void);              // generates the buffer identifier, nothing more;
		err_code Delete (void);

		const
		CCfg& Cfg (void) const;
		CCfg& Cfg (void) ;

		TError&  Error (void) const;
		uint32_t GetId (void) const;
		static
		uint32_t Get_size (const e_bnd_tgts, CError&);
		uint32_t Get_size (void) const;
		static
		bool  Is_bound (const uint32_t _buffer_id, const e_bnd_tgts, CError&); // the getting currently bound buffer identifier requires bind target type;
		bool  Is_bound (void) const; // https://stackoverflow.com/questions/22123222/what-are-the-effects-of-unbinding-opengl-buffers ;
		static
		bool  Is_valid (const uint32_t _buffer_id, CError&);
		bool  Is_valid (void) const; // checks the reference of the buffer identifier to buffer object; in case of failure the error status is updated;

		e_bnd_tgts Target (void) const;
		const bool Target (const e_bnd_tgts); // it can be used by the child class before calling its 'Bind' procedure; returns 'true' in case of change 'target' value;

#if (0)
		err_code Unbind (void) ;
#else
		static
		err_code Unbind (const procs::e_bnd_tgts, CError&);
#endif

	protected:
		CBuffer_Base& operator = (const CBuffer_Base&) = delete; CBuffer_Base& operator = (CBuffer_Base&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_buf_id;
		CCfg     m_cfg;
		e_bnd_tgts m_target;
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