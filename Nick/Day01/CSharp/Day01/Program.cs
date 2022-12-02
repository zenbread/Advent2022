namespace Day01;
public class Program
{
    static string testInput = @"1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
";
    static int testExpected1 = 24_000;
    static int testExpected2 = 45_000;
    static void Main(string[] args)
    {
        string path = System.IO.Directory.GetParent(Environment.CurrentDirectory) + @"\input.txt";
        string input = System.IO.File.ReadAllText(path);
        int value = Part1.Compute(testInput);
        if (testExpected1 == value)
        {
            Console.WriteLine($"Test Passed...");
            value = Part1.Compute(input);
            Console.WriteLine($"First Part: {value}");
        }
        value = Part2.Compute(testInput);
        if (testExpected2 == value)
        {
            Console.WriteLine($"Test Passed...");
            value = Part2.Compute(input);
            Console.WriteLine($"Second Part: {value}");
        }
    }
}
