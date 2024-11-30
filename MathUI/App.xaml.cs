﻿using MathUI.Commands;
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
        public App()
        {
            Util.AppCultureInfo = Thread.CurrentThread.CurrentUICulture;
        }
    }

}
