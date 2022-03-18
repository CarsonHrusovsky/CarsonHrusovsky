//Binary Search Tree and Additional functions.
//NOTE: This program is designed to run with the 'treedata2021.txt file'.
#include <iostream>
#include <fstream>
using namespace std;

struct NODE { //Global structure for tree.
	
	int key;
	NODE* rchild;
	NODE* lchild;	
};
typedef NODE * NODEPTR;//Typedefs. NODEPTR can be used in place of node.

const int BLANKLINES = 10;
//===========Prototypes==================//
int main(void);
void openMenu();
void myclear_screen(const int lines);
void fileRead(NODEPTR & root);
void insertValue(NODEPTR & root, int num);
void printSorted(NODEPTR root);
void singleValue(NODEPTR & root);
void pause();
bool inTree(NODEPTR root, int num);
void lookupNum(NODEPTR root);
void deleteTree(NODEPTR & root);
void removeValue(NODEPTR & root, int num);
void whatValue(NODEPTR root);
void balanceTree(NODEPTR & root);
int nodeCounter(NODEPTR root);
void dataFiller(NODEPTR root, int data[], int & pos);
void balancer(NODEPTR & root, int c, int data[], int & pos);
int heightFinder(NODEPTR root);
void rootValue(NODEPTR root);
NODEPTR finMin(NODEPTR root);
void BFT(NODEPTR tree);
void heightFixer(NODEPTR root);

int main(void)
{
	int choice = 0;
	bool menuloop = true;
	NODEPTR root = NULL;
	do {
	
		myclear_screen(BLANKLINES); //clear screen
		openMenu(); //open menu
		
		cout << "Please print the value associated with the required function... ";
		cin >> choice;
		switch(choice)
		{
			
				case 1:
					fileRead(root);
					break;
				
				case 2:
					balanceTree(root);
					//BFT(root);
					break;
					
				case 3:
					lookupNum(root);
					break;
				case 4:
					heightFixer(root);
					break;
				case 5:
					printSorted(root);
					pause();
					break;
				case 6:
					rootValue(root);
					break;
				case 7:
					singleValue(root);
					break;
				case 8:
					whatValue(root);
					break;
				case 9:
					deleteTree(root);
					root = NULL;
					break;
				case 0:
					menuloop = false;
					break;
					
				
		
			};
		} while (menuloop);
}
void openMenu(void)
{
	
	
	cout << "Carson Hrusovsky" << endl; //Menu
	cout << "_________________________" << endl;
	cout << "=========================" << endl;
	cout << "==SEARCH TREE MAIN MENU==" << endl;
	cout << "=========================" << endl;
	cout << "_________________________" << endl;
	cout << "Options are as follows:" << endl;
	cout << "1.) Read integers from a file" << endl;
	cout << "2.) Balance the tree" << endl;
	cout << "3.) Look up a tree value" << endl;
	cout << "4.) Report the height of the tree" << endl;
	cout << "5.) Print sorted tree" << endl;
	cout << "6.) Report root node value" << endl;
	cout << "7.) Insert value into tree" << endl;
	cout << "8.) Delete value from tree" << endl;
	cout << "9.) Delete the whole tree" << endl;
	cout << "0.) Exit the program" << endl;
	cout << "_________________________" << endl;
	
	
}
void myclear_screen(const int lines)
{
	
	for (int i=0; i < lines; i++)
		cout << endl;
	
}
void pause() //Pause function
{
	char useless;
	cout << "Type any character to return to the main menu: ";
	cin >> useless;
}
void fileRead(NODEPTR & root) //Reading in file integers
{
	int fileNum;
	ifstream infile;
	infile.open("treedata2021.txt");
	
	if (!infile)
	{
		cerr << "Unable to open file!" ;
		exit(1);	
		
	} 
	infile >> fileNum;
	while (fileNum != -1)
		{
			//cout << fileNum << endl; //Testing Purposes Only
			insertValue(root, fileNum);
			infile >> fileNum;
			
		}
	
}
void singleValue(NODEPTR & root)//This program gets the value from the user to be entered into the tree
{
	int value=0;
	cout << "Print the value to add to the tree:" << endl;
	cin >> value;
	
	insertValue(root, value);
	
}
void insertValue(NODEPTR & root, int num) //This inserts values (Hence the name!)
{
	
	if (root == NULL)
	{
		root = new NODE;	
		root->lchild = NULL;
		root->rchild = NULL;
		root->key = num;
		return;
	}
	
	if (root->key == num) 
		return;

	if (root->key > num) {
		insertValue(root->lchild, num);
		}
	else {
		insertValue(root->rchild, num);
		}
	
	

}
void lookupNum(NODEPTR root) //Look up function. Takes in a variable and then feeds it to inTree function.
{
	int lookup=0;
	cout << "Enter the value you wish to look up: ";
	cin >> lookup;
	inTree(root, lookup);
	if(inTree(root,lookup) == true) //References the bool function below.
	{
		cout << "Yes it is here!" << endl;
		pause();
	}
	else
	{
		cout << "Not here!" << endl;
		pause();
	}
	
}
bool inTree(NODEPTR root, int num)
{
	if(root == NULL)
	{
		return false;
	}
	if(root->key == num)
	{
		return true;
	}
	
	if(root->key > num)
		return inTree(root->lchild, num);
	
	else
		return inTree(root->rchild, num);
}
void printSorted(NODEPTR root) 
{
	if(root == NULL)
	{
		return;
	}
		
	printSorted(root->lchild);
	
	cout << root->key << endl; //Print in sorted order
	
	printSorted(root->rchild);

	
}

void deleteTree(NODEPTR & root) //Delete tree function. I believe this one is working correctly
{
	if(root == NULL) 
	{					
		return;
	}
	
	deleteTree(root->lchild);
	deleteTree(root->rchild);	

	delete root;
	
	
}
void whatValue(NODEPTR root)//Finds the value you want to delete.
{
	int doneWith;
	cout << "Please enter the value you wish to delete: ";
	cin >> doneWith;
	removeValue(root, doneWith);
	
	
}
void removeValue(NODEPTR & root, int num) //Recursive delete node function that traverses the tree in order to find the value you want to delete.
{
	NODEPTR temp = NULL;
	NODEPTR tempPTR = NULL;
	
	if(root == NULL)
		return;
	
	if(root->key > num)
	{
		removeValue(root->lchild, num);	
	}
	else if(root->key < num)
	{
		removeValue(root->rchild, num);
	}
	else //If you get here you must be at the value you want to delete.
	{
		if(root->lchild == NULL) //Left is null, make root point to the next child, then delete root.
		{
			temp = root;
			root = root->rchild;
			delete temp;
		}
		else if(root->rchild == NULL) //Right is null, make root point to the next child, then delete root.
		{
			temp = root;
			root = root->lchild;
			delete temp;
		}
		else //Two Children
		{
			NODEPTR now = root->rchild;
			cout << "Test" << now->key << endl;
			tempPTR = finMin(now);
			cout << "Test" << now->key << endl;
			tempPTR = now;
			root->key = tempPTR->key;
			removeValue(root->rchild, root->key);
			
		}
	}
}
NODEPTR finMin(NODEPTR root)//Find minimum value for the delete value function.
{
	if(root->lchild != NULL)
	{
		return	finMin(root->lchild);
	}
	return root;
}
void balanceTree(NODEPTR & root) 
{
	int c = 0; //Counts number of node
	int pos = 0; //Keeps track of position in both dataFiller and balancer.
	c = nodeCounter(root);
	int * data = new int [c];
	dataFiller(root, data, pos); //Loads up array
	deleteTree(root);
	root = NULL;
	pos = 0;
	balancer(root, c, data, pos); //Balances tree using array
	delete [] data;


}
int nodeCounter(NODEPTR root) 
{
	int c = 1;
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		c += nodeCounter(root->lchild);
		c += nodeCounter(root->rchild);
		return c;
	}
	

}
void dataFiller(NODEPTR root, int data[], int & pos) //loads up array
{

		
	if(root == NULL)
	{
		return;
	}
	
		
	dataFiller(root->lchild, data, pos);
	
	data[pos++] = root->key;
			
	dataFiller(root->rchild, data, pos);
	
	
}
void balancer(NODEPTR & root, int c, int data[], int & pos) //Balances tree by dividing in half via the root node.
{
	if (c > 0)
	{
		root = new NODE;
		root->lchild = NULL;
		root->rchild = NULL;
		balancer(root->lchild, c/2, data, pos);
		root->key = data[pos];
		pos++;
		balancer(root->rchild, (c-1)/2, data, pos);	
	}
	
}
int heightFinder(NODEPTR root)  
{
	if(root == NULL)
		return 0;
		
	return 1 + max(heightFinder(root->lchild), heightFinder(root->rchild));
}
void rootValue(NODEPTR root)
{
	
	cout << "The root value is "; 
	cout << root->key << endl;
	pause();
	
	
}
void heightFixer (NODEPTR root)
{
	int fixed = 0;
	fixed = heightFinder(root);
	if(fixed!=0)
	{			
		fixed = fixed-1;
		cout << fixed << endl;
	}
	else
	{
		fixed = 0;
		cout << fixed << endl;	
	}
	pause();
}

// Breath First Traversal of a Binary Tree 
void BFT(NODEPTR tree)
{
   if (tree == NULL) // IF TREE EMPTY THEN RETURN !!!!!
      return;
      
    // tree not empty
	
   NODEPTR * queue = new NODEPTR [nodeCounter(tree)];	   	  
   int enqueue = 0;
   int dequeue = 0;
   NODEPTR p;
   
   p = tree;   // set up temporary pointer to move through the tree
   
  
      queue[enqueue++] = p;  // add node value to queue
      while (!(enqueue == dequeue)) // queue not empty
      {
	     p = queue[dequeue++];  // dequeue the first node ptr
		 cout << p->key << endl; // print the value
		 if (p->lchild != NULL)
		     queue[enqueue++] = p-> lchild;
		 if (p->rchild != NULL)
		     queue[enqueue++] = p-> rchild;
      } 
}