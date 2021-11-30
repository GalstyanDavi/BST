#include"avlbst.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main()
{
	std::cout << "-------------BST------------------------" << std::endl;
	BinarySearchTree<int, int > bst;
	bst.insert(std::pair<int, int>(2, 2));
	bst.insert(std::pair<int, int>(1, 1));
	bst.insert(std::pair<int, int>(3, 3));
	bst.insert(std::pair<int, int>(1, 11));
	bst.insert(std::pair<int, int>(10, 10));
	bst.insert(std::pair<int, int>(8, 8));
	bst.insert(std::pair<int, int>(4, 4));
	bst.remove(10);
	bst.print();
	

	std::cout << "-------------AVL------------------------" << std::endl;
	AVLTree<int, int> avl;
	avl.insert(std::pair<int, int>(1, 1));
	avl.insert(std::pair<int, int>(1, 11));
	avl.insert(std::pair<int, int>(2, 2));
	avl.insert(std::pair<int, int>(3,3));
	avl.insert(std::pair<int, int>(4, 4));
	avl.insert(std::pair<int, int>(5, 5));
	avl.insert(std::pair<int, int>(6, 6));
	avl.insert(std::pair<int, int>(7, 7));
	avl.insert(std::pair<int, int>(8, 8));
	avl.insert(std::pair<int, int>(9, 9));
	avl.insert(std::pair<int, int>(10, 10));
	avl.print();


}
