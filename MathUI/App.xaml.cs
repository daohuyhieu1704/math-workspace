using MathUI.Commands;
using MathUI.Utils;
using System.Configuration;
using System.Data;
using System.Windows;

namespace MathUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static event EventHandler LanguageChanged;
        public App()
        {
            Util.AppCultureInfo = Thread.CurrentThread.CurrentUICulture;
            CommandRegistry.DiscoverAndRegisterCommands();
        }
        public static void OnLanguageChanged()
        {
            LanguageChanged?.Invoke(null, EventArgs.Empty);
        }
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            MathUI.Utils.ResxDynamicResourceProvider.LoadResourceToApplication("TopPanelRes");
        }
    }

}
