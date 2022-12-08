namespace _08;
class Program
{
  static void Main(string[] args)
  {
    List<List<int>> heights = new List<List<int>>();
    List<List<bool>> visible = new List<List<bool>>();
    List<List<int>> scores = new List<List<int>>();

    do
    {
      string? line = Console.ReadLine();
      if (line == null)
      {
        break;
      }
      var r1 = new List<int>();
      var r2 = new List<bool>();
      var r3 = new List<int>();
      for (int i = 0; i < line.Length; i++)
      {
        r1.Add(int.Parse(line[i].ToString()));
        r2.Add(false);
        r3.Add(1);
      }

      heights.Add(r1);
      visible.Add(r2);
      scores.Add(r3);
    } while (true);

    for (int i = 0; i < heights.Count(); i++)
    {
      var row = heights[i];
      int maxLeftIndex = 0, maxRightIndex = row.Count() - 1;
      int maxLeft = row[maxLeftIndex], maxRight = row[maxRightIndex];
      int maxUpIndex = 0, maxDownIndex = heights.Count() - 1;
      int maxUp = heights[maxUpIndex][i], maxDown = heights[maxDownIndex][i];

      int jl, jr;
      for (jl = 1, jr = heights[i].Count() - 2; jr >= 1; jl++, jr--)
      {
        // left -> right
        visible[i][jl] = visible[i][jl] || (maxLeft < row[jl]);
        // right -> left
        visible[i][jr] = visible[i][jr] || (maxRight < row[jr]);
        // up -> down
        visible[jl][i] = visible[jl][i] || (maxUp < heights[jl][i]);
        // down -> up
        visible[jr][i] = visible[jr][i] || (maxDown < heights[jr][i]);

        if (heights[jl][i] > maxUp)
        {
          maxUp = heights[jl][i];
        }
        if (heights[jr][i] > maxDown)
        {
          maxDown = heights[jr][i];
        }
        if (row[jl] > maxLeft)
        {
          maxLeft = row[jl];
        }
        if (row[jr] > maxRight)
        {
          maxRight = row[jr];
        }
      }

      visible[i][jl] = true;
      visible[i][jr] = true;
      visible[jl][i] = true;
      visible[jr][i] = true;
    }

    for (int i = 0; i < heights.Count(); i++)
    {
      for (int j = 0; j < heights.Count(); j++)
      {
        int off = 0;
        var cur = heights[i][j];

        while (j - off > 0 && heights[i][j - ++off] < cur) { }
        scores[i][j] *= off;
        off = 0;
        while (i - off > 0 && heights[i - ++off][j] < cur) { }
        scores[i][j] *= off;
        off = 0;
        while (off + j + 1 < heights.Count() && heights[i][j + ++off] < cur) { }
        scores[i][j] *= off;
        off = 0;
        while (off + i + 1 < heights.Count() && heights[i + ++off][j] < cur) { }
        scores[i][j] *= off;
        off = 0;
      }
    }

    int res1 = 0;
    int res2 = 0;
    foreach (var row in visible) { foreach (var el in row) { if (el) { res1++; } } }
    foreach (var row in scores) { foreach (var el in row) { res2 = Math.Max(res2, el); } }
    System.Console.WriteLine("part 1: {0}\npart 2: {1}", res1, res2);
  }
}
