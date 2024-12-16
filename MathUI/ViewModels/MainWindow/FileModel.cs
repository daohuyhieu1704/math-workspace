using MathUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.ViewModels.MainWindow
{
    public class FileModel : ViewModelBase
    {
        private string _filePath;
        public string FilePath
        {
            get => _filePath;
            set => Set(ref _filePath, value);
        }
        private uint _fileId;

        public uint FileId
        {
            get => _fileId;
            set => Set(ref _fileId, value);
        }

        private string _fileName;
        public string FileName
        {
            get => _fileName;
            set => Set(ref _fileName, value);
        }
        public FileModel(uint sessionId, string filePath)
        {
            FileId = sessionId;
            FilePath = filePath;
            FileName = System.IO.Path.GetFileName(filePath);
        }
    }
}
