using MathUI.Models;
using MathUI.Presenters;
using MathUI.Resources;
using MathUI.Utils;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Text.RegularExpressions;

namespace MathUI.ViewModels
{
    public class DialogLanguageViewModel : ViewModelBase
    {
        private StringUtils.HyphenType _hyphenType = StringUtils.HyphenType.Hyphen;
        public ICommand WindowGotFocus { get; set; }
        public ICommand BtnOKCmd => new RelayCommand<DialogLanguage>(p => true, BtnOKCmdExecute);

        private ObservableCollection<LanguageData> _listLanguage;

        private string tooltipPreview;
        public string TooltipPreview
        {
            get => tooltipPreview;
            set
            {
                tooltipPreview = value;
                OnPropertyChanged(nameof(TooltipPreview));
            }
        }

        public ObservableCollection<LanguageData> ListLanguage
        {
            get => _listLanguage;
            set
            {
                _listLanguage = value;
                OnPropertyChanged(nameof(ListLanguage));
            }
        }

        private LanguageData _selectedLanguage;
        public LanguageData SelectedLanguage
        {
            get => _selectedLanguage;
            set
            {
                _selectedLanguage = value;
                OnPropertyChanged(nameof(SelectedLanguage));
            }
        }
        public DialogLanguageViewModel()
        {
            LoadListLanguage();
            ShowHint(ListLanguage);
        }
        private void LoadListLanguage()
        {
            ListLanguage =
            [
                new LanguageData(StringUtils.AddHypephenToString(DialogLanguageRes.Vietnamese, _hyphenType, 1), "vn"),
                new LanguageData(StringUtils.AddHypephenToString(DialogLanguageRes.English, _hyphenType, 2), "en"),
            ];

            var currentLanguage = ListLanguage.First(x => x.TwoLetterIso == Util.AppCultureInfo?.TwoLetterISOLanguageName);
            SelectedLanguage = currentLanguage ?? ListLanguage.First(x => x.TwoLetterIso == "vn");
        }

        private void BtnOKCmdExecute(DialogLanguage dialog)
        {
            if (SelectedLanguage is null) return;

            var cultureInfo = new CultureInfo(SelectedLanguage.TwoLetterIso);
            CultureInfo.CurrentUICulture = cultureInfo;
            CultureInfo.CurrentCulture = cultureInfo;
            Util.AppCultureInfo = cultureInfo;
            ResxDynamicResourceProvider.LoadResourceToApplication("MainWindowRes");
            ResxDynamicResourceProvider.LoadResourceToApplication("TopPanelRes");
            dialog.Close();
        }
        private void ShowHint<T>(ObservableCollection<T> listStr)
        {
            if (listStr is null) return;

            var startLength = 2;
            var spaceStr = "  ";
            TooltipPreview = "[ ";

            switch (typeof(T).Name)
            {
                case nameof(String):
                    foreach (var item in listStr)
                    {
                        if (TooltipPreview.Length > startLength)
                        {
                            TooltipPreview += spaceStr;
                        }
                        TooltipPreview += item;
                    }
                    break;
                case nameof(LanguageData):
                    foreach (var item in listStr)
                    {
                        if (TooltipPreview.Length > startLength)
                        {
                            TooltipPreview += spaceStr;
                        }
                        TooltipPreview += (item as LanguageData).Name;
                    }
                    break;
            }

            TooltipPreview += " ]";
        }
    }
}
