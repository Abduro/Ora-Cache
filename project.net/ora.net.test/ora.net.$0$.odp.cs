/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2025 at 23:16:32.9078696, UTC+4, Batumi, Saturday;
	This is Ebo Pack ODP.NET unit test definition file;
*/
using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ora.net.odp.test {

	using TAddress = ora.net.odp.COraAddress;
	using TDataSrc = ora.net.odp.COraDataSrc;
	using TService = ora.net.odp.COraService;
	using TLogin   = ora.net.odp.COraLogin;
	using TConnect = ora.net.odp.COraConnect;
	
	[TestClass]
	public class CAddress {
		private readonly TAddress t_address = new TAddress();
		public CAddress() {}
		[TestMethod]
		public void Set() {

			t_address.Host = "TDoc";
			t_address.Port = 1521;

			_out.What(t_address.ToString());
		}
	};

	[TestClass]
	public class CService {
		private readonly TService t_service = new TService();
		public CService() {}
		[TestMethod]
		public void Set() {
			t_service.Name = "XE";
			_out.What(t_service.ToString());
		}
	};
	
	[TestClass]
	public class CDataSrc {

		private readonly TDataSrc t_dat_src = new TDataSrc();

		public CDataSrc() {}
		[TestMethod]
		public void Set() {

			t_dat_src.Address().Host = "TDoc";
			t_dat_src.Address().Port = 1521;

			t_dat_src.Service().Name = "XE";

			_out.What(t_dat_src.ToString());
		}
	};

	[TestClass]
	public class CConnect {

		private readonly TConnect t_connect = new TConnect();

		public CConnect (){}

		[TestMethod]
		public void Open() {

			this.t_connect.Login().Pwd  = "system"; // https://www.srikanthtechnologies.com/blog/oracle/reset_system_pwd.aspx ;
			this.t_connect.Login().User = "SYSTEM";

			this.t_connect.DataSource().Address().Set("TDoc", 1521);
			this.t_connect.DataSource().Service().Name = "XE";

			if (this.t_connect.Open()) {
				this.t_connect.Dispose();
				_out.What("Connect is open;");
			}
			else {
				_out.What(this.t_connect.Error.ToString());
			}
		}

		[TestMethod]
		public void Set() {

			this.t_connect.Login().Pwd = "{1|2|3}";
			this.t_connect.Login().User = "Abu";

			this.t_connect.DataSource().Address().Set("TDoc", 1521);
			this.t_connect.DataSource().Service().Name = "XE";

			_out.What(this.t_connect.ToString());
		}
	};

	[TestClass]
	public class CLogin {

		private readonly TLogin t_login = new TLogin("Abu", "{1|2|3}");

		public CLogin (){}

		[TestMethod]
		public void Set () {

			_out.What(this.t_login.Print());

		}
	};
}