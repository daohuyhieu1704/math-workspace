using System;

namespace MathUI.Commands
{
    [AttributeUsage(AttributeTargets.Method, Inherited = false)]
    public class CommandMethod(string commandName) : Attribute
    {
        public string CommandName { get; } = commandName;
    }
}
