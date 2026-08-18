using System;
using FirstFloor.ModernUI.Windows.Controls;

namespace Virt.Cam.UI {

	public partial class MainWindow : ModernWindow {

		public MainWindow() {
			Virt.Cam.UI.Storage.Theme theme = new Virt.Cam.UI.Storage.Theme();
#if __use_dark
			FirstFloor.ModernUI.Presentation.AppearanceManager.Current.ThemeSource =
			new Uri("pack://application:,,,/FirstFloor.ModernUI;component/Assets/ModernUI.Dark.xaml");
#else
			FirstFloor.ModernUI.Presentation.AppearanceManager.Current.ThemeSource = theme.Locate;
#endif
			InitializeComponent();
			WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
		}
	}
}
