namespace Day01;

public class Part2
{
    static public int Compute(string s)
    {
        var sep = s.Split(new string[] { "\r\n", "\r", "\n" }, StringSplitOptions.None);

        List<int> totals = new();
        int counter = 0;
        foreach (var item in sep)
        {
            if (String.IsNullOrEmpty(item))
            {
                totals.Add(counter);
                counter = 0;
                continue;
            }
            counter += int.Parse(item);
        }
        // Get last item
        totals.Add(counter);

        totals.Sort((x, y) => y.CompareTo(x));
        return totals.Take(3).Sum();
    }
}