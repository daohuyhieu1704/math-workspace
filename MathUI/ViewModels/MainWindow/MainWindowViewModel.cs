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
using MathUI.Utils;

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
        private readonly UndoRedoManager undoRedoManager = new();
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

        private ObservableCollection<FileModel> _fileStorage;

        public ObservableCollection<FileModel> FileStorage
        {
            get => _fileStorage;
            set
            {
                Set(ref _fileStorage, value);
                OnPropertyChanged(nameof(FileStorage));
            }
        }

        private int _fileSelectedIdx;
        public int FileSelectedIdx
        {
            get => _fileSelectedIdx;
            set
            {
                Set(ref _fileSelectedIdx, value);
                OnPropertyChanged(nameof(FileSelectedIdx));
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
            IsNewFile = true;
            CloseTabCommand = new RelayCommand<string>((fileName) => true, CloseTab);
            SelectCmd = new RelayCommand<Window>((exp) => true, Select);
        }

        private void CloseTab(string fileName)
        {
            for (int i = 0; i < FileStorage.Count; i++)
            {
                if (FileStorage[i].FilePath == fileName)
                {
                    FileStorage.RemoveAt(i);
                    FileSelectedIdx = 0;
                    break;
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
            //uint lineId = line.Id;
            //var parameters = new object[] { lineId, pnt1[0], pnt2[0] };
            //undoRedoManager.ExecuteCommand(new CommandAction(
            //    commandName: "LINE",
            //    parameters: parameters,
            //    undoAction: () =>
            //    {
            //        uint id = (uint)parameters[0];
            //        DrawingManager.Instance.removeEntity(id);
            //    },
            //    redoAction: () =>
            //    {
            //        Point3d redoPnt1 = (Point3d)parameters[1];
            //        Point3d redoPnt2 = (Point3d)parameters[2];
            //        using MathLine redoLine = new(redoPnt1, redoPnt2);
            //        redoLine.Draw();
            //    }
            //));
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
            uint circleId = mathCircle.Draw();

            //var parameters = new object[] { circleId, pnt1[0], pnt2[0] };

            //undoRedoManager.ExecuteCommand(new CommandAction(
            //    commandName: "CIRCLE",
            //    parameters: parameters,
            //    undoAction: () =>
            //    {
            //        uint id = (uint)parameters[0];
            //        DrawingManager.Instance.removeEntity(id);
            //    },
            //    redoAction: () =>
            //    {
            //        Point3d redoPnt1 = (Point3d)parameters[1];
            //        Point3d redoPnt2 = (Point3d)parameters[2];
            //        using MathCircle redoCircle = new(redoPnt1, redoPnt1.DistanceTo(redoPnt2));
            //        redoCircle.Draw();
            //    }
            //));
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
            uint arcId = arc.Draw();

            // var parameters = new object[] { arcId, pnt[0], pnt2[0], pnt3[0] };

            //undoRedoManager.ExecuteCommand(new CommandAction(
            //    commandName: "ARC",
            //    parameters: parameters,
            //    undoAction: () =>
            //    {
            //        uint id = (uint)parameters[0];
            //        DrawingManager.Instance.removeEntity(id);
            //    },
            //    redoAction: () =>
            //    {
            //        Point3d redoPnt1 = (Point3d)parameters[1];
            //        Point3d redoPnt2 = (Point3d)parameters[2];
            //        Point3d redoPnt3 = (Point3d)parameters[3];
            //        using MathArc redoArc = new(redoPnt1, redoPnt2, redoPnt3);
            //        redoArc.Draw();
            //    }
            //));
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
                uint polylineId = mathPolyline.Draw();

                // var parameters = new object[] { polylineId, pnt1[0], pnt2[0], n };

                //undoRedoManager.ExecuteCommand(new CommandAction(
                //    commandName: "POLYLINE",
                //    parameters: parameters,
                //    undoAction: () =>
                //    {
                //        uint id = (uint)parameters[0];
                //        DrawingManager.Instance.removeEntity(id);
                //    },
                //    redoAction: () =>
                //    {
                //        Point3d redoPnt1 = (Point3d)parameters[1];
                //        Point3d redoPnt2 = (Point3d)parameters[2];
                //        double redoBulge = (double)parameters[3];
                //        using MathPolyline redoPolyline = new();
                //        redoPolyline.AddVertex(redoPnt1, redoBulge);
                //        redoPolyline.AddVertex(redoPnt2);
                //        redoPolyline.Draw();
                //    }
                //));
            }
            else
            {
                HistoryWindow += "Invalid input\n";
            }
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
            undoRedoManager.Undo();
        }

        [CommandMethod("REDO")]
        internal void Redo()
        {
            undoRedoManager.Redo();
        }

        [CommandMethod("NEW")]
        internal void NewFile()
        {
            DrawingManager.Instance.createSession("Untitled");
            FileStorage.Add(new FileModel(DrawingManager.Instance.CurrentSessionId, "Untitled"));
            FileSelectedIdx = FileStorage.Count - 1;
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
                //if (FileStorage.Find(???))
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
            //textBox.GotFocus += (sender, e) =>
            //{
            //    selectEntity = entities.FirstOrDefault(x => x.Key == selectEntity.Id);
            //};
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

            Expander expander = new()
            {
                Foreground = Brushes.White,
                Background = new SolidColorBrush(Color.FromRgb(68, 68, 68)),
                Margin = new Thickness(0, 0, 0, 10),
                IsExpanded = true
            };

            Grid headerGrid = new Grid();
            headerGrid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(1, GridUnitType.Star) });
            headerGrid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });

            TextBlock headerLabel = new TextBlock
            {
                Text = selectEntity.Id.ToString(),
                Foreground = Brushes.White,
                VerticalAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(headerLabel, 0);
            headerGrid.Children.Add(headerLabel);
            Button deleteButton = new Button
            {
                Content = "X",
                Foreground = Brushes.White,
                Background = new SolidColorBrush(Color.FromRgb(200, 50, 50)),
                Padding = new Thickness(5),
                Margin = new Thickness(5, 0, 0, 0),
                VerticalAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(deleteButton, 1);
            headerGrid.Children.Add(deleteButton);

            deleteButton.Click += (s, e) =>
            {
                parentPanel.Children.Remove(expander);
            };
            expander.Header = headerGrid;

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
            parentPanel.Children.Clear();
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
                        List<string> labels = ["type", "startPnt.x", "startPnt.y", "startPnt.z", "endPnt.x", "endPnt.y", "endPnt.z"];
                        List<bool> isReadOnly = [true, false, false, false, false, false, false];
                        List<string> values = ["OdMathLine", jsonObject["startPnt"]["x"].ToString(), jsonObject["startPnt"]["y"].ToString(), jsonObject["startPnt"]["z"].ToString(),
                            jsonObject["endPnt"]["x"].ToString(), jsonObject["endPnt"]["y"].ToString(), jsonObject["endPnt"]["z"].ToString()];
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
                        List<string> labels = ["type", "startPnt.x", "startPnt.y", "startPnt.z", "bulge"];
                        List<bool> isReadOnly = [true, false, false, false, false];
                        List<string> values = ["OdMathArc", 
                            jsonObject["startPnt"]["x"].ToString(), jsonObject["startPnt"]["y"].ToString(), jsonObject["startPnt"]["z"].ToString(), 
                            jsonObject["bulge"].ToString(),
                            ];
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
            if (FileStorage.Count != 0)
            {
                DrawingManager.Instance.changeSession(FileStorage[FileSelectedIdx].FileId);
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
            uint planeId = mathPlane.Draw();

            // var parameters = new object[] { planeId, orgn, nrml };

            //undoRedoManager.ExecuteCommand(new CommandAction(
            //    commandName: "PLANE",
            //    parameters: parameters,
            //    undoAction: () =>
            //    {
            //        uint id = (uint)parameters[0];
            //        DrawingManager.Instance.removeEntity(id);
            //    },
            //    redoAction: () =>
            //    {
            //        Point3d redoOrgn = new Point3d(orgn[0], orgn[1], orgn[2]);
            //        Vector3d redoNrml = new Vector3d(nrml[0], nrml[1], nrml[2]);
            //        using MathPlane redoPlane = new(redoOrgn, redoNrml);
            //        redoPlane.Draw();
            //    }
            //));
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
                    uint solidId = math3DSolid.Draw();

                    var parameters = new object[] { solidId, entitieId[0], n };

                    CommandWindow = "";
                    HistoryWindow += text.ToString() + "\n";

                    //undoRedoManager.ExecuteCommand(new CommandAction(
                    //    commandName: "EXTRUDE",
                    //    parameters: parameters,
                    //    undoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        DrawingManager.Instance.removeEntity(id);
                    //    },
                    //    redoAction: () =>
                    //    {
                    //        uint id2d = (uint)parameters[1];
                    //        double redoHeight = (double)parameters[2];
                    //        using Math3dSolid redoSolid = new();
                    //        redoSolid.createExtrudeSolid(id2d, redoHeight, Vector3d.ZAxis);
                    //        redoSolid.Draw();
                    //    }
                    //));
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
                uint solidId = math3DSolid.Draw();

                var parameters = new object[] { solidId, entitieId[0], pathId[0] };

                //undoRedoManager.ExecuteCommand(new CommandAction(
                //    commandName: "SWEEP",
                //    parameters: parameters,
                //    undoAction: () =>
                //    {
                //        uint id = (uint)parameters[0];
                //        DrawingManager.Instance.removeEntity(id);
                //    },
                //    redoAction: () =>
                //    {
                //        uint id2d = (uint)parameters[1];
                //        uint idPath = (uint)parameters[2];
                //        using Math3dSolid redoSolid = new();
                //        redoSolid.createSweepSolid(id2d, idPath);
                //        redoSolid.Draw();
                //    }
                //));
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

                    uint entityId = ent.Id;
                    var parameters = new object[] { entityId, ent.Scale };

                    //undoRedoManager.ExecuteCommand(new CommandAction(
                    //    commandName: "SCALE",
                    //    parameters: parameters,
                    //    undoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d oldScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / oldScale.XFactor, 1 / oldScale.YFactor, 1 / oldScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    },
                    //    redoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d redoScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / redoScale.XFactor, 1 / redoScale.YFactor, 1 / redoScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    }
                    //));
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
        internal async void Trans()
        {
            try
            {
                EntitySelection entitySelection = new();
                List<uint> entitieId = await entitySelection.getEntities(1);
                Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                if (ent == null)
                {
                    HistoryWindow += "Select fail\n";
                    return;
                }
                PointSelection pointSelection = new PointSelection();
                List<Point3d> pnts = await pointSelection.getPoints(1);

                TextInputPrompt textInputPrompt = new(this);
                string text = await textInputPrompt.GetText();
                List<string> values = text.Split(' ').ToList();
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
                Matrix3d matrix3D = Matrix3d.Translate(new Vector3d(orgn[0], orgn[1], orgn[2]));
                ent.TransformBy(matrix3D);

                uint entityId = ent.Id;
                var parameters = new object[] { entityId, matrix3D };

                //undoRedoManager.ExecuteCommand(new CommandAction(
                //    commandName: "TRANS",
                //    parameters: parameters,
                //    undoAction: () =>
                //    {
                //        uint id = (uint)parameters[0];
                //        Matrix3d oldMatrix = (Matrix3d)parameters[1];
                //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                //        redoEntity.TransformBy(oldMatrix.Inverse());
                //    },
                //    redoAction: () =>
                //    {
                //        uint id = (uint)parameters[0];
                //        Matrix3d redoMatrix = (Matrix3d)parameters[1];
                //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                //        redoEntity.TransformBy(redoMatrix.Inverse());
                //    }
                //));
            }
            catch
            {
                HistoryWindow += "Invalid input\n";
            }
        }

        [CommandMethod("ROTATE")]
        internal async void Rotate()
        {
            try
            {
                HistoryWindow += "Select entity:\n";
                EntitySelection entitySelection = new EntitySelection();
                List<uint> entitieId = await entitySelection.getEntities(1);
                Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                if (ent == null)
                {
                    HistoryWindow += "Select fail\n";
                    return;
                }


                HistoryWindow += "Pick base point:\n";
                PointSelection pointSelection = new();
                TextInputPrompt textPntPrompt = new(this);
                Task<List<Point3d>> pointTask = pointSelection.getPoints(1);
                Task<string> textTask = textPntPrompt.GetText();

                Task completedTask = await Task.WhenAny(pointTask, textTask);

                List<Point3d> pnts = [];
                string text = string.Empty;

                if (completedTask == pointTask)
                {
                    pnts = await pointTask;
                }
                else if (completedTask == textTask)
                {
                    text = await textTask; // Đảm bảo lấy kết quả nếu đây là task hoàn thành
                    List<string> values = text.Split(' ').ToList();
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
                    pnts.Add(new Point3d(orgn[0], orgn[1], orgn[2]));
                }

                HistoryWindow += "Pick rotate vector:\n";
                TextInputPrompt textPntPrompt2 = new(this);
                string textTask2 = await textPntPrompt2.GetText();
                List<string> values2 = textTask2.Split(' ').ToList();
                List<double> orgn2 = [];
                for (int i = 0; i < values2.Count; i++)
                {
                    if (double.TryParse(values2[i], out double n2))
                    {
                        orgn2.Add(n2);
                    }
                    else
                    {
                        HistoryWindow += "Invalid input\n";
                        return;
                    }
                }
                Vector3d vector = new(orgn2[0], orgn2[1], orgn2[2]);

                HistoryWindow += "Angle:\n";
                TextInputPrompt textInputPrompt2 = new(this);
                string text2 = await textInputPrompt2.GetText();
                if (double.TryParse(text2, out double n3))
                {
                    HistoryWindow += text2.ToString() + "\n";
                    double rad = n3 * Math.PI / 180;
                    //Matrix3d rot = Matrix3d.Rotation(rad, Vector3d.XAxis, pnts[0]);
                    ent.RotateBy(vector, rad, pnts[0]);

                    uint entityId = ent.Id;
                    //var parameters = new object[] { entityId, rot };

                    //undoRedoManager.ExecuteCommand(new CommandAction(
                    //    commandName: "ROTATE",
                    //    parameters: parameters,
                    //    undoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Matrix3d rotMat = (Matrix3d)parameters[1];
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.TransformBy(rotMat.Inverse());
                    //    },
                    //    redoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Matrix3d rotMat = (Matrix3d)parameters[1];
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.TransformBy(rotMat.Inverse());
                    //    }
                    //));
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
        internal async void P2W()
        {
            try
            {
                EntitySelection entitySelection = new ();
                List<uint> entitieId = await entitySelection.getEntities(1);
                if (entitieId[0] != 0)
                {
                    Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                    EntitySelection planeSelection = new();
                    List<uint> planeId = await planeSelection.getEntities(1);
                    MathPlane plane = (MathPlane)DrawingManager.Instance.getEntityById<MathPlane>(planeId[0]);
                    Matrix3d matrix3 = Matrix3d.PlaneToWorld(plane.Origin, plane.Normal);
                    ent.TransformBy(matrix3);

                    //undoRedoManager.ExecuteCommand(new CommandAction(
                    //    commandName: "P2W",
                    //    parameters: parameters,
                    //    undoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d oldScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / oldScale.XFactor, 1 / oldScale.YFactor, 1 / oldScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    },
                    //    redoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d redoScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / redoScale.XFactor, 1 / redoScale.YFactor, 1 / redoScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    }
                    //));
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

        [CommandMethod("W2P")]
        internal async void W2P()
        {
            try
            {
                EntitySelection entitySelection = new();
                List<uint> entitieId = await entitySelection.getEntities(1);
                if (entitieId[0] != 0)
                {
                    Entity ent = DrawingManager.Instance.getEntityById(entitieId[0]);
                    EntitySelection planeSelection = new();
                    List<uint> planeId = await planeSelection.getEntities(1);
                    MathPlane plane = (MathPlane)DrawingManager.Instance.getEntityById<MathPlane>(planeId[0]);
                    Matrix3d matrix3 = Matrix3d.WorldToPlane(plane.Origin, plane.Normal);
                    ent.TransformBy(matrix3);

                    //undoRedoManager.ExecuteCommand(new CommandAction(
                    //    commandName: "P2W",
                    //    parameters: parameters,
                    //    undoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d oldScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / oldScale.XFactor, 1 / oldScale.YFactor, 1 / oldScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    },
                    //    redoAction: () =>
                    //    {
                    //        uint id = (uint)parameters[0];
                    //        Scale3d redoScale = (Scale3d)parameters[1];
                    //        Scale3d scale = new(1 / redoScale.XFactor, 1 / redoScale.YFactor, 1 / redoScale.ZFactor);
                    //        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                    //        redoEntity.Scale = scale;
                    //    }
                    //));
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

        [CommandMethod("LANG")]
        internal static void ChangeLanguage()
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
