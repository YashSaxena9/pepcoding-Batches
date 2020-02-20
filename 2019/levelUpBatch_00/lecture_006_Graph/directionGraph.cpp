#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int n = 9;
vector<vector<int>> graph(n, vector<int>());
// vector<vector<Edge *>> graph(7, vector<Edge *>()); //
// ArrayList<Integer>[] graph=new ArrayList[7];

void addEdge(int u, int v, int w)
{
    graph[u].push_back(v);
}

void display()
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " -> ";
        for (int e : graph[i])
        {
            cout << e << ", ";
        }
        cout << endl;
    }

    cout << endl;
}

void topoDfs(int src, vector<bool> &vis, vector<int> &st)
{
    vis[src] = true;
    for (int e : graph[src])
    {
        if (!vis[e])
            topoDfs(e, vis,st);
    }

    st.push_back(src);
}

void topologiocalSort()
{
    vector<bool> vis(n, false);
    vector<int> st;

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            topoDfs(i, vis, st);
    }
}

void khansAlso()
{
    vector<int> incidentEdges(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int ele : graph[i])
        {
            incidentEdges[ele]++;
        }
    }

    queue<int> que, ans;
    for (int i = 0; i < incidentEdges.size(); i++)
    {
        if (incidentEdges[i] == 0)
        {
            que.push(i);
        }
    }

    while (que.size() != 0)
    {
        int vtx = que.front();
        que.pop();

        ans.push(vtx);

        for (int nbr : graph[vtx])
        {
            if (--incidentEdges[nbr] == 0)
            {
                que.push(nbr);
            }
        }
    }

    if (ans.size() != graph.size())
    {
        cout << "Topological sort is not possible: Cycle" << endl;
    }
    else
    {
        while (ans.size() != 0)
        {
            cout << ans.front() << " ";
            ans.pop();
        }
        cout << endl;
    }
}