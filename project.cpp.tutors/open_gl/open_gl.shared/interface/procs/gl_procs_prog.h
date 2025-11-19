#ifndef _GL_PROCS_PROG_H_INCLUDED
#define _GL_PROCS_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 01:17:24.959, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL program functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

namespace program {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResource.xhtml >> the table of associations of properties to interfaces;
	/* important: not all interfaces is enumerated yet; */
	enum class e_interface : uint32_t {
	/* alias     | value    | OpenGL symbolic name | brief description ;
	-------------+----------+----------------------+-------------------*/
	e_buff_var   = 0x92E5, // GL_BUFFER_VARIABLE   | the query is targeted at the set of active buffer variables used by program;
	e_prog_in    = 0x92E3, // GL_PROGRAM_INPUT     | the query is targeted at the set of active input variables used by the *first* shader stage of program;
	e_prog_out   = 0x92E4, // GL_PROGRAM_OUTPUT    | the query is targeted at the set of active output variables produced by the *last* shader stage of program;
	e_uniform    = 0x92E1, // GL_UNIFORM           | the query is targeted at the set of active uniforms within program;
	};
	typedef e_interface e_iface;
	/* important: not all properties is enumerated yet; */
	enum class e_property : uint32_t {
	/* alias     | value    | OpenGL symbolic name | brief description ;
	-------------+----------+----------------------+-------------------*/
	e_active_res = 0x92F5, // GL_ACTIVE_RESOURCES  | the number of resources in the active resource list for particular interface;
	e_arr_size   = 0x92FB, // GL_ARRAY_SIZE        | the number of active array elements of an active variable; (in)
	e_arr_stride = 0x92FE, // GL_ARRAY_STRIDE      | the stride between array elements in an active variable; (out)
	e_loc_index  = 0x930F, // GL_LOCATION_INDEX    | the fragment color index of an active fragment shader output variable;
	e_location   = 0x930E, // GL_LOCATION          | the assigned location for an active uniform, input, output, or subroutine uniform variable;
	e_name_len   = 0x92F9, // GL_NAME_LENGTH       | the length of the name string associated with an active variable;
	e_offset     = 0x92FC, // GL_OFFSET            | the offset of an active variable ;
	e_type       = 0x92FA, // GL_TYPE              | the type of an active variable; (in)
	};
	typedef e_property e_prop;
	typedef ::std::map<e_interface, ::std::vector<e_property>> TIface_assoc;

	// the querying interface info is available from 4.3 version of OpenGL API;
	class CInterface : public CBase {
	typedef void (__stdcall *pfn_Get) (uint32_t _prog_id, uint32_t _u_iface, uint32_t _u_prop, int32_t* _p_value); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInterface.xhtml ;
	public:
		CInterface (void); ~CInterface (void) = default;

		static const ::std::vector<e_property>& GetProps (const e_interface);  // finds for given interface all properties associated with it;
		static const bool Is_acceptable (const uint32_t _u_interface);         // checks input argument for being belong to interface names/identifiers enumeration;
		static const bool Is_related (const e_interface, const e_property);    // checks the relation between input values of interface and property;

		err_code Get (const uint32_t _prog_id, const e_interface, const e_property, uint32_t& _u_value); // queries the property of the interface identifed by 'e_interface' in program, the property identifier of which is one of 'e_property' elements;
		err_code Get_all (void);

	private:
		CInterface& operator = (const CInterface&) = delete; CInterface& operator = (CInterface&&) = delete;
	};

	typedef ::std::map<e_property, ::std::vector<e_interface>> TProp_assoc;

	class CProperty {
	public:
		static const bool Is_checked (const e_interface, const ::std::vector<e_property>& _props, ::std::vector<e_property>& _error); // checks property set for consistency with given interface;
		static const ::std::vector<e_interface>& Find (const e_property); // finds for given property all interfaces associated with it;

	private: CProperty (void) = delete; CProperty (const CProperty&) = delete; CProperty (CProperty&&) = delete; ~CProperty (void) = delete;
	private: CProperty& operator = (const CProperty&) = delete; CProperty& operator = (CProperty&&) = delete;
	};

	typedef ::std::vector<e_property> TRawProps;
	typedef ::std::vector<int32_t> TRawValues;    // perhaps 'signed' integer data type is required for returning negative coordinate value;

	class CResource : public CBase {
	typedef int32_t (__stdcall *pfn_GetLoc) (uint32_t _prog_id, uint32_t _u_iface, const char* _p_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceLocation.xhtml
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResource.xhtml ;
	typedef void (__stdcall *pfn_GetRes ) (uint32_t _prog_id, uint32_t _u_iface, uint32_t _u_ndx, uint32_t _u_prop_count, const uint32_t* _p_props, uint32_t _u_buf_size, uint32_t* _p_length, int32_t* _p_params);
	typedef void (__stdcall *pfn_GetName) (uint32_t _prog_id, uint32_t _u_iface, uint32_t _u_ndx, uint32_t _u_buf_size, uint32_t* _p_length, char* _p_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceName.xhtml ;
	public:
		CResource (void); ~CResource (void) = default;

		err_code Get_all (void);

		int32_t  GetLocate (const uint32_t _prog_id, const e_interface, const char* _p_att_name); // queries the location of a named resource within a program;
		err_code GetName (const uint32_t _prog_id, const e_interface, const uint32_t _u_ndx, CString&); // queries the name of an indexed resource within a program;
		err_code GetValues (const uint32_t _prog_id, const e_interface, const uint32_t _u_ndx, const TRawProps&, TRawValues&); // retrieves values for multiple properties of a single active resource within a program object;

	private:
		CResource& operator = (const CResource&) = delete; CResource& operator = (CResource&&) = delete;
	};

	class CShaders : public CBase {
	typedef void (__stdcall *pfn_Attach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
	typedef void (__stdcall *pfn_Attached) (uint32_t _prog_id, uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttachedShaders.xhtml ;
	typedef void (__stdcall *pfn_Detach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml ;
	public:
		CShaders (void); ~CShaders (void) = default;

		err_code Attach  (const uint32_t _prog_id, const uint32_t _shader_id); // attaches the shader object specified by '_shader_id' to the program object specified by '_prog_id' ;
		err_code Detach  (const uint32_t _prog_id, const uint32_t _shader_id); // detaches a shader object from a program object to which it is attached ;
		err_code Attached(const uint32_t _prog_id, const uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // returns the identifiers of the shader objects attached to a program object;

		err_code Get_all (void);

	private:
		CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
	};
}
	// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
	enum class e_prog_params : uint32_t {
	/* alias          | value    | OpenGL symbolic name           | brief description ;
	------------------+----------+--------------------------------+-------------------*/
	e_act_attrs       = 0x8B87, // GL_ACTIVE_ATTRIBUTES           | the number of active attribute variables for program; 
	e_attr_name_max   = 0x8B8A, // GL_ACTIVE_ATTRIBUTE_MAX_LENGTH | the length of the longest active attribute name for program;
	e_act_uniforms    = 0x8B86, // GL_ACTIVE_UNIFORMS             | the number of active uniform variables for program;
	e_act_uniform     = 0x8B87, // GL_ACTIVE_UNIFORM_MAX_LENGTH   | the length of the longest active attribute name for program;
	e_attach_shaders  = 0x8B85, // GL_ATTACHED_SHADERS            | the number of shader objects attached to program;
	e_delete_status   = 0x8B80, // GL_DELETE_STATUS               | a program is currently flagged for deletion;
	e_log_info_len    = 0x8B84, // GL_INFO_LOG_LENGTH             | the number of characters in the information log for program; 
	e_lnk_status      = 0x8B82, // GL_LINK_STATUS                 | the last link operation on program was successful or not; 
	e_valid_status    = 0x8B83, // GL_VALIDATE_STATUS             | the last validation operation on program was successful, or isn't;
	};

	class CProg : public CBase {
	typedef uint32_t (__stdcall *pfn_Create)   (void); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
	typedef void     (__stdcall *pfn_Delete)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)  (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
	typedef uint32_t (__stdcall *pfn_IsProg)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsProgram.xhtml ;
	typedef void     (__stdcall *pfn_Params)   (uint32_t _prog_id, uint32_t _param_id, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
	typedef void     (__stdcall *pfn_Use)      (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
	typedef void     (__stdcall *pfn_Validate) (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
	public:
		CProg (void); ~CProg (void) = default;

		uint32_t Create  (void);  // creates an empty program object and returns a non-zero value by which it can be referenced ;
		err_code Delete  (const uint32_t _prog_id);  // frees the memory and invalidates the name associated with the program object specified by _prog_id ;
		err_code InfoLog (const uint32_t _prog_id, const int32_t _buf_size, int32_t* _log_len, char* _p_log); // returns the information log for the specified program object ;
		bool     IsProg  (const uint32_t _prog_id);  // determines '_prog_id' refers to a program object or doesn't;
		err_code Params  (const uint32_t _prog_id, const uint32_t _param_id, int32_t* _p_params); // returns the requested object parameter ;
		err_code Use (const uint32_t _prog_id);      // installs the program object specified by program as part of current rendering state ;
		err_code Validate (const uint32_t _prog_id); // checks to see whether the executables contained in program can execute given the current OpenGL state ;

		err_code Get_all (void); // gets all functions' pointers at once;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
	};
}}}}

typedef ex_ui::draw::open_gl::procs::program::CInterface TIfaceProcs; TIfaceProcs&  __get_iface_procs (void);
typedef ex_ui::draw::open_gl::procs::program::CResource  TResProcs ;  TResProcs&  __get_res_procs (void);
typedef ex_ui::draw::open_gl::procs::program::CShaders TProgShaders;  TProgShaders&  __get_$_bind_procs (void);
typedef ex_ui::draw::open_gl::procs::CProg TProgProcs; TProgProcs&  __get_prog_procs (void);

#endif/*_GL_PROCS_PROG_H_INCLUDED*/