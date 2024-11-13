using MathUI.ViewModels.MainWindow;
using System;
using System.Collections.Generic;
using System.Linq;
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

        private void DrawRect_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawRect());
        }

        private void DrawSquare_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.DrawSquare());
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

        private void CloseApp_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.CloseApp());
        }

        private void Dist_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => ViewModel.Dist());
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
    }
}
