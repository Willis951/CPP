//Email : cerro005@cougars.csusm.edu
//Name: William Cerros
//Student ID: Cerro005
//Email : cerro005@cougars.csusm.edu

/* Program will create Binary Tree Search Tree. User will populate tree by entering a list of numbers seperated by a space. 
   Program includes function to traverse tree in PreOrder, Inorder, and PostOrder. Program also includes a search function 
   and a remove function. */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* Binary Search Tree Class*/
class BST {
	/* Structure of Tree Nodes */
	struct Node {
		int key;
		Node* left;
		Node* right;
	};

	/* Root of a Binary Tree and any subsequent subtrees */
	Node* root;


	Node* insert(int key, Node* newNode) {
		if (newNode == NULL) {
			newNode = new Node;
			newNode->key = key;
			newNode->left = newNode->right = NULL;
		}

		else if (key < newNode->key)
			newNode->left = insert(key, newNode->left);
		else if (key > newNode->key)
			newNode->right = insert(key, newNode->right);

		return newNode;
	}

	Node* remove(int key, Node* target) {
		Node* temp;
		if (target == NULL) {
			cout << "Number not found. " << endl;
			cout << "\n";
			return NULL;
		}
		else if (key < target->key)
			target->left = remove(key, target->left);
		else if (key > target->key)
			target->right = remove(key, target->right);

		else if (target->left && target->right)
		{
			temp = rightMostNode(target->left);
			target->key = temp->key;
			target->left = remove(temp->key, target->left);
		}

		else {
			temp = target;
			if (target->left == NULL)
				target = target->right;
			else if (target->right == NULL)
				target = target->left;
			delete temp;
			cout << "Number has been deleted" << endl;
			cout << "\n";
		}

		return target;
	}

	Node* rightMostNode(Node* node) {
		Node* current = node;
		while (current->right != NULL)
			current = current->right;
		return current;
}

	Node* search(int key, Node* target) {
		if (target != NULL) {
			if (key == target->key) {
				cout << "Number found: " << target->key << endl;
				cout << "\n";
				return target;
			}

			if (key < target->key) {
				return search(key, target->left);
			}

			else {
				return search(key, target->right);
			}
		}

		else {
			cout << "Number not found." << endl;
			cout << "\n";
			return NULL;
		}
	}

	void inorder(Node* target) {
		if (target == NULL)
		{
			return;
		}

		inorder(target->left);
		cout << target->key << " ";
		inorder(target->right);
	}

	void preorder(Node* target) {
		if (target == NULL)
		{
			return;
		}

		cout << target->key << " ";
		preorder(target->left);
		preorder(target->right);
	}

	void postorder(Node* target) {
		if (target == NULL) {
			return;
		}

		postorder(target->left);
		postorder(target->right);
		cout << target->key << " ";
	}

public:
	BST() {
		root = NULL;
	}

	void insert(int key) {
		root = insert(key, root);
	}

	void remove(int key) {
		root = remove(key, root);
	}

	void displayInorder() {
		inorder(root);
		cout << endl;
	}

	void displayPreorder() {
		preorder(root);
		cout << "\n";
	}

	void displayPostorder() {
		postorder(root);
		cout << "\n";
	}

	Node* search(int key) {
		return search(key, root);
	}
};


/* Program will parse a string and extract the numbers, then place them in an array. After the string is parsed, the 
   contents of the array will be added to the BinaryTree. Numbers are parsed sequentially so the Binary Tree is populated
   in the order which the user enters the numbers. */
void parseString(string list, BST &binaryTree)
{
	int array[100]{ 0 };
	stringstream intList;
	string temp;
	int number;
	intList << list;
	int i = 0;
	
	/* Extracting numbers from the string */
	while (!intList.eof())
	{
		intList >> temp;

		if (stringstream(temp) >> number) {
			array[i] = number;
			i++;
		}
	}

	int k = 0;

	/* Inserting numbers into the Binary Tree */
	do {
		binaryTree.insert(array[k]);
		k++;
	} while (array[k] != 0);
	

}

/* Virtual menu that offers functions to user */
void bstMenu()
{
	cout << "Please make a selection " << endl;
	cout << "1.)Inorder Traversal" << endl;
	cout << "2.)PreOrder Traversal" << endl;
	cout << "3.)PostOrder Traveral" << endl;
	cout << "4.)Add" << endl;
	cout << "5.)Search" << endl;
	cout << "6.)Remove" << endl;
	cout << "7.)Exit" << endl;
}

/* Menu function serves as a virtual menu where user can create a Binary Search Tree */
void menu()
{
	BST binaryTree;
	int userChoice; //User either chooses to create a BST or AVL Tree
	string numberList; //List of numbers entered by user
	cout << " Welcome to the Binary Tree Program \n";
	cout << "Please make a selection \n";
	cout << "1.) Create BST \n";

	cin >> userChoice;
	cin.ignore();
	
	/* To create a BST, user must first enter a list of number to populate the tree */
	/* User can not enter number 0 since that number prefills the array */
	if (userChoice == 1) {
		cout << "\nPlease enter a list of numbers (except 0) to insert. Each number must be seperated by a space." << endl;
		getline(cin, numberList);
		parseString(numberList, binaryTree);

		int menuChoice;
		do {
			bstMenu();
			cin >> menuChoice;
			cin.ignore();

			/* Inorder Traversal */
			if (menuChoice == 1) {
				binaryTree.displayInorder();
				cout << "\n";
			}

			/* Preorder Traversal */
			else if (menuChoice == 2) {
				binaryTree.displayPreorder();
				cout << "\n";
			}

			/* Postorder Traversal */
			else if (menuChoice == 3) {
				binaryTree.displayPostorder();
				cout << "\n";
			}
			 /* Adding key to tree */
			else if (menuChoice == 4) {
				string numbers;
				cout << "Enter number(s) seperated by a space: ";
				getline(cin, numbers);
				parseString(numbers, binaryTree);
			}

			/* Searching for key */
			else if (menuChoice == 5) {
				cout << "Enter a number you would like to search for: " << endl;
				int key;
				cin >> key;
				cin.ignore();
				binaryTree.search(key);
			}

			/* Removing key */
			else if (menuChoice == 6) {
				cout << "Enter a number you would like to delete. " << endl;
				int key;
				cin >> key;
				cin.ignore();
				binaryTree.remove(key);
			}


			/* Exting Program*/
			else {
				cout << "goodbye!";
			}

		} while (menuChoice != 7); /* Loop runs until the user selects option 7*/

	}
}

int main()
{
	menu();
	return 0;
}

