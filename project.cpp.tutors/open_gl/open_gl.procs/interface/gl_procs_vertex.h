#ifndef _GL_PROCS_VERTEX_H_INCLUDED
#define _GL_PROCS_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 12:10:39.867, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL vertex related functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
#include "gl_types.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace vertex {
	
	class CArray : public CBase {
	typedef void (__stdcall *pfn_Binding) (uint32_t _arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
	typedef void (__stdcall *pfn_Delete ) (int32_t _n_count, const uint32_t* _p_arrays); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	typedef void (__stdcall *pfn_GetIds ) (int32_t _n_count, uint32_t* _p_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
	typedef int32_t (__stdcall *pfn_IsArr) (uint32_t _u_arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml ; (no ms windows doc);
	public:
		CArray (void); ~CArray (void) = default;

		err_code Bind    (const uint32_t _arr_id); // binds the vertex array object with identifier (aka name) of the array; in case of _arr_id == 0, unbound process is initiated;
		err_code Delete  (const uint32_t _n_count, const uint32_t* _p_arrays); // deletes vertex array objects;
		err_code GetIds  (const uint32_t _n_count, uint32_t* _p_ids); // generates vertex array object identifiers (aka names) and guarantees that none of the returned names was in use immediately before the call to it ;
		/* the excerpt from https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml :
		return false in cases
		...if array is zero, or if array is not the name of a vertex array object, or if an error occurs...
		...if array is a name returned by glGenVertexArrays, by that has not yet been bound through a call to glBindVertexArray...
		*/
		bool Is_array (const uint32_t _arr_id); // determines if an identifier (aka name) corresponds to a vertex array object;

		err_code Get_all (void) ;

	private:
		CArray& operator = (const CArray&) = delete; CArray& operator = (CArray&&) = delete;
	};

	class CAttr : public CBase {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveAttrib.xhtml ;
	typedef void    (__stdcall *pfn_Active ) (uint32_t _prog_id, uint32_t _n_ndx, uint32_t _u_buf_size, uint32_t* _p_length, int32_t* _p_size, uint32_t* _p_type, char* _p_name);
	typedef void    (__stdcall *pfn_Disable) (uint32_t _arr_id , uint32_t _n_ndx); // since v.4.5; // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void    (__stdcall *pfn_Enable ) (uint32_t _arr_id , uint32_t _n_ndx); // since v.4.5; // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef int32_t (__stdcall *pfn_GetIndex)(uint32_t _prog_id, const char* _p_att_name);         // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
	typedef void    (__stdcall *pfn_SetIndex)(uint32_t _prog_id, uint32_t _u_ndx, const char* _p_att_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml ;
	public:
		CAttr (void); ~CAttr (void) = default;

		err_code Disable  (const uint32_t _arr_id , const uint32_t _n_ndx); // disables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code Enable   (const uint32_t _arr_id , const uint32_t _n_ndx); // enables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code GetActive(const uint32_t _prog_id, const uint32_t _n_ndx, uint32_t& _u_size, uint32_t& _u_type, CString& _name); // gets info of an active attribute variable for the specified program object;
		int32_t  GetIndex (const uint32_t _prog_id, _pc_sz _p_att_name);    // returns the location (i.e. the index) of an attribute variable ; *after* the link;
		err_code SetIndex (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx); // sets the index *before* the link, otherwise no effect;

		err_code Get_all (void) ;

	private:
		CAttr& operator = (const CAttr&) = delete; CAttr& operator = (CAttr&&) = delete;
	};

	class CAttrArray : public CBase {
	typedef void (__stdcall *pfn_Disable) (uint32_t _u_ndx);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void (__stdcall *pfn_Enable ) (uint32_t _u_ndx);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	public:
		CAttrArray (void); ~CAttrArray (void) = default;

		err_code Disable (const uint32_t _u_ndx);  // disables currently bound vertex attribute array object for the operation;
		err_code Enable  (const uint32_t _u_ndx);  // enables currently bound vertex attribute array object for the operation;

		err_code Get_all (void) ;

	private:
		CAttrArray& operator = (const CAttrArray&) = delete; CAttrArray& operator = (CAttrArray&&) = delete;
	};

	// https://dictionaryblog.cambridge.org/2019/07/24/evolving-and-disrupting-verbs-meaning-change/ ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttrib.xhtml ;
	// https://github.com/abbrcode/abbreviations-in-code ;

	class CAttrMod : public CBase {
	typedef void (__stdcall *pfn_3f) (uint32_t _u_ndx, float _f_0, float _f_1, float _f_2);
	typedef void (__stdcall *pfn_4f) (uint32_t _u_ndx, float _f_0, float _f_1, float _f_2, float _f_3);
	public:
		CAttrMod (void); ~CAttrMod (void) = default;

		err_code Modify_f3 (const uint32_t _u_ndx, const float _f_0, const float _f_1, const float _f_2);
		err_code Modify_f4 (const uint32_t _u_ndx, const float _f_0, const float _f_1, const float _f_2, const float _f_3);

		err_code Get_all (void) ;

	private:
		CAttrMod& operator = (const CAttrMod&) = delete; CAttrMod& operator = (CAttrMod&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	class CAttrPtr : public CBase {
	typedef void (__stdcall *pfn_AttPtr)   (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_I) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_L) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	public:
		CAttrPtr (void); ~CAttrPtr (void) = default;
		// the input arg 'size' should *not* have 'signed int' data type, because all acceptable values are greater than 0 (zero);
		// the input arg 'stride' may have value 0 or greater; its data type intentionally is changed to 'unsigned';
		err_code Set   (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const bool _b_normalized, const uint32_t _u_stride, const uint32_t _u_offset = 0); // defines an array of generic vertex attribute data (signed & unsigned) ;
		err_code Set_I (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT ;
		err_code Set_L (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // specifies state for a generic vertex attribute array associated with a shader attribute variable declared with 64-bit double precision components ;

		err_code Get_all (void) ;

	private:
		CAttrPtr& operator = (const CAttrPtr&) = delete; CAttrPtr& operator = (CAttrPtr&&) = delete;
	};
}
}}}}

typedef ex_ui::draw::open_gl::procs::vertex::CArray     TVertArrProcs;      TVertArrProcs&  __get_arr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttr      TVertAttrProcs;     TVertAttrProcs& __get_attr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttrArray TAttrArrProcs;      TAttrArrProcs&  __get_attr_arr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttrMod   TVertAttrModProcs;  TVertAttrModProcs& __get_attr_mod_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttrPtr   TVertAttrPtrProcs;  TVertAttrPtrProcs& __get_attr_ptr_procs (void);

#endif/*_GL_PROCS_VERTEX_H_INCLUDED*/