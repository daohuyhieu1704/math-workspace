using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Interop;
using MathGL;

namespace MathUI.Common
{
    public class EngineHost : HwndHost
    {
        public IntPtr hwndHost;
        const int WM_MY_MESSAGE = 0x0401;

        protected override bool TranslateAcceleratorCore(ref MSG msg, ModifierKeys modifiers)
        {
            if (msg.message == WM_MY_MESSAGE)
            {
                return false;
            }

            return base.TranslateAcceleratorCore(ref msg, modifiers);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == WM_MY_MESSAGE)
            {
                handled = true;
            }

            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {

            hwndHost = GLEngineNative.Instance.InitializeWindow(hwndParent.Handle);
            if (hwndHost == IntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to create OpenGL window.");
            }
            return new HandleRef(this, hwndHost);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
        }
    }
}
