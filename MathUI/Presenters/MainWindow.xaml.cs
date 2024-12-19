using MathGL;
using MathUI.Commons;
using MathUI.ViewModels.MainWindow;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Text.Json.Nodes;
using System.Resources;
using MathUI.Resources;
using MathUI.Commands;
using System.Windows.Media.Media3D;
using MathUI.Utils;
using System.Collections.ObjectModel;

namespace MathUI.Presenters
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public delegate void MouseClickCallback(int x, int y);
        private readonly MainWindowViewModel vm;
        private readonly UndoRedoManager undoRedoManager = new();
        public MainWindow()
        {
            InitializeComponent();
            this.Loaded += MainWindow_Loaded;
            this.KeyDown += Window_KeyDown;
            vm = new MainWindowViewModel(this);
            CommandRegistry.DiscoverAndRegisterCommands(vm);
            DataContext = vm;
            vm.InputCommandWindow = InputCommandWindow;
            CallbackBridge.RegisterMouseCallback(OnMouseClick);
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
            {
                if (DataContext is MainWindowViewModel viewModel)
                {
                    //viewModel.RemoveSelectedObject();
                }
            }

        }
        void OnMouseClick(int x, int y)
        {
            CommandAction((model) => model.RegenViewModel());
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var grid = FindName("EngineContainer");
            if (grid is Grid engineContainer)
            {
                engineContainer.Children.Add(new EngineHost());
                DrawingManager.Instance.ProcessGLUTEvents();
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
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //if (e.LeftButton == MouseButtonState.Pressed)
            //{
            //    CommandAction((model) => model.Select());
            //}
        }

        private void TL_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TL());
        }

        private void TM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TM());
        }

        private void TR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TR());
        }

        private void ML_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.ML());
        }

        private void TMM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TMM());
        }

        private void BMM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BMM());
        }

        private void MR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.MR());
        }

        private void BL_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BL());
        }

        private void BM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BM());
        }

        private void BR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BR());
        }

        private void CommandTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                CommandAction((model) => model.AppendCommand());
            }
        }

        private void InputCommandWindow_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}