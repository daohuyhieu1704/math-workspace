﻿
using MathGL;
using MathUI.Commons;
using MathUI.ViewModels.MainWindow;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using Telerik.Windows.Controls;

namespace MathUI.Presenters
{
   
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer _glutTimer;
        public MainWindow()
        {
            InitializeComponent();
            //this.Loaded += MainWindow_Loaded;
            MainWindowViewModel viewModel = new MainWindowViewModel(this);

        }
    

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var grid = FindName("EngineContainer");
            if (grid is Grid engineContainer)
            {
                engineContainer.Children.Add(new EngineHost());
                DrawingManager.Instance.ProcessGLUTEvents();
                //_glutTimer = new DispatcherTimer
                //{
                //    Interval = TimeSpan.FromMilliseconds(16)
                //};
                //_glutTimer.Tick += (s, args) => 
                //_glutTimer.Start();
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

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.MiddleButton == MouseButtonState.Pressed)
            {
            }
        }

        private void Window_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            //CommandAction((model) => model.ZoomViewport(e));
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
            //CommandAction((model) => model.ML());
        }

        private void TMM_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.TMM());
        }

        private void BMM_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.BMM());
        }

        private void MR_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.MR());
        }

        private void BL_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.BL());
        }

        private void BM_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.BM());
        }

        private void BR_click(object sender, RoutedEventArgs e)
        {
            //CommandAction((model) => model.BR());
        }

        private void CommandTextBox_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                //CommandAction((model) => model.AppendCommand());
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0 && e.AddedItems[0] is string selectedCommand)
            {
                var viewModel = (MainWindowViewModel)DataContext;
                viewModel.CommandWindow = selectedCommand;
            }
        }

        private void commandsAutoComplete_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}