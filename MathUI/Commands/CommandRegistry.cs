﻿using MathUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Threading.Tasks;

namespace MathUI.Commands
{
    public static class CommandRegistry
    {
        private static readonly Dictionary<string, Func<Task>> Commands = [];

        public static void Register(string commandName, Func<Task> commandDelegate)
        {
            if (!Commands.ContainsKey(commandName))
            {
                Commands[commandName] = commandDelegate;
            }
        }

        public static void DiscoverAndRegisterCommands(ViewModelBase instance)
        {
            var assembly = Assembly.GetExecutingAssembly();
            DiscoverAndRegisterExternalCommands(instance, assembly);
        }

        public static void DiscoverAndRegisterExternalCommands(ViewModelBase instance, Assembly assembly)
        {
            foreach (var type in assembly.GetTypes())
            {
                foreach (var method in type.GetMethods(BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance))
                {
                    var attribute = method.GetCustomAttribute<CommandMethod>();
                    if (attribute != null)
                    {
                        string commandName = attribute.CommandName;

                        Func<Task> commandDelegate;
                        if (method.IsStatic)
                        {
                            commandDelegate = CreateDelegateForMethod(method);
                        }
                        else
                        {
                            commandDelegate = CreateDelegateForMethod(method, instance);
                        }

                        Register(commandName, commandDelegate);
                    }
                }
            }
        }

        public static async Task InvokeAsync(string commandName)
        {
            if (Commands.TryGetValue(commandName, out var commandDelegate))
            {
                await commandDelegate();
            }
            else
            {
                throw new InvalidOperationException($"Command '{commandName}' not found.");
            }
        }

        private static Func<Task> CreateDelegateForMethod(MethodInfo method, object? instance = null)
        {
            // Kiểm tra nếu phương thức trả về Task hoặc Task kế thừa
            if (typeof(Task).IsAssignableFrom(method.ReturnType))
            {
                return () => (Task?)method.Invoke(instance, null) ?? Task.CompletedTask;
            }
            else if (method.ReturnType == typeof(void))
            {
                Action action = (Action)Delegate.CreateDelegate(typeof(Action), instance, method);
                return () =>
                {
                    action();
                    return Task.CompletedTask;
                };
            }
            else
            {
                throw new InvalidOperationException($"Unsupported return type for method {method.Name}. Must be Task or void.");
            }
        }


        public static bool IsACmd(string commandName)
        {
            return Commands.ContainsKey(commandName);
        }
    }
}
