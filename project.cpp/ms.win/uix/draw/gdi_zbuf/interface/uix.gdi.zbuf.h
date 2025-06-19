#ifndef _UIX_GDI_ZBUF_H_INCLUDED
#define _UIX_GDI_ZBUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:35:03, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface declaration file.
*/
#include "uix.gdi.defs.h"
#include "uix.gdi.blend.h"
#include "uix.gdi.shade.h"

namespace ex_ui { namespace draw { namespace memory {

	#define _ATL_NO_AUTOMATIC_NAMESPACE

	using namespace ex_ui::draw::defs;
	using CLine = geometry::_2D::shapes::CLine;
	using CRect = ::ATL::CRect;

	using namespace ex_ui::draw::blend;
	using namespace ex_ui::draw::shade;

	class CSurface { // this class is exactly for memory device context;
	public:
		 CSurface (void); CSurface (const CSurface&) = delete; CSurface (CSurface&&) = delete;
		~CSurface (void);

	public:
		err_code  ApplyTo(const HDC _h_mem_dc);  // applies the new bitmap of a surface to memory device;
		const
		t_rect&   Area (void) const;
		t_rect&   Area (void) ;

		err_code  Create (const HDC _h_origin, const t_rect& _rc_draw); // creates a new surface bitmap that is compatible to input device context;
		err_code  Destroy(void);

		TError&   Error(void) const;
		bool   Is_valid(void) const;

		const
		HBITMAP&  Prev (void) const;
		HBITMAP&  Prev (void) ;
		const
		HBITMAP&  New  (void) const;
		HBITMAP&  New  (void) ;

	private:
		CSurface& operator = (const CSurface&) = delete;
		CSurface& operator = (CSurface&&) = delete;

	private:
		mutable
		CError   m_error;
		HBITMAP  m_surface[2]; // 0|old surface; 1|new surface;
		t_rect   m_rc_draw;    // draw area of a surface; https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/crect-class ;
	};

	//the CZBuffer is not inherited from ::WTL::CMemoryDC due to it makes public its fields, that is not necessary definitely;
	class CZBuffer : public ::WTL::CDC { typedef ::WTL::CDC TDC;
	public:
		 CZBuffer (void);
		 CZBuffer (const HDC _h_origin, const t_rect& _rc_draw);
		 CZBuffer (const CZBuffer&) = delete; CZBuffer (CZBuffer&&) = delete;
		~CZBuffer (void);

	public: // life cycle method(s)
		/*
			Todo: *important*: the this::Reset() copies entire bitmap of this in-memory device to specified location of the target one;
			                   because it is assumed this in-memory device context serves the entire client area of the target;
			it requires a review: the Reset() must be dependent on what draw area must be copied entire or just a part;
		*/
		err_code  Create(const HDC _h_origin, const t_rect& _rc_draw);
		err_code  Reset (void) ; // copies the buffer content to original device context and resets the buffer to uninitialized state;

	public: // error handling;
		TError&   Error (void) const;
		bool   Is_valid (void) const;

	public: // draw method(s);
		/* if color of line has the alpha value that is not opaque, the draw of a rectangle by alpha blend is used;
		   strictly vertical or horizontal line is drawn by this function in this version of this lib implementation; */
		err_code  Draw  (const CLine&);
		err_code  Draw  (const CLine& , const rgb_color); // draws the line by overriding its color by input one;
		/* draws plain rectangle by using color provided, alpha blending is applicable;
		   it is assumed the rectangle is not created or extracted from 32-bpp image, thus per-pixel-alpha option is not used; */
		err_code  Draw  (const CRect& , const TRgbQuad&);
		err_code  Draw  (const t_rect&, const TRgbQuad&);
		err_code  Draw  (const t_rect&, const rgb_color); // draws the input rectangle in solid color, alpha channel value is not applied;

		const
		CSurface& Surface (void) const;
		CSurface& Surface (void) ;

	public:
		static bool Is_DC (const HDC);     // returns true if an input handle has proper data type such as: OBJ_DC|OBJ_MEMDC;
		static bool Is_DC_mem (const HDC); // returns true if an input handle has proper data type is OBJ_MEMDC;

	private:
		CZBuffer& operator = (const CZBuffer&) = delete;
		CZBuffer& operator = (CZBuffer&&) = delete;

	private:
		CError   m_error ;
		HDC      m_origin;
		CSurface m_surface;
	};
}}}
#if (0)
typedef ex_ui::draw::CZBuffer  TZBuffer;
#endif
#endif/*_UIX_GDI_ZBUF_H_INCLUDED*/