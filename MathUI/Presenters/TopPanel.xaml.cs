using MathUI.Resources;
using MathUI.ViewModels.MainWindow;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MathUI.Presenters
{
    /// <summary>
    /// Interaction logic for TopPanel.xaml
    /// </summary>
    public partial class TopPanel : UserControl
    {
        private ResourceManager resourceMan;
        public static readonly DependencyProperty ViewModelProperty =
        DependencyProperty.Register("ViewModel", typeof(MainWindowViewModel), typeof(TopPanel), new PropertyMetadata(null));

        public MainWindowViewModel ViewModel
        {
            get { return (MainWindowViewModel)GetValue(ViewModelProperty); }
            set { SetValue(ViewModelProperty, value); }
        }
        public TopPanel()
        {
            InitializeComponent();
            switch (System.Globalization.CultureInfo.CurrentUICulture.TwoLetterISOLanguageName)
            {
                case "en":
                    resourceMan = new global::System.Resources.ResourceManager("MathUI.Resources.TopPanelRes", typeof(TopPanelRes).Assembly);
                    break;
                case "vn":
                    resourceMan = new global::System.Resources.ResourceManager("MathUI.Resources.TopPanelResvn", typeof(TopPanelRes).Assembly);
                    break;
            }
        }
        private void CommandAction(Action<MainWindowViewModel> callback)
        {
            try
            {
                if (DataContext is not MainWindowViewModel model)
                {
                    return;
                }

                callback(model);
            }
            catch (Exception)
            {
            }
        }

        private void DrawLine_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawLine());
        }

        private void DrawCircle_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawCircle());
        }

        private void DrawArc_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawArc());
        }

        private void Undo_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Undo());
        }

        private void Redo_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Redo());
        }

        private void New_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.NewFile());
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.OpenFile());
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.SaveFile());
        }

        private void Select_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Select());
        }

        private void FileTabControl_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ViewModel == null)
            {
                return;
            }
            CommandAction((model) => ViewModel.ChangeTab());
        }

        private void DrawPoly_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawPoly());
        }

        private void Plane_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawPlane());
        }

        private void Extrude_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Extrude());
        }

        private void Sweep_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Sweep());
        }

        private void Scale_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Scale());
        }

        private void Trans_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Trans());
        }

        private void Rotate_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Rotate());
        }

        private void P2W_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.P2W());
        }

        private void W2P_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.W2P());
        }

        private void Language_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.ChangeLanguage());
        }

        private void Netload_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.NetLoad());
        }
    }
}
