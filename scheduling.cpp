#include"avlbst.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename Key>
void readFromFile(int & exams,int & students,int&slots,vector<vector<Key>>& classes,const string &path)
{
	std::fstream file(path, std::ios_base::in);

	file >> exams >> students >> slots;
	std::string str;
	getline(file, str);

	while (getline(file, str))
	{

		int index = 0;
		vector<int> class_numbers;
		while (index < str.size())
		{
			while (!(str[index] >= '0' && str[index] <= '9') && (index < str.size()))
				index++;
			string s_number = "";

			while ((str[index] >= '0' && str[index] <= '9') && (index < str.size()))
				s_number += str[index++];
			if (!s_number.empty())
				class_numbers.push_back(stoi(s_number));
		}
		classes.push_back(class_numbers);
	}

}

template <typename Key, typename Value>
void getSlots(const vector<vector<Value>>& classes, int row, int slot,const int & slots, AVLTree<Key, Value>& avl_slots)
{
	if (slot >= slots)
		return;
	if (row >= classes.size())
		return;
	for (int j = 0; j < classes[row].size(); j++)
	{
		if (!avl_slots.find(classes[row][j]))
		{
			avl_slots.insert(std::pair<Key, Value>(classes[row][j], slot++));
			for (int r = row + 1; r < classes.size(); r++)
			{
				if (find(classes[r ].begin(), classes[r].end(), classes[row][j]) != classes[r].end())
				{
					getSlots(classes, r , slot,slots, avl_slots);
				}
			}
		}
	}
	return;
}

template <typename Key, typename Value>
int getTreeSize(const AVLTree<int, int>& tree)
{
	int count = 0;
	for (typename BinarySearchTree<Key, Value >::iterator it = tree.begin(); it != tree.end(); ++it)
		count++;
	return count;
}

int main(int argc, char** argv)
{
	int exams = 0;
	int students = 0;
	int slots = 0;
	int slot = 1;
	int avl_slots_size = 0;
	std::vector<vector<int>> classes;
	string path;
	AVLTree<int, int> avl_slots;


	if (argc == 2) {
		path = argv[1];
	}
	else
	{
		cout << "Usage: ./scheduling InputFile\n";
		return 1;
	}
	try {

		readFromFile<int>(exams, students, slots, classes, path);

		for (int i = 0; i < classes.size(); i++) {
			getSlots<int, int>(classes, i, slot, slots, avl_slots);
		}

		avl_slots_size = getTreeSize<int, int>(avl_slots);
		if (exams == avl_slots_size)
			avl_slots.print();
		else
			std::cout << "No valid solution" << std::endl;
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
}