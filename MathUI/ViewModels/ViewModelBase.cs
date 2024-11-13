using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace MathUI.ViewModels
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        protected bool Set<T>(ref T field, T value, string propertyName)
        {
            if (EqualityComparer<T>.Default.Equals(field, value))
            {
                return false;
            }

            field = value;
            OnPropertyChanged(propertyName);
            return true;
        }

        protected bool Set<T>(ref T field, T value, params string[] propertyNames)
        {
            if (EqualityComparer<T>.Default.Equals(field, value))
            {
                return false;
            }

            field = value;
            foreach (var propertyName in propertyNames)
            {
                OnPropertyChanged(propertyName);
            }

            return true;
        }

        public class RelayCommand<T>(Predicate<T> canExecute, Action<T> execute) : ICommand
        {
            private readonly Predicate<T> _canExecute = canExecute;
            private readonly Action<T> _execute = execute ?? throw new ArgumentNullException(nameof(execute));

            public bool CanExecute(object? parameter)
            {
                try
                {
                    if (parameter != null)
                    {
                        return _canExecute == null || _canExecute((T)parameter);
                    }

                    return true;
                }
                catch
                {
                    return true;
                }
            }

            public void Execute(object? parameter)
            {
                if (parameter != null)
                {
                    _execute((T)parameter);
                }
            }

            public event EventHandler? CanExecuteChanged
            {
                add => CommandManager.RequerySuggested += value;
                remove => CommandManager.RequerySuggested -= value;
            }
        }

        public class ActionCommand<T>(Action<T> action) : ICommand
        {
            public event EventHandler? CanExecuteChanged;
            private readonly Action<T> _action = action;

            public bool CanExecute(object parameter) { return true; }

            public void Execute(object parameter)
            {
                if (_action != null)
                {
                    var castParameter = (T)Convert.ChangeType(parameter, typeof(T));
                    _action(castParameter);
                }
            }
        }

        protected void ValidateProperty<T>(T value, [CallerMemberName] string? propertyName = null, bool skip = false)
        {
            if (skip)
            {
                return;
            }

            Validator.ValidateProperty(value, new ValidationContext(this) { MemberName = propertyName });
        }

        protected bool TryValidateProperty<T>(T value, out ICollection<ValidationResult> results, [CallerMemberName] string propertyName = null)
        {
            results = new List<ValidationResult>();
            return Validator.TryValidateProperty(value, new ValidationContext(this) { MemberName = propertyName }, results);
        }
    }
}
