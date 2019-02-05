/*
ID: Kevun1
LANG: C++11
TASK: lamps
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("lamps.in");
ofstream fout("lamps.out");

string press_button(string input, int button) {
	switch (button) {
	case 1:
		//toggle all
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] == '0')
				input[i] = '1';
			if (input[i] == '1')
				input[i] = '0';
		}
		break;
	case 2:
		//toggle odd
		for (int i = 0; i < input.size(); i += 2) {
			if (input[i] == '0')
				input[i] = '1';
			if (input[i] == '1')
				input[i] = '0';
		}
		break;
	case 3:
		//toggle even
		for (int i = 1; i < input.size(); i += 2) {
			if (input[i] == '0')
				input[i] = '1';
			if (input[i] == '1')
				input[i] = '0';
		}
		break;
	case 4:
		//toggle 3k + 1
		for (int k = 0; 3 * k < input.size(); ++k) {
			if (input[3*k] == '0')
				input[3*k] = '1';
			if (input[3*k] == '1')
				input[3*k] = '0';
		}
		break;
	}
	return input;
}

string reset_lamps(string input) {
	for (int i = 0; i < input.size(); ++i) {
		input[i] = '1';
	}
	return input;
}

int c;
vector<int> on_numbers;
vector<int> off_numbers;
//check is state is valid
bool check_validity(string state, int button_combos) {
	if (button_combos % 2 != c % 2 || button_combos > c)
		return false;
	for (int num : on_numbers) {
		//state starts indexing at 0, the numbers start with 1
		if (state[num - 1] != '1')
			return false;
	}
	for (int num : off_numbers) {
		if (state[num - 1] != '0')
			return false;
	}
	return true;
}

int main(){
	int n;
	fin >> n >> c;
	string lamps;
	for (int i = 0; i < n; ++i) {
		lamps += "1";
	}
	string original_lamps = lamps;
	int on_number;
	fin >> on_number;
	while (on_number != -1) {
		on_numbers.push_back(on_number);
		fin >> on_number;
	}
	int off_number;
	fin >> off_number;
	while (off_number != -1) {
		off_numbers.push_back(off_number);
		fin >> off_number;
	}

	set<string> results;
	//order of button presses doesn't matter, and pressing a switch more than once is the same as pressing
	//it x % 2 times. Therefore, it is like only pressing each switch only zero or one times
	for (int b1 = 0; b1 <= 1; ++b1) {
		for (int b2 = 0; b2 <= 1; ++b2) {
			for (int b3 = 0; b3 <= 1; ++b3) {
				for (int b4 = 0; b4 <= 1; ++b4) {
					if (b1)
						lamps = press_button(lamps, 1);
					if (b2)
						lamps = press_button(lamps, 2);
					if (b3)
						lamps = press_button(lamps, 3);
					if (b4)
						lamps = press_button(lamps, 4);

					//check if state is valid
					if (check_validity(lamps, b1 + b2 + b3 + b4)) {
						results.insert(lamps);
					}

					lamps = reset_lamps(lamps);
				}
			}
		}
	}

	for (string s : results) {
		fout << s << endl;
	}
	if (results.empty())
		fout << "IMPOSSIBLE" << endl;

	return 0;
}