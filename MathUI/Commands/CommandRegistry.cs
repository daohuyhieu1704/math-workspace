using System;
using System.Collections.Generic;
using System.Reflection;

namespace MathUI.Commands
{
    public static class CommandRegistry
    {
        private static readonly Dictionary<string, Delegate> Commands = new Dictionary<string, Delegate>();

        public static void Register(string commandName, Delegate commandDelegate)
        {
            if (!Commands.ContainsKey(commandName))
            {
                Commands[commandName] = commandDelegate;
            }
        }

        public static List<string> CommandNames => new(Commands.Keys);

        public static void DiscoverAndRegisterCommands()
        {
            var assembly = Assembly.GetExecutingAssembly();
            foreach (var type in assembly.GetTypes())
            {
                foreach (var method in type.GetMethods(BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance))
                {
                    var attribute = method.GetCustomAttribute<CommandMethod>();
                    if (attribute != null)
                    {
                        string commandName = attribute.CommandName;

                        Delegate commandDelegate;
                        if (method.IsStatic)
                        {
                            commandDelegate = Delegate.CreateDelegate(typeof(Action), method);
                        }
                        else
                        {
                            var instance = Activator.CreateInstance(type);
                            commandDelegate = Delegate.CreateDelegate(typeof(Action), instance, method);
                        }

                        Register(commandName, commandDelegate);
                    }
                }
            }
        }

        public static void Invoke(string commandName)
        {
            if (Commands.TryGetValue(commandName, out var commandDelegate))
            {
                commandDelegate.DynamicInvoke();
            }
            else
            {
                throw new InvalidOperationException($"Command '{commandName}' not found.");
            }
        }
    }
}
