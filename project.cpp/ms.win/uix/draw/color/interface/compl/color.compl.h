#ifndef _SHAREDUIXCTRLCLRS_H_INCLUDED
#define _SHAREDUIXCTRLCLRS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Nov-2019 at 2:23:52a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared drawing library complementary colors pairs declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:23:45.7340975 am, UTC+7, Novosibirsk, Sunday;
*/
#include <vector>
#include "shared.gen.sys.err.h"

#ifndef HexToRgb
#define HexToRgb(_hex)  ( RGB( LOBYTE((_hex)>>16),LOBYTE((_hex)>>8),LOBYTE((_hex))) )
#endif
#ifndef H2C
#define H2C(_hex) HexToRgb(_hex)
#endif

namespace ex_ui { namespace color {

	class CComplClr  {
	public:
		enum _algo : DWORD {
			e_simplistic = 0x0, // https://stackoverflow.com/questions/3054873/programmatically-find-complement-of-colors 
		};
	private:
		_algo    m_algo;
		COLORREF m_clr ; // this is a result colour; alpha channel byte is used;

	public:
		 CComplClr (void);
		 CComplClr (const CComplClr&);
		 CComplClr (const COLORREF _clr_src, const _algo = _algo::e_simplistic);
		~CComplClr (void);

	public:
		_algo    Algo (void) const ;
		bool     Algo (const _algo);  // returns true if algorythm value is changed;
		COLORREF Get  (void) const;   // gets a result color;
		HRESULT  Set  (const COLORREF _clr_from, const _algo e_how_to_make_it = _algo::e_simplistic); // alpha channel byte is used;

	public:
		 CComplClr& operator = (const CComplClr&); // makes a copy;
		 CComplClr& operator <<(const _algo);      // sets algorithm value;
		 CComplClr& operator <<(const COLORREF);   // creates complementary color for given one; alpha channel byte is used;
	};
}}

typedef ex_ui::color::CComplClr::_algo TCmpClrAlgo;

namespace ex_ui { namespace color {
	
	class CComplClrs {
		// https://looka.com/blog/logo-color-combinations/
		// http://incubar.net/11-best-color-combinations-for-painting-rooms/
	private:
		COLORREF    m_clr[3];
		CString     m_name  ;
		CString     m_desc  ;
	public:
		 CComplClrs (void);
		 CComplClrs (const COLORREF _dark, const COLORREF _mid, const COLORREF _lt, LPCTSTR _lp_sz_nm, LPCTSTR _lp_sz_ds);
		~CComplClrs (void);

	public:
		const DWORD& Dark  (void) const;
		      DWORD& Dark  (void)      ;
		const DWORD& Light (void) const;
		      DWORD& Light (void)      ;
		const DWORD& Middle(void) const;
		      DWORD& Middle(void)      ;
	public:
		const bool   Is    (void) const; // returns true if one colour is valid at least;
	public:
		const
		CString&     Desc  (void) const;
		CString&     Desc  (void)      ;
		const
		CString&     Name  (void) const;
		CString&     Name  (void)      ;
	};

	typedef ::std::vector<CComplClrs> TComplClrs;

	class CComplClrs_Enum {
	private:
		TComplClrs  m_clrs;

	public:
		 CComplClrs_Enum (void);
		~CComplClrs_Enum (void);

	public:
		const CComplClrs& Item(const size_t _ndx) const;
		const TComplClrs& Raw (void) const;
		const size_t      Size(void) const;

	public:
		const CComplClrs& operator[](const size_t _ndx) const;
	};

}}

#endif/*_SHAREDUIXCTRLCLRS_H_INCLUDED*/