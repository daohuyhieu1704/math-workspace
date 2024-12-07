using MathUI.Resources;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace MathUI.Utils
{
    public static class ResxDynamicResourceProvider
    {
        private static readonly ResourceManager DialogLanguageResManager = DialogLanguageRes.ResourceManager;
        private static readonly ResourceManager MainWindowResManager = MainWindowRes.ResourceManager;
        private static readonly ResourceManager TopPanelResManager = TopPanelRes.ResourceManager;

        public static void UpdateDynamicResources(string cultureCode)
        {
            // Thay đổi ngôn ngữ hiện tại
            var culture = new CultureInfo(cultureCode);
            CultureInfo.CurrentUICulture = culture;

            // Cập nhật tất cả các tài nguyên được nạp từ Resx
            foreach (var key in Application.Current.Resources.Keys)
            {
                if (key is string resourceKey)
                {
                    var resourceValue = MathUI.Resources.DialogLanguageRes.ResourceManager.GetString(resourceKey, culture);
                    if (resourceValue != null)
                    {
                        Application.Current.Resources[resourceKey] = resourceValue;
                    }
                }
            }
        }

        public static string GetString(string key, string resourceFile)
        {
            ResourceManager manager = resourceFile switch
            {
                "DialogLanguageRes" => DialogLanguageResManager,
                "MainWindowRes" => MainWindowResManager,
                "TopPanelRes" => TopPanelResManager,
                _ => throw new ArgumentException($"Unknown resource file: {resourceFile}")
            };

            return manager.GetString(key, CultureInfo.CurrentUICulture) ?? string.Empty;
        }

        public static void LoadResourceToApplication(string resourceFile)
        {
            ResourceManager manager = resourceFile switch
            {
                "DialogLanguageRes" => DialogLanguageResManager,
                "MainWindowRes" => MainWindowResManager,
                "TopPanelRes" => TopPanelResManager,
                _ => throw new ArgumentException($"Unknown resource file: {resourceFile}")
            };

            string resourceName = CultureInfo.CurrentUICulture.TwoLetterISOLanguageName switch
            {
                "vn" => $"MathUI.Resources.{resourceFile}vn",
                _ => $"MathUI.Resources.{resourceFile}"
            };

            var resourceType = resourceFile switch
            {
                "DialogLanguageRes" => typeof(DialogLanguageRes),
                "MainWindowRes" => typeof(MainWindowRes),
                "TopPanelRes" => typeof(TopPanelRes),
                _ => throw new ArgumentException($"Unknown resource file: {resourceFile}")
            };

            manager = new ResourceManager(resourceName, resourceType.Assembly);

            var resourceSet = manager.GetResourceSet(CultureInfo.CurrentUICulture, true, true);
            if (resourceSet != null)
            {
                foreach (System.Collections.DictionaryEntry entry in resourceSet)
                {
                    if (entry.Key is string key && entry.Value is string value)
                    {
                        Application.Current.Resources[$"{resourceFile}_{key}"] = value;
                    }
                }
            }
        }
    }
}
