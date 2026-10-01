#ifndef _UIXOBJECTACCESSOR_H_AFA91F1D_51F5_4e01_9C69_61A5D74D0906_INCLUDED
#define _UIXOBJECTACCESSOR_H_AFA91F1D_51F5_4e01_9C69_61A5D74D0906_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser object accessor class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 3:42:14p, UTC+7, Novosibirsk, Monday;
*/
namespace ex_ui { namespace web { namespace core
{
	class CWebBrowserObjectAccessor
	{
	private:
		CAxWindow&     m_browser;
	public:
		 CWebBrowserObjectAccessor(::ATL::CAxWindow& browser_ref);
		~CWebBrowserObjectAccessor(void);
	public:
		HRESULT        GenericDocument(::ATL::CComPtr<IDispatch>&      doc_ref);
		HRESULT        DocumentObject (::ATL::CComPtr<IHTMLDocument2>& doc_ref);
		HRESULT        DocumentObject (::ATL::CComPtr<IHTMLDocument3>& doc_ref);
		HRESULT        ElementObject  (::ATL::CComPtr<IHTMLElement>&   elm_ref, LPCTSTR pId);
	};
}}}

#endif/*_UIXOBJECTACCESSOR_H_AFA91F1D_51F5_4e01_9C69_61A5D74D0906_INCLUDED*/