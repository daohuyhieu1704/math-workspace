using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace MathUI.Utils
{
    public class LocalizationExtension : Binding
    {
        public LocalizationExtension(string name) : base("[" + name + "]")
        {
            this.Mode = BindingMode.OneWay;
            this.Source = TranslationSource.Instance;
        }
    }
    public class TranslationSource : INotifyPropertyChanged
    {
        private static readonly TranslationSource instance = new TranslationSource();

        public static TranslationSource Instance
        {
            get { return instance; }
        }

        private string _path;
        public string Path
        {
            get => _path;
            set
            {
                _path = value;
                this.ResManager = new ResourceManager(GetPathResources(_path), Assembly.GetExecutingAssembly());
            }
        }

        public ResourceManager ResManager = null;

        private CultureInfo _currentCulture = CultureInfo.GetCultureInfo(Thread.CurrentThread.CurrentUICulture.Name);

        public string this[string key]
        {
            get
            {
                return ResManager.GetString(key, _currentCulture);
            }
        }

        public CultureInfo CurrentCulture
        {
            get { return this._currentCulture; }
            set
            {
                if (this._currentCulture != value)
                {
                    this._currentCulture = value;

                    if (Path != null)
                    {
                        this.ResManager = new ResourceManager(GetPathResources(Path), Assembly.GetExecutingAssembly());
                    }

                    var @event = this.PropertyChanged;
                    if (@event != null)
                    {
                        @event.Invoke(this, new PropertyChangedEventArgs(string.Empty));
                    }
                }
            }
        }

        private string GetPathResources(string pathRes)
        {
            var dirPath = pathRes.ToString().Split('.');
            var lastPath = dirPath.Last() + "Res";
            dirPath = dirPath.Take(dirPath.Count() - 1).ToArray();

            var curPath = String.Join(".", dirPath);
            var curCulture = Instance.CurrentCulture;
            var path = curPath + ".Resources." + lastPath;

            if (curCulture.TwoLetterISOLanguageName != "en")
            {
                path += curCulture.TwoLetterISOLanguageName;
            }

            return path;
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
