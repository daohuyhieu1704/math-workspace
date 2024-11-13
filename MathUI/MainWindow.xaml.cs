using MathGL;
using MathUI.Commons;
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

namespace MathUI
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
            this.Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var grid = FindName("EngineContainer");
            if (grid is Grid engineContainer)
            {
                engineContainer.Children.Add(new EngineHost());
                GLEngineNative.Instance.ProcessGLUTEvents();
                //_glutTimer = new DispatcherTimer
                //{
                //    Interval = TimeSpan.FromMilliseconds(16)
                //};
                //_glutTimer.Tick += (s, args) => 
                //_glutTimer.Start();
            }
        }
    }
}