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
using Geometry;
using MathUI.Commands;
using static System.Net.Mime.MediaTypeNames;
using MathUI.Presenters;

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

        private TextBox _InputCommandWindow;
        public TextBox InputCommandWindow
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
            CloseTabCommand = new RelayCommand<string>((fileName) => true, CloseTab);
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

        public void LoadEngine(Presenters.MainWindow mainWindow)
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

        public void ZoomViewport(MouseWheelEventArgs e)
        {
        }

        public async void DrawLine()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt1 = await pointSelection.getPoints(1);
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            using MathLine line = new(pnt1[0], pnt2[0]);
            line.Draw();
        }

        public async void DrawCircle()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 center:" + "\n";
            List<Point3d> pnt1 = await pointSelection.getPoints(1);
            HistoryWindow += "Pick 2nd point on circle:" + "\n";
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            using MathCircle mathCircle = new(pnt1[0], pnt1[0].DistanceTo(pnt2[0]));
            mathCircle.Draw();
        }

        public async void DrawArc()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick start points:" + "\n";
            List<Point3d> pnt = await pointSelection.getPoints(1);
            HistoryWindow += "Pick end points:" + "\n";
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            HistoryWindow += "Pick 3rd point on circle:" + "\n";
            List<Point3d> pnt3 = await pointSelection.getPoints(1);
            using MathArc arc = new(pnt[0], pnt2[0], pnt3[0]);
            arc.Draw();
        }

        internal async void DrawPoly()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick start points: ";
            List<Point3d> pnt1 = await pointSelection.getPoints(1);
            HistoryWindow += pnt1[0].ToString() + "\n";
            HistoryWindow += "Pick end points: ";
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            HistoryWindow += pnt2[0].ToString() + "\n";
            HistoryWindow += "Bulge: ";
            TextInputPrompt textInputPrompt = new(this);
            string text = await textInputPrompt.GetText();
            if (double.TryParse(text, out double n))
            {
                CommandWindow = "";
                HistoryWindow += text.ToString() + "\n";
                using MathPolyline mathPolyline = new();
                mathPolyline.AddVertex(pnt1[0], n);
                mathPolyline.AddVertex(pnt2[0]);
                mathPolyline.Draw();
            }
            else
            {
                HistoryWindow += "Invalid input\n";
            }
            //bool isEscPressed = false;

            //KeyEventHandler escapeHandler = (s, ke) =>
            //{
            //    if (ke.Key == Key.Escape)
            //    {
            //        isEscPressed = true;
            //    }
            //};

            //try
            //{
            //    Application.Current.MainWindow.KeyDown += escapeHandler;

            //    while (!isEscPressed)
            //    {
            //        await Task.Delay(100);
            //    }
            //}
            //finally
            //{
            //    Application.Current.MainWindow.KeyDown -= escapeHandler;
            //}
        }

        internal void AppendCommand()
        {
            // DrawingManager.Instance.AppendCommand(CommandWindow);
            // CommandWindow = "";
            // HistoryWindow += CommandWindow + "\n";
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

        internal void Select()
        {
            // Shape = EntitySelection.LastId.ToString();
        }

        internal void ChangeTab()
        {
        }

        internal void readJson()
        {

        }

        internal void DrawPlane()
        {
            throw new NotImplementedException();
        }

        internal async void Extrude()
        {
            try
            {
                HistoryWindow += "Select entity:\n";
                EntitySelection entitySelection = new EntitySelection();
                List<uint> entitieId = await entitySelection.getEntities(1);
                if (entitieId[0] == 0) {
                    HistoryWindow += "Entity Not found\n";
                    return;
                }
                TextInputPrompt textInputPrompt = new(this);
                HistoryWindow += "Height:\n";
                string text = await textInputPrompt.GetText();
                if (double.TryParse(text, out double n))
                {
                    Math3dSolid math3DSolid = new();
                    math3DSolid.createExtrudeSolid(entitieId[0], n, Vector3d.ZAxis);
                    math3DSolid.Draw();
                    CommandWindow = "";
                    HistoryWindow += text.ToString() + "\n";
                }
                else
                {
                    HistoryWindow += "Invalid input\n";
                }
            }
            catch
            {
                HistoryWindow += "Invalid input\n";
            }
        }

        internal async void Sweep()
        {
            try
            {
                HistoryWindow += "Select entity:\n";
                EntitySelection entitySelection = new EntitySelection();
                List<uint> entitieId = await entitySelection.getEntities(1);
                if (entitieId[0] == 0)
                {
                    HistoryWindow += "Entity Not found\n";
                    return;
                }

                HistoryWindow += "Select path:\n";
                List<uint> pathId = await entitySelection.getEntities(1);
                if (pathId[0] == 0)
                {
                    HistoryWindow += "Path Not found\n";
                    return;
                }
                Math3dSolid math3DSolid = new();
                math3DSolid.createSweepSolid(entitieId[0], pathId[0]);
                math3DSolid.Draw();
            }
            catch
            {
                HistoryWindow += "Invalid input\n";
            }
        }

        internal async void Scale()
        {
            try
            {
                EntitySelection entitySelection = new EntitySelection();
                List<uint> entitieId = await entitySelection.getEntities(1);
                Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                TextInputPrompt textInputPrompt = new(this);
                string text = await textInputPrompt.GetText();
                if (double.TryParse(text, out double n))
                {
                    CommandWindow = "";
                    HistoryWindow += text.ToString() + "\n";
                    ent.Scale = new Scale3d(n, n, n);
                }
                else
                {
                    HistoryWindow += "Invalid input\n";
                }
            }
            catch
            {
                HistoryWindow += "Invalid input\n";
            }
        }

        internal void Trans()
        {
            throw new NotImplementedException();
        }

        internal async void Rotate()
        {
            try
            {
                EntitySelection entitySelection = new EntitySelection();
                List<uint> entitieId = await entitySelection.getEntities(1);
                Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                if (ent == null)
                {
                    HistoryWindow += "Entity Not found\n";
                    return;
                }
                PointSelection pointSelection = new PointSelection();
                List<Point3d> pnts = await pointSelection.getPoints(1);

                TextInputPrompt textInputPrompt = new(this);
                string text = await textInputPrompt.GetText();
                if (double.TryParse(text, out double n))
                {
                    CommandWindow = "";
                    HistoryWindow += text.ToString() + "\n";
                    ent.TransformBy(Matrix3d.Rotation(45, Vector3d.XAxis, pnts[0]));
                }
                else
                {
                    HistoryWindow += "Invalid input\n";
                }
            }
            catch
            {
                HistoryWindow += "Invalid input\n";
            }
        }

        internal void P2W()
        {
            throw new NotImplementedException();
        }

        internal void W2P()
        {
            throw new NotImplementedException();
        }

        internal void ChangeLanguage()
        {
            DialogLanguage dialogLanguage = new DialogLanguage();
            dialogLanguage.ShowDialog();

            if (dialogLanguage.DialogResult == true)
            {
                // GLEngine.Instance.ChangeLanguage();
            }
        }

        public ICommand CloseTabCommand { get; }
    }
}
