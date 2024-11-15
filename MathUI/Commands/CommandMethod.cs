
namespace MathUI.Commands
{
    [AttributeUsage(AttributeTargets.Method, Inherited = false)]
    public class CommandMethod : Attribute
    {
        public string CommandName { get; }

        public CommandMethod(string commandName)
        {
            CommandName = commandName;
        }
    }
}