#include <iostream>
#include <fstream>
#include "MovieTree.hpp"


//could not get parent pointer of children to be assigned, or the function to work
//print works, assign works, parents do not


using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */

void _grader_inorderTraversal(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		_grader_inorderTraversal(root->leftChild);
		cout << root->titleChar << " ";
		_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

void showMovieHelper(TreeNode* current){
	if(current == NULL){
		return;
	}
	showMovieHelper(current->leftChild);
	cout << "Movies starting with letter: " << current->titleChar << endl;
	LLMovieNode* crawler = current->head;
	while(crawler->next != NULL){
		cout << " >> " << crawler->title << " " << crawler->rating << endl;
		crawler = crawler->next;
	}
	cout << " >> " << crawler->title << " " << crawler->rating << endl;
	showMovieHelper(current->rightChild);
}

void MovieTree::showMovieCollection(){
	showMovieHelper(root);
	return;
}


//================================================================


TreeNode* newTreeData(char newChar, int r, string t, int y, float rt){
	TreeNode* nn = new TreeNode;
	nn->head = getLLMovieNode(r, t, y, rt);
	nn->titleChar = newChar;
}

TreeNode* addLetterHelper(TreeNode* currNode, char newChar, int r, string t, int y, float rt){
	if(currNode == NULL){
    	return newTreeData(newChar, r, t, y, rt);
  }
  else if(currNode->titleChar < newChar){
    currNode->rightChild = addLetterHelper(currNode->rightChild, newChar, r, t, y, rt);
  }
  else if(currNode->titleChar > newChar){
    currNode->leftChild = addLetterHelper(currNode->leftChild, newChar, r, t, y, rt);
  }
  return currNode;
}


//i am so sorry

TreeNode* searchParent(TreeNode* curr, char key)
{
	if(curr->rightChild->titleChar == key || curr->leftChild->titleChar == key){
		cout << "parent: " << curr->titleChar << endl;
		cout << "Children: ";
		if(curr->leftChild != NULL){
			cout << curr->leftChild->titleChar << endl;
		}
		if(curr->rightChild != NULL){
		 	cout << curr->rightChild->titleChar << endl;
		}
        return curr;
	}
    else if (curr->titleChar > key){
        return searchParent(curr->leftChild, key);
	}
    else{
        return searchParent(curr->rightChild, key);
	}
}

void addLLMovie(TreeNode* root, int r, string t, int y, float rt){
	LLMovieNode* crawler = root->head;
	LLMovieNode* prev = NULL;
	LLMovieNode* newNode = NULL;
	while(t > crawler->title && crawler->next != NULL){
		if(t < crawler->next->title){
			prev = crawler;
		}
		crawler = crawler->next;
	}
	/*cout << "crawler title: " << crawler->title << endl;
	if(prev != NULL){
		cout << "Prev is: " << prev->title << endl;
	}
	else{
		cout << "Prev is null" << endl;
	}*/

	if(crawler == root->head){
		newNode = getLLMovieNode( r, t, y, rt);
		newNode->next = root->head;
		root->head = newNode;
		return;
	}

	if(prev == NULL){
		newNode = getLLMovieNode(r, t, y, rt);
		crawler->next = newNode;
		return;
	}

	else{
		newNode = getLLMovieNode(r, t, y, rt);
		prev->next = newNode;
		newNode->next = crawler;
		return;

	}

}


void MovieTree::insertMovie(int ranking, string title, int year, float rating){
	char searchChar = title[0];
	TreeNode* treeFinder = searchCharNode(searchChar);
	//If the character list isnt found and tree is empty
	if(root == NULL){
		root = new TreeNode;
		root->head = getLLMovieNode(ranking, title, year, rating);
		root->titleChar = searchChar;
	}

	//char isnt found and tree is not empty
	else if(treeFinder == NULL){
		treeFinder = addLetterHelper(root, searchChar, ranking, title, year, rating);
		
	}

	//if it is found
	else{
		addLLMovie(treeFinder, ranking, title, year, rating);
		
	}
}