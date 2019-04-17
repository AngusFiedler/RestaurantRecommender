import 'dart:collection';

class Graph<T>
{
  int edges = 0;
  Map<T, List<T>> AdjacenecyList = <T, List<T>>{};
  Set<T> visited = new Set<T>();

  addEdge(T v, T w)
  {
    if(AdjacenecyList[v] == null)
    {
      AdjacenecyList[v] = <T>[];
    }
    AdjacenecyList[v].add(w);
    if(AdjacenecyList[w] == null)
    {
      AdjacenecyList[w] = <T>[];
    }
    AdjacenecyList[w].add(v);
    edges++;
  }

  BreadthFirstSearch(T v)
  {
    visited.clear();
    var queue = new Queue<T>();
    visited.add(v);
    queue.addLast(v);
    while (!queue.isNotEmpty)
    {
      var p = queue.removeFirst();
      print('Visited vertex: $p');
      for (T n in AdjacenecyList[p])
      {
        if (!visited.contains(n))
        {
          visited.add(n);
          queue.addLast(n);
        }
      }
    }
  }

  DepthFirstTraversal(T v)
  {
    visited.clear();
    _DepthFirstTraveral(v);
  }

  _DepthFirstTraveral(T v)
  {
    visited.add(v);
    if (AdjacenecyList.containsKey(v))
    {
      print("Visited vertex: $v");
      for (T n in AdjacenecyList[v])

        if (!visited.contains(n))
        {
          _DepthFirstTraveral(n);
        }
      }
   }
}
