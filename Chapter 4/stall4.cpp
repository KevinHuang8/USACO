/*
ID: Kevun1
LANG: C++11
TASK: stall4
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
#include <queue>
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("stall4.in");
ofstream fout("stall4.out");

typedef long long LL;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
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

int main(){
	int cows, stalls;
	fin >> cows >> stalls;

	PushRelabel flow(stalls + cows + 2);
	int sink = stalls + cows + 1;
	for (int i = 1; i <= cows; ++i) {
		int n;
		fin >> n;
		flow.AddEdge(0, i , 1);
		for (int j = 0; j < n; ++j) {
			int stall;
			fin >> stall;
			flow.AddEdge(i, cows + stall, 1);
		}
	}
	for (int i = cows + 1; i <= cows + stalls; ++i) {
		flow.AddEdge(i, sink, 1);
	}

	fout << flow.GetMaxFlow(0, sink) << endl;

	return 0;
}