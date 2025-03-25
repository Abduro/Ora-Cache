/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2025 at 23:35:40.0903197, UTC+4, Batumi, Saturday;
	This is Ebo Pack Oracle OLEDB.NET base unit test definition file;
*/
using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ora.net.oledb.test {

	using TProvider = ora.net.oledb.CProvider;
	using TProv_enum = ora.net.oledb.CProv_enum;

	// https://learn.microsoft.com/en-us/visualstudio/test/getting-started-with-unit-testing ;
	[TestClass]
	public class CDbProvider
	{
		private readonly TProvider t_target = new TProvider();

		public CDbProvider() {
			bool b_break = false;
			b_break = (false != true);
			if (b_break) { 
			}
		}

		[TestMethod]
		public void Print()
		{
			string cs_out = t_target.Print(); // #not_set is expected for new object;
			Console.WriteLine(cs_out);
		}
	};

	[TestClass]
	public class CDbProv_enum {

		public CDbProv_enum () {}

		[TestMethod]
		public void Get () {

			TProv_enum prov_enum = new TProv_enum();
			// expected: there is no odp.net data provider, because it is the extension of ADO.NET;
			IEnumerable < TProvider > t_provs = prov_enum.Get();
			foreach (TProvider prov_ in t_provs) {
				Console.WriteLine(prov_.Print());
			}
		}
	};
}