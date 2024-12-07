using MathUI;
using MathUI.Commands;

namespace CustomCommand
{
    public class Class1
    {
        public void TestToo()
        {
            Console.WriteLine("TestToo() invoked!");
        }

        public static void StaticTest()
        {
            Console.WriteLine("StaticTest() invoked!");
        }

        [CommandMethod("TestToo")]
        public void RegisterTestToo()
        {
            CommandRegistry.Register("TestToo", TestToo);
        }

        [CommandMethod("StaticTest")]
        public static void RegisterStaticTest()
        {
            CommandRegistry.Register("StaticTest", StaticTest);
        }
    }
}
