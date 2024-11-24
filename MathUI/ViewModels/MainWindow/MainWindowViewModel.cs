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
using System.Text.Json.Nodes;

namespace MathUI.ViewModels.MainWindow
{
    public class IconButtonViewModel : ViewModelBase
    {
        public string Icon { get; set; }
        public string Label { get; set; }
        public ICommand ClickHandler { get; set; }
    }

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
            // GLEngine.Instance.TLViewport();
        }

        public void TM()
        {
            // GLEngine.Instance.TMViewport();
        }

        public void TR()
        {
            // GLEngine.Instance.TRViewport();
        }

        public void ML()
        {
            // GLEngine.Instance.MLViewport();
        }

        public void TMM()
        {
            // GLEngine.Instance.TMMViewport();
        }

        public void BMM()
        {
            // GLEngine.Instance.BMMViewport();
        }

        public void MR()
        {
            // GLEngine.Instance.MRViewport();
        }

        public void BL()
        {
            // GLEngine.Instance.BLViewport();
        }

        public void BM()
        {
            // GLEngine.Instance.BMViewport();
        }

        public void BR()
        {
            // GLEngine.Instance.BRViewport();
        }

        public void RealtimeHandle()
        {
        }

        public void ZoomViewport(MouseWheelEventArgs e)
        {
        }

        public async void DrawLine()
        {
            //PointSelection pointSelection = new();
            //HistoryWindow += "Pick 2 points:" + "\n";
            //List<Point3d> pnt1 = await pointSelection.getPoints(1);
            //LineJig lineJig = new(pnt1[0]);
            //lineJig.Commit();
            //List<Point3d> pnt2 = await pointSelection.getPoints(1);
            //Line line = new(pnt1[0], pnt2[0]);
            //line.Draw();
            //HistoryWindow += line.GetCommand() + "\n";
        }

        public async void DrawCircle()
        {
            //PointSelection pointSelection = new();
            //HistoryWindow += "Pick 2 center:" + "\n";
            //List<Point3d> pnt1 = await pointSelection.getPoints(1);
            //using LineJig lineJig = new(pnt1[0]);
            //using CircleJig circleJig = new(pnt1[0]);
            //lineJig.Commit();
            //circleJig.Commit();
            //List<Point3d> pnt2 = await pointSelection.getPoints(1);
            //Circle circle = new(pnt1[0], pnt1[0].DistanceTo(pnt2[0]));
            //circle.Draw();
            //HistoryWindow += circle.GetCommand() + "\n";
        }

        internal async void DrawRect()
        {
            //PointSelection pointSelection = new();
            //HistoryWindow += "Pick 2 points:" + "\n";
            //List<Point3d> pnt = await pointSelection.getPoints(2);
            //Line line1 = new(new Point3d(pnt[0].X, pnt[1].Y, 0), pnt[1]);
            //line1.Draw();

            //Line line2 = new(pnt[1], new Point3d(pnt[1].X, pnt[0].Y, 0));
            //line2.Draw();

            //Line line3 = new(new Point3d(pnt[1].X, pnt[0].Y, 0), pnt[0]);
            //line3.Draw();

            //Line line4 = new(pnt[0], new Point3d(pnt[0].X, pnt[1].Y, 0));
            //line4.Draw();

            //HistoryWindow += line1.GetCommand() + "\n";
            //HistoryWindow += line2.GetCommand() + "\n";
            //HistoryWindow += line3.GetCommand() + "\n";
            //HistoryWindow += line4.GetCommand() + "\n";
        }

        public async void DrawSquare()
        {
            //PointSelection pointSelection = new();
            //HistoryWindow += "Pick 2 points:" + "\n";
            //List<Point3d> pnt = await pointSelection.getPoints(2);
            //TextInput textInp = new(this);
            //string text = await textInp.GetText();
            //if (double.TryParse(text, out var z))
            //{
            //    Square square = new(pnt[0].ConvertTo2d(), pnt[1].ConvertTo2d(), z);
            //    square.Draw();
            //    HistoryWindow += square.GetCommand() + "\n";
            //}
        }

        internal void AppendCommand()
        {
            // DrawingManager.Instance.AppendCommand(CommandWindow);
            CommandWindow = "";
            HistoryWindow += CommandWindow + "\n";
        }

        internal void Undo()
        {
        }

        internal void Redo()
        {
        }

        internal void NewFile()
        {
            FileItems.Add("Untitled");
            FileSelected = FileItems.Last();
            FilePaths.Add("");
            PathSelected = FilePaths.Last();
            IsNewFile = true;
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

        internal void readJson()
        {
            JsonObject json = DrawingManager.Instance.Entities;
            string jsonString = json.ToString();
        }

        public ICommand CloseTabCommand { get; }
    }
}
