#ifndef _GL_VERTEX_H_INCLUDED
#define _GL_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vertex {
#if (1)
	class CCoord : private no_copy {
	public:
		CCoord (const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f); CCoord (const CCoord&); CCoord (CCoord&&); ~CCoord (void) = default;

		float X (void) const; void  X (const float); float& X (void);
		float Y (void) const; void  Y (const float); float& Y (void);
		float Z (void) const; void  Z (const float); float& Z (void);

	public:
		CCoord& operator = (const CCoord&);
		CCoord& operator = (CCoord&&); // neither 'swap' or 'move' operations due to there is no non-copyable handles; https://en.cppreference.com/w/cpp/algorithm/swap.html ; 
	private:
		float m_coord[3]; // 0:_x; 1:_y; 2:_z;
	};
#endif
	// https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects ;
	class CArray {
	public:
		CArray (void); CArray (const CArray&) = delete; CArray (CArray&&) = delete; ~CArray (void);

		err_code Bind   (void); // perhaps it would be better to replace word 'bind' by 'activate' or 'current';
		bool  Is_bound  (void) const;
		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;
		uint32_t GetId  (void) const;
		err_code Unbind (void);

	private:
		CArray& operator = (const CArray&) = delete; CArray& operator = (CArray&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_arr_id;
	};


}
#if (0)	
	class CVertex {
	public:
		 CVertex (void) ;  CVertex (const CVertex&) = delete; CVertex (CVertex&&) = delete;
		~CVertex (void) ;

		 TError& Error (void) const;

	private:
		 CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;
		 mutable
		 CError  m_error;
	};
#endif
}}}

#endif/*_GL_VERTEX_H_INCLUDED*/