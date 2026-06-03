#ifndef _TEST_CASE_$M$_FRUSTUM_H_INCLUDED
#define _TEST_CASE_$M$_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:09:32.348, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_procs_frustum.h"

namespace test { namespace open_gl { namespace frustum {

	using namespace shared::defs;
	using CFrustum = ::open_gl::procs::projection::CFrustum;
	using f_planes = ::open_gl::procs::projection::f_planes;
	using f_rect   = ::open_gl::procs::projection::f_rect;

	class CTstFrustum {
	public:
		 CTstFrustum (const bool _b_verbose = true); CTstFrustum (const CTstFrustum&) = delete; CTstFrustum (CTstFrustum&&) = delete;
		~CTstFrustum (void) = default;

		err_code  Set (const f_rect& _clip, const f_planes&); // f_rect contains boundary values that are normalized to the range [-1.0 ... 1.0]; 
		err_code  Set (const t_rect& _clip, const f_planes&); // t_rect must be converted to f_rect with taking into account aspects and fov_y; (not implemented yet)

		const
		CFrustum& operator ()(void) const;
		CFrustum& operator ()(void) ;

	private:
		CTstFrustum& operator = (const CTstFrustum&) = delete; CTstFrustum& operator = (CTstFrustum&&) = delete;
		CFrustum m_frustum;
		bool     m_verbose;
	};

}}}

#if (0)
#include "camera.frustum.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1;
*/
namespace test { namespace open_gl { namespace frustum { namespace ver_1_1 {

	using CAspect  = ::open_gl::camera::frustum::CAspect;
	using CCfg     = ::open_gl::camera::frustum::CCfg;
	using CFoV     = ::open_gl::camera::frustum::CFoV;
	using CFrustum = ::open_gl::camera::CFrustum;
	using CPlane   = ::open_gl::camera::frustum::CPlane;
	
	class CTstAspect {
	public:
		CTstAspect (const bool _b_verbose = true); CTstAspect (const CTstAspect&) = delete; CTstAspect (CTstAspect&&) = delete; ~CTstAspect (void) = default;

		err_code Set (const uint32_t _height, const uint32_t _width); // sets size values directly, without using a surface window handle;

		const
		CAspect& operator ()(void) const;
		CAspect& operator ()(void) ;

	private:
		CTstAspect& operator = (const CTstAspect&) = delete; CTstAspect& operator = (CTstAspect&&) = delete;
		CAspect m_aspect;
		bool    m_verbose;
	};

	class CTstCfg {
	public:
		CTstCfg (const bool _b_verbose = true); CTstCfg (const CTstCfg&) = delete; CTstCfg (CTstCfg&&) = delete; ~CTstCfg (void) = default;

		err_code Set_defaults (void);

		const
		CCfg&  operator ()(void) const;
		CCfg&  operator ()(void) ;

	private:
		CTstCfg& operator = (const CTstCfg&) = delete; CTstCfg& operator = (CTstCfg&&) = delete;
		CCfg m_cfg;
		bool m_verbose;
	};
	
	class CTstFoV {
	public:
		CTstFoV (const bool _b_verbose = true); CTstFoV (const CTstFoV&) = delete; CTstFoV (CTstFoV&&) = delete; ~CTstFoV (void) = default;

		const
		CFoV& operator ()(void) const;
		CFoV& operator ()(void) ;

	private:
		CTstFoV& operator = (const CTstFoV&) = delete; CTstFoV& operator = (CTstFoV&&) = delete;
		CFoV m_fov;
		bool m_verbose;
	};

	class CTstFrustum {
	public:
		CTstFrustum (const bool _b_verbose = true); CTstFrustum (const CTstFrustum&) = delete; CTstFrustum (CTstFrustum&&) = delete; ~CTstFrustum (void) = default;

		err_code Update (void);  // updates perspective projection matrix by applying current configuration values;

		const
		CFrustum& operator ()(void) const;
		CFrustum& operator ()(void) ;

	private:
		CTstFrustum& operator = (const CTstFrustum&) = delete; CTstFrustum& operator = (CTstFrustum&&) = delete;
		CFrustum m_frust;
		bool   m_verbose;
	};
}}}}
#endif

#endif/*_TEST_CASE_$M$_FRUSTUM_H_INCLUDED*/