//using MathDX;
using MathGL;
//using MathUI.Utils.EngineHost;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
//using MathCore;
//using MathCore.Geom;
using System.Windows.Threading;
using System.Windows.Input;
//using MathUI.Utils;
using System.Windows;
using Microsoft.Win32;
using System.IO;
using SharpDX.Direct2D1;

namespace MathUI.ViewModels.MainWindow
{
    public class MainWindowViewModel : ViewModelBase
    {

        public ObservableCollection<string> CommandHistory { get; set; } = new ObservableCollection<string>();
        public ObservableCollection<string> CommandsList { get; set; }


        public void AddCommandToHistory(string command)
        {
            if (!string.IsNullOrWhiteSpace(command))
            {
                CommandHistory.Add(command);
            }
        }
        public void LoadCommandHistory()
        {
            // Thêm lịch sử lệnh vào CommandsList
            CommandsList = new ObservableCollection<string>(CommandHistory);
        }

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

        private ObservableCollection<string> _commandSuggestions = new ObservableCollection<string>();
        public ObservableCollection<string> CommandSuggestions
        {
            get => _commandSuggestions;
            set
            {
                _commandSuggestions = value;
                OnPropertyChanged(nameof(CommandSuggestions));
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

        // Hàm lọc các gợi ý theo từ khóa
        private void UpdateCommandSuggestions()
        {
            CommandSuggestions.Clear();
            var keyword = CommandWindow?.ToLower() ?? "";
            var suggestions = new List<string> { "line", "circle", "rectangle", "square", "polygon" }
                .Where(cmd => cmd.StartsWith(keyword))
                .ToList();
            suggestions.ForEach(cmd => CommandSuggestions.Add(cmd));
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
            var grid = mainWindow.FindName("EngineContainer");
            EngineName = "OpenGL";
            if (grid is Grid engineContainer)
            {
                //engineContainer.Children.Add(new EngineHost(typeof(GLEngine)));
                // engineContainer.Children.Add(new EngineHost(typeof(DXEngine)));

                HistoryWindow += "Engine started\n";
            }
        }

        public void TL()
        {
            //GLEngine.Instance.TLViewport();
        }

        public void TM()
        {
            //GLEngine.Instance.TMViewport();
        }

        public void TR()
        {
            //GLEngine.Instance.TRViewport();
        }

        //public void ML()
        //{
        //    GLEngine.Instance.MLViewport();
        //}

        //public void TMM()
        //{
        //    GLEngine.Instance.TMMViewport();
        //}

        //public void BMM()
        //{
        //    GLEngine.Instance.BMMViewport();
        //}

        //public void MR()
        //{
        //    GLEngine.Instance.MRViewport();
        //}

        //public void BL()
        //{
        //    GLEngine.Instance.BLViewport();
        //}

        //public void BM()
        //{
        //    GLEngine.Instance.BMViewport();
        //}

        //public void BR()
        //{
        //    GLEngine.Instance.BRViewport();
        //}

        //public void RealtimeHandle()
        //{
        //    List<Point3d> point3Ds = GLEngine.Instance.Points;
        //    if (point3Ds.Count == 0)
        //    {
        //        return;
        //    }
        //    MouseX = point3Ds.Last().X.ToString();
        //    MouseY = point3Ds.Last().Y.ToString();
        //}

        //public void ZoomViewport(MouseWheelEventArgs e)
        //{
        //    if (e.Delta > 0)
        //    {
        //        GLEngine.Instance.ZoomFactor -= 1.0f;
        //    }
        //    else
        //    {
        //        // Zoom out
        //        GLEngine.Instance.ZoomFactor += 1.0f;
        //    }

        //}

        //public async void DrawLine()
        //{
        //    PointSelection pointSelection = new();
        //    HistoryWindow += "Pick 2 points:" + "\n";
        //    List<Point3d> pnt1 = await pointSelection.getPoints(1);
        //    LineJig lineJig = new(pnt1[0]);
        //    lineJig.Commit();
        //    List<Point3d> pnt2 = await pointSelection.getPoints(1);
        //    Line line = new(pnt1[0], pnt2[0]);
        //    line.Draw();
        //    HistoryWindow += line.GetCommand() + "\n";
        //}

        //public async void DrawCircle()
        //{
        //    PointSelection pointSelection = new();
        //    HistoryWindow += "Pick 2 center:" + "\n";
        //    List<Point3d> pnt1 = await pointSelection.getPoints(1);
        //    using LineJig lineJig = new(pnt1[0]);
        //    using CircleJig circleJig = new(pnt1[0]);
        //    lineJig.Commit();
        //    circleJig.Commit();
        //    List<Point3d> pnt2 = await pointSelection.getPoints(1);
        //    Circle circle = new(pnt1[0], pnt1[0].DistanceTo(pnt2[0]));
        //    circle.Draw();
        //    HistoryWindow += circle.GetCommand() + "\n";
        //}
        //internal async void DrawRect()
        //{
        //    PointSelection pointSelection = new();
        //    HistoryWindow += "Pick 2 points:" + "\n";
        //    List<Point3d> pnt = await pointSelection.getPoints(2);
        //    Line line1 = new(new Point3d(pnt[0].X, pnt[1].Y, 0), pnt[1]);
        //    line1.Draw();

        //    Line line2 = new(pnt[1], new Point3d(pnt[1].X, pnt[0].Y, 0));
        //    line2.Draw();

        //    Line line3 = new(new Point3d(pnt[1].X, pnt[0].Y, 0), pnt[0]);
        //    line3.Draw();

        //    Line line4 = new(pnt[0], new Point3d(pnt[0].X, pnt[1].Y, 0));
        //    line4.Draw();

        //    HistoryWindow += line1.GetCommand() + "\n";
        //    HistoryWindow += line2.GetCommand() + "\n";
        //    HistoryWindow += line3.GetCommand() + "\n";
        //    HistoryWindow += line4.GetCommand() + "\n";
        //}

        //public async void DrawSquare()
        //{
        //    PointSelection pointSelection = new();
        //    HistoryWindow += "Pick 2 points:" + "\n";
        //    List<Point3d> pnt = await pointSelection.getPoints(2);
        //    TextInput textInp = new(this);
        //    string text = await textInp.GetText();
        //    if (double.TryParse(text, out var z))
        //    {
        //        Square square = new(pnt[0].ConvertTo2d(), pnt[1].ConvertTo2d(), z);
        //        square.Draw();
        //        HistoryWindow += square.GetCommand() + "\n";
        //    }
        //}

        //internal void AppendCommand()
        //{
        //    GLEngine.Instance.AppendCommand(CommandWindow);
        //    CommandWindow = "";
        //    HistoryWindow += CommandWindow + "\n";
        //}

        //internal void Undo()
        //{
        //    GLEngine.Instance.Undo();
        //}

        //internal void Redo()
        //{
        //    GLEngine.Instance.Redo();
        //}

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
            var dialog = new OpenFileDialog
            {
                FileName = "Document",
                DefaultExt = ".txt",
                Filter = "Text documents (.txt)|*.txt"
            };

            bool? result = dialog.ShowDialog();

            if (result == true)
            {
                // Open document
                string filePath = dialog.FileName;

                try
                {
                    string content = File.ReadAllText(filePath);
                    MessageBox.Show(content, "File content at path: " + filePath);

                    var topPnl = context.FindName("TopPanelElm") as UserControl;
                    if (topPnl != null)
                    {
                        var FileTabControl = topPnl.FindName("FileTabControl") as TabControl;
                        if (FileTabControl != null)
                        {
                            HistoryWindow = "";
                            var fileName = Path.GetFileName(filePath);
                            if (FilePaths.Contains(filePath))
                            {
                                FileSelected = fileName;
                                PathSelected = filePath;
                                IsNewFile = false;
                            }
                            else
                            {
                                FileItems.Add(fileName);
                                FileSelected = fileName;
                                FilePaths.Add(filePath);
                                PathSelected = filePath;
                                var cmdList = content.Split("\r\n").ToList();
                                //GLEngine.Instance.CreateSession(filePath);
                                foreach (var cmd in cmdList)
                                {
                                    //GLEngine.Instance.AppendPrompt(cmd);
                                    HistoryWindow += cmd + "\n";
                                }
                                IsNewFile = false;
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("An error occurred while reading the file:");
                    Console.WriteLine(e.Message);
                }
            }
            else
            {
                Console.WriteLine("No file was selected.");
            }
        }

        internal void SaveFile()
        {
            if (IsNewFile)
            {
                var dialog = new SaveFileDialog
                {
                    FileName = "Untitled",
                    DefaultExt = ".txt",
                    Filter = "Text documents (.txt)|*.txt"
                };

                bool? result = dialog.ShowDialog();

                string filePath = dialog.FileName;
                try
                {
                    string data = string.Empty;
                    //data = GLEngine.Instance.History.Aggregate(data, (current, cmd) => current + (cmd + "\r\n"));
                    File.WriteAllText(filePath, data);
                    Console.WriteLine("File saved successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("An error occurred while saving the file: " + ex.Message);
                }
            }
            else
            {
                try
                {
                    string data = string.Empty;
                    //data = GLEngine.Instance.History.Aggregate(data, (current, cmd) => current + (cmd + "\r\n"));
                    //File.WriteAllText(GLEngine.Instance.CurrentFilePath, data);
                    Console.WriteLine("File saved successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("An error occurred while saving the file: " + ex.Message);
                }
            }
        }

        //internal async void Select()
        //{
        //    //EntitySelection entitySelection = new();
        //    //List<Entity> entity = await entitySelection.getEntities();
        //    if (entity.Count == 0)
        //    {
        //        return;
        //    }
        //    Shape = entity[0].Shape;
        //    PositionX = entity[0].Position.X;
        //    PositionY = entity[0].Position.Y;
        //    PositionZ = entity[0].Position.Z;
        //}

        internal void CloseApp()
        {
            context.Close();
        }

        //internal async void Dist()
        //{
        //    PointSelection pointSelection = new();
        //    HistoryWindow += "Pick 2 points:" + "\n";
        //    List<Point3d> pnt = await pointSelection.getPoints(2);
        //    double dist = pnt[0].DistanceTo(pnt[1]);
        //    HistoryWindow += "Distance between 2 points: " + dist + "\n";
        //}

        //internal void ChangeTab()
        //{
        //    if (FileSelected != null)
        //    {
        //        PathSelected = FilePaths[FileItems.IndexOf(FileSelected)];
        //        GLEngine.Instance.ChangeSession(PathSelected);
        //    }
        //}

        //internal async void DrawPoly()
        //{
        //    HistoryWindow += "Total vertices:" + "\n";
        //    TextInput textInp = new(this);
        //    string text = await textInp.GetText();
        //    if (double.TryParse(text, out var z))
        //    {
        //        HistoryWindow += $"Pick {z} points:" + "\n";
        //        for (int i = 0; i < z; i++)
        //        {
        //            //HistoryWindow += "Pick vertex " + (i + 1) + "\n";
        //            PointSelection pointSelection = new();

        //            List<Point3d> pnt = await pointSelection.getPoints(1);
        //            List<Point3d> pnt1 = await pointSelection.getPoints(1);
        //            using LineJig lineJig = new(pnt1[0]);
        //            lineJig.Commit();
        //            if (i == 0)
        //            {
        //            }
        //            else
        //            {
        //                List<Point3d> pnt2 = await pointSelection.getPoints(1);
        //                Line line = new(pnt1[0], pnt2[0]);
        //                line.Draw();
        //                HistoryWindow += line.GetCommand() + "\n";
        //            }
        //        }
        //    }
        //}

        public ICommand CloseTabCommand { get; }
    }
}
