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
using System.Resources;
using MathUI.Resources;
using Newtonsoft.Json;
using MathUI.Models;
using System.Reflection;
using System.Text.Json;
using Newtonsoft.Json.Linq;
using System.Runtime.InteropServices.JavaScript;
using System.Windows.Media;
using System.Reflection.Emit;

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
        private ResourceManager resManager;
        private DispatcherTimer _timer;
        public Presenters.MainWindow context;
        string _MouseX;
        public bool OnInput { get; set; } = false;
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
            HistoryWindow = "";
            context = mainWindow;
            FileItems = ["Untitled"];
            FilePaths = ["Untitled"];
            FileSelected = "Untitled";
            PathSelected = "Untitled";
            IsNewFile = true;
            CloseTabCommand = new RelayCommand<string>((fileName) => true, CloseTab);
            SelectCmd = new RelayCommand<Window>((exp) => true, Select);
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
            DrawingManager.Instance.TLViewport();
        }

        public void TM()
        {
            DrawingManager.Instance.TMViewport();
        }

        public void TR()
        {
            DrawingManager.Instance.TRViewport();
        }

        public void ML()
        {
            DrawingManager.Instance.MLViewport();
        }

        public void TMM()
        {
            DrawingManager.Instance.TMMViewport();
        }

        public void BMM()
        {
            DrawingManager.Instance.BMMViewport();
        }

        public void MR()
        {
            DrawingManager.Instance.MRViewport();
        }

        public void BL()
        {
            DrawingManager.Instance.BLViewport();
        }

        public void BM()
        {
            DrawingManager.Instance.BMViewport();
        }

        public void BR()
        {
            DrawingManager.Instance.BRViewport();
        }

        [CommandMethod("LINE")]
        public async void DrawLine()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt1 = await pointSelection.getPoints(1);
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            using MathLine line = new(pnt1[0], pnt2[0]);
            line.Draw();
        }

        [CommandMethod("CIRCLE")]
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

        [CommandMethod("ARC")]
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

        [CommandMethod("POLYLINE")]
        public async void DrawPoly()
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

        internal async void AppendCommand()
        {
            if (OnInput) return;
            if (CommandRegistry.IsACmd(CommandWindow))
            {
               await CommandRegistry.InvokeAsync(CommandWindow);
                CommandWindow = "";
            }
            else
            {
                HistoryWindow += CommandWindow + "\n";
                CommandWindow = "";
            }
        }

        [CommandMethod("UNDO")]
        internal void Undo()
        {
        }

        [CommandMethod("REDO")]
        internal void Redo()
        {
        }

        [CommandMethod("NEW")]
        internal void NewFile()
        {
            FileItems.Add("Untitled");
            DrawingManager.Instance.createSession("Untitled");

            FileSelected = FileItems.Last();
            FilePaths.Add("");
            PathSelected = FilePaths.Last();
            IsNewFile = true;
        }

        [CommandMethod("OPEN")]
        internal void OpenFile()
        {
            var dialog = new OpenFileDialog
            {
                FileName = "Document",
                DefaultExt = ".json",
                Filter = "JSON files (.json)|*.json"
            };

            bool? result = dialog.ShowDialog();

            if (result == true)
            {
                // Open document
                string filePath = dialog.FileName;

                try
                {
                    string content = File.ReadAllText(filePath);

                    // Deserialize JSON content using Newtonsoft.Json
                    var jsonObject = JsonConvert.DeserializeObject<Dictionary<string, object>>(content);
                    if (jsonObject == null)
                    {
                        HistoryWindow += "The JSON content is not valid.\n";
                        return;
                    }
                    if (jsonObject.TryGetValue("entities", out var entities))
                    {
                        if (entities is JArray jsonArray)
                        {
                            var alo = jsonArray.ToObject<List<string>>();
                            if (alo == null)
                            {
                                HistoryWindow += "The 'entities' key is not a valid JSON array.\n";
                                return;
                            }
                            foreach (var item in alo)
                            {
                                uint id = Entity.FromJson(item);
                                //Entity entity = DrawingManager.Instance.getEntityById(id);
                                //entity.Draw();
                                HistoryWindow += item + "\n";
                            }
                        }
                        else
                        {
                            HistoryWindow += "The 'entities' key is not a valid JSON array.\n";
                        }
                    }
                    else
                    {
                        HistoryWindow += "The 'entities' key does not exist in the JSON content." + "\n";
                    }
                }
                catch (Exception e)
                {
                    HistoryWindow += "An error occurred while reading the file:" + "\n";
                    HistoryWindow += e.Message + "\n";
                }
            }
            else
            {
                HistoryWindow += "No file was selected." + "\n";
            }
        }

        [CommandMethod("SAVE")]
        internal void SaveFile()
        {
            if (IsNewFile)
            {
                var dialog = new SaveFileDialog
                {
                    FileName = "Untitled",
                    DefaultExt = ".json",
                    Filter = "JSON files (.json)|*.json"
                };

                bool? result = dialog.ShowDialog();

                if (result == true)
                {
                    string filePath = dialog.FileName;

                    try
                    {
                        List<string> entityJson = DrawingManager.Instance.GetAllEntityJsons();
                        var dataToSave = new
                        {
                            entities = entityJson
                        };

                        var jsonData = JsonConvert.SerializeObject(dataToSave, Formatting.Indented);

                        File.WriteAllText(filePath, jsonData);
                        HistoryWindow += "File saved successfully.\n";
                    }
                    catch (Exception ex)
                    {
                        HistoryWindow += "An error occurred while saving the file: " + ex.Message + "\n";
                    }
                }
            }
            else
            {
                try
                {
                    List<string> entityJson = DrawingManager.Instance.GetAllEntityJsons();
                    var dataToSave = new
                    {
                        entities = entityJson
                    };

                    var jsonData = JsonConvert.SerializeObject(dataToSave, Formatting.Indented);

                    File.WriteAllText(DrawingManager.Instance.CurrentFilePath, jsonData);
                    HistoryWindow += "File saved successfully.\n";
                }
                catch (Exception ex)
                {
                    HistoryWindow += "An error occurred while saving the file: " + ex.Message + "\n";
                }
            }
        }
        private void AddTextBoxToGrid(Grid grid, string label, string value, JObject json, int row, int column)
        {
            TextBox textBox = new TextBox
            {
                Text = value,
                Margin = new Thickness(5),
                Tag = label
            };

            textBox.KeyDown += (sender, e) =>
            {
                if (e.Key == Key.Enter)
                {
                    var updatedTextBox = (TextBox)sender;
                    string updatedValue = updatedTextBox.Text;
                    if (label.Contains('.'))
                    {
                        var labels = label.Split('.');
                        if (json.ContainsKey(labels[0]))
                        {
                            if (double.TryParse(updatedValue, out double doubleValue))
                            {
                                json[labels[0]][labels[1]] = doubleValue;
                            }
                            else
                            {
                                json[labels[0]][labels[1]] = updatedValue;
                            }
                        }
                    }
                    else
                    {
                        if (double.TryParse(updatedValue, out double doubleValue))
                        {
                            json[label] = doubleValue;
                        }
                        else
                        {
                            json[label] = updatedValue;
                            // Handle invalid double conversion
                        }
                    }
                    var jsonData = JsonConvert.SerializeObject(json, Formatting.Indented);
                    selectEntity.FromJson2(jsonData);
                }
            };

            //textBox.TextChanged += (sender, e) =>
            //{
            //};

            Grid.SetRow(textBox, row);
            Grid.SetColumn(textBox, column);
            grid.Children.Add(textBox);
        }

        public void CreateUI(StackPanel parentPanel, List<string> labels, List<string> values, List<bool> isReadOnly, JObject json)
        {
            if (labels.Count != values.Count)
                throw new ArgumentException("Labels and values must have the same number of elements.");

            Expander expander = new Expander
            {
                Header = "General",
                Foreground = Brushes.White,
                Background = new SolidColorBrush(Color.FromRgb(68, 68, 68)),
                Margin = new Thickness(0, 0, 0, 10),
                IsExpanded = true
            };

            Grid grid = new Grid
            {
                Margin = new Thickness(5)
            };

            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto, SharedSizeGroup = "Column1" });
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(1, GridUnitType.Star), SharedSizeGroup = "Column2" });

            for (int i = 0; i < labels.Count; i++)
            {
                grid.RowDefinitions.Add(new RowDefinition { Height = GridLength.Auto });

                AddTextBlockToGrid(grid, labels[i], i, 0, Brushes.White);
                if (isReadOnly[i])
                    AddTextBlockToGrid(grid, values[i], i, 1, Brushes.White);
                else
                    AddTextBoxToGrid(grid, labels[i], values[i], json, i, 1);
            }
            expander.Content = grid;
            parentPanel.Children.Add(expander);
        }

        private void AddTextBlockToGrid(Grid grid, string text, int row, int column, Brush foreground)
        {
            TextBlock textBlock = new TextBlock
            {
                Text = text,
                Margin = new Thickness(5),
                Foreground = foreground
            };
            Grid.SetRow(textBlock, row);
            Grid.SetColumn(textBlock, column);
            grid.Children.Add(textBlock);
        }

        private Entity selectEntity;

        [CommandMethod("SELECT")]
        internal async void Select(Window window)
        {
            Presenters.LeftSide? leftSide = window.FindName("leftSide") as Presenters.LeftSide;
            StackPanel? stack = leftSide?.FindName("InputPanel") as StackPanel;
            if (stack == null) return;
            HistoryWindow += "Select entity:\n";
            EntitySelection entitySelection = new();
            List<uint> entitieId = await entitySelection.getEntities(1);
            if (entitieId[0] == 0)
            {
                HistoryWindow += "Entity Not found\n";
                return;
            }
            selectEntity = DrawingManager.Instance.getEntityById(entitieId[0]);
            if (selectEntity == null)
            {
                HistoryWindow += "Invalid entity id\n";
                return;
            }
            string jsonString = selectEntity.ToJson();
            var jsonObject = JObject.Parse(jsonString);
            string type = jsonObject["type"].ToString();

            switch (type)
            {
                case "OdMathLine":
                    {
                        List<string> labels = ["type", "Start X", "Start Y", "Start Z", "End X", "End Y", "End Z"];
                        List<bool> isReadOnly = [true, false, false, false, false, false, false];
                        List<string> values = ["OdMathLine", jsonObject["start"]["x"].ToString(), jsonObject["start"]["y"].ToString(), jsonObject["start"]["z"].ToString(), jsonObject["end"]["x"].ToString(), jsonObject["end"]["y"].ToString(), jsonObject["end"]["z"].ToString()];
                        CreateUI(stack, labels, values, isReadOnly, jsonObject);
                        break;
                    }
                case "OdMathCircle":
                    {
                        List<string> labels = ["type", "center.x", "center.y", "center.z", "radius"];
                        List<bool> isReadOnly = [true, false, false, false, false, false, false];
                        List<string> values = ["OdMathCircle", jsonObject["center"]["x"].ToString(), jsonObject["center"]["y"].ToString(), jsonObject["center"]["z"].ToString(), jsonObject["radius"].ToString()];
                        CreateUI(stack, labels, values, isReadOnly, jsonObject);
                        break;
                    }
                case "OdMathArc":
                    {
                        List<string> labels = ["type", "Start X", "Start Y", "Start Z", "End X", "End Y", "End Z", "Center X", "Center Y", "Center Z", "Radius"];
                        List<bool> isReadOnly = [true, false, false, false, false, false, false];
                        List<string> values = ["OdMathArc", jsonObject["start"]["x"].ToString(), jsonObject["start"]["y"].ToString(), jsonObject["start"]["z"].ToString(), jsonObject["end"]["x"].ToString(), jsonObject["end"]["y"].ToString(), jsonObject["end"]["z"].ToString(), jsonObject["center"]["x"].ToString(), jsonObject["center"]["y"].ToString(), jsonObject["center"]["z"].ToString(), jsonObject["radius"].ToString()];
                        CreateUI(stack, labels, values, isReadOnly, jsonObject);
                        break;
                    }
                case "OdMathPolyline":
                    {
                        List<string> labels = ["type", "Vertexes"];
                        List<bool> isReadOnly = [true, false];
                        List<string> values = ["OdMathPolyline", jsonObject["vertexes"].ToString()];
                        CreateUI(stack, labels, values, isReadOnly, jsonObject);
                        break;
                    }
                case "OdMathSolid":
                {
                    List<string> labels = ["type", "Vertexes"];
                    List<bool> isReadOnly = [true, false];
                    List<string> values = ["OdMathSolid", jsonObject["vertexes"].ToString()];
                    CreateUI(stack, labels, values, isReadOnly, jsonObject);
                    break;
                }
                case "OdMathPlane":
                {
                    List<string> labels = ["type", "origin.x", "origin.y", "origin.z", "normal.x", "normal.y", "normal.z"];
                    List<bool> isReadOnly = [true, false, false, false, false, false, false];
                    List<string> values = ["OdMathPlane", 
                        jsonObject["origin"]["x"].ToString(), jsonObject["origin"]["y"].ToString(), jsonObject["origin"]["z"].ToString(),
                        jsonObject["normal"]["x"].ToString(), jsonObject["normal"]["y"].ToString(), jsonObject["normal"]["z"].ToString()
                        ];
                    CreateUI(stack, labels, values, isReadOnly, jsonObject);
                    break;
                }
                default:
                    break;
            }
        }

        internal void ChangeTab()
        {
            if (FileSelected != null)
            {
                PathSelected = FilePaths[FileItems.IndexOf(FileSelected)];
                //DrawingManager.Instance.ChangeSession(PathSelected);
            }
        }

        internal void readJson()
        {

        }

        [CommandMethod("PLANE")]
        internal async void DrawPlane()
        {
            HistoryWindow += "Origin:\n";
            TextInputPrompt textInputPrompt = new(this);
            string text = await textInputPrompt.GetText();
            List<string> values = [.. text.Split(' ')];
            List<double> orgn = [];
            for (int i = 0; i < values.Count; i++)
            {
                if (double.TryParse(values[i], out double n))
                {
                    orgn.Add(n);
                }
                else
                {
                    HistoryWindow += "Invalid input\n";
                    return;
                }    
            }

            HistoryWindow += "Normal:\n";
            text = await textInputPrompt.GetText();
            values = text.Split(' ').ToList();
            List<double> nrml = [];
            for (int i = 0; i < values.Count; i++)
            {
                if (double.TryParse(values[i], out double n))
                {
                    nrml.Add(n);
                }
                else
                {
                    HistoryWindow += "Invalid input\n";
                    return;
                }
            }

            using MathPlane mathPlane = new(new Point3d(orgn[0], orgn[1], orgn[2]), new Vector3d(nrml[0], nrml[1], nrml[2]));
            mathPlane.Draw();
        }

        [CommandMethod("EXTRUDE")]
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
                HistoryWindow += "Height:\n";
                TextInputPrompt textInputPrompt = new(this);
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

        [CommandMethod("SWEEP")]
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

        [CommandMethod("SCALE")]
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

        [CommandMethod("TRANS")]
        internal void Trans()
        {
            throw new NotImplementedException();
        }

        [CommandMethod("ROTATE")]
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

        [CommandMethod("P2W")]
        internal void P2W()
        {
            throw new NotImplementedException();
        }

        [CommandMethod("W2P")]
        internal void W2P()
        {
            throw new NotImplementedException();
        }

        [CommandMethod("LANG")]
        internal void ChangeLanguage()
        {
            DialogLanguage dialogLanguage = new DialogLanguage();
            dialogLanguage.ShowDialog();
        }

        [CommandMethod("REGEN")]
        internal void RegenViewModel()
        {
            string json = DrawingManager.Instance.EntityJson;
            if (json != "")
            {
                RegenLeftPanel(json);
            }
        }

        private void RegenLeftPanel(string json)
        {
            if (string.IsNullOrEmpty(json))
            {
                return;
            }

            dynamic? jsonObject = JsonConvert.DeserializeObject(json);
            if (jsonObject != null)
            {
                EntityModel? model = EntityModel.FromJson(json);
                Shape = model?.Type ?? "";
                PositionX = model?.Position.X ?? 0;
                PositionY = model?.Position.Y ?? 0;
                PositionZ = model?.Position.Z ?? 0;
            }

        }

        [STAThread]
        [CommandMethod("NETLOAD")]
        public void NetLoad()
        {
            OpenFileDialog openFileDialog = new()
            {
                Title = "Chọn tệp cần tải",
                Filter = "Tất cả các tệp (*.*)|*.*|File Text (*.txt)|*.txt|File DLL (*.dll)|*.dll",
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)
            };
            openFileDialog.Filter = "DLL Files (*.dll)|*.dll";
            if (openFileDialog.ShowDialog() == true)
            {
                string selectedFile = openFileDialog.FileName;
                try
                {
                    Assembly assembly = Assembly.LoadFrom(selectedFile);
                    CommandRegistry.DiscoverAndRegisterExternalCommands(this, assembly);
                    HistoryWindow += $"Loaded - {assembly.FullName}\n";
                }
                catch (Exception ex)
                {
                    HistoryWindow += $"Error - {ex.Message}\n";
                }
            }
        }
        public static List<Assembly> ExternalAssembly = [];
        public ICommand CloseTabCommand { get; }
        public ICommand SelectCmd { get; }
    }
}
