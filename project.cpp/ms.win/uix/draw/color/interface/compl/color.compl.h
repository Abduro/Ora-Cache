#ifndef _SHAREDUIXCTRLCLRS_H_INCLUDED
#define _SHAREDUIXCTRLCLRS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Nov-2019 at 2:23:52a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared drawing library complementary colors pairs declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:23:45.7340975 am, UTC+7, Novosibirsk, Sunday;
*/
#include "color._defs.h"
#include "color.rgb.h"

#ifndef HexToRgb
#define HexToRgb(_hex)  ( RGB( LOBYTE((_hex)>>16),LOBYTE((_hex)>>8),LOBYTE((_hex))) )
#endif
#ifndef H2C
#define H2C(_hex) HexToRgb(_hex)
#endif

namespace ex_ui { namespace color { namespace complementary {

	// https://en.wikipedia.org/wiki/Complementary_colors ;
	/*
		the most definitions of the complementary colors is not correct;
		what about a piece of shit on underpants of a certain color?
		this means a context in which to talk about these 'pleasant-looking' colors;
	*/
	// https://www.thoughtco.com/complementary-and-complimentary-1689348 ;

	using namespace ex_ui::color;
	using namespace ex_ui::color::rgb;

	class COne  { // ToDo: does not have required or desirable functionality; possibly must be child of the color class or quad one;
	public:
		enum _algo : uint32_t {
			e_simplistic = 0x0, // https://stackoverflow.com/questions/3054873/programmatically-find-complement-of-colors 
		};

	public:
		 COne (void);
		 COne (const COne&);
		 COne (const rgb_color _src, const _algo = _algo::e_simplistic); COne (COne&&) = delete;
		~COne (void);

	public:
		_algo     Algo (void) const ;
		bool      Algo (const _algo);  // returns true if algorythm value is changed;
		rgb_color Get  (void) const;   // gets a result color;
		err_code  Set  (const rgb_color _from, const _algo e_how_to_make_it = _algo::e_simplistic); // alpha channel byte is used;

#if defined(_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif
	public:
		 COne& operator = (const COne&);
		 COne& operator <<(const _algo);       // is useless yet;
		 COne& operator <<(const rgb_color);   // creates complementary color for given one; alpha channel byte is used;
		 COne& operator = (COne&&) = delete;

	private:
		_algo     m_algo;
		rgb_color m_clr ; // this is a result colour; alpha channel byte is used;
	};
}}}

typedef ex_ui::color::complementary::COne::_algo TComplAlgo;

namespace ex_ui { namespace color { namespace complementary {

	class CSet { // by default all three colors have white color value with alpha channel is set to opaque;
	public:
		 CSet (void); CSet (const CSet&); CSet (CSet&&);
		 CSet (const rgb_color _dark, const rgb_color _mid, const rgb_color _lt, _pc_sz _p_name, _pc_sz _p_desc);
		~CSet (void);

	public:
		const
		rgb_color& Dark  (void) const; const rgb_color& C0 (void) const;  // returns the value of a dark shade color; (ro);
		rgb_color& Dark  (void)      ;       rgb_color& C0 (void) ;       // returns the value of a dark shade color; (rw);

		const
		rgb_color& Light (void) const; const rgb_color& C2 (void) const;  // returns the value of a light shade color; (ro);
		rgb_color& Light (void)      ;       rgb_color& C2 (void) ;       // returns the value of a light shade color; (rw);

		const
		rgb_color& Medium(void) const; const rgb_color& C1 (void) const;  // returns the value of a medium shade color; (ro);
		rgb_color& Medium(void)      ;       rgb_color& C1 (void) ;       // returns the value of a medium shade color; (rw);

	public:
		const bool Is (void) const; // returns true if one colour is valid at least;

	public:
		const
		CString&  Desc (void) const;
		CString&  Desc (void)      ;
		const
		CString&  Name (void) const;
		CString&  Name (void)      ;

#if defined(_DEBUG)
		CString   Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	private:
		CSet& operator = (const CSet&);
		CSet& operator = (CSet&&);

		// https://looka.com/blog/logo-color-combinations/
		// http://incubar.net/11-best-color-combinations-for-painting-rooms/
	private:
		rgb_color   m_clr[3];
		CString     m_name  ;
		CString     m_desc  ;
	};
	using CTriplet = ex_ui::color::complementary::CSet;
	typedef ::std::vector<CTriplet> TRawSets;

	class CSet_Enum {
	public:
		 CSet_Enum (void); CSet_Enum (const CSet_Enum&) = delete; CSet_Enum (CSet_Enum&&) = delete;
		~CSet_Enum (void);

	public:
		const CSet&     Get (const uint32_t _ndx) const;
		const TRawSets& Raw (void) const;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	public:
		const CSet& operator[](const uint32_t _ndx) const; // if input index is out of range of the color elements, a reference to fake object is returned;

	public:
		CSet_Enum& operator = (const CSet_Enum&) = delete;
		CSet_Enum& operator = (CSet_Enum&&) = delete;

	protected:
		TRawSets m_sets;
	};

}}}

#endif/*_SHAREDUIXCTRLCLRS_H_INCLUDED*/