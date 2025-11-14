/*
Pseudocode


vector recursiveLeft(arr, start, end) {
	if start == end return vector<int>{start};

	mid = (start + end) / 2;

	left = recursiveLeft(arr, start, mid);
	right = recursiveLeft(arr, mid + 1, end);

	max = 0;
	for(int i = 0; i < left.length(); i++) {
		if max < arr[left[i]] {max = arr[left[i]]};
	}

	vector combined = left;
	for(int i = 0; i < right.length(); i++) {
		if arr[right[i]] > max {combined.append(right[i])};
	}

	return combined;
}

vector recursiveRight(arr, start, end) {
	if start == end return vector<int>{start};

	mid = (start + end) / 2;

	left = recursiveRight(arr, start, mid);
	right = recursiveRight(arr, mid + 1, end);

	max = 0;
	for(int i = 0; i < right.length(); i++) {
		if max < arr[right[i]] {max = arr[right[i]]};
	}

	vector combined = right;
	for(int i = 0; i < left.length(); i++) {
		if arr[left[i]] > max {combined.append(left[i])};
	}

	return combined;
}
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<int> recursiveLeft(std::vector<int> list, int start, int end);
std::vector<int> recursiveRight(std::vector<int> list, int start, int end);


int main() {
	std::ifstream input;
	input.open("input1.txt");
	if(!input) {
		std::cerr << "Error: Could not open input file." << std::endl;
		return 1;
	}

	std::vector<int> list;
	char c;
	std::string temp = "";
	int state = 0;
	while(input.get(c)) {
		switch(state) {
			case 0:
				if(c == '[') {state = 1;}
				break;
			case 1:
				if(isdigit(c)) {temp += c;}
				else if(c == ',') {list.push_back(stoi(temp)); temp = "";}
				else if(iswspace(c)) {}
				else if(c == ']') {list.push_back(stoi(temp)); temp = ""; state = 2;}
				else {state = 3;}
				break;
			case 2:
				break;
			case 3:
				std::cerr << "Error: invalid input. Should be [#,#,#,#...]";
				return 1;
				break;			
		}
	}

	std::vector<int> left = recursiveLeft(list, 0, list.size() - 1);
	std::vector<int> right = recursiveRight(list, 0, list.size() - 1);

	input.close();

	std::ofstream output;
	output.open("output1.txt");
	if(!output) {
		std::cerr << "Error: Could not open output file." << std::endl;
		return 1;
	}

	output << "Left view --> [";
	for(long unsigned int i = 0; i < left.size(); i++) {
		output << left[i];
		if(i != left.size() - 1) {
			output << ", ";
		}
	}
	output << "]" << std::endl;
	output << "Right view --> [";
	for(long unsigned int i = 0; i < right.size(); i++) {
		output << right[i];
		if(i != right.size() - 1) {
			output << ", ";
		}
	}
	output << "]" << std::endl;

	output.close();

	return 0;
}

std::vector<int> recursiveLeft(std::vector<int> list, int start, int end) {
	if(start == end) {
		return std::vector<int>{start};
	}

	int mid = (start + end) / 2;

	std::vector<int> left = recursiveLeft(list, start, mid);
	std::vector<int> right = recursiveLeft(list, mid + 1, end);

	int max = 0;
	for(long unsigned int i = 0; i < left.size(); i++) {
		if(max < list[left[i]]) {
			max = list[left[i]];
		}
	}

	std::vector<int> combined = left;
	for(long unsigned int i = 0; i < right.size(); i++) {
		if(list[right[i]] > max) {
			combined.push_back(right[i]);
		}
	}

	return combined;
}

std::vector<int> recursiveRight(std::vector<int> list, int start, int end) {
	if(start == end) {
		return std::vector<int>{start};
	}

	int mid = (start + end) / 2;

	std::vector<int> left = recursiveRight(list, start, mid);
	std::vector<int> right = recursiveRight(list, mid + 1, end);

	int max = 0;
	for(long unsigned int i = 0; i < right.size(); i++) {
		if(max < list[right[i]]) {
			max = list[right[i]];
		}
	}

	std::vector<int> combined = right;
	for(long unsigned int i = 0; i < left.size(); i++) {
		if(list[left[i]] > max) {
			combined.push_back(left[i]);
		}
	}

	return combined;
}
