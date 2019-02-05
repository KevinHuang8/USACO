/*
ID: Kevun1
LANG: C++11
TASK: milk4
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("milk4.in");
ofstream fout("milk4.out");

vector<int> pails;
bool found = false;
vector<int> answer;
int q, p;

/*
see below for meaning of dp

to calculate the dp when you add an additional pail to the list, use

dp[x] = true if dp[x - pail] is true

if you can make dp[Q] true, then you are done
*/
bool can_use(int pail, vector<bool> &dp) {
	dp[pail] = true;
	for (int i = 1; i <= q - pail; ++i) {
		if (dp[i]) {
			if (i + pail == q)
				return true;
			dp[i + pail] = true;
		}
	}
	return false;
}

//pail = index of pail, not value
//dfs with iterative deepening
/*
example of search tree with q=16, pails={3, 5, 7}

    start
	/  |  \
   3   5   7
  / \  |   
  5  7 7  
  |
  7

go from maxdepth = 1 to p
for each maxdepth, you are looking for a solution of that length. You go from smallest maxdepth to maximum to
find the minimum length solution.

used stores the current path down the tree, representing the solution

dp[x] - bool representing whether you can make x with all of the current pails in the tree, i.e. the ones in used

at each step, calculate whether or not you can make Q with the current pails in "used". If you can, you are done. The reason
you don't have to keep searching is because the search tree is designed in such a way that you branch out to the smallest
pail size first, and you encounter the minimum length solution first due to iterative deepening.

*/
void dfs(int pail, vector<int> used, vector<bool> dp, int depth) {
	if (found)
		return;

	if (pail != -1)
		used.push_back(pails[pail]);

	if (pail != -1 && can_use(pails[pail], dp)) {
		found = true;
		answer = used;
		return;
	}

	if (depth == 0)
		return;

	for (int i = pail + 1; i < pails.size(); ++i) {
		dfs(i, used, dp, depth - 1);
	}
}

int main(){
	fin >> q >> p;

	for (int i = 0; i < p; ++i) {
		int pail;
		fin >> pail;
		bool add = true;
		//get rid of unnecessary pails
		for (int i = 0; i < pails.size(); ++i) {
			//i.e. if you have 6, then you add 3, you don't need the 6
			//do this for each multiple of the newly added pail. If there are multiple, duplicates are created
			if (pails[i] % pail == 0) {
				pails[i] = pail;
				add = false;
			}
			//i.e. if you already have 3, then you don't need to add 6
			if (pail % pails[i] == 0) {
				add = false;
				break;
			}
		}
		if (add)
			pails.push_back(pail);
	}

	//removes duplicates created
	sort(pails.begin(), pails.end());
	auto x = unique(pails.begin(), pails.end());
	pails.erase(x, pails.end());

	vector<int> used; vector<bool> dp(q + 1);
	for (int i = 1; i <= p; ++i) {
		if (!found)
			dfs(-1, used, dp, i);
	}

	fout << answer.size();
	for (int a : answer) {
		fout << " " << a;
	}
	fout << endl;

	return 0;
}