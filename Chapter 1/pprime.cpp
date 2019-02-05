/*
ID: Kevun1
LANG: C++11
TASK: pprime
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
ifstream fin("pprime.in");
ofstream fout("pprime.out");

bool is_prime(int n) {
	if (n % 2 == 0)
		return false;

	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0)
			return false;
	}

	return true;
}
/*
Generate all palindromes and test which ones are prime
*/
int main() {
	int a, b;
	fin >> a >> b;

	vector<int> prime_palindromes;

	//one digit
	for (int d1 = 1; d1 <= 9; d1 += 2) {
		int palindrome = d1;
		if (palindrome >= a && is_prime(palindrome)) {
			prime_palindromes.push_back(palindrome);
		}
	}

	//two - three digits
	for (int d1 = 1; d1 <= 9; d1 += 2) {
		int palindrome = 10 * d1 + d1;
		if (palindrome >= a && palindrome <= b && is_prime(palindrome)) {
			prime_palindromes.push_back(palindrome);
		}
		for (int d2 = 0; d2 <= 9; ++d2) {
			int palindrome2 = 100 * d1 + 10 * d2 + d1;
			if (palindrome2 >= a && palindrome2 <= b && is_prime(palindrome2)) {
				prime_palindromes.push_back(palindrome2);
			}
		}
	}

	//four to five digits
	for (int d1 = 1; d1 <= 9; d1 += 2) {
		for (int d2 = 0; d2 <= 9; ++d2) {
			int palindrome = 1000 * d1 + 100 * d2 + 10 * d2 + d1;
			if (palindrome >= a && palindrome <= b && is_prime(palindrome)) {
				prime_palindromes.push_back(palindrome);
			}
			for (int d3 = 0; d3 <= 9; ++d3) {
				int palindrome2 = 10000 * d1 + 1000 * d2 + 100 * d3 + 10 * d2 + d1;
				if (palindrome2 >= a && palindrome2 <= b && is_prime(palindrome2)) {
					prime_palindromes.push_back(palindrome2);
				}
			}
		}
	}

	//six to seven digits
	for (int d1 = 1; d1 <= 9; d1 += 2) {
		for (int d2 = 0; d2 <= 9; ++d2) {
			for (int d3 = 0; d3 <= 9; ++d3) {
				int palindrome = pow(10, 5)*d1 + pow(10, 4)*d2 + 1000 * d3 + 100 * d3 + 10 * d2 + d1;
				if (palindrome >= a && palindrome <= b && is_prime(palindrome)) {
					prime_palindromes.push_back(palindrome);
				}
				for (int d4 = 0; d4 <= 9; ++d4) {
					int palindrome2 = pow(10, 6)*d1 + pow(10, 5)*d2 + pow(10, 4)*d3 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
					if (palindrome2 >= a && palindrome2 <= b && is_prime(palindrome2)) {
						prime_palindromes.push_back(palindrome2);
					}
				}

			}
		}
	}

	//eight digits
	for (int d1 = 1; d1 <= 9; d1 += 2) {
		for (int d2 = 0; d2 <= 9; ++d2) {
			for (int d3 = 0; d3 <= 9; ++d3) {
				for (int d4 = 0; d4 <= 9; ++d4) {
					int palindrome = pow(10, 7)*d1 + pow(10, 6)*d2 + pow(10, 5)*d3 + pow(10, 4)*d4 + pow(10, 3)*d4
						+100 * d3 + 10 * d2 + d1;
					if (palindrome >= a && is_prime(palindrome)) {
						prime_palindromes.push_back(palindrome);
					}
				}
			}
		}
	}
	sort(prime_palindromes.begin(), prime_palindromes.end());

	for (int i : prime_palindromes) {
		fout << i << endl;
	}


	return 0;
}