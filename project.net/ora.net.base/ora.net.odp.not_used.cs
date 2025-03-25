/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Mar-2025 at 08:36:37.2529181, UTC+4, Batumi, Thursday;
	This is Ebo Pack ODP.NET provider(s) wrapper base interface implementation file;
*/
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.IO;
using Microsoft.Win32;

namespace ora.net.odp {

	public class CFilter {
		private readonly List<string> m_criteria = new List<string>();

		public CFilter () {}
		// https://www.merriam-webster.com/thesaurus/criterion ;
		public bool Append (string _criterion) {
			bool b_added = false;
			if (false == this.Is_valid(_criterion))
				return b_added;
			if (true  == this.Has(_criterion))
				return b_added;

			string criterion_ = _criterion.Trim();
			this.m_criteria.Add(criterion_);

			return b_added = true;
		}
		public bool Append (params string[] _criteria) {
			bool b_added = false;

			foreach(string criterion_ in _criteria) {
				if (this.Append(criterion_))
					b_added = true; // it is enough to have only one case of success for setting value of the result;
			}

			return b_added;
		}
		public bool Is_empty () { return 0 == this.m_criteria.Count; }
		public bool Is_passed(string _value){

			if (this.Is_empty())
				return true; // if this filter has no criterion, regardless of _value's validity 'true' is returned;

			if (false == this.Is_valid(_value))
				return false;

			bool b_passed = false;

			// https://stackoverflow.com/questions/444798/case-insensitive-containsstring ;
			foreach (string s_criterion in this.m_criteria) {
				if (-1 < _value.IndexOf(s_criterion, StringComparison.OrdinalIgnoreCase)) {
					b_passed = true;
					break;
				}
			}

			return b_passed;
		}
		public bool Is_valid (string _criterion) {
			bool b_valid = false;
			if (string.IsNullOrEmpty(_criterion))
				return b_valid;
			if (string.IsNullOrWhiteSpace(_criterion))
				return b_valid;

			string criterion_ = _criterion.Trim();

			return (b_valid = 0 < criterion_.Length);
		}
		public bool Has (string _criterion) {

			if (true == this.Is_empty()
				|| false == this.Is_valid(_criterion))
				return false;

			bool b_has = false;

			string criterion_ = _criterion.Trim();
			foreach (string s_element in this.m_criteria) {
				if (0 == string.Compare(criterion_, s_element, StringComparison.OrdinalIgnoreCase)) {
					b_has = true; break;
				}
			}

			return b_has;
		}
	#if DEBUG
		public string Print() {

			string cs_out = "";

			foreach(string s_criterion in this.m_criteria) {
				cs_out += s_criterion;
				cs_out += ";\n";
			}

			return cs_out;
		}
	#endif
	}

	public class CFinder {
		public CFinder () {}
		//
		// *Note*: The path to the DLL module from the registry is not actually the path where the required DLL is located, for example:
		//     registry: C:\Users\Tech_Dog\Desktop\Ora-11g-exp\app\oracle\product\11.2.0\server\bin\ ;
		//     file-system: C:\Users\Tech_Dog\Desktop\Ora-11g-exp\app\oracle\product\11.2.0\server\odp.net\bin\ ;
		//
		private readonly List<string> m_folders = new List<string>();
		private CFilter m_filter = new CFilter();
		// https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/ref ;
		public ref CFilter Filter() { return ref this.m_filter; }
		public List<string> SeachFolders() { return this.m_folders; }

		// this method returns the em[ty string in case if module is not found;
		// otherwise, the actual folder path where required file resides is returned;
		public string Search (string _root, string _p_module_name) {

			string s_path = "";

			this.m_folders.Clear();

			string root_ = _root;

			root_ = root_.Trim(); // ToDo: not good approach because change value of input arg is bad idea;
			if (string.IsNullOrEmpty(root_) || string.IsNullOrWhiteSpace(root_))
				return s_path;
			// https://learn.microsoft.com/en-us/dotnet/standard/base-types/trimming ;
			_p_module_name = _p_module_name.Trim();
			if (string.IsNullOrEmpty(_p_module_name) || string.IsNullOrWhiteSpace(_p_module_name))
				return s_path;
			// https://learn.microsoft.com/en-us/dotnet/api/system.string.lastindexof ; 
			int n_index = root_.LastIndexOf('\\');
			if (n_index != -1)
				root_ = root_.Remove(n_index + 1, root_.Length - n_index - 1);

			s_path = this.Lookup(root_, _p_module_name);
			return s_path;
		}

		private string Lookup (string _root, string _file) {
			string s_path = "";

			bool b_passed = this.m_filter.Is_passed(_root);
			if ( b_passed ) {
				this.m_folders.Add(_root);

				// https://learn.microsoft.com/en-us/dotnet/api/system.io.directory.getfiles ; << synch and slow;
				// https://stackoverflow.com/questions/12524398/directory-getfiles-how-to-get-only-filename-not-full-path ;
				string[] files_ = Directory.GetFiles(_root).Select(file => Path.GetFileName(file)).ToArray();
				foreach (string s_file in files_) {

					if (s_file.Equals(_file, StringComparison.OrdinalIgnoreCase)) {

						string s_full_path = _root + "\\" + s_file;
						var versionInfo = FileVersionInfo.GetVersionInfo(s_full_path);

						s_path = _root;
						return s_path;
					}
				}
			}
			// https://stackoverflow.com/questions/2106877/is-there-a-faster-way-than-this-to-find-all-the-files-in-a-directory-and-all-sub/
			string[] folders_ = Directory.GetDirectories(_root);
			foreach (string s_folder in folders_) {
				s_path = this.Lookup(s_folder, _file);
				if (0 < s_path.Length)
					break;
			}

			return s_path;
		}
	};

	public class CModule {
		public CModule (){}
		public string Path { get; set; }
		public string Version { get; set; }

		// https://stackoverflow.com/questions/204739/what-is-the-c-sharp-equivalent-of-friend ; this a workround of abbsense 'friend' keyword;
		// it is the reason for making property 'set' to public;
		#if DEBUG
		public string Print () {

			string s_path = string.IsNullOrEmpty(this.Path) ? "#not_set" : this.Path;
			string s_version = string.IsNullOrEmpty(this.Version) ? "#not_set" : this.Version;

			string s_out = string.Format("path={0};version={1}", s_path, s_version);
			return s_out;
		}
		#endif
	};

	public class CRegistry {

		private const string s_root_entry = @"Software\Oracle\Odp.Net";

		private readonly Microsoft.Win32.RegistryKey root_ = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(s_root_entry, false);
		private readonly List<CModule> modules_ = new List<CModule>();

		public string Version { get; private set; }

		public CRegistry (){}

		public bool Get() {
			bool b_result = null != this.root_;
			if (!b_result)
				return b_result;
			if (this.modules_.Count > 0) {
				this.modules_.Clear();
			}

			string[] s_versions = root_.GetSubKeyNames();

			Array.Sort<string>(s_versions); // it looks like to be not necessary;

			foreach (string s_version in s_versions) {

				RegistryKey regVerKey = this.root_.OpenSubKey(s_version);
				if (null != regVerKey) {

					string s_dll_path = (string)regVerKey.GetValue("DllPath");

#pragma warning disable IDE0017
					CModule module_ = new CModule();
					module_.Path    = s_dll_path;
					module_.Version = s_version;
#pragma warning restore IDE0017
					this.modules_.Add(module_);
				}
			}
			return b_result = this.modules_.Count > 0;
		}
		public List<CModule> Modules() { return this.modules_; }
	};
}