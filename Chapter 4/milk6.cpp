/*
ID: Kevun1
LANG: C++11
TASK: milk6
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <queue>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("milk6.in");
ofstream fout("milk6.out");

typedef long long LL;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
	bool operator==(Edge& other) {
		return from == other.from && to == other.to && other.cap == cap;
	}
};

struct PushRelabel {
	int N;
	vector<vector<Edge> > G;
	vector<LL> excess;
	vector<int> dist, active, count;
	queue<int> Q;

	PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2 * N) {}

	void AddEdge(int from, int to, int cap) {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}

	void Enqueue(int v) {
		if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
	}

	void Push(Edge &e) {
		int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
		if (dist[e.from] <= dist[e.to] || amt == 0) return;
		e.flow += amt;
		G[e.to][e.index].flow -= amt;
		excess[e.to] += amt;
		excess[e.from] -= amt;
		Enqueue(e.to);
	}

	void Gap(int k) {
		for (int v = 0; v < N; v++) {
			if (dist[v] < k) continue;
			count[dist[v]]--;
			dist[v] = max(dist[v], N + 1);
			count[dist[v]]++;
			Enqueue(v);
		}
	}

	void Relabel(int v) {
		count[dist[v]]--;
		dist[v] = 2 * N;
		for (int i = 0; i < G[v].size(); i++)
			if (G[v][i].cap - G[v][i].flow > 0)
				dist[v] = min(dist[v], dist[G[v][i].to] + 1);
		count[dist[v]]++;
		Enqueue(v);
	}

	void Discharge(int v) {
		for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
		if (excess[v] > 0) {
			if (count[dist[v]] == 1)
				Gap(dist[v]);
			else
				Relabel(v);
		}
	}

	LL GetMaxFlow(int s, int t) {
		count[0] = N - 1;
		count[N] = 1;
		dist[s] = N;
		active[s] = active[t] = true;
		for (int i = 0; i < G[s].size(); i++) {
			excess[s] += G[s][i].cap;
			Push(G[s][i]);
		}

		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
			active[v] = false;
			Discharge(v);
		}

		LL totflow = 0;
		for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
		return totflow;
	}
};
int v, e;

vector<vector<Edge>> build_residual_network(PushRelabel& flow, int i) {
	vector<vector<Edge>> residual_adj(v + 1);
	for (int i = 1; i <= v; ++i) {
		for (Edge adj : flow.G[i]) {
			if (adj.cap - adj.flow > 0)
				residual_adj[i].push_back(Edge(i, adj.to, adj.cap - adj.flow, 0, 0));
			if (adj.flow > 0)
				residual_adj[adj.to].push_back(Edge(adj.to, i, adj.flow, 0, 0));
		}
	}
	return residual_adj;
}

int find_min_cut(PushRelabel &flow, int i = 0) {
	int num_edges = 0;

	auto residual_network = build_residual_network(flow, i);

	//bfs
	unordered_set<int> visited;
	visited.insert(1);
	vector<int> frontier = { 1 };
	while (!frontier.empty()) {
		vector<int> next_frontier;
		for (int node : frontier) {
			for (Edge adj_e : residual_network[node]) {
				int adj = adj_e.to;
				if (visited.find(adj) == visited.end()) {
					visited.insert(adj);
					next_frontier.push_back(adj);
				}
			}
		}
		frontier = next_frontier;
	}

	for (int v : visited) {
		for (Edge edge : flow.G[v]) {
			if (visited.find(edge.to) == visited.end()) {
				++num_edges;
			}
		}
	}

	return num_edges;
}
/*
Network Flow - Min cut
*/
int main(){
	vector<Edge> edges;
	fin >> v >> e;
	PushRelabel flow(v + 1);
	/*
	Flow2 is a reweighted version of the original graph, so that the min cut
	found in flow2 always contains the least number of edges out of all min cuts.
	Reweight follows the formula: c' = e*c + 1

	Proof:
	let v be the value of a min cut and n be the number of edges in a min cut
	You want a reweight such that if v1 == v2 and n1 < n2, v1' < v2'
	one possibility is add 1 to each weight, so v1' = v1 + n1
	However, you must ensure that if
	v1 < v2, then
	v1 + n1 < v2 + n2
	
	rearrange:
	v2 - v1 > n1 - n2
	However, n1 - n2, the difference in the number of edges between two min cuts,
	is bounded by E, the number of edges in the entire graph
	n1 - n2 < E. The bound is not tight, but good enough.
	Therefore, v2 - v1 > E
	v2 - v1 is at least 1, so multipling v2 - v1 by E will satisfy the inequality
	This means multiplying all capacities by E and adding 1 is the correct reweight
	*/
	PushRelabel flow2(v + 1);
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		fin >> a >> b >> c;
		flow.AddEdge(a, b, c);
		flow2.AddEdge(a, b, e*c + 1);
		edges.push_back(Edge(a, b, c, 0, 0));
	}

	int max_flow = flow.GetMaxFlow(1, v);
	flow2.GetMaxFlow(1, v);
	//num_edges - minimum number of edges out of all min cuts
	int num_edges = find_min_cut(flow2);
	if (max_flow == 0)
		num_edges = 0;

	int max_f = max_flow;
	vector<int> solution;
	int found = 0;
	//iterate through all edges and see which ones are part of the min cut
	//search from low index to high index to get lexiographically smallest solution 
	for (int i = 0; i < edges.size(); ++i) {
		Edge ed = edges[i];
		//construct a new graph with the edge removed
		PushRelabel graph2(v + 1);
		for (int j = 0; j < edges.size(); ++j) {
			if (j == i)
				continue;
			graph2.AddEdge(edges[j].from, edges[j].to, edges[j].cap);
		}
		int f = graph2.GetMaxFlow(1, v);
		int num = find_min_cut(graph2, i);
		if (f == 0)
			num = 0;
		//If the edge is part of a min cut, removing it must decrease the min cut by the capacity of the edge
		//Also, if the edge is part of the minimum edge min cut, removing it must decrease the size of the
		//min cut by one
		if (f == max_f - ed.cap && num == num_edges - 1 && found < num_edges) {
			solution.push_back(i + 1);
			++found;
		}
	}

	fout << max_flow << " " << solution.size() << endl;
	for (int s : solution) {
		fout << s << endl;
	}

	return 0;
}