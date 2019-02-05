/*
ID: Kevun1
LANG: C++11
TASK: shopping
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
ifstream fin("shopping.in");
ofstream fout("shopping.out");

//cost[a][b][c][d][e] = cost to buy a, b, c, d, e quantity of products 1, 2, 3, 4, 5
//cost[a][b][c][d][e] = min(cost[a - o_a][b - o_b][c - o_c][d - o_d][e - o_e] + o_price) for all offers
//where o_x = number of product x you must buy with a particular offer
//basically chooses the best offer to use to get to that amount
int cost[6][6][6][6][6];

struct offer {
	int price;
	//items_to_quantity[a] = number of items of a
	int items_to_quantity[1001] = { 0 };
};

/*
DP
*/
int main(){
	int n_offers;
	fin >> n_offers;
	vector<offer> offers;
	vector<int> products = { 1000, 1000, 1000, 1000, 1000 };
	int quotas[6] = { 0 };
	for (int of = 0; of < n_offers; ++of) {
		offer deal;
		int n_items;
		fin >> n_items;
		for (int i = 0; i < n_items; ++i) {
			int key, amount;
			fin >> key >> amount;
			deal.items_to_quantity[key] = amount;
		}
		int price;
		fin >> price;
		deal.price = price;
		offers.push_back(deal);
	}
	int n_prods;
	fin >> n_prods;
	for (int prod = 0; prod < n_prods; ++prod) {
		offer deal;
		int key, quota, price;
		fin >> key >> quota >> price;
		deal.items_to_quantity[key] = 1;
		deal.price = price;
		offers.push_back(deal);
		products[prod] = key;
		quotas[prod] = quota;
	}
	cost[0][0][0][0][0] = 0;
	for (int p1 = 0; p1 < 6; ++p1) {
		for (int p2 = 0; p2 < 6; ++p2) {
			for (int p3 = 0; p3 < 6; ++p3) {
				for (int p4 = 0; p4 < 6; ++p4) {
					for (int p5 = 0; p5 < 6; ++p5) {
						if (p1 == 0 && p2 == 0 && p3 == 0 && p4 == 0 && p5 == 0)
							continue;
						int min_price = 2100000000;
						for (int of = 0; of < offers.size(); ++of) {
							int q1 = p1 - offers[of].items_to_quantity[products[0]];
							if (q1 < 0)
								continue;
							int q2 = p2 - offers[of].items_to_quantity[products[1]];
							if (q2 < 0)
								continue;
							int q3 = p3 - offers[of].items_to_quantity[products[2]];
							if (q3 < 0)
								continue;
							int q4 = p4 - offers[of].items_to_quantity[products[3]];
							if (q4 < 0)
								continue;
							int q5 = p5 - offers[of].items_to_quantity[products[4]];
							if (q5 < 0)
								continue;
							int c = cost[q1][q2][q3][q4][q5] + offers[of].price;
							if (c < min_price)
								min_price = c;
						}
						cost[p1][p2][p3][p4][p5] = min_price;
					}
				}
			}
		}
	}

	fout << cost[quotas[0]][quotas[1]][quotas[2]][quotas[3]][quotas[4]] << endl;

	return 0;
}