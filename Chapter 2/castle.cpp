/*
ID: Kevun1
LANG: C++11
TASK: castle
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("castle.in");
ofstream fout("castle.out");

//pair hash
struct key_hash : public unary_function<pair<int, int>, size_t>
{
	size_t operator()(const pair<int, int>& k) const
	{
		return k.first ^ k.second;
	}
};

int width, height;
unordered_map<pair<int, int>, vector<pair<int, int>>, key_hash> adjacency_list;
//maps input id -> list of directions w/o a wall
unordered_map<int, vector<char>> key_map;
vector<pair<int, int>> modules;

void populate_key_map() {
	vector<char> c = { 'N', 'E', 'S' };
	key_map[1] = c;
	c = { 'W','S','E' };
	key_map[2] = c;
	c = { 'E','S' };
	key_map[3] = c;
	c = { 'N','W','S' };
	key_map[4] = c;
	c = { 'N','S' };
	key_map[5] = c;
	c = { 'W','S' };
	key_map[6] = c;
	c = { 'S' };
	key_map[7] = c;
	c = { 'W','N','E' };
	key_map[8] = c;
	c = { 'N','E' };
	key_map[9] = c;
	c = { 'W','E' };
	key_map[10] = c;
	c = { 'E' };
	key_map[11] = c;
	c = { 'N','W' };
	key_map[12] = c;
	c = { 'N' };
	key_map[13] = c;
	c = { 'W' };
	key_map[14] = c;
	c = {};
	key_map[15] = c;
	c = { 'N','S','E','W' };
	key_map[0] = c;
}

//returns the id of a adjacent module, on the left, right, top, or bottom, (-1, -1) means does not exist
pair<int, int> get_adjacent(pair<int, int> module, char direction) {
	if (direction == 'N') {
		if (module.first == 1)
			return make_pair(-1, -1);
		return make_pair(module.first - 1, module.second);
	}
	else if (direction == 'E') {
		if (module.second == width)
			return make_pair(-1, -1);
		return make_pair(module.first, module.second + 1);
	}
	else if (direction == 'S') {
		if (module.first == height)
			return make_pair(-1, -1);
		return make_pair(module.first + 1, module.second);
	}
	else if (direction == 'W') {
		if (module.second == 1)
			return make_pair(-1, -1);
		return make_pair(module.first, module.second - 1);
	}
	return make_pair(-1, -1);
}

//add value to adjacency_list[key], creates a new vector if none existed
void map_add(pair<int, int> key, pair<int, int> value) {
	if (adjacency_list.find(key) == adjacency_list.end()) {
		vector<pair<int, int>> v;
		adjacency_list[key] = v;
	}
	adjacency_list[key].push_back(value);
}

//module id -> component number
unordered_map<pair<int, int>, int, key_hash> component;
//component # -> component size
unordered_map<int, int> component_sizes;
unordered_set<pair<int, int>, key_hash> visited;
int flood_fill(pair<int, int> node, int curr_component) {
	int size = 1;
	component[node] = curr_component;
	visited.insert(node);
	for (pair<int, int> adjacent : adjacency_list[node]) {
		if (visited.find(adjacent) == visited.end()) {
			size += flood_fill(adjacent, curr_component);
		}
	}
	return size;
}

/*
Flood fill
*/
int main(){
	populate_key_map();

	fin >> width >> height;
	for (int h = 1; h <= height; ++h) {
		for (int w = 1; w <= width; ++w) {
			//id - how modules are identified
			pair<int, int> id = make_pair(h, w);
			int module;
			fin >> module;
			modules.push_back(id);
			//for solitary rooms
			if (key_map[module].empty()) {
				vector<pair<int, int>> v;
				adjacency_list[id] = v;
			}
			for (char c : key_map[module]) {
				map_add(id, get_adjacent(id, c));
			}
		}
	}
	int curr_component = 1;
	for (pair<int, int> module : modules) {
		if (visited.find(module) == visited.end()) {
			component_sizes[curr_component] = flood_fill(module, curr_component);
			++curr_component;
		}
	}
	int largest_combined = 0;
	//module that you remove the wall from
	pair<int, int> key_module;
	char direction;
	//iterate over each module; north to south, east to west
	//and try to remove the North and East walls of each module to see what happens
	for (int w = width; w >= 1; --w) {
		for (int h = 1; h <= height; ++h) {
			pair<int, int> id = make_pair(h, w);
			if (get_adjacent(id, 'E') != make_pair(-1, -1)) {
				pair<int, int> east = get_adjacent(id, 'E');
				if (component[east] != component[id] &&
					component_sizes[component[east]] + component_sizes[component[id]] >= largest_combined) {
					largest_combined = component_sizes[component[east]] + component_sizes[component[id]];
					key_module = id;
					direction = 'E';
				}
			}
			if (get_adjacent(id, 'N') != make_pair(-1, -1)) {
				pair<int, int> north = get_adjacent(id, 'N');
				if (component[north] != component[id] &&
					component_sizes[component[north]] + component_sizes[component[id]] >= largest_combined) {
					largest_combined = component_sizes[component[north]] + component_sizes[component[id]];
					key_module = id;
					direction = 'N';
				}
			}
		}
	}

	//number of rooms
	fout << curr_component - 1 << endl;

	int largest_room = 0;
	for (int i = 1; i < curr_component; ++i) {
		if (component_sizes[i] > largest_room)
			largest_room = component_sizes[i];
	}
	fout << largest_room << endl;

	fout << largest_combined << endl;

	fout << key_module.first << " " << key_module.second << " " << direction << endl;

	return 0;
}