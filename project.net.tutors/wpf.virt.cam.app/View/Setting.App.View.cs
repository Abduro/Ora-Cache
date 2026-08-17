using System.ComponentModel;
using System.Windows.Media ;

using FirstFloor.ModernUI.Presentation;

namespace Virt.Cam.UI.Content
{
	/// <summary>
	/// A simple view model for configuring theme, font and accent colors.
	/// </summary>
	public class SettingsAppearanceViewModel : NotifyPropertyChanged
	{
		private const string FontSmall = "Small";
		private const string FontLarge = "Large";

		// accent colors from metro design principles
		private readonly Color[] accentColors = new Color[]{
			Color.FromRgb(0x33, 0x99, 0xff),   // blue
			Color.FromRgb(0x00, 0xab, 0xa9),   // teal
			Color.FromRgb(0x33, 0x99, 0x33),   // greenF
			Color.FromRgb(0x8c, 0xbf, 0x26),   // lime
			Color.FromRgb(0xf0, 0x96, 0x09),   // orange
			Color.FromRgb(0xff, 0x45, 0x00),   // orange red
			Color.FromRgb(0xe5, 0x14, 0x00),   // red
			Color.FromRgb(0xff, 0x00, 0x97),   // magenta
			Color.FromRgb(0xa2, 0x00, 0xff),   // purple            
		};

		private Color  selectedAccentColor;
		private readonly LinkCollection themes = new LinkCollection();
		private Link   selectedTheme;
		private string selectedFontSize;

		public SettingsAppearanceViewModel()
		{
			// add the default themes
			this.themes.Add(new Link { DisplayName = "Dark" , Source = AppearanceManager.DarkThemeSource  });
			this.themes.Add(new Link { DisplayName = "Light", Source = AppearanceManager.LightThemeSource });

			this.SelectedFontSize = AppearanceManager.Current.FontSize == FontSize.Large ? FontLarge : FontSmall;

			SyncThemeAndColor();
			AppearanceManager.Current.PropertyChanged += OnAppearanceManagerPropertyChanged;
		}

		public bool IsSaved {
			get {
				Fake.Core.UI.Storage.Theme theme = new Fake.Core.UI.Storage.Theme();
				return theme.Mode;
			}
			set {
				Fake.Core.UI.Storage.Theme theme = new Fake.Core.UI.Storage.Theme();
				if (value)
					theme.Name = selectedTheme.DisplayName;
				else
					theme.Name = null;
			}
		}

		private void SyncThemeAndColor()
		{
			// synchronizes the selected viewmodel theme with the actual theme used by the appearance manager;
			// it is supposed the theme registry storage is applied on main form creation;
			if (this.selectedTheme == null) {

				Fake.Core.UI.Storage.Theme theme = new Fake.Core.UI.Storage.Theme();
				string cs_path = theme.Locate.OriginalString;
				AppearanceManager.Current.ThemeSource = theme.Locate;

				if (cs_path.IndexOf("Dark") > -1)
					this.selectedTheme = this.themes[0];
				else
					this.selectedTheme = this.themes[1];
			}

			// and makes sure accent color is up-to-date;
			this.SelectedAccentColor = AppearanceManager.Current.AccentColor;
		}

		private void OnAppearanceManagerPropertyChanged(object sender, PropertyChangedEventArgs e) {
			if (e.PropertyName == "ThemeSource" || e.PropertyName == "AccentColor") {
				SyncThemeAndColor();
			}
		}

		public LinkCollection Themes { get { return this.themes; } }
		public string[] FontSizes { get { return new string[] { FontSmall, FontLarge }; } }
		public Color[] AccentColors { get { return this.accentColors; } }

		public Link SelectedTheme
		{
			get { return this.selectedTheme; }
			set {
				if (this.selectedTheme!= value) {
					this.selectedTheme = value;
					OnPropertyChanged("SelectedTheme");
					AppearanceManager.Current.ThemeSource = value.Source;

					if (this.IsSaved) {
						Fake.Core.UI.Storage.Theme theme = new Fake.Core.UI.Storage.Theme {
							Name = selectedTheme.DisplayName
						};
					}
				}
			}
		}

		public string SelectedFontSize
		{
			get { return this.selectedFontSize; }
			set {
				if (this.selectedFontSize != value) {
					this.selectedFontSize = value;
					OnPropertyChanged("SelectedFontSize");

					AppearanceManager.Current.FontSize = value == FontLarge ? FontSize.Large : FontSize.Small;
				}
			}
		}

		public Color SelectedAccentColor
		{
			get { return this.selectedAccentColor; }
			set {
				if (this.selectedAccentColor != value)
				{
					this.selectedAccentColor = value;
					OnPropertyChanged("SelectedAccentColor");

					AppearanceManager.Current.AccentColor = value;
				}
			}
		}
	}
}
