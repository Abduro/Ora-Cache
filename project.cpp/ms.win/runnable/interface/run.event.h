#ifndef _RUN_EVENT_H_INCLUDED
#define _RUN_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 26-Dec-2010 at 7:00:02pm, GMT+3, Rostov-on-Don, Sunday;
	This is SFX project Asynchronous notifying/waiting object interface declartion file.
	-----------------------------------------------------------------------------
	Adopted to Pulspay Server project on 2-May-2012 at 1:09:18pm, GMT+3, Rostov-on-Don, Wednesday;
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:21:09am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:17:15am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Internext project on 20-Aug-2014 at 8:03:27pm, GMT+3, Taganrog, Wednesday;
	Adopted to Fake GPS project on 11-Dec-2019 at 7:59:09p, UTC+7, Novosibirsk, Wednesday;
*/
#include "run.base.h"

namespace shared { namespace runnable {

	interface IGenericEventNotify // ToDo: the name of the interface looks like not so appropriate as should be;
	{
		virtual err_code  GenEvt_OnNotify(const _variant_t v_evt_id)  {v_evt_id; return __e_not_impl; }
		virtual err_code  GenEvt_OnNotify(const _long n_evt_id) _pure;
		virtual err_code  GenEvt_OnNotify(const _long n_evt_id, const _variant_t v_data) {n_evt_id; v_data; return __e_not_impl; }
	};

	class CMarshaller {
	public:
		CMarshaller(IGenericEventNotify&, const _variant_t& v_evt_id);
		virtual ~CMarshaller(void);

	public:
		virtual err_code  Create (void);
		virtual err_code  Destroy(void);
		virtual HWND      GetHandle_Safe(void) const;

	private:
		CMarshaller (void) = delete;
		CMarshaller (const CMarshaller&) = delete;
		CMarshaller (CMarshaller&&) = delete;

		CMarshaller& operator = (const CMarshaller&) = delete;
		CMarshaller& operator = (CMarshaller&&) = delete;

	public:
		virtual err_code  Fire (const bool bAsynch = true);
		virtual err_code  Fire2(void);

	public:
		static  err_code  Fire (const HWND hHandler, const bool bAsynch = true);
	protected:
		HANDLE m_handler;
	};

	class CDelayEvent
	{
	public:
		enum _frm : d_word {
			e_na      = 0,
			eInfinite = (d_word)-1
		};
	protected:
		volatile d_word     m_nTimeSlice;    // time space in milliseconds;
		volatile d_word     m_nTimeFrame;    // total time to wait for;
	protected:
		d_word    m_nCurrent;                // current time;
	public:
		CDelayEvent(const d_word nTimeSlice, const d_word nTimeFrame);
		virtual ~CDelayEvent(void);
	public:
		virtual bool Elapsed(void) const;
		virtual bool IsReset(void) const;

		virtual void Reset  (const d_word nTimeSlice = _frm::e_na, const d_word nTimeFrame = _frm::e_na);
		virtual void Wait   (void);

	public:
		CDelayEvent& operator= (const d_word) ; // sets time frame value for waiting for;
	};

}}

#endif/*_RUN_EVENT_H_INCLUDED*/