#ifndef _SYS_REG_ROUTER_H_INCLUDED
#define _SYS_REG_ROUTER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Feb-2026 at 21:34:57.671, UTC+4, Batumi, Monday;
	This Ebo Pack OpenGL tutorials' registry paths' router class interface declaration file;
*/
#include "shared.defs.h"
namespace shared { namespace sys_core { namespace storage {
namespace route { using namespace shared::defs;
	class CCtx {
	public:
		class CVersion {
		public:
			enum e_values : uint32_t {
			e_core  = 0x0, // the core flag;
			e_major = 0x1, // the major version of the context;
			e_minor = 0x2, // the minor version of the context;
			};
			CVersion (void); CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete; ~CVersion (void) = default;

			CString Name (const e_values) const; // gets value name for input enumeration element;
			_pc_sz  Root (void) const;           // gets root key path for context version properties/sub-keys;
		private:
			CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;
		};
	public:
		CCtx (void); CCtx (const CCtx&) = delete; CCtx (CCtx&&) = delete; ~CCtx (void) = default;

		_pc_sz Root (void) const; // gets root key path for context properties/sub-keys;
		const
		CVersion& Version (void) const;

	private:
		CCtx& operator = (const CCtx&) = delete; CCtx& operator = (CCtx&&) = delete;
		CVersion m_version;
	};

	class CDraw {
	public:
		enum e_targets : uint32_t {
		e_grid = 0x0,
		e_tria = 0x1,
		};
		CDraw (void); CDraw (const CDraw&) = delete; CDraw (CDraw&&) = delete; ~CDraw (void) = default;

		CString Name (const e_targets) const; // gets value name for input enumeration element;
		_pc_sz  Root (void) const;            // gets root key path for drawable objects;

	private:
		CDraw& operator = (const CDraw&) = delete; CDraw& operator = (CDraw&&) = delete;
	};

	class CGrid {
	public:
		class CCell {
		public:
			enum e_values : uint32_t {
			e_height = 0x0,
			e_width  = 0x1,
			};
		public:
			CCell (void); CCell (const CCell&) = delete; CCell (CCell&&) = delete; ~CCell (void) = default;

			CString Name (const e_values) const; // gets value name for input enumeration element;
			_pc_sz  Root (void) const;

		private:
			CCell& operator = (const CCell&) = delete; CCell& operator = (CCell&&) = delete;
		};
	public:
		CGrid (void); CGrid (const CGrid&) = delete; CGrid (CGrid&&) = delete; ~CGrid (void) = default;
		const
		CCell& Cell (void) const;
		CCell& Cell (void) ;
		_pc_sz Root (void) const;

		_pc_sz Clr_name (void) const; // returns grid lines color value name;

	private:
		CGrid& operator = (const CGrid&) = delete; CGrid& operator = (CGrid&&) = delete;
		CCell  m_cell;
	};

	class CRoot {
	public:
		enum e_renderer : uint32_t { // the renderer identifier changes the root path of the tutorials;
			    e_direct_x = 0x0,
				e_open_gl  = 0x1,    // default value for this version of the implementation;
		};
	public:
		CRoot (void); CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		const
		HKEY    Key  (void) const;
		_pc_sz  Path (void) const;              // returns the root path without renderer identifier;
		CString Path (const e_renderer) const;  // returns the root path to the renderer key by input renderer value;

		e_renderer Renderer (void) const;       // returns currently set renderer identifier;
		const bool Renderer (const e_renderer); // sets current renderer identifier; returns 'true' in case of value change;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};

	class CShaders {
	public:
		// https://en.wikipedia.org/wiki/Shader ;
		enum e_types : uint32_t { // this enumeration is an abstraction from the constant values of OpenGL and DirectX shader types;
		e__undef   = 0x0,
		e_fragment = 0x2, // fragment shaders, also known as pixel shaders, compute color and other attributes of each 'fragment' (a single output pixel);
		e_vertex   = 0x6, // transforms each vertex's 3D position in virtual space to the 2D coordinate at which it appears on the screen;
		};
	public:
		CShaders (void); CShaders (const CShaders&) = delete; CShaders (CShaders&&) = delete; ~CShaders (void) = default;

		CString  Name (const e_types) const;    // returns the registry key value name for input shader type; 
		CString  Path (_pc_sz _p_object) const; // returns the registry key path to shaders of the object by its name;
		_pc_sz   Root (void) const; // gets root key path for all shader types;

		class CTestCase {
		public:
			CTestCase (void) = default; CTestCase (const CTestCase&) = delete; CTestCase (CTestCase&&) = delete; ~CTestCase (void) = default;

			static CString Key_path (const uint32_t _u_number);  // returns the key path for given test case number;

		private:
			CTestCase& operator = (const CTestCase&) = delete; CTestCase& operator = (CTestCase&&) = delete;
		};

	private:
		CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
	};

	class CTheme {
	public:
		enum e_element : uint32_t {
		e_bkgnd  = 0x0, // background color;
		e_border = 0x1, // border color (any state of the control that the border belongs to);
		};
		CTheme (void) ; CTheme (const CTheme&) = delete; CTheme (CTheme&&) = delete; ~CTheme (void) = default;

		CString Path (const e_element) const; // returns the registry path to the color value of the element specified;
		_pc_sz  Root (void) const;

		static
		_pc_sz  To_str (const e_element);

	private:
		CTheme& operator = (const CTheme&) = delete; CTheme& operator = (CTheme&&) = delete;
	};

	class CViewport {
	public:
		CViewport (void); CViewport (const CViewport&) = delete; CViewport (CViewport&&) = delete; ~CViewport (void) = default;
		const
		CGrid&   Grid (void) const;
		CGrid&   Grid (void) ;
		_pc_sz   Root (void) const;  // gets root key path of the viewport component;

	private:
		CViewport& operator = (const CViewport&) = delete; CViewport& operator = (CViewport&&) = delete;
		CGrid m_grid;
	};
}
	using namespace route;

	class CReg_router {
	public:
		 CReg_router (void) ; CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&) = delete;
		~CReg_router (void) ;

		const  CCtx&  Ctx  (void) const;  // there is no need to returns the reference to non-constant object;
		const  CDraw& Draw (void) const;  // gets info of what shape/view to draw;
		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;
		const
		CShaders& Shaders (void) const;
		CShaders& Shaders (void) ;
		const
		CTheme& Theme (void) const;
		CTheme& Theme (void) ;
		const
		CViewport& Viewport (void) const;
		CViewport& Viewport (void) ;

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;

		CCtx   m_ctx ;
		CDraw  m_draw;
		CRoot  m_root;
		CShaders  m_shaders;
		CTheme    m_theme;
		CViewport m_v_port;
	};

}}}

typedef shared::sys_core::storage::CReg_router TReg_router;
typedef shared::sys_core::storage::route::CShaders TReg_shaders;
typedef TReg_shaders::CTestCase TReg_test_case;

shared::sys_core::storage::CReg_router&  Get_reg_router (void); // returns the reference to the singleton of the router object;

#endif/*_SYS_REG_ROUTER_H_INCLUDED*/