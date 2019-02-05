/*
ID: Kevun1
LANG: C++11
TASK: milk
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
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("milk.in");
ofstream fout("milk.out");

/*
Greedy, fractional knapsack
*/
int main(){
	int requirement, n_farmers;
	fin >> requirement >> n_farmers;
	vector<pair<int, int>> farmers;
	int price, amount;
	while (fin >> price >> amount) {
		farmers.push_back(make_pair(price, amount));
	}

	sort(farmers.begin(), farmers.end());

	int total_price = 0;
	for (int i = 0; i < farmers.size(); ++i) {
		int p = farmers[i].first;
		int a = farmers[i].second;
		
		int amount_purchased = min(requirement, a);

		requirement -= amount_purchased;
		total_price += amount_purchased*p;

		if (requirement == 0)
			break;
	}

	fout << total_price << endl;

	return 0;
}