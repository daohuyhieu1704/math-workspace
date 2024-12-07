using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.Utils
{
    public class CommandAction
    {
        public string CommandName { get; set; }
        public object[] Parameters { get; set; } // Các tham số của lệnh
        public Action UndoAction { get; set; }  // Hành động Undo
        public Action RedoAction { get; set; }  // Hành động Redo

        public CommandAction(string commandName, object[] parameters, Action undoAction, Action redoAction)
        {
            CommandName = commandName;
            Parameters = parameters;
            UndoAction = undoAction;
            RedoAction = redoAction;
        }
    }

    public class UndoRedoManager
    {
        private readonly Stack<CommandAction> undoStack = new();
        private readonly Stack<CommandAction> redoStack = new();

        public void ExecuteCommand(CommandAction command)
        {
            command.RedoAction.Invoke();
            undoStack.Push(command);
            redoStack.Clear();
        }

        public void Undo()
        {
            if (undoStack.Count > 0)
            {
                CommandAction command = undoStack.Pop();
                command.UndoAction.Invoke();
                redoStack.Push(command);
            }
        }

        public void Redo()
        {
            if (redoStack.Count > 0)
            {
                CommandAction command = redoStack.Pop();
                command.RedoAction.Invoke();
                undoStack.Push(command);
            }
        }
    }
}
