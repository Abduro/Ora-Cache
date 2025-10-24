#ifndef _GL_SHAPE_BS_H_INCLUDED
#define _GL_SHAPE_BS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 20:56:51.657, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D/3D shape base wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace data {
	typedef ::std::vector<float>  TRawData;
	class CData { // this class is the wrapper over parameters for calling the one of the functions glVertexAttrib*Pointer();
	public:
		CData (void); CData (const CData&) = delete; CData (CData&&) = delete; ~CData (void);

		TError&   Error (void) const;
		uint32_t  Index (void) const;
		bool      Index (const uint32_t);    // returns 'true' in case of attribute index value is changed;

		bool   Is_normalized (void) const;
		bool   Is_normalized (const bool);   // returns 'true' in case of normalization flag value change;

		const
		TRawData& Raw (void) const;
		TRawData& Raw (void) ;
		uint32_t  Offset (void) const;
		bool      Offset (const uint32_t);   // returns 'true' in case of offset value change;
		uint32_t  Stride (void) const;
		bool      Stride (const uint32_t);   // returns 'true' in case of stride value change;
		uint32_t  Size   (void) const;

	private:
		CData& operator = (const CData&) = delete; CData& operator = (CData&&) = delete;
		mutable
		CError   m_error;
		TRawData m_data ;
		uint32_t m_index;
		uint32_t m_offset;
		bool     m_normal; // vertex value(s) normalization flag;
		uint32_t m_stride;
	};
}
}}}

typedef ex_ui::draw::open_gl::data::CData TData;

#endif/*_GL_SHAPE_BS_H_INCLUDED*/