#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <fstream>
#include <string>


using namespace std;

typedef struct node node;


struct node {
	int index;
	int size;
	string name;
	vector<node*> children;
	node* parent;
	long total;
};


void printTree(node* x) {
	cout << "name =" << x->name << endl;
	for (int i = 0; i < (x->children.size()); i++) {
		cout << "children =" << (x->children.at(i)->name) << endl;
	}
}

node* newNode(string name, node* parent = nullptr, int size = 0) {
	node* newnode = new node;
	newnode->name = name;
	newnode->size = size;
	if (parent != nullptr) {
		for (int i = 0; i < parent->children.size(); i++) {
			if (parent->children.at(i) == newnode) {
				break;
			}
			else if (i + 1 == parent->children.size()) {
				parent->children.push_back(newnode);
			}
		}
		newnode->parent = parent;
	}
	return newnode;
}


int main() {

	ifstream file("Tree.txt");
	string str;
	string cd = "$ cd";
	string ls = "$ ls";
	string dir = "dir";
	node* current = NULL;
	node* root = newNode("/");
	node* test = newNode("test");
	root->children.push_back(test);



	while (getline(file, str)) {
		if (str.substr(0, 4) == cd) {
			string dirname = str.substr(5);
			if (dirname == "/") {
				current = root;
			}
			else if (dirname == "..") {
				current = current->parent;
			}
			else {
				dirname = str.substr(5);
				newNode(dirname, current);
			}
		}
		else if (str.substr(0, 4) == ls) {

			string line;
			vector<string> lines;
			
			while (!file.eof() && file.peek() != '$') {
						getline(file, line);
						lines.push_back(line);
					}
				for (int i = 0; i < lines.size(); i++) {
					if (lines.at(i).substr(0, 3) == dir) {
						string dirname = lines.at(i).substr(5);
						newNode(dirname, current);
					}
					else {
						for (int k = 0; k+1 < lines.at(i).length(); k++) {
							if (lines.at(i)[k] == ' ') {
								int size = stoi(lines.at(i).substr(0, k));
								string filename = lines.at(i).substr(k+1);
								newNode(filename, current, size);
								break;
							}

						}
					}

				}
				lines.clear();
			}
		}
	printTree(root);
	}
