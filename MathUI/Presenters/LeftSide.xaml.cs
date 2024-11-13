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
    /// Interaction logic for LeftSide.xaml
    /// </summary>
    public partial class LeftSide : UserControl
    {
        public static readonly DependencyProperty ViewModelProperty =
        DependencyProperty.Register("ViewModel", typeof(MainWindowViewModel), typeof(LeftSide), new PropertyMetadata(null));

        public MainWindowViewModel ViewModel
        {
            get { return (MainWindowViewModel)GetValue(ViewModelProperty); }
            set { SetValue(ViewModelProperty, value); }
        }

        public LeftSide()
        {
            InitializeComponent();
        }
    }
}
