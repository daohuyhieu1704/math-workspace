using System.Collections.ObjectModel;
using MathUI.ViewModels;

namespace MathUI.Presenters
{
    internal class CommandsViewModel
    {
        private Data source = new Data();

        private ObservableCollection<Command> commandsList = new ObservableCollection<Command>();
        public ObservableCollection<Command> CommandsList
        {
            get { return commandsList; }
        }

        private ObservableCollection<string> commandHistory = new ObservableCollection<string>();
        public ObservableCollection<string> CommandHistory
        {
            get { return commandHistory; }
        }

        public CommandsViewModel()
        {
            // Load existing commands
            foreach (var command in source.GetCommands())
            {
                commandsList.Add(command);
            }
        }

        // Method to add command to history
        public void AddCommandToHistory(string command)
        {
            if (!commandHistory.Contains(command))
            {
                commandHistory.Add(command);
            }
        }
    }
}
