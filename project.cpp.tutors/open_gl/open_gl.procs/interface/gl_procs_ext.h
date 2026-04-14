#ifndef _GL_PROCS_EXT_H_INCLUDED
#define _GL_PROCS_EXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2026 at 14:28:53.565, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL extension wrapper interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

	// this is an extension installed under current OS;
	class CExt_Item {
	public:
		CExt_Item (_pc_sz _p_name = 0); CExt_Item (const CExt_Item&); CExt_Item (CExt_Item&&); ~CExt_Item (void) = default;

		bool Is_valid (void) const; // checks for this element name emptiness;

		_pc_sz  Name (void) const;  // gets extension item name;
		void    Name (_pc_sz);      // sets extension item name; no check for input pointer for null value, just trimming if nessary;
	
		CExt_Item& operator = (const CExt_Item&); CExt_Item& operator = (CExt_Item&&);
		CExt_Item& operator <<(_pc_sz _p_name);
		CExt_Item& operator <<(const CString& _cs_name);

	private:
		CString m_name;
	};
	/*in order to determine where the OS resides on remote desktop or not the following extension indicates that:
	  https://en.wikipedia.org/wiki/OpenGL >> ARB >> Architecture Review Board;
	  (1) the function wglGetExtensionsStringARB() pointer exists under OS installed on local machine, on remote desktop doesn't;
	*/
	typedef ::std::vector<CExt_Item> ext_items_t;
	// gets available extensions installed under the current OS and graphical card driver provider;
	class CExt_Enum {
	public:
		CExt_Enum (void); CExt_Enum (const CExt_Enum&) = delete; CExt_Enum (CExt_Enum&&) = delete; ~CExt_Enum (void) = default;
		TError& Error (void) const;
		const
		ext_items_t&  Get (void) const;
		bool Is_remote (void) const;
		/* for loading available extensions the following steps are required:
		   (1) to create message-only window (aka fake) and to get context device from it;
		   (2) to find pixel format descriptor by required params: color, stencil, z-axis (depth) bits;
		   (3) to set the context defice to the found pixel format;
		   (4) to create OpenGL renderer from the device context and make it active;
		   (5) finally, to get the the available extensions' list string by calling OpenGL glGetString(GL_EXTENSIONS); 
		*/
		err_code Load (void);

	private:
		CExt_Enum& operator = (const CExt_Enum&) = delete; CExt_Enum& operator = (CExt_Enum&&) = delete;
		mutable
		CError      m_error;
		ext_items_t m_items;
	};

}}}}

typedef ex_ui::draw::open_gl::procs::CExt_Enum TProcExtEnum; TProcExtEnum&  Get_ProcExt (void);

#endif/*_GL_PROCS_EXT_H_INCLUDED*/