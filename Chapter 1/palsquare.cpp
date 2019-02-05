/*
ID: Kevun1
LANG: C++11
TASK: palsquare
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
ifstream fin("palsquare.in");
ofstream fout("palsquare.out");

//can do many base converting operations
class BaseConverter
{
public:
	static string to_base(int dec, int base) {
		int remainder;
		char encoded;
		string result;
		while (dec) {
			remainder = dec % base;
			encoded = encode(remainder);
			dec /= base;
			result = string(1, encoded) + result;
		}
		return result;
	}

	static string to_binary(int dec) {
		return to_base(dec, 2);
	}

	static int to_decimal(string n, int base) {
		int dec;
		int place_value = 1;
		for (int i = n.length() - 1; i >= 0; --i) {
			if (decode(n[i]) >= base)
				return -1;
			dec += decode(n[i]) * place_value;
			place_value *= base;
		}
		return dec;
	}

	static int bin_to_dec(string bin) {
		return to_decimal(bin, 2);
	}

	//converts 'n' from 'base1' to 'base2'
	static string base_to_base(string n, int base1, int base2) {
		return to_base(to_decimal(n, base1), base2);
	}

private:
	static char encode(int n) {
		if (n < 10)
			return '0' + n;
		return 'A' + n - 10;
	}

	static int decode(char c) {
		if (c >= '0' && c <= '9')
			return c - '0';
		return c - 'A' + 10;
	}

};

bool is_palindromic(string n) {
	string rev = n;
	reverse(rev.begin(), rev.end());
	return (rev == n);
}

int main(){
	int base;
	fin >> base;

	for (int i = 1; i <= 300; ++i) {
		string n = BaseConverter::to_base(i*i, base);
		if (is_palindromic(n)) {
			fout << BaseConverter::to_base(i, base) << " " << n << endl;
		}
	}

	return 0;
}