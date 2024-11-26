using MathUI.ViewModels.MainWindow;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace MathUI.Commands
{
    public class TextInputPrompt
    {
        private MainWindowViewModel vm;
        private TaskCompletionSource<string> _tcs;

        public event KeyEventHandler KeyDown;
        public TextInputPrompt(MainWindowViewModel viewModel)
        {
            vm = viewModel;
        }

        internal async Task<string> GetText()
        {
            _tcs = new TaskCompletionSource<string>();
            if (vm.InputCommandWindow != null)
            {
                vm.InputCommandWindow.KeyDown += OnKeyDown;
            }
            return await _tcs.Task;
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                if (vm.InputCommandWindow != null)
                {
                    vm.InputCommandWindow.KeyDown -= OnKeyDown;
                }

                _tcs.SetResult(vm.CommandWindow);
                vm.CommandWindow = "";
            }
        }
    }
}
