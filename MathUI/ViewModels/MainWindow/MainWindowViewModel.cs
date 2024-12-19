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
using static MathUI.ViewModels.ViewModelBase;
using System.DirectoryServices;

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


        static private int anonSessionIdx = 0;

        private static string AnonToStr
        {
            get
            {
                string retVal = $"Untitled{(anonSessionIdx == 0 ? "" : $"({anonSessionIdx})")}.json";
                anonSessionIdx++;
                return retVal;
            }
        }

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

        private ObservableCollection<string> _fileStorageName;

        public ObservableCollection<string> FileStorageName
        {
            get => _fileStorageName;
            set
            {
                Set(ref _fileStorageName, value);
                OnPropertyChanged(nameof(FileStorageName));
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

        internal void RemoveSelectedObject()
        {
            if (FileSelected != null)
            {
                //// Xóa đối tượng đã chọn khỏi danh sách
                //FileStorage.Remove(FileSelected);

                //// Cập nhật FileSelected và FileSelectedIdx
                //FileSelected = FileStorage.FirstOrDefault(); // Nếu còn đối tượng, lấy đối tượng đầu tiên
                //FileSelectedIdx = FileStorage.IndexOf(FileSelected!); // Cập nhật chỉ mục của đối tượng đã chọn
            }
            else
            {
                MessageBox.Show("No object selected to delete.");
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
            string anonStr = AnonToStr;
            DrawingManager.Instance.createSession(anonStr);
            FileStorage = [new FileModel(DrawingManager.Instance.CurrentSessionId, anonStr)];
            FileStorageName = [anonStr];
            FileSelected = anonStr;
        }

        private void CloseTab(string fileName)
        {
            for (int i = 0; i < FileStorageName.Count; i++)
            {
                if (FileStorageName[i] == fileName)
                {
                    FileStorageName.RemoveAt(i);
                    FileStorage.RemoveAt(i);
                    FileSelected = FileStorageName[0];
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
            try
            {
                PointSelection pointSelection = new();
                HistoryWindow += "Pick 2 points:" + "\n";

                // Attempt to get the first point
                List<Point3d> pnt1 = await pointSelection.getPoints(1);
                if (pnt1 == null || pnt1.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the first point.\n";
                    return;
                }

                // Attempt to get the second point
                List<Point3d> pnt2 = await pointSelection.getPoints(1);
                if (pnt2 == null || pnt2.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the second point.\n";
                    return;
                }

                // Ensure points are valid
                if (pnt1[0].IsEqual(pnt2[0]))
                {
                    HistoryWindow += "Error: Invalid points provided.\n";
                    return;
                }

                // Draw the line
                using MathLine line = new(pnt1[0], pnt2[0]);
                line.Draw();

                uint lineId = line.Id;
                var parameters = new object[] { lineId, pnt1[0], pnt2[0] };

                //// Register the undo/redo action
                //undoRedoManager.ExecuteCommand(new CommandAction(
                //    commandName: "LINE",
                //    parameters: parameters,
                //    undoAction: () =>
                //    {
                //        try
                //        {
                //            uint id = (uint)parameters[0];
                //            DrawingManager.Instance.removeEntity(id);
                //        }
                //        catch (Exception ex)
                //        {
                //            HistoryWindow += "Error during undo: " + ex.Message + "\n";
                //        }
                //    },
                //    redoAction: () =>
                //    {
                //        try
                //        {
                //            Point3d redoPnt1 = (Point3d)parameters[1];
                //            Point3d redoPnt2 = (Point3d)parameters[2];
                //            using MathLine redoLine = new(redoPnt1, redoPnt2);
                //            redoLine.Draw();
                //        }
                //        catch (Exception ex)
                //        {
                //            HistoryWindow += "Error during redo: " + ex.Message + "\n";
                //        }
                //    }
                //));
            }
            catch (Exception ex)
            {
                // Log any unexpected exceptions
                HistoryWindow += "Unexpected error: " + ex.Message + "\n";
            }
        }


        [CommandMethod("CIRCLE")]
        public async void DrawCircle()
        {
            try
            {
                PointSelection pointSelection = new();
                HistoryWindow += "Pick center point:" + "\n";

                // Attempt to get the center point
                List<Point3d> pnt1 = await pointSelection.getPoints(1);
                if (pnt1 == null || pnt1.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the center point.\n";
                    return;
                }

                HistoryWindow += "Pick a point on the circle:" + "\n";

                // Attempt to get a point on the circle
                List<Point3d> pnt2 = await pointSelection.getPoints(1);
                if (pnt2 == null || pnt2.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick a point on the circle.\n";
                    return;
                }

                // Ensure points are valid
                if (pnt1[0].IsEqual(pnt2[0]))
                {
                    HistoryWindow += "Error: Invalid points provided.\n";
                    return;
                }

                // Calculate radius
                double radius = pnt1[0].DistanceTo(pnt2[0]);
                if (radius <= 0)
                {
                    HistoryWindow += "Error: Invalid radius calculated.\n";
                    return;
                }

                // Create and draw the circle
                using MathCircle mathCircle = new(pnt1[0], radius);
                uint circleId = mathCircle.Draw();
                HistoryWindow += $"Circle drawn with ID: {circleId}\n";


                //var parameters = new object[] { circleId, pnt1[0], pnt2[0] };

                //undoRedoManager.ExecuteCommand(new CommandAction(
                //    commandName: "CIRCLE",
                //    parameters: parameters,
                //    undoAction: () =>
                //    {
                //        try
                //        {
                //            uint id = (uint)parameters[0];
                //            DrawingManager.Instance.removeEntity(id);
                //        }
                //        catch (Exception ex)
                //        {
                //            HistoryWindow += "Error during undo: " + ex.Message + "\n";
                //        }
                //    },
                //    redoAction: () =>
                //    {
                //        try
                //        {
                //            Point3d redoPnt1 = (Point3d)parameters[1];
                //            Point3d redoPnt2 = (Point3d)parameters[2];
                //            using MathCircle redoCircle = new(redoPnt1, redoPnt1.DistanceTo(redoPnt2));
                //            redoCircle.Draw();
                //        }
                //        catch (Exception ex)
                //        {
                //            HistoryWindow += "Error during redo: " + ex.Message + "\n";
                //        }
                //    }
                //));
            }
            catch (Exception ex)
            {
                // Log any unexpected exceptions
                HistoryWindow += "Unexpected error: " + ex.Message + "\n";
            }
        }


        [CommandMethod("ARC")]
        public async void DrawArc()
        {
            try
            {
                PointSelection pointSelection = new();
                HistoryWindow += "Pick start point:" + "\n";

                // Attempt to get the start point
                List<Point3d> pnt = await pointSelection.getPoints(1);
                if (pnt == null || pnt.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the start point.\n";
                    return;
                }

                HistoryWindow += "Pick end point:" + "\n";

                // Attempt to get the end point
                List<Point3d> pnt2 = await pointSelection.getPoints(1);
                if (pnt2 == null || pnt2.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the end point.\n";
                    return;
                }

                HistoryWindow += "Pick a third point on the arc:" + "\n";

                // Attempt to get the third point
                List<Point3d> pnt3 = await pointSelection.getPoints(1);
                if (pnt3 == null || pnt3.Count < 1)
                {
                    HistoryWindow += "Error: Failed to pick the third point.\n";
                    return;
                }

                // Ensure points are valid
                if (pnt[0].IsEqual(pnt2[0]) || pnt[0].IsEqual(pnt3[0]))
                {
                    HistoryWindow += "Error: Invalid points provided.\n";
                    return;
                }

                // Create and draw the arc
                using MathArc arc = new(pnt[0], pnt2[0], pnt3[0]);
                uint arcId = arc.Draw();
                HistoryWindow += $"Arc drawn with ID: {arcId}\n";

                /*
                var parameters = new object[] { arcId, pnt[0], pnt2[0], pnt3[0] };

                undoRedoManager.ExecuteCommand(new CommandAction(
                    commandName: "ARC",
                    parameters: parameters,
                    undoAction: () =>
                    {
                        try
                        {
                            uint id = (uint)parameters[0];
                            DrawingManager.Instance.removeEntity(id);
                        }
                        catch (Exception ex)
                        {
                            HistoryWindow += "Error during undo: " + ex.Message + "\n";
                        }
                    },
                    redoAction: () =>
                    {
                        try
                        {
                            Point3d redoPnt1 = (Point3d)parameters[1];
                            Point3d redoPnt2 = (Point3d)parameters[2];
                            Point3d redoPnt3 = (Point3d)parameters[3];
                            using MathArc redoArc = new(redoPnt1, redoPnt2, redoPnt3);
                            redoArc.Draw();
                        }
                        catch (Exception ex)
                        {
                            HistoryWindow += "Error during redo: " + ex.Message + "\n";
                        }
                    }
                ));
                */
            }
            catch (Exception ex)
            {
                // Log any unexpected exceptions
                HistoryWindow += "Unexpected error: " + ex.Message + "\n";
            }
        }


        [CommandMethod("POLYLINE")]
        public async void DrawPoly()
        {
            try
            {
                HistoryWindow += "Enter the total number of vertices: ";
                TextInputPrompt textInputPrompt = new(this);
                string numVertsStr = await textInputPrompt.GetText();

                if (!int.TryParse(numVertsStr, out int numVerts) || numVerts < 2)
                {
                    HistoryWindow += "Invalid input. Please enter a valid number greater than or equal to 2.\n";
                    return;
                }

                List<Point3d> vertices = [];

                for (int i = 0; i < numVerts; i++)
                {
                    try
                    {
                        PointSelection pointSelection = new();
                        HistoryWindow += $"Pick vertex {i + 1}:\n";
                        List<Point3d> point = await pointSelection.getPoints(1);

                        if (point == null || point.Count == 0)
                        {
                            HistoryWindow += $"Failed to select vertex {i + 1}. Aborting operation.\n";
                            return;
                        }

                        vertices.Add(point[0]);
                    }
                    catch (Exception ex)
                    {
                        HistoryWindow += $"Error selecting vertex {i + 1}: {ex.Message}\n";
                        return;
                    }
                }

                try
                {
                    using MathPolyline mathPolyline = new();
                    foreach (var vertex in vertices)
                    {
                        mathPolyline.AddVertex(vertex);
                    }

                    uint polylineId = mathPolyline.Draw();
                    HistoryWindow += $"Polyline drawn with ID: {polylineId}\n";

                    // Uncomment below if undo/redo functionality is required
                    /*
                    var parameters = new object[] { polylineId, vertices };

                    undoRedoManager.ExecuteCommand(new CommandAction(
                        commandName: "POLYLINE",
                        parameters: parameters,
                        undoAction: () =>
                        {
                            try
                            {
                                uint id = (uint)parameters[0];
                                DrawingManager.Instance.removeEntity(id);
                            }
                            catch (Exception ex)
                            {
                                HistoryWindow += "Error during undo: " + ex.Message + "\n";
                            }
                        },
                        redoAction: () =>
                        {
                            try
                            {
                                List<Point3d> redoVertices = (List<Point3d>)parameters[1];
                                using MathPolyline redoPolyline = new();
                                foreach (var vertex in redoVertices)
                                {
                                    redoPolyline.AddVertex(vertex);
                                }
                                redoPolyline.Draw();
                            }
                            catch (Exception ex)
                            {
                                HistoryWindow += "Error during redo: " + ex.Message + "\n";
                            }
                        }
                    ));
                    */
                }
                catch (Exception ex)
                {
                    HistoryWindow += $"Error drawing polyline: {ex.Message}\n";
                }
            }
            catch (Exception ex)
            {
                HistoryWindow += $"Unexpected error: {ex.Message}\n";
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
            HistoryWindow += "Undo executed.\n";
        }

        [CommandMethod("REDO")]
        internal void Redo()
        {
            undoRedoManager.Redo();
            HistoryWindow += "Redo executed.\n";
        }

        [CommandMethod("NEW")]
        internal void NewFile()
        {
            try
            {
                string anonStr = AnonToStr;

                // Attempt to create a new drawing session
                DrawingManager.Instance.createSession(anonStr);

                // Add the new session to file storage
                FileStorage.Add(new FileModel(DrawingManager.Instance.CurrentSessionId, anonStr));
                FileStorageName.Add(anonStr);

                // Select the newly created file
                FileSelected = FileStorageName[^1];

                // Mark as a new file
                IsNewFile = true;

                // Log success message (optional, depending on context)
                HistoryWindow += $"New file created with session ID: {DrawingManager.Instance.CurrentSessionId}\n";
            }
            catch (Exception ex)
            {
                // Log error to HistoryWindow or an error log
                HistoryWindow += $"Error creating new file: {ex.Message}\n";

                // Optionally reset or handle application state here
                IsNewFile = false;
            }
        }

        [CommandMethod("OPEN")]
        internal void OpenFile()
        {
            try
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
                    // Get the selected file path
                    string filePath = dialog.FileName;

                    try
                    {
                        // Extract file name
                        string fileName = System.IO.Path.GetFileName(filePath);

                        // Check if the file is already in storage
                        if (FileStorageName.Contains(fileName))
                        {
                            FileModel? fileModel = FileStorage.FirstOrDefault(x => x.FileName == fileName);
                            if (fileModel != null)
                            {
                                DrawingManager.Instance.changeSession(fileModel.FileId);
                                HistoryWindow += $"Switched to existing session for file: {fileName}\n";
                            }
                        }
                        else
                        {
                            // Create a new session
                            DrawingManager.Instance.createSession(fileName);
                            FileStorage.Add(new FileModel(DrawingManager.Instance.CurrentSessionId, fileName));
                            FileStorageName.Add(fileName);
                            FileSelected = fileName;

                            // Read and process the JSON content
                            string content = File.ReadAllText(filePath);
                            var jsonObject = JsonConvert.DeserializeObject<Dictionary<string, object>>(content);

                            if (jsonObject == null)
                            {
                                HistoryWindow += "Invalid JSON content.\n";
                                return;
                            }

                            if (jsonObject.TryGetValue("entities", out var entities))
                            {
                                if (entities is JArray jsonArray)
                                {
                                    var entityList = jsonArray.ToObject<List<string>>();
                                    if (entityList == null)
                                    {
                                        HistoryWindow += "'entities' is not a valid JSON array.\n";
                                        return;
                                    }

                                    foreach (var item in entityList)
                                    {
                                        uint id = Entity.FromJson(item);
                                        HistoryWindow += $"Entity loaded with ID: {id}\n";
                                    }

                                    HistoryWindow += $"Successfully loaded {entityList.Count} entities from file: {fileName}\n";
                                }
                                else
                                {
                                    HistoryWindow += "'entities' is not a valid JSON array.\n";
                                }
                            }
                            else
                            {
                                HistoryWindow += "'entities' key is missing in the JSON content.\n";
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        HistoryWindow += "An error occurred while processing the file:\n";
                        HistoryWindow += ex.Message + "\n";
                    }
                }
                else
                {
                    HistoryWindow += "No file was selected.\n";
                }
            }
            catch (Exception ex)
            {
                HistoryWindow += "An unexpected error occurred while opening the file:\n";
                HistoryWindow += ex.Message + "\n";
            }
        }

        [CommandMethod("SAVE")]
        internal void SaveFile()
        {
            try
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
                            // Serialize and save data
                            SaveToFile(filePath);
                            HistoryWindow += $"File saved successfully at: {filePath}\n";
                            IsNewFile = false;
                        }
                        catch (Exception ex)
                        {
                            HistoryWindow += "An error occurred while saving the file: " + ex.Message + "\n";
                        }
                    }
                    else
                    {
                        HistoryWindow += "Save operation was canceled.\n";
                    }
                }
                else
                {
                    try
                    {
                        // Use existing file path for saving
                        SaveToFile(DrawingManager.Instance.CurrentFilePath);
                        HistoryWindow += "File saved successfully.\n";
                    }
                    catch (Exception ex)
                    {
                        HistoryWindow += "An error occurred while saving the file: " + ex.Message + "\n";
                    }
                }
            }
            catch (Exception ex)
            {
                HistoryWindow += "An unexpected error occurred during the save operation: " + ex.Message + "\n";
            }
        }

        // Helper method to save file
        private void SaveToFile(string filePath)
        {
            // Get entity data as JSON
            List<string> entityJson = DrawingManager.Instance.GetAllEntityJsons();

            // Prepare data for serialization
            var dataToSave = new
            {
                entities = entityJson
            };

            // Serialize data to JSON with indentation for readability
            var jsonData = JsonConvert.SerializeObject(dataToSave, Formatting.Indented);

            // Write JSON data to file
            File.WriteAllText(filePath, jsonData);
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
            try
            {
                // Find the left side and input panel
                Presenters.LeftSide? leftSide = window.FindName("leftSide") as Presenters.LeftSide;
                StackPanel? stack = leftSide?.FindName("InputPanel") as StackPanel;
                if (stack == null)
                {
                    HistoryWindow += "Input panel not found.\n";
                    return;
                }

                // Prompt user to select an entity
                HistoryWindow += "Select entity:\n";
                EntitySelection entitySelection = new();
                List<uint> entityIds = await entitySelection.getEntities(1);

                // Validate entity selection
                if (entityIds == null || entityIds.Count == 0 || entityIds[0] == 0)
                {
                    HistoryWindow += "Entity not found.\n";
                    return;
                }

                // Retrieve selected entity
                selectEntity = DrawingManager.Instance.getEntityById(entityIds[0]);
                if (selectEntity == null)
                {
                    HistoryWindow += "Invalid entity ID.\n";
                    return;
                }

                // Parse entity JSON
                string jsonString = selectEntity.ToJson();
                JObject jsonObject = JObject.Parse(jsonString);
                string type = jsonObject["type"]?.ToString() ?? "Unknown";

                // Define UI elements based on entity type
                switch (type)
                {
                    case "OdMathLine":
                        CreateUI(stack,
                            new List<string> { "type", "startPnt.x", "startPnt.y", "startPnt.z", "endPnt.x", "endPnt.y", "endPnt.z" },
                            new List<string>
                            {
                        "OdMathLine",
                        jsonObject["startPnt"]["x"].ToString(),
                        jsonObject["startPnt"]["y"].ToString(),
                        jsonObject["startPnt"]["z"].ToString(),
                        jsonObject["endPnt"]["x"].ToString(),
                        jsonObject["endPnt"]["y"].ToString(),
                        jsonObject["endPnt"]["z"].ToString()
                            },
                            new List<bool> { true, false, false, false, false, false, false },
                            jsonObject);
                        break;

                    case "OdMathCircle":
                        CreateUI(stack,
                            new List<string> { "type", "center.x", "center.y", "center.z", "radius" },
                            new List<string>
                            {
                        "OdMathCircle",
                        jsonObject["center"]["x"].ToString(),
                        jsonObject["center"]["y"].ToString(),
                        jsonObject["center"]["z"].ToString(),
                        jsonObject["radius"].ToString()
                            },
                            new List<bool> { true, false, false, false, false },
                            jsonObject);
                        break;

                    case "OdMathArc":
                        CreateUI(stack,
                            new List<string> { "type", "startPnt.x", "startPnt.y", "startPnt.z", "bulge" },
                            new List<string>
                            {
                        "OdMathArc",
                        jsonObject["startPnt"]["x"].ToString(),
                        jsonObject["startPnt"]["y"].ToString(),
                        jsonObject["startPnt"]["z"].ToString(),
                        jsonObject["bulge"].ToString()
                            },
                            new List<bool> { true, false, false, false, false },
                            jsonObject);
                        break;

                    case "OdMathPolyline":
                    case "OdMathSolid":
                        CreateUI(stack,
                            new List<string> { "type", "Vertexes" },
                            new List<string> { type, jsonObject["vertexes"].ToString() },
                            new List<bool> { true, false },
                            jsonObject);
                        break;

                    case "OdMathPlane":
                        CreateUI(stack,
                            new List<string> { "type", "origin.x", "origin.y", "origin.z", "normal.x", "normal.y", "normal.z" },
                            new List<string>
                            {
                        "OdMathPlane",
                        jsonObject["origin"]["x"].ToString(),
                        jsonObject["origin"]["y"].ToString(),
                        jsonObject["origin"]["z"].ToString(),
                        jsonObject["normal"]["x"].ToString(),
                        jsonObject["normal"]["y"].ToString(),
                        jsonObject["normal"]["z"].ToString()
                            },
                            new List<bool> { true, false, false, false, false, false, false },
                            jsonObject);
                        break;

                    default:
                        HistoryWindow += $"Unsupported entity type: {type}\n";
                        break;
                }
            }
            catch (Exception ex)
            {
                HistoryWindow += $"An error occurred during selection: {ex.Message}\n";
            }
        }

        internal void ChangeTab()
        {
            try
            {
                // Check if there are any files in storage
                if (FileStorage.Count == 0)
                {
                    HistoryWindow += "No files available to switch tabs.\n";
                    return;
                }

                // Find the selected file model
                FileModel? model = FileStorage.FirstOrDefault(x => x.FileName == FileSelected);
                if (model == null)
                {
                    HistoryWindow += $"File '{FileSelected}' not found in storage.\n";
                    return;
                }

                // Change to the session corresponding to the selected file
                DrawingManager.Instance.changeSession(model.FileId);
                HistoryWindow += $"Switched to session with file: {FileSelected}\n";
            }
            catch (Exception ex)
            {
                // Handle unexpected errors
                HistoryWindow += $"An error occurred while changing the tab: {ex.Message}\n";
            }
        }

        [CommandMethod("PLANE")]
        internal async void DrawPlane()
        {
            try
            {
                // Prompt for Origin
                HistoryWindow += "Enter the Origin (x y z):\n";
                TextInputPrompt textInputPrompt = new(this);
                string text = await textInputPrompt.GetText();
                List<string> values = text.Split(' ').ToList();

                // Validate and parse Origin
                List<double> orgn = new();
                if (!TryParseValues(values, 3, out orgn))
                {
                    HistoryWindow += "Invalid input for Origin. Please enter three numeric values separated by spaces.\n";
                    return;
                }

                // Prompt for Normal
                HistoryWindow += "Enter the Normal vector (x y z):\n";
                text = await textInputPrompt.GetText();
                values = text.Split(' ').ToList();

                // Validate and parse Normal
                List<double> nrml = new();
                if (!TryParseValues(values, 3, out nrml))
                {
                    HistoryWindow += "Invalid input for Normal vector. Please enter three numeric values separated by spaces.\n";
                    return;
                }

                // Create and draw the plane
                using MathPlane mathPlane = new(new Point3d(orgn[0], orgn[1], orgn[2]), new Vector3d(nrml[0], nrml[1], nrml[2]));
                uint planeId = mathPlane.Draw();
                HistoryWindow += $"Plane drawn successfully with ID: {planeId}\n";

                // Uncomment for undo/redo functionality
                /*
                var parameters = new object[] { planeId, orgn, nrml };

                undoRedoManager.ExecuteCommand(new CommandAction(
                    commandName: "PLANE",
                    parameters: parameters,
                    undoAction: () =>
                    {
                        try
                        {
                            uint id = (uint)parameters[0];
                            DrawingManager.Instance.removeEntity(id);
                        }
                        catch (Exception ex)
                        {
                            HistoryWindow += "Error during undo: " + ex.Message + "\n";
                        }
                    },
                    redoAction: () =>
                    {
                        try
                        {
                            Point3d redoOrgn = new Point3d(orgn[0], orgn[1], orgn[2]);
                            Vector3d redoNrml = new Vector3d(nrml[0], nrml[1], nrml[2]);
                            using MathPlane redoPlane = new(redoOrgn, redoNrml);
                            redoPlane.Draw();
                        }
                        catch (Exception ex)
                        {
                            HistoryWindow += "Error during redo: " + ex.Message + "\n";
                        }
                    }
                ));
                */
            }
            catch (Exception ex)
            {
                // Handle unexpected errors
                HistoryWindow += $"An unexpected error occurred: {ex.Message}\n";
            }
        }

        private static bool TryParseValues(List<string> input, int expectedCount, out List<double> result)
        {
            result = new List<double>();
            if (input.Count != expectedCount)
            {
                return false;
            }

            foreach (string value in input)
            {
                if (double.TryParse(value, out double parsedValue))
                {
                    result.Add(parsedValue);
                }
                else
                {
                    return false;
                }
            }

            return true;
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
                // Step 1: Select Entity
                EntitySelection entitySelection = new();
                List<uint> entityIds = await entitySelection.getEntities(1);

                if (entityIds == null || entityIds.Count == 0 || entityIds[0] == 0)
                {
                    HistoryWindow += "Entity selection failed.\n";
                    return;
                }

                Entity ent = DrawingManager.Instance.getEntityById(entityIds[0]);
                if (ent == null)
                {
                    HistoryWindow += "Invalid entity selected.\n";
                    return;
                }

                // Step 2: Get Translation Vector from User
                HistoryWindow += "Enter translation vector (x y z):\n";
                TextInputPrompt textInputPrompt = new(this);
                string input = await textInputPrompt.GetText();
                List<string> values = input.Split(' ').ToList();

                // Validate and parse translation vector
                if (!TryParseValues(values, 3, out List<double> translationVector))
                {
                    HistoryWindow += "Invalid input for translation vector. Please enter three numeric values separated by spaces.\n";
                    return;
                }

                // Step 3: Apply Translation Transformation
                Matrix3d matrix3D = Matrix3d.Translate(new Vector3d(translationVector[0], translationVector[1], translationVector[2]));
                ent.TransformBy(matrix3D);

                // Log success
                HistoryWindow += $"Entity transformed successfully with translation vector: ({translationVector[0]}, {translationVector[1]}, {translationVector[2]}).\n";

                // Uncomment for undo/redo functionality
                /*
                uint entityId = ent.Id;
                var parameters = new object[] { entityId, matrix3D };

                undoRedoManager.ExecuteCommand(new CommandAction(
                    commandName: "TRANS",
                    parameters: parameters,
                    undoAction: () =>
                    {
                        uint id = (uint)parameters[0];
                        Matrix3d oldMatrix = (Matrix3d)parameters[1];
                        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                        redoEntity.TransformBy(oldMatrix.Inverse());
                    },
                    redoAction: () =>
                    {
                        uint id = (uint)parameters[0];
                        Matrix3d redoMatrix = (Matrix3d)parameters[1];
                        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                        redoEntity.TransformBy(redoMatrix);
                    }
                ));
                */
            }
            catch (Exception ex)
            {
                HistoryWindow += $"An unexpected error occurred: {ex.Message}\n";
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
                // Step 1: Select Entity
                EntitySelection entitySelection = new();
                List<uint> entityIds = await entitySelection.getEntities(1);

                if (entityIds == null || entityIds.Count == 0 || entityIds[0] == 0)
                {
                    HistoryWindow += "Entity selection failed. Please select a valid entity.\n";
                    return;
                }

                Entity ent = DrawingManager.Instance.getEntityById(entityIds[0]);
                if (ent == null)
                {
                    HistoryWindow += "Invalid entity selected.\n";
                    return;
                }

                // Step 2: Select Plane
                HistoryWindow += "Select a plane:\n";
                EntitySelection planeSelection = new();
                List<uint> planeIds = await planeSelection.getEntities(1);

                if (planeIds == null || planeIds.Count == 0 || planeIds[0] == 0)
                {
                    HistoryWindow += "Plane selection failed. Please select a valid plane.\n";
                    return;
                }

                MathPlane plane = (MathPlane)DrawingManager.Instance.getEntityById<MathPlane>(planeIds[0]);
                if (plane == null)
                {
                    HistoryWindow += "Invalid plane selected.\n";
                    return;
                }

                // Step 3: Transform Entity from World to Plane
                Matrix3d matrix3 = Matrix3d.WorldToPlane(plane.Origin, plane.Normal);
                ent.TransformBy(matrix3);

                HistoryWindow += "Entity successfully transformed to the plane.\n";

                // Uncomment for undo/redo functionality
                /*
                var parameters = new object[] { entityIds[0], matrix3 };

                undoRedoManager.ExecuteCommand(new CommandAction(
                    commandName: "W2P",
                    parameters: parameters,
                    undoAction: () =>
                    {
                        uint id = (uint)parameters[0];
                        Matrix3d oldMatrix = (Matrix3d)parameters[1];
                        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                        redoEntity.TransformBy(oldMatrix.Inverse());
                    },
                    redoAction: () =>
                    {
                        uint id = (uint)parameters[0];
                        Matrix3d redoMatrix = (Matrix3d)parameters[1];
                        Entity redoEntity = DrawingManager.Instance.getEntityById(id);
                        redoEntity.TransformBy(redoMatrix);
                    }
                ));
                */
            }
            catch (Exception ex)
            {
                HistoryWindow += $"An unexpected error occurred: {ex.Message}\n";
            }
        }

        [CommandMethod("LANG")]
        internal static void ChangeLanguage()
        {
            DialogLanguage dialogLanguage = new();
            dialogLanguage.ShowDialog();
        }

        [CommandMethod("REGEN")]
        internal void RegenViewModel()
        {
            RegenLeftPanel();
        }

        private void RegenLeftPanel()
        {
            uint entitieId = DrawingManager.Instance.EntitySelectedId;
            if (entitieId == 0)
            {
                HistoryWindow += "Entity Not found\n";
                return;
            }

            Presenters.LeftSide? leftSide = context.FindName("leftSide") as Presenters.LeftSide;
            StackPanel? stack = leftSide?.FindName("InputPanel") as StackPanel;
            if (stack == null) return;
            HistoryWindow += "Select entity:\n";
            EntitySelection entitySelection = new();
            if (entitieId == 0)
            {
                HistoryWindow += "Entity Not found\n";
                return;
            }

            selectEntity = DrawingManager.Instance.getEntityById(entitieId);

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

        [STAThread]
        [CommandMethod("NETLOAD")]
        public void NetLoad()
        {
            try
            {
                OpenFileDialog openFileDialog = new()
                {
                    Title = "Chọn tệp cần tải",
                    Filter = "DLL Files (*.dll)|*.dll|Tất cả các tệp (*.*)|*.*",
                    InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)
                };

                // Show file dialog and get user selection
                if (openFileDialog.ShowDialog() == true)
                {
                    string selectedFile = openFileDialog.FileName;

                    try
                    {
                        // Attempt to load the selected assembly
                        Assembly assembly = Assembly.LoadFrom(selectedFile);

                        // Discover and register commands from the assembly
                        CommandRegistry.DiscoverAndRegisterExternalCommands(this, assembly);

                        // Log successful load
                        HistoryWindow += $"Successfully loaded assembly: {assembly.FullName}\n";
                    }
                    catch (FileNotFoundException)
                    {
                        HistoryWindow += "Error: The selected file was not found.\n";
                    }
                    catch (BadImageFormatException)
                    {
                        HistoryWindow += "Error: The selected file is not a valid .NET assembly.\n";
                    }
                    catch (UnauthorizedAccessException)
                    {
                        HistoryWindow += "Error: Access to the selected file is denied.\n";
                    }
                    catch (Exception ex)
                    {
                        HistoryWindow += $"An unexpected error occurred: {ex.Message}\n";
                    }
                }
                else
                {
                    // Log when no file is selected
                    HistoryWindow += "No file was selected.\n";
                }
            }
            catch (Exception ex)
            {
                // Handle unexpected errors during the dialog display or file selection
                HistoryWindow += $"An unexpected error occurred: {ex.Message}\n";
            }
        }

        public static List<Assembly> ExternalAssembly = [];
        public ICommand CloseTabCommand { get; }
        public ICommand SelectCmd { get; }
        public ICommand RegenCmd { get; }  
    }
}
