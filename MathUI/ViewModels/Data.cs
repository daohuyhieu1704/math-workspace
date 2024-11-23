using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.ViewModels
{
    internal class Data
    {
        private ObservableCollection<Command> commands = new();

        public void CreateCommandsData()
        {
            commands.Add(new Command()
            {
                Title = "circle 1"
            });
            commands.Add(new Command()
            {
                Title = "circle 2"
            });
            commands.Add(new Command()
            {
                Title = "circle 3"
            });
            commands.Add(new Command()
            {
                Title = "line 1"
            });
            commands.Add(new Command()
            {
                Title = "line 2"
            });
            commands.Add(new Command()
            {
                Title = "line 3"
            });
        }
        public ObservableCollection<Command> GetCommands()
        {
            commands.Clear();
            CreateCommandsData();
            return commands;
        }
    }
}

