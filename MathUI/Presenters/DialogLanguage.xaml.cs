using MathUI.ViewModels;
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
using System.Windows.Shapes;

namespace MathUI.Presenters
{
    /// <summary>
    /// Interaction logic for DialogLanguage.xaml
    /// </summary>
    public partial class DialogLanguage : Window
    {
        public DialogLanguage()
        {
            InitializeComponent();
            DataContext = new DialogLanguageViewModel();
        }
    }
}
