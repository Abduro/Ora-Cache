/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2025 at 00:27:37.8561083, UTC+4, Batumi, Sunday;
	This is Ebo Pack Oracle data provider auxiliary (not used) unit test definition file;
*/
using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ora.net.not_used.test {

	using TFilter = ora.net.odp.CFilter;
	using TFinder = ora.net.odp.CFinder;
	using TModule = ora.net.odp.CModule;
	using TRegistry = ora.net.odp.CRegistry;

	[TestClass]
	public class CFilter {

		private readonly TFilter filter_ = new TFilter();

		public CFilter () {}
		[TestMethod]
		public void Compose() {

			this.filter_.Append(new string[]{ "odp.net", "oledb" });
			_out.What(this.filter_.Print());
		}
	};

	[TestClass]
	public class CFinder {

		private readonly TFinder m_finder = new TFinder();

		public CFinder () {}

		[TestMethod]
		public void Search () {

			TRegistry reg_ = new TRegistry();
			if (false == reg_.Get()) {
				_out.What("#no_items");
				return;
			}

			List<TModule> modules_ = reg_.Modules();

			if (0 < modules_.Count) { // it is not necessary to check, because the method 'Get' returns 'true';

				this.m_finder.Filter().Append(new string[]{ "odp.net", "oledb" });

				string s_root = modules_[modules_.Count - 1].Path;
				string s_found = this.m_finder.Search(s_root, "Oracle.DataAccess.dll");
					
				List<string> folders = this.m_finder.SeachFolders();
				foreach (string s_folder in folders) {
					_out.What(s_folder);
				}
				if (s_found != "")
					_out.What(string.Format("Found at: {0}", s_found));
			}
		}
	};

	[TestClass]
	public class CDllModule {

		private readonly TModule t_module = new TModule();

		public CDllModule () {}

		[TestMethod]
		public void Print() {
			string cs_out = t_module.Print();  // #not_set is expected for new object;
			_out.What(cs_out);
		}
	};

	[TestClass]
	public class CRegistry
	{
		public CRegistry() { }

		private readonly TRegistry t_registry = new TRegistry();

		[TestMethod]
		public void Get()
		{
			if (null == t_registry)
				return;

			bool b_result = t_registry.Get();

			List<TModule> t_modules = t_registry.Modules();

			foreach (TModule module_ in t_modules) {
				Console.WriteLine(module_.Print());
			}
		}
	};
}