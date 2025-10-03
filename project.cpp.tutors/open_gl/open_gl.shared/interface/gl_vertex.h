#ifndef _GL_VERTEX_H_INCLUDED
#define _GL_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vertex {

	class CCoord {
	public:
		CCoord (const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f); CCoord (const CCoord&); CCoord (CCoord&&); ~CCoord (void);

		float X (void) const; void  X (const float); float& X (void);
		float Y (void) const; void  Y (const float); float& Y (void);
		float Z (void) const; void  Z (const float); float& Z (void);

	public:
		CCoord& operator = (const CCoord&);
		CCoord& operator = (CCoord&&); // neither 'swap' or 'move' operations due to there is no non-copyable handles; https://en.cppreference.com/w/cpp/algorithm/swap.html ; 
	private:
		float m_coord[3]; // 0:_x; 1:_y; 2:_z;
	};
}

	class CVertex {
	public:
		 CVertex (void) ;  CVertex (const CVertex&) = delete; CVertex (CVertex&&) = delete;
		~CVertex (void) ;

		 TError& Error (void) const;
		 static
		 procs::CVertex& Procs (void);

	private:
		 CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;
		 mutable
		 CError  m_error;
	};

}}}

#endif/*_GL_VERTEX_H_INCLUDED*/