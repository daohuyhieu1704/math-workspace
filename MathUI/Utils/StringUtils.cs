using MathUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.Utils
{
    public static class StringUtils
    {
        public enum HyphenType
        {
            None,
            Hyphen,
            Colons,
            Dot
        }
        public static string AddHypephenToString(string str, HyphenType hyphenType, int num)
        {
            return str.Insert(0, num + GetHypenType(hyphenType));
        }

        public static IList<string> AddHypephenToListString(List<string> str, HyphenType hyphenType)
        {
            for (int i = 0; i < str.Count; i++)
            {
                str[i] = i + 1 + GetHypenType(hyphenType) + str[i];
            }

            return str;
        }
        private static string GetHypenType(HyphenType hyphenType)
        {
            string result = string.Empty;
            switch (hyphenType)
            {
                case HyphenType.None:
                    result = string.Empty;
                    break;
                case HyphenType.Hyphen:
                    result = "- ";
                    break;
                case HyphenType.Colons:
                    result = ": ";
                    break;
                case HyphenType.Dot:
                    result = ". ";
                    break;
            }

            return result;
        }
    }
}
