#define _CRT_SECURE_NO_WARNINGS
#include"BSTree.h"


int main()
{
	K::BSTree<int> bst;

	bst.Insert(1);
	bst.Insert(5);
	bst.Insert(6);
	bst.Insert(10);
	bst.Insert(18);
	bst.Insert(3);
	bst.Insert(4);

	bst.InOrder();

	bst.Erase(1);
	bst.Erase(1);
	bst.InOrder();

	bst.Erase(10);
	bst.Erase(4);
	bst.InOrder();
	return 0;
}