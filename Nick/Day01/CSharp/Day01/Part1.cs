namespace Day01;

class Part1
{
    public static int Compute(string s)
    {
        var sep = s.Split(new string[] { "\r\n", "\r", "\n" }, StringSplitOptions.None);

        int highest = 0;
        int counter = 0;
        foreach (var item in sep)
        {
            if (String.IsNullOrEmpty(item))
            {
                if (highest < counter) highest = counter;
                counter = 0;
                continue;
            }
            counter += int.Parse(item);
        }
        // Grab the last one
        if (highest < counter) highest = counter;

        return highest;
    }
}