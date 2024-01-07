对于每一个线索格子，格子右上角（如果有）看作行节点，数字看作点权，格子左下角（如果有）看作列节点，数字看作点权；每个空格看作行节点到列节点的边，构造二分图，那么问题变成给所有边赋值，使每个节点的点权恰好等于它的所有边的边权异或和。

性质 $1$：二分图是连通的。

证明：

我们考虑题目中的这句话：每一段连续的空格的左边或者上面的格子包含线索。

假设一段连续的空格是横着的，那么最左边的空格的左边会有一个线索，我们从中任取一个的空格，认为这个连续空格（只有一个）是竖着的，那么这个空格的上面也会有一个线索，所以每一个空格均表示一条行节点和列节点的边。

我认为题目应该再加上一句话：每个 $1$ 类型和 $3$ 类型的格子下面一个格子必定是空格，每个 $2$ 类型和 $3$ 类型的格子右边一个格子必定是空格。否则这个格子就没意义了。

性质 $2$：求出二分图的任意一颗生成树，生成树外的边可以任意赋值。

证明：

我们任取一条生成树外的边权为 $x$ 的边 $(l, r)$，只要令生成树上从 $l$ 到 $r$ 的路径的所有边异或上 $x$，就可以抵消掉这条边。

性质 $3$：给出一颗生成树和每个节点的点权，要么无解，要么生成树的边的赋值方案是唯一的。

证明：

我们给生成树任意指定一个根节点，对于每一个叶子节点，从它到父节点的边的边权只能为叶子节点的点权；对于每一个非叶子节点，从它到儿子的边的边权已经算出，只剩从它到父节点的边的边权未固定，依靠它的点权，就可以把边权算出；对于根节点，从它到儿子的边的边权已经算出，直接判断它的边权的异或和是否等于点权即可。

所以我们只要求出二分图的任意一颗生成树，把生成树外的格子任意赋值，使用dfs确定生成树上的边权，最后记得检查一下有没有重复的格子，就做完了。

```cpp
/*
下面是一些变量的解释

int kind[i][j] : 表示格子 (i, j) 的类型
int wt[i] : 表示编号为 i 的线索权值
pii p[i][j]
p[i][j].first : 表示格子 (i, j) 上方的线索编号
p[i][j].second : 表示格子 (i, j) 左方的线索编号
递推求出每个kind=4格子的 p[i][j]

vector&lt;array&lt;int, 4&gt;&gt; e;
起点线索编号，终点线索编号，格子坐标
以线索编号为点，线索权值为点权，格子为边，建二分图

vector&lt;vector&lt;array&lt;int, 3&gt;&gt;&gt; g;
first 表示终点线索编号，second 表示格子坐标
求出二分图的任意一颗生成树
取了的边vis[i][j]=1

把生成树外的格子(vis[i][j]==0)随机赋值
cwt[i] : 表示编号为 i 的线索的当前权值
ewt[i][j] : 表示格子 (i, j) 的权值

*/
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  return 0;
}
```