using MathGL;
using MathUI.Commons;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Threading;
using System.Windows.Input;
using System.Windows;
using Microsoft.Win32;
using System.IO;
using MathUI.Commons;
using System.Windows.Media.Media3D;
using System.Windows.Shapes;

namespace MathUI.ViewModels.MainWindow
{
    public class MainWindowViewModel : ViewModelBase
    {
        private DispatcherTimer _timer;
        public Presenters.MainWindow context;
        string _MouseX;
        public string MouseX
        {
            get => _MouseX;
            set
            {
                _MouseX = value;
                OnPropertyChanged("MouseX");
            }
        }

        string _MouseY;
        public string MouseY
        {
            get => _MouseY;
            set
            {
                _MouseY = value;
                OnPropertyChanged("MouseY");
            }
        }

        private string _engineName;
        public string EngineName
        {
            get => _engineName;
            set
            {
                _engineName = value;
                OnPropertyChanged("EngineName");
            }
        }

        private string _historyWindow;
        public string HistoryWindow
        {
            get => _historyWindow;
            set
            {
                _historyWindow = value;
                OnPropertyChanged("HistoryWindow");
            }
        }

        private string commandWindow;

        public string CommandWindow
        {
            get => commandWindow;
            set
            {
                commandWindow = value;
                OnPropertyChanged("CommandWindow");
            }
        }

        private System.Windows.Controls.TextBox _InputCommandWindow;
        public System.Windows.Controls.TextBox InputCommandWindow
        {
            get => _InputCommandWindow;
            set
            {
                _InputCommandWindow = value;
                OnPropertyChanged("InputCommandWindow");
            }
        }

        private string shape;
        public string Shape
        {
            get => shape;
            set
            {
                shape = value;
                OnPropertyChanged("Shape");
            }
        }

        private double _positionX;
        public double PositionX
        {
            get => _positionX;
            set
            {
                _positionX = value;
                OnPropertyChanged("PositionX");
            }
        }

        private double _positionY;
        public double PositionY
        {
            get => _positionY;
            set
            {
                _positionY = value;
                OnPropertyChanged("PositionY");
            }
        }

        private double _positionZ;
        public double PositionZ
        {
            get => _positionZ;
            set
            {
                _positionZ = value;
                OnPropertyChanged("PositionZ");
            }
        }

        private ObservableCollection<string> _fileItems;

        public ObservableCollection<string> FileItems
        {
            get => _fileItems;
            set
            {
                Set(ref _fileItems, value);
                OnPropertyChanged(nameof(FileItems));
            }
        }

        private ObservableCollection<string> _filePaths;

        public ObservableCollection<string> FilePaths
        {
            get => _filePaths;
            set
            {
                Set(ref _filePaths, value);
                OnPropertyChanged(nameof(FilePaths));
            }
        }

        private string _fileSelected;
        public string FileSelected
        {
            get => _fileSelected;
            set
            {
                Set(ref _fileSelected, value);
                OnPropertyChanged(nameof(FileSelected));
            }
        }

        private string _pathSelected;
        public string PathSelected
        {
            get => _pathSelected;
            set
            {
                Set(ref _pathSelected, value);
                OnPropertyChanged(nameof(PathSelected));
            }
        }

        private bool _isNewFile;
        public bool IsNewFile
        {
            get => _isNewFile;
            set
            {
                Set(ref _isNewFile, value);
                OnPropertyChanged(nameof(IsNewFile));
            }
        }

        public MainWindowViewModel(Presenters.MainWindow mainWindow)
        {
            EngineName = "OpenGL";
            HistoryWindow = "";
            context = mainWindow;
            FileItems = ["Untitled"];
            FilePaths = ["Untitled"];
            FileSelected = "Untitled";
            PathSelected = "Untitled";
            IsNewFile = true;
            CloseTabCommand = new RelayCommand<string>((fileName) => true, (fileName) => CloseTab(fileName));
        }

        private void CloseTab(string fileName)
        {
            if (FileItems.Contains(fileName))
            {
                FileItems.Remove(fileName);
                if (FileItems.Count > 0)
                {
                    FileSelected = FileItems[0];
                }
            }
        }

        public void LoadEngine(MathUI.Presenters.MainWindow mainWindow)
        {
        }

        public void TL()
        {
        }

        public void TM()
        {
        }

        public void TR()
        {
        }

        public void ML()
        {
        }

        public void TMM()
        {
        }

        public void BMM()
        {
        }

        public void MR()
        {
        }

        public void BL()
        {
        }

        public void BM()
        {
        }

        public void BR()
        {
        }

        public void RealtimeHandle()
        {
        }

        public void ZoomViewport(MouseWheelEventArgs e)
        {
        }

        public async void DrawLine()
        {
        }

        public async void DrawCircle()
        {
        }
        internal async void DrawRect()
        {
        }

        public async void DrawSquare()
        {
        }

        internal void AppendCommand()
        {
        }

        internal void Undo()
        {
        }

        internal void Redo()
        {
        }

        internal void NewFile()
        {
        }

        internal void OpenFile()
        {
        }

        internal void SaveFile()
        {
        }

        internal async void Select()
        {
        }

        internal void CloseApp()
        {
        }

        internal async void Dist()
        {
        }

        internal void ChangeTab()
        {
        }

        internal async void DrawPoly()
        {
        }

        public ICommand CloseTabCommand { get; }
    }
}
