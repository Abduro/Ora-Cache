#ifndef _CONSOLE_NOTIFY_H_INCLUDED
#define _CONSOLE_NOTIFY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Sep-2022 at 09:52:51.8319344, UTC+7, Novosibirsk, Friday;
	This is MS Windows console generic event notification callback interface declaration file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:29:53pm, GMT+4, Saint-Petersburg, Sunday;
	Adopted to File Guardian project on 6-Jan-2016 at 9:26:48am, GMT+7, Phuket, Rawai, Wednesday;
*/
#include "shared.types.h"
namespace shared { namespace console {

	using namespace shared::types;

	class CRecordType {
	public:
		enum _type {
			eInfo    = 0x0,
			eWarning = 0x1,
			eError   = 0x2
		};
	};

	typedef CRecordType::_type TRecordType; typedef TRecordType TRecType;

	interface INotify
	{
		virtual void   Notify_OnEvent(const TRecordType, const UINT  nResId) PURE;
		virtual void   Notify_OnEvent(const TRecordType, LPCTSTR pszDetails) PURE;
		virtual void   Notify_OnError(const UINT nResId) PURE;
		virtual void   Notify_OnInfo (const UINT nResId) PURE;
	};

	class CNotifyDefImpl : public INotify
	{
	public:
		 CNotifyDefImpl (void);
		~CNotifyDefImpl (void);

	private: // INotify ;
#pragma warning(disable: 4481)
		virtual void   Notify_OnEvent(const TRecordType, const UINT  nResId) override final;
		virtual void   Notify_OnEvent(const TRecordType, LPCTSTR pszDetails) override final;
		virtual void   Notify_OnError(const UINT nResId) override final;
		virtual void   Notify_OnInfo (const UINT nResId) override final;
#pragma warning(default: 4481)
	};

}}

#endif/*_CONSOLE_NOTIFY_H_INCLUDED*/