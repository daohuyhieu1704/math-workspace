
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
// 
// This template generates PublicResXFileCodeGenerator compatible code plus some
// useful extensions. 
// 
// The original version provided by ResXResourceManager is restricted to resource key names
// that are valid c# identifiers to keep this template simple (KISS!).
// 
// Us it as it is or as a scaffold to generate the code you need.
//
// As long as you have ResXResourceManager running in the background, the generated code 
// will be kept up to date.
//  
//------------------------------------------------------------------------------

namespace MathUI.Resources {
    using System;

    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by a text template.
    // To add or remove a member, edit your .ResX file.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("ResXResourceManager", "1.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    public class TopPanelRes {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal TopPanelRes() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("MathUI.Resources.TopPanelRes", typeof(TopPanelRes).Assembly);
                    resourceMan = temp;
                }

                switch (System.Globalization.CultureInfo.CurrentUICulture.TwoLetterISOLanguageName)
                {
                    case "en":
						resourceMan = new global::System.Resources.ResourceManager("MathUI.Resources.TopPanelRes", typeof(TopPanelRes).Assembly);
						break;
                    case "vn":
                       resourceMan = new global::System.Resources.ResourceManager("MathUI.Resources.TopPanelResvn", typeof(TopPanelRes).Assembly);
                       break;
                }

                return resourceMan;
            }
        }

        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }

        /// <summary>
        ///   Looks up a localized string similar to "Language"
        /// </summary>
        public static string Language {
            get {
                return ResourceManager.GetString("Language", resourceCulture) ?? string.Empty;
            }
        }

        /// <summary>
        ///   Looks up a localized string similar to "Settings"
        /// </summary>
        public static string Settings {
            get {
                return ResourceManager.GetString("Settings", resourceCulture) ?? string.Empty;
            }
        }
    }


}


