//Email : cerro005@cougars.csusm.edu
// Name: William Cerros
// Student ID: Cerro005
//Email : cerro005@cougars.csusm.edu


#include <fstream>
#include <iostream>
#include <unordered_map>
#include <iterator>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

//Map will hold the frequency values for each Char
//Key = Char, Mapped Value = Frequency

unordered_map<char, int> frequency_map;
unordered_map<char, string> huffmanCode;


/* Huffman Tree Node*/
struct HT_Node
{
	char ch;
	int weight;
	HT_Node* lc;
	HT_Node* rc;
};

/* Function will create a new tree node */
HT_Node* create_node(char ch, int freq, HT_Node* lc, HT_Node* rc)
{
	HT_Node* node = new HT_Node();

	node->ch = ch;
	node->weight = freq;
	node->lc = lc;
	node->rc = rc;
	return node;
}

/* Object will be used to compare the weight values of two nodes 
   This will order our heap */
struct comp
{
	bool operator()(HT_Node* lc, HT_Node* rc)
	{
		return lc->weight > rc->weight;
	}
};

/* Traversing the huffman tree and storing the huffman code in a map */
void fill_huffmanCode(HT_Node* root, string str)
{
	if (root == nullptr)
		return;

	if (!root->lc && !root->rc) {
		huffmanCode[root->ch] = str;
	}

	fill_huffmanCode(root->lc, str + "0");
	fill_huffmanCode(root->rc, str + "1");
}

HT_Node* buildHuffmanTree()
{
	/* We will use a priority queue to store the nodes of Huffman Tree */
	priority_queue<HT_Node*, vector<HT_Node*>, comp> pq;

	/* Each char will be placed into a leaf node, and added to priority queue */
	for (auto pair : frequency_map) {
		pq.push(create_node(pair.first, pair.second, nullptr, nullptr));
	}

	/* While loop will remove leaf nodes and join them in a tree */
	/* The process continues until we have only one tree 5*/
	while (pq.size() != 1) {
		/* Remove the two nodes with highest priority */
		/* The lower frequency the higher the prioriry */
		HT_Node* left = pq.top();
		pq.pop();
		HT_Node* right = pq.top();
		pq.pop();

		/* New internal node will be created with previous two nodes as children */
		/* Internal node frequency is equal to the sum of children frequencies */
		/* Add new internal node to the priority queue */
		int sum = left->weight + right->weight;
		pq.push(create_node('\0', sum, left, right));
	}

	/* Root node is the pointer to the top of the Huffman Tree */
	HT_Node* root = pq.top();

	/* Now we traverse the Huffman Tree and place Huffman Codes in a map */
	fill_huffmanCode(root, "");

	/* Printing out huffman codes */
	cout << "Printing Huffman Codes" << endl;
	for (auto pair : huffmanCode)
		cout << pair.first << " " << pair.second << endl;

	cout << "\n";

	return root;
}

/* Takes a string in the form of a char array and translates it to its huffman code */
const char* encode(const char* text) {
	string temp(text);
	// print encoded string
	string str = "";
	for (char ch : temp) {
		str += huffmanCode[ch];
	}

	const char* code = str.c_str();

	cout << code << endl;
	return code;
}

/* Decode method will traverse from the root node down to the leaf node to decode the encoded string */
void decode(HT_Node* root, int& index, string str)
{
	if (root == nullptr)
		return;

	if (!root->lc && !root->rc)
	{
		cout << root->ch;
		return;
	}


	index++;

	if (str[index] == '0')
		decode(root->lc, index, str);
	else
		decode(root->rc, index, str);
}

/* Function will read the contents of freq.txt and place the char with its associated frequency value
   into a map */
void readFreq()
{
	ifstream inFile;
	string line;
	string temp_value;
	string temp_key;
	char key;
    int mapped_value;
	stringstream ss;
	inFile.open("freq.txt");
	if (!inFile) {
		cout << "Unable to open file.";
		cout << "Program will close.";
		exit(1);
	}

	/* Extracting the key and its mapped value then placing them into a map */
	while (getline(inFile, line)) {
		temp_key = line.substr(1, 1);
		key = temp_key[0];
		temp_value = line.substr(7, 3);
		mapped_value = stoi(temp_value);
		frequency_map.insert(pair<char, int>(key, mapped_value));
	}


	cout << "Printing Frequency Map" << endl;
	for (auto pair : frequency_map)
		cout << pair.first << " " << pair.second << endl;

	cout << "\n";
}

int main()
{
	readFreq();
	HT_Node* root = buildHuffmanTree();
	const char* str = "Hello World ";
	cout << "String to encode: " << str << endl;
	cout << "Encoded String is: ";
	encode(str);

	cout << "\n\n";

	int index = -1;
	string encoded_string = "1010100100010100111010011001000110111000100000110100101110101110100010010011";
	cout << "Encoded String to decode: " << encoded_string << endl;
	cout << "Decoded string is: ";
	while (index < (int) encoded_string.size() - 2) {
		decode(root, index, encoded_string);
	}

	cout << "\n\n";
}