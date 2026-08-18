/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Jan-2020 at 10:21:22a, UTC+7, Novosibirsk, Wednesday;
	This is system registry storage wrapper implementation file.
*/
using System;
using Microsoft.Win32;

namespace Virt.Cam.Stg {

	public class Registry {
		private const string s_root_entry = @"Software";
		private const string s_virt_entry = @"VirtCam" ; private readonly string s_virt_path = s_root_entry + @"\" + s_virt_entry;
		private const string s_sets_entry = @"Settings"; private readonly string s_sets_path = s_virt_entry + @"\" + s_sets_entry;

#if __do_not_use_because_it_requires_admin_permissions__
		Microsoft.Win32.RegistryKey root_ = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(s_root_, true);
#else
		Microsoft.Win32.RegistryKey root_ = Microsoft.Win32.Registry.CurrentUser.OpenSubKey(s_root_entry, true);
#endif
		public Registry() {
			if (string.IsNullOrEmpty(s_virt_path)) { }
			if (this.Is() == false) {
				root_.CreateSubKey(s_sets_path);
			}
		}

		public bool Delete(string _key) {
			bool b_result = false;

			if (string.IsNullOrEmpty(_key))
				return b_result;

			string s_path = s_sets_path + "\\" + _key;

			root_.DeleteSubKey(s_path, true);
			return (b_result = true);
		}

		public bool Delete(string _key, string _name) {
			bool b_result = false;

			if (string.IsNullOrEmpty(_key) || string.IsNullOrEmpty(_name))
				return b_result;

			string s_path = s_sets_path;
			RegistryKey sets_enum = root_.OpenSubKey(s_sets_path, true);
			RegistryKey sets_key  = sets_enum.OpenSubKey(_key, true);

			if (sets_key == null)
				return b_result;

			sets_key.DeleteValue(_name, false);
			return (b_result = true);
		}

		public bool Get(string _key, string _name, ref bool _value) {

			string cs_value = "";

			bool b_result = this.Get(_key, _name, ref cs_value);
			if ( b_result ) {
				_value = cs_value.Equals("true", StringComparison.OrdinalIgnoreCase);
			}
			else
				_value = false;

			return b_result;
		}

		public bool Get(string _key, string _name, ref string _value) {
			bool b_result = false;

			if (string.IsNullOrEmpty(_key) || string.IsNullOrEmpty(_name))
				return b_result;

			string s_path = s_sets_path;
			RegistryKey sets_enum = root_.OpenSubKey(s_sets_path, true);
			RegistryKey sets_key  = sets_enum.OpenSubKey(_key);

			if (sets_key == null)
				return b_result;

			_value   = (string)sets_key.GetValue(_name);
			b_result = !string.IsNullOrEmpty(_value);

			return b_result;
		}

		private bool Is() {
			return (root_.OpenSubKey(s_virt_entry) != null);
		}

		public bool Set(string _key, string _name, string _value) {
			bool b_result = false;

			if (string.IsNullOrEmpty(_key) || string.IsNullOrEmpty(_name) || string.IsNullOrEmpty(_value))
				return b_result;

			RegistryKey sets_enum = root_.OpenSubKey(s_sets_path, true);
			RegistryKey sets_key  = sets_enum.CreateSubKey(_key);
			sets_key.SetValue(_name, _value);
			b_result = true;

			return b_result;
		}

		public bool Set(string _key, string _name, uint _value) {
			bool b_result = false;

			if (string.IsNullOrEmpty(_key) || string.IsNullOrEmpty(_name))
				return b_result;

			RegistryKey sets_enum = root_.OpenSubKey(s_sets_path, true);
			RegistryKey sets_key  = sets_enum.CreateSubKey(_key);
			sets_key.SetValue(_name, _value);

			return b_result;
		}
	}
}
