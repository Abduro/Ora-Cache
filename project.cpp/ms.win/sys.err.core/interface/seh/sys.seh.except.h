#ifndef _SYS_ERR_SEH_EXC_H_INCLUDED
#define _SYS_ERR_SEH_EXC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com)on 30-Dec-2023 at 11:45:47.6568421, UTC+7, Novosibirsk, Saturday;
	This is shared library Win32 SEH translator interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 06:50:04.7177656, UTC+7, Novosibirsk, Saturday;
*/
#include "sys.seh.common.h"
/*
	warning C4535: calling _set_se_translator() requires /EHa
	this warning appears for letting to know this project file MUST have:
	<ClCompile>
		<ExceptionHandling>Async</ExceptionHandling>
	</ClCompile>
	or through project settings:
	Cfg props >> C/C++ >> Code Generation >> Enable C++  Exceptions = Yes with SEH Exceptions (/EHa);
*/

namespace shared { namespace sys_core { namespace seh {

	class CAction {       // an action/operation that is performed when using memory access;
	public:
		enum eType {
			eRead  = 0,   // read operation ;
			eWrite = 1,   // write operation;
			eDepVa = 8,   // a user-mode data execution prevention (DEP) violation;
		};
	public:
		 CAction (void);
		 CAction (const CAction&);
		 CAction (const TRecord&);
		 CAction (const TRecord*);
		 CAction (const TPointers*);
		 CAction (CAction&&) = delete;
		~CAction (void);

	public:
		TAddress Data (void) const;     // a pointer of a data associated to particular action;
		eType    Type (void) const;     // a type of an action being performed;
		HRESULT  Set  (const TPointers*);
		HRESULT  Set  (const TRecord*); // checks input pointer for nullability, nothing special ;
		HRESULT  Set  (const TRecord&); // sets attributes/fields value of this class;

	public:
		CAction& operator = (const CAction&);
		CAction& operator <<(const TRecord&);
		CAction& operator <<(const TRecord*);
		CAction& operator <<(const TPointers*);

		CAction& operator = (CAction&&) = delete;

	private:
		CAction& operator <<(const eType);    // for simplicity of copying attribute value ;
		CAction& operator <<(const TAddress); // for simplicity of copying attribute value ;

	private:
		eType    m_type ;
		TAddress m_data ;
	};

	typedef CAction TOperate;

	class CEx_Base { // actually, this is a base class for children that use a value of the flags; maybe it needs new appropriate class name;
	public:
		CEx_Base (const DWORD _value = 0);
		CEx_Base (const CEx_Base&);
		CEx_Base (const TPointers*);
		CEx_Base (const TRecord*);
		virtual  ~CEx_Base (void);       // the virtuality is not necessary but nevertheless for some special cases maybe;

	public:
		virtual DWORD   Get (void) const;
		virtual bool    Set (const DWORD _value);
		virtual HRESULT Set (const TPointers*);
		virtual HRESULT Set (const TRecord*);

		virtual bool Has (const DWORD _value) const; // checks a containing of input value in current value of this class;

	public:
		CEx_Base& operator = (const CEx_Base&);
		CEx_Base& operator <<(const DWORD _value);
		CEx_Base& operator <<(const TPointers*);
		CEx_Base& operator <<(const TRecord*);

		operator DWORD (void) const;

	protected:
		DWORD m_value;
	};

	class CExUnwind : public CEx_Base { // perhaps it would be better to use virtual inheritance;
	                 typedef CEx_Base TBase;
	public:
		enum eStage : DWORD {
			eUndef    = 0x0,
			eProgress = EXCEPTION_UNWINDING , // unwind is in progress ;
			eExit     = EXCEPTION_EXIT_UNWIND , // exit unwind is in progress ;
			eTargeted = EXCEPTION_TARGET_UNWIND , // target unwind in progress ;
			eCollided = EXCEPTION_COLLIDED_UNWIND , // collided exception handler call ;
		};
	public:
		 CExUnwind (void) ;
		 CExUnwind (const CExUnwind&);
		~CExUnwind (void);

	public:
		bool IsCollided (void) const;
		bool IsExiting  (void) const;
		bool InProgress (void) const;
		bool IsTargeted (void) const;
		

		bool Is (void) const; // checks a validity of the unwind state of the exception;

	public:
		CExUnwind& operator = (const CExUnwind&);

		operator bool (void) const; // if excption is in one of unwind stages, this operator returns true;

	};

	class CExState : public CEx_Base { // perhaps it would be better to use virtual inheritance ;
	                typedef CEx_Base TBase;
	public:
		enum eState : DWORD {
			eUndef = 0,
		};
	public:
		 CExState (const DWORD _value = eState::eUndef) ;
		 CExState (const CExState&);
		~CExState (void) ;

	public:
		bool    Set (const DWORD _value) override; // *important*: overriding this property can not change continuable property value;
		HRESULT Set (const TPointers*) override;   // updates this class, unwind property and continuable one;

	public:
		bool CanContinue  (void) const;       // if the property is true, the program execution can be continued after an exception occurs;
		const
		CExUnwind& Unwind (void) const;       // gets possible unwind stage;

	public:
		CExState& operator = (const CExState&);
		CExState& operator <<(const TPointers*);
	protected:
		CExState& operator <<(bool _b_continue);

	private:
		bool    m_continue;
		CExUnwind m_unwind;
	};

	class CException {
	public:
		 CException (void);
		 CException (const CException&);
		 CException (const TPointers*);    // pointers are provided by setting filter function ;
		 CException (CException&&) = delete;
		~CException (void);

	public:
		const CAction& Cause (void) const; // the action is intended to perform an operation in memory, and this may cause an exception to occur;
		const TPointers* Pointers(void) const;
		const CExState& State (void) const;

	public:
		bool Is  (void) const;
		bool Set (const TPointers*);

	public:
		CException& operator = (const CException&);
		CException& operator <<(const TPointers* );

		CException& operator = (CException&&) = delete;

	public:
		operator const TPointers* (void) const;
		operator const CString (void) const;

	public:
		CString ToString (void) const;

	public:
		static CString ToString (const TPointers*);

	private:
		TPointers* m_ptrs;
		CAction    m_action;
		CExState   m_state;
	};

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/set-se-translator ;

#include <eh.h>

	class CTranslator {
	public:
		 CTranslator (void) noexcept;
		 CTranslator (_se_translator_function) noexcept;
		~CTranslator (void) noexcept;

	private:
		const _se_translator_function m_prev_func;

	private:
		static void Do(UINT, TPointers*);
	};

}}}

#endif/*_SYS_ERR_SEH_EXC_H_INCLUDED*/