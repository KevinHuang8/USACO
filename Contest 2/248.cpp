/*
ID: Kevun1
LANG: C++11
TASK: name
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


ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("name.in");
//ofstream fout("name.out");
/*
public class two48 {
public static void main(String[] args) throws IOException {
BufferedReader br = new BufferedReader(new FileReader("248.in"));
PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("248.out")));
int n = Integer.parseInt(br.readLine());
int[] list = new int[n];
for(int i = 0; i < n; i++) {
list[i] = Integer.parseInt(br.readLine());
}
int[][] dp = new int[n][n];
int ret = 0;
for(int len = 1; len <= n; len++) {
for(int i = 0; i + len <= n; i++) {
int j = i+len-1;
dp[i][j] = -1;
if(len == 1) {
dp[i][j] = list[i];
}
for(int k = i; k < j; k++) {
if(dp[i][k] == dp[k+1][j] && dp[i][k] > 0) {
dp[i][j] = Math.max(dp[i][j], dp[i][k] + 1);
}
}
ret = Math.max(ret, dp[i][j]);
}
}
pw.println(ret);
pw.close();
}
}
*/
int main(){
	int n;
	fin >> n;
	vector<int> seq;
	for (int i = 0; i < n; ++i) {
		int x;
		fin >> x;
		seq.push_back(x);
	}

	int dp[250][250];

	int ret = 0;
	for (int len = 1; len <= n; ++len) {
		for (int i = 0; i + len <= n; ++i) {
			int j = i + len - 1;
			dp[i][j] = -1;
			if (len == 1) {
				dp[i][j] = seq[i];
			}
			for (int k = i; k < j; ++k) {
				if (dp[i][k] == dp[k + 1][j] && dp[i][k] > 0) {
					dp[i][j] = max(dp[i][j], dp[i][k] + 1);
				}
			}
			ret = max(ret, dp[i][j]);
		}
	}
	fout << ret << endl;
	return 0;
}