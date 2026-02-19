#ifndef _TEST_CASE_$M$_VIRT_CAM_H_INCLUDED
#define _TEST_CASE_$M$_VIRT_CAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Feb-2026 at 21:54:47.258, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL draw virtual camera wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_case_$m$.mat3x3.h"
#include "test_case_$m$.mat4x4.h"
#include "virt_camera.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using CCamPos = ex_ui::draw::open_gl::camera::opers::CPosition;
	using CCamRot = ex_ui::draw::open_gl::camera::opers::CRotation;
	using CCamTarget = ex_ui::draw::open_gl::camera::opers::CTarget;
	using CVirtCamera = ex_ui::draw::open_gl::CVirtCamera;

	class CTPosition {
	public:
		CTPosition (void); CTPosition (const CTPosition&) = delete; CTPosition (CTPosition&&) = delete; ~CTPosition (void) = default;

		static _pc_sz To_str (const CCamPos&);

	private:
		CTPosition& operator = (const CTPosition&) = delete; CTPosition& operator = (CTPosition&&) = delete;
	};

	class CTRotation {
	public:
		CTRotation (void); CTRotation (const CTRotation&) = delete; CTRotation (CTRotation&&) = delete; ~CTRotation (void) = default;

		static _pc_sz To_str (const CCamRot&);

	private:
		CTRotation& operator = (const CTRotation&) = delete; CTRotation& operator = (CTRotation&&) = delete;
	};

	class CTTarget {
	public:
		CTTarget (void); CTTarget (const CTTarget&) = delete; CTTarget (CTTarget&&) = delete; ~CTTarget (void) = default;

		static _pc_sz To_str (const CCamTarget&);

	private:
		CTTarget& operator = (const CTTarget&) = delete; CTTarget& operator = (CTTarget&&) = delete;
	};

	class CTVirtCam {
	public:
		CTVirtCam (void); CTVirtCam (const CTVirtCam&) = delete; CTVirtCam (CTVirtCam&&) = delete; ~CTVirtCam (void) = default;
		TError& Error (void) const;

		err_code Create (void); // gets the singleton object of the virtual cam and prints out the initial state of its components;

	private:
		CTVirtCam& operator = (const CTVirtCam&) = delete; CTVirtCam& operator = (CTVirtCam&&) = delete;
		CError  m_error;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VIRT_CAM_H_INCLUDED*/