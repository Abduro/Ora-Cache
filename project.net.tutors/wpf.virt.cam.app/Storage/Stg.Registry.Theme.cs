/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Jan-2020 at 11:02:04a, UTC+7, Novosibirsk, Wednesday;
	This is virtual camera  UI theme storage implementation file.
*/
using System;
using Virt.Cam.Stg;

namespace Virt.Cam.UI.Storage {
	class Theme {
		private const string m_default = "dark";

		public Theme () { }

		public Uri Locate {
			get {
				string cs_name = this._get_name();
				if ( cs_name.Equals(m_default, StringComparison.OrdinalIgnoreCase))
					return new Uri("pack://application:,,,/FirstFloor.ModernUI;component/Assets/ModernUI.Dark.xaml");
				else
					return new Uri("pack://application:,,,/FirstFloor.ModernUI;component/Assets/ModernUI.Light.xaml");
			}
			set {}
		}

		public bool Mode {
			get { return this._get_mode(); }
		}

		public string Name {
			get { return this._get_name(); }
			set { this._set_name(value); }
		}

		private bool   _get_mode() {
			string cs_name  = _get_name();
			string cs_value = "";
			Registry hive   = new Registry();
			bool   b_result = hive.Get("Theme", "current", ref cs_value);
			return b_result && string.IsNullOrEmpty(cs_name) == false;
		}

		private string _get_name () {
			string cs_value = m_default;
			Registry hive   = new Registry();
			bool b_result   = hive.Get("Theme", "current", ref cs_value);
			if (!b_result || string.IsNullOrEmpty(cs_value))
				cs_value = m_default;
			return cs_value;
		}

		private bool   _set_name(string _value) {
			Registry hive   = new Registry();
			if (string.IsNullOrEmpty(_value)) {
				return hive.Delete("Theme", "current");
			}
			else {
				return hive.Set("Theme", "current", _value);
			}
		}
	}
}
