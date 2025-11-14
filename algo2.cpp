/*
Pseudocode

greedySelect(list) {
	sorted = sortList(list);

	selected;
	time = 0

	for each item in sorted {
		if(time <= item.start) {
			selected.push_back(item);
			time = item.finish;
		}
	}

	return selected;
}


*/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct Activity {
	int start;
	int finish;
	Activity(int s, int f) : start(s), finish(f) {}
};

std::vector<Activity> greedySelect(std::vector<Activity> list);

int main() {
	std::ifstream input;
	input.open("input2.txt");
	if(!input) {
		std::cerr << "Error: Could not open input2.txt.";
		return 1;
	}

	std::vector<Activity> list;
	char c;
	int state = 0;
	std::string temp1 = "";
	std::string temp2 = "";
	while(input.get(c)) {
		switch(state) {
			case 0:
				if(c == '(') {state = 1;}
				break;
			case 1:
				if(isdigit(c)) {temp1 += c;}
				else if(c == ',') {state = 2;}
				else if(iswspace(c)) {}
				else state = 3;
				break;
			case 2:
				if(isdigit(c)) {temp2 += c;}
				else if(iswspace(c)) {}
				else if(c == ')') {list.push_back(Activity(stoi(temp1), stoi(temp2))); temp1 = temp2 = ""; state = 0;}
				else state = 3;
				break;
			case 3:
				std::cerr << "Error: Invalid input formatting. Should be (#,#) per item.";
				return 1;
				break;
		}
	}

	std::vector<Activity> result = greedySelect(list);
	input.close();

	std::ofstream output;
	output.open("output2.txt");
	if(!output) {
		std::cerr << "Error: Could not open output2.txt";
		return 1;
	}

	output << "[";
	for(long unsigned int i = 0; i < result.size(); i++) {
		output << "(" << result[i].start << ", " << result[i].finish << ")";
		if(i != result.size() - 1) {
			output << ", ";
		}
	}
	output << "]" << std::endl;
	output.close();

	return 0;
}

bool compare(Activity &a1, Activity &a2) {
	return a1.finish < a2.finish;
}

std::vector<Activity> greedySelect(std::vector<Activity> list) {
	std::sort(list.begin(), list.end(), compare);

	std::vector<Activity> selected;
	int time = 0;

	for(long unsigned int i = 0; i < list.size(); i++) {
		if(list[i].start >= time) {
			selected.push_back(list[i]);
			time = list[i].finish;
		}
	}

	return selected;
}
