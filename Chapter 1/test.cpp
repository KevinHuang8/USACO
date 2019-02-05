/*
ID: Kevun1
LANG: C++11
TASK: name
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


ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("name.in");
//ofstream fout("name.out");

struct a {
	int var;
	a(int param) : var(param) {}
	void change() {
		var += 1;
	}
};

void modify(a& x) {
	x.var += 1;
	x.change();
}

int main(){
	a foo(5);
	modify(foo);
	cout << foo.var << endl;
	return 0;
}