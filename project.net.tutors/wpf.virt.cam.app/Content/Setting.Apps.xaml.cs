using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Virt.Cam.UI.Content {
	
	public partial class SettingsAppearance : UserControl {

		private readonly SettingsAppearanceViewModel m_view = new SettingsAppearanceViewModel();

		public SettingsAppearance() {

			InitializeComponent();

			this.DataContext = m_view;
			this.Loaded += OnLoaded;
		}
		// it is not clear how to connect checked state to property; standard click handler is used;
		private void OnSaved(object sender, RoutedEventArgs e) {
			if (this.theme_save.IsChecked == true) {
				m_view.IsSaved = true;
			}
			else {
				m_view.IsSaved = false;
			}
		}

		private void OnLoaded(object sender, RoutedEventArgs e) {

			Keyboard.Focus(this.theme_list);
			this.theme_save.IsChecked = m_view.IsSaved;
		}
	}
}