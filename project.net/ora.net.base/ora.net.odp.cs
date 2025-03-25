/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2025 at 22:48:00.5582999, UTC+4, Batumi, Thursday;
	This is Ebo Pack ODP.NET provider(s) wrapper base interface implementation file;
*/
using System;
using Oracle.DataAccess.Client;

// https://learn.microsoft.com/en-us/dotnet/standard/garbage-collection/implementing-dispose ;

namespace ora.net.odp {

	public enum EProtocol {
		eTCP = 0, // default;
	};

	public class COraError { // this is simplified version of error object, only base attributes;
		public COraError () {}
		public COraError (int _n_code, string _s_desc) { this.Set(_n_code, _s_desc); }

		public int Code { get { return this.m_code; } set { this.m_code = value; }}
		public string Desc { get { return this.m_desc; } set { this.m_desc = value; }}

		public void Set(int _n_code, string _s_desc) {
			this.Code = _n_code;
			this.Desc = _s_desc;
		}

		public override string ToString () {
			string s_out = string.Format("Err: code={0};desc={1}", this.Code, this.Desc);
			return s_out;
		}

		private int m_code = 0;
		private string m_desc = "";
	};
	
	public class COraAddress { // this class uses TCP protocol by default;
		
		public COraAddress() {}
		public COraAddress(string _s_host, UInt16 _n_port) { this.Set(_s_host, _n_port); }

		public string Host { get { return this.m_host; } set { this.m_host = value; } }
		public UInt16 Port { get { return this.m_port; } set { this.m_port = value; } }

		public bool Is_valid () { return false == string.IsNullOrEmpty(this.Host) && 0 != this.Port; }
		public bool Set(string _s_host, UInt16 _n_port) {
			this.Host = _s_host; this.Port = _n_port;
			return true; // no evaluation of data change is set, thus always 'true';
		}
		public override string ToString() {
			string cs_out = string.Format("ADDRESS=(PROTOCOL=TCP)(HOST={0})(PORT={1})", this.Host, this.Port);
			return cs_out;
		}

		private string m_host = "";
		private UInt16 m_port = 0;
	//	private EProtocol m_proto = EProtocol.eTCP;
	};

	public class COraService {
		public COraService() {}

		public bool Is_valid () { return false == string.IsNullOrEmpty(this.Name); }
		public string Name { get { return this.m_name; } set { this.m_name = value; }}

		public override string ToString() {
			string s_out = string.Format("(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME={0}))", this.Name);
			return s_out;
		}

		private string m_name = "";
	};

	public class COraDataSrc {
		public COraDataSrc() {}

		public ref COraAddress Address() { return ref this.m_address; }
		public ref COraService Service() { return ref this.m_service; }

		public bool Is_valid () { return this.Address().Is_valid() && this.Service().Is_valid(); }

		public override string ToString() {
			// it is suppossed the address list consists of one address only;
			string s_out = string.Format("Data Source=(DESCRIPTION=(ADDRESS_LIST=({0})){1})", this.Address().ToString(), this.Service().ToString());
			return s_out;
		}

		private COraAddress m_address = new COraAddress();
		private COraService m_service = new COraService();
	}

	public class COraLogin {

		private string m_user;
		private string m_pwd ;

		public COraLogin (){}
		public COraLogin (string _user, string _pwd){
			this.Set(_user, _pwd);
		}

		public string Pwd  { get { return this.m_pwd ; } set { this.m_pwd  = value; } }
		public string User { get { return this.m_user; } set { this.m_user = value; } }

		public bool Set (string _user, string _pwd) { // no change data evaluation is made yet, thus always returns true;
			bool b_changed = true;
			this.Pwd = _pwd;
			this.User = _user;
			return b_changed;
		}

		public bool Is_set () {

			bool b_set = (
				false == string.IsNullOrEmpty(this.Pwd)  && 
				false == string.IsNullOrEmpty(this.User) &&
				false == string.IsNullOrWhiteSpace(this.Pwd) &&
				false == string.IsNullOrWhiteSpace(this.User)
			);
			return b_set;
		}

		#if DEBUG
		public string Print () {

			if (false == this.Is_set())
				return "#not_set";

			return string.Format("user={0};pwd={1};", this.User, this.Pwd);
		}
		#endif
	};
	// no error object is created yet;
	public class COraConnect : IDisposable {

		public COraConnect (){}

		public bool Close () {
			bool b_result = false;

			if (false == this.Is_opened())
				return b_result;
			if (this.m_ora_con == null) // maybe it is not necessary but just in case;
				return b_result;

			try {
				this.m_ora_con.Close(); // no error handling is here yet;
				this.m_open = false;
			}
			catch (OracleException) {}
			catch (Exception) {}

			return b_result = true;
		}

		public bool Is_opened () { return this.m_open; }

		public bool Open () {
			bool b_result = false;

			if (this.Is_opened())
				return b_result;
			if (this.m_ora_con == null) // maybe it is not necessary but just in case;
				return b_result;

			try {
				this.m_ora_con.ConnectionString = this.ToString();
				this.m_ora_con.Open();
				this.m_open = true;
			}
			catch (OracleException _ora_ex) {
				this.m_error.Set(_ora_ex.Number, _ora_ex.Message);
			}
			catch (Exception) {}

			return b_result = this.m_open;
		}

		public ref COraDataSrc DataSource() { return ref this.m_data_src; }
		public ref COraLogin Login() { return ref this.m_login; }

		public COraError Error { get { return this.m_error; } private set {}}

		public override string ToString() {
			// it doesn't work;
			// return string.Format("User Id={0};Password={1};Data Source={2}", this.Login().User, this.Login().Pwd, this.DataSource);

			// https://stackoverflow.com/questions/30489018/odp-net-connectionstring ; thanks to b.pell ;
			string s_conn = string.Format("{0};User Id={1};Password={2};Validate Connection=true;", this.DataSource().ToString(), this.Login().User, this.Login().Pwd);
			return s_conn;
		}

		public void Dispose() {

			if (this.m_open) {
				this.m_ora_con.Close();
				this.m_open = false;
			}
			if (false == this.m_disposed) {
				
				this.m_ora_con.Dispose();
				this.m_disposed = true;
			}
			GC.SuppressFinalize(this);
		}
#if (false)
		protected virtual void Dispose (bool _b_closing) {

			if (this.m_closed)
				return;

		}
#endif
		private bool m_disposed = false;
		private bool m_open = false;

		private COraDataSrc m_data_src = new COraDataSrc();
		private COraLogin m_login = new COraLogin();
		private OracleConnection m_ora_con = new OracleConnection();
		private COraError m_error = new COraError();
	};
}