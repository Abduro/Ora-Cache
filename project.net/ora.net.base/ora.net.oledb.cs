/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Mar-2025 at 09:57:42.0077837, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OLEDB provider(s) wrapper base interface implementation file;
*/
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;

// https://github.com/kblok/StackOverflowExamples/blob/master/AspNetDemoProject/AspNetDemoProject/Demos/ProvidersList.aspx.cs ;
// https://learn.microsoft.com/en-us/dotnet/api/system.data.oledb.oledbenumerator ;

namespace ora.net.oledb {

	// https://learn.microsoft.com/en-us/dotnet/api/system.data.oledb.oledbenumerator.getrootenumerator ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms711200(v=vs.85) ;

	public enum EType
	{
		e_Binder = 0x0,           // indicates a provider binder that supports direct URL binder ;
		e_DataSource_MDP = 0x1,   // this is a multidimensional (OLAP) provider (MDP) ;
		e_DataSource_TDP = 0x2,   // tabular data provider (TDP) ;
		e_Enumerator = 0x3,       // this is a provider enumerator ;
	};

	public class CProvider {

		public Guid    ClsID { get ; private set ; }
		public string  Desc  { get ; private set ; }
		public bool    IsParent { get ; private set ; }
		public Guid    Moniker  { get ; private set ; } // this is a parse name ;
		public string  Name { get ; private set ; }
		public EType   Type { get ; private set ; }

		public CProvider () {
		}

		// https://www.codeproject.com/Tips/1231609/Enumerating-OleDb-Providers ;
		public CProvider (System.Data.IDataRecord _rec) {
			this.ClsID    = Guid.Parse((string)_rec[ "SOURCES_CLSID" ]) ;
			this.Moniker  = Guid.Parse((string)_rec[ "SOURCES_PARSENAME" ]) ;
			this.Desc     = (string)_rec[ "SOURCES_DESCRIPTION" ] ;
			this.IsParent = (bool)_rec[ "SOURCES_ISPARENT" ] ;
			this.Name     = (string)_rec[ "SOURCES_NAME" ] ;
			this.Type     = (EType)_rec[ "SOURCES_TYPE" ] ;
		}

		#if DEBUG
		public string Print () {

			string s_name = string.IsNullOrEmpty(this.Name) ? "#not_set" : this.Name;
			string s_desc = string.IsNullOrEmpty(this.Desc) ? "#not_set" : this.Desc;

			string s_out = string.Format("name={0};desc={1}", s_name, s_desc);
			return s_out;
		}
		#endif
	};

	// https://learn.microsoft.com/en-us/dotnet/api/system.data.idatarecord.getordinal ;
	public sealed class CProv_enum {

		public CProv_enum () {}
		public IEnumerable<CProvider> Get() {

			using (IDataReader reader_ = OleDbEnumerator.GetRootEnumerator()){
				while (reader_.Read()) {
					yield return (new CProvider(reader_));
				}
			}
			yield break;
		}
	};

}