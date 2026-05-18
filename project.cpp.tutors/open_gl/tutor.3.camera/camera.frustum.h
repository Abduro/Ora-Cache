#ifndef _CAMERA_FRUSTUM_H_INCLUDED
#define _CAMERA_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2026 at 09:42:37.070, UTC+4, Batumi, Wednesday;
	This is OpenGL tutorials' virtual camera frustum interface declaration file;
*/
#include "drawable.defs.h"

namespace open_gl {
namespace camera  { using namespace shared::defs;
namespace frustum { using namespace shared::defs;

	using ex_ui::draw::open_gl::math::defs::f_epsilon;
	using ex_ui::draw::open_gl::math::defs::deg_2_rad;
	using ex_ui::draw::open_gl::math::defs::rad_2_deg;

	using ::open_gl::views::c_angle;
	using ::open_gl::views::s_size;

	class CAspect {
	public:
		CAspect (void);
		CAspect (const HWND _h_surface);
		CAspect (const uint32_t _u_height, const uint32_t _u_width); CAspect (const CAspect&); CAspect (CAspect&&) = delete; ~CAspect (void) = default;

		TError&  Error (void) const;
		float    Ratio (void) const;
		static
		bool  Is_valid (const t_size_u&, CError&);
		bool  Is_valid (void) const;

		err_code Set (const HWND _h_surface);  // sets size by client area of the given window handle;
		err_code Set (const uint32_t _u_height, const uint32_t _u_width);

		CAspect& operator = (const CAspect&); CAspect& operator = (CAspect&&) = delete;
		const
		t_size_u& operator <<(const HWND _h_surface); // sets the size by given window handle client rectangle;
		operator  float (void) const;                 // gets the ratio value;

	private:
		mutable
		CError   m_error;
		t_size_u m_size;
	};

	/* query: FOV in opengl; (Google AI)
	   In OpenGL, Field of View (FOV) defines the extent of the observable world seen through the camera at any given moment.
	   It is a critical component of the perspective projection matrix, which simulates how objects appear smaller as they get further away.
	Quick Reference for FOV Values:
	   (1) Narrow FOV (30°–45°): Often used for "zooming" or sniper scopes. It reduces peripheral vision but makes distant objects appear larger;
	   (2) Standard FOV (45°–60°): Common for third-person cameras or "natural" viewing;
	   (3) Wide FOV (90°–120°): Standard for first-person shooters (FPS) to increase awareness, though it can cause "fisheye" distortion at the screen edges;
	*/
	/* some rules:
	(1) all angle value related classes uses input and output values in degrees, all functions' implementation uses radians internally;
	(2) possibly caching radians for the same angle values in degrees (performance optimization);
	*/
	class CFoV {
	public:
		enum e_angle : uint32_t { // enumerates angle value (in degrees) of field of view;
		     e_narrow_min = 30, e_narrow_max = 45, e_std_min = 45, e_std_max = 60, e_wide_min = 90, e_wide_max = 120
		};

		class CBase {
		public:
			CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

			TError& Error (void) const;
			const
			c_angle&  Get (void) const;    // gets the angle value;
			err_code  Set (const e_angle); // sets a pre-defined angle value (degrees);

			bool Is_valid (void) const;    // checks angle value, if the value is less than e_narrow_min or is greater than e_wide_max, returns 'false';

		protected:
			CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
			mutable
			CError  m_error;
			c_angle m_angle; // supposed to be in degrees for better readability regardless the fact that all calculation in trigonometry uses radians;
		};
		class CHorz : public CBase {
		public:
			CHorz (void); CHorz (const CHorz&) = delete; CHorz (CHorz&&) = delete; ~CHorz (void) = default;

			err_code Set (const float _fov_y, const CAspect&); // set the angle value by camera vertical FOV and surface aspects' ratio;

		private:
			CHorz& operator = (const CHorz&) = delete; CHorz& operator = (CHorz&&) = delete;
		};
		class CVert : public CBase {
		public:
			CVert (void); CVert (const CVert&) = delete; CVert (CVert&&) = delete; ~CVert (void) = default;

			err_code Set (const float _f_dist, const uint32_t _u_obj_height); // calculates vertical angle of FoV at the specific distance for looking at the object of given height;
			err_code Set (const float _f_horz, const CAspect&); // converts horz FOV angle to vert FOV one by applying window/surface aspects' ratio;
			err_code Set (const e_angle); // sets one of pre-defined angle values;

		private:
			CVert& operator = (const CVert&) = delete; CVert& operator = (CVert&&) = delete;
		};

		CFoV (void); CFoV (const CFoV&) = delete; CFoV (CFoV&&) = delete; ~CFoV (void) = default;

		static _pc_sz Class (void); // gets this class name for setting error object source field;
		const
		CHorz& Horz (void) const;
		CHorz& Horz (void);
		const
		CVert& Vert (void) const;
		CVert& Vert (void);
		static
		bool Is_valid (const float _f_angle, CError&); // checks angle value (degrees), if the value is less than e_narrow_min or is greater than e_wide_max, returns 'false';

	private:
		CFoV& operator = (const CFoV&) = delete; CFoV& operator = (CFoV&&) = delete;
		CHorz m_horz;
		CVert m_vert;
	};

	/* query: what values have near and far planes usually in opengl; (Google AI)
	   near and far clipping planes are distance values from the camera, typically set as positive, with common values being near = 0.1 and far = 100.0 (or 1000.0);
	   these define the viewing frustum, where objects closer than 'near' or farther than 'far' are clipped and not rendered;
	Typical Values:
	   (1) Near Plane: Usually a small positive value (e.g., 0.1, 0.01, 1.0). A near plane of 0.0 is generally avoided to prevent perspective division errors;
	   (2) Far Plane: Usually a large positive value (e.g., 100.0, 1000.0, 10000.0), determined by the size of the scene;
	Key Considerations:
	   (1) Depth Precision: Setting the near plane too close (e.g., 0.0001) and the far plane too far (e.g., 100,000) causes *Z-fighting*,
	       where the depth buffer lacks precision to distinguish nearby objects;
	   (2) Logarithmic Depth: The precision is not linear; most precision is packed near the near plane;
	   (3) Perspective Projection: In perspective projection, the distance is measured in view space, often looking down the -Z axis;
	   (4) Reverse Z: For better precision, many modern applications use [1, 0] depth ranges (near=1, far=0); << !very interesting!
	   (5) glFrustum /Perspective: These functions take the distance to the planes.
	       The near/far planes are defined in the projection matrix construction as *-near* and *-far* because the camera looks down the negative z-axis.
	*/

	class CPlane {
	public:
		CPlane (void); CPlane (const CPlane&); CPlane (CPlane&&) = delete; ~CPlane (void) = default;

		float    Dist (void) const;  // gets the distance to the plane;
		err_code Dist (const float); // sets the distance to this near plane; returns __s_ok, otherwise an error code;

		TError& Error (void) const;
		bool Is_valid (void) const;  // checks the distance value and plane size;

		const s_size& Half (void) const;  // returns the half of the actual size;
		const s_size& Size (void) const;  // returns the full size of the plane;

		float    Height (void) const;     // gets the height of this plane;
		err_code Height (const float _fov_y); // calculates the near pane height for given FOV; it is assumed the distance value is already set to this plane;

		float    Width  (void) const;     // gets the width of this plane;
		err_code Width  (const CAspect&); // sets the width of this plane; it is assumed the height of this plane is already calculated, otherwise error is returned;

		CPlane&  operator = (const CPlane&); CPlane& operator = (CPlane&&) = delete;
		err_code operator <<(const float _f_dest);

		operator float (void) const; // returns distance value of this plane;
	protected:
		mutable
		CError m_error;
		float  m_dist ;
		s_size m_half ;
		s_size m_size ;
	};

	class CPlanes {
	public:
		// https://stackoverflow.com/questions/2454019/why-arent-static-const-floats-allowed ;
		static inline const float f_dist_min = 0.0001f; // perhaps these values will be changed later, after passing the test cases;
		static inline const float f_dist_max = 1000.0f; // the above comment refers to this variable too;

		class CFar : public CPlane { // yon;
		public:
			CFar (void);
			CFar (const float _f_dist); CFar (const CFar&); CFar (CFar&&) = delete; ~CFar (void) = default;

			CFar& operator = (const CFar&); CFar& operator = (CFar&&) = delete;
		};

		// https://stackoverflow.com/questions/3410096/setting-near-plane-in-opengl ;
		class CNear : public CPlane { // hither;
		public:
			CNear (void);
			CNear (const float _f_dist); CNear (const CNear&); CNear (CNear&&) = delete; ~CNear (void) = default;

			CNear& operator = (const CNear&); CNear& operator = (CNear&&) = delete;

		private:
			mutable CError m_error;
		};
	public:
		CPlanes (void); CPlanes (const CPlanes&) = delete; CPlanes (CPlanes&&) = delete; ~CPlanes (void) = default;
		const
		CFar& Far (void) const;   // gets the reference to far plane; (ro)
		CFar& Far (void);         // gets the reference to far plane; (rw)

		static bool Is_valid (const float _f_dist, CError&); // checks given distance for minimum and maximum value, i.e. in this range [0.0001...1000.0];
		static bool Is_valid (const t_size_u&, CError&);     // checks given size for 0 value;
		const
		CNear& Near (void) const; // gets the reference to near plane; (ro)
		CNear& Near (void);       // gets the reference to near plane; (rw)

	private:
		CPlanes& operator = (const CPlanes&) = delete; CPlanes& operator = (CPlanes&&) = delete;
		CFar  m_far ;
		CNear m_near;
	};

	class CCfg {		
	public:
		CCfg (void); CCfg (const CCfg&) = delete; CCfg (CCfg&&) = delete; ~CCfg (void) = default;

		err_code Default (void); // sets default values such as: FoV vertical = 60 degree, near plane distance 1.0f, far plane distance 100.f;
		TError&  Error (void) const;
		const
		CFoV& FoV (void) const;
		CFoV& FoV (void) ;
		const
		CPlanes& Planes (void) const;
		CPlanes& Planes (void) ;

	private:
		CCfg& operator = (const CCfg&) = delete; CCfg& operator = (CCfg&&) = delete;
		CFoV    m_fov;
		CPlanes m_planes;
		CError  m_error;
	};
}
	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;
	class CFrustum {
	public:
		using CAspect = frustum::CAspect;
		using CCfg = frustum::CCfg;
		CFrustum (void); CFrustum (const CFrustum&) = delete; CFrustum (CFrustum&&) = delete; ~CFrustum (void) = default;
		const
		CAspect&  Aspect (void) const;
		CAspect&  Aspect (void) ;
		const
		CCfg& Cfg (void) const;
		CCfg& Cfg (void) ;

		TError&   Error (void) const;
		const
		c_mat4x4& Project (void) const; // gets the reference to projective matrix; (ro)
		c_mat4x4& Project (void) ;      // gets the reference to projective matrix; (rw)

		err_code  Update  (void); // it is supposed that the window size is applied to aspect object, the cfg is set to appropriate values;

	public:
		CFrustum& operator = (const CFrustum&) = delete; CFrustum& operator = (CFrustum&&) = delete;
		CAspect   m_aspect;
		CError    m_error;
		c_mat4x4  m_proj ;
		CCfg m_cfg;
	};
}}

#endif/*_CAMERA_FRUSTUM_H_INCLUDED*/