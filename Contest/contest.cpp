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
ifstream fin("citystate.in");
ofstream fout("citystate.out");

set<string> states;
unordered_map<string, map<string, int>> cities;

int main(){
	int n;
	fin >> n;

	int count = 0;
	for (int i = 0; i < n; ++i) {
		string city, state;
		fin >> city >> state;
		city = city.substr(0, 2);
		states.insert(state);
		if (cities.find(state) == cities.end()) {
			map<string, int> s;
			cities[state] = s;
		}
		++cities[state][city];
	}

	for (string state : states) {
		for (auto p : cities[state]) {
			string city = p.first;
			int repeats = p.second;
			for (int i = 0; i < repeats; ++i) {
				//a state has the same name as the city
				if (cities.find(city) != cities.end() && city != state) {
					//if that state has a city w/ the same name as the original state
					if (cities[city].find(state) != cities[city].end())
						count += cities[city][state];
				}
			}
		}
	}

	fout << count / 2 << endl;

	return 0;
}