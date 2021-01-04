#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <queue>

using namespace std;

//All these functions are working. Mostly all bi-tree transverals



// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  //write your code
  root = NULL;

}

MovieTree::~MovieTree() {
  //write your code
  root = NULL;

}

void printMovieHelper(MovieNode* currNode){
  if(currNode){
    printMovieHelper(currNode->left);
    cout << "Movie: " << currNode->title << " " << currNode->rating << endl;
    printMovieHelper(currNode->right);

  }
}

void MovieTree::printMovieInventory() {
   //write your code

  if(root == NULL){
    cout << "Tree is Empty. Cannot Print" << endl;
  }
  else{
    printMovieHelper(root);
  }

}

MovieNode* addMovieHelper(MovieNode* currNode, int ranking, string title, int year, float rating){
  if(currNode == NULL){
    return getMovieNode(ranking, title, year, rating);
  }
  else if(currNode->title < title){
    currNode->right = addMovieHelper(currNode->right, ranking, title, year, rating);
  }
  else if(currNode->title > title){
    currNode->left = addMovieHelper(currNode->left, ranking, title, year, rating);
  }
  return currNode;
  
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {

  root = addMovieHelper(root, ranking, title, year, rating);

}

MovieNode* findMovieHelper(MovieNode* currNode, string title){
  if(currNode == NULL){
    return NULL;
  }
  if(currNode->title == title){
    return currNode;
  }
  if(currNode->title > title){
    return findMovieHelper(currNode->left, title);
  }
  return findMovieHelper(currNode->right, title);
}

void MovieTree::findMovie(string title) {
  //write your code
  MovieNode* temp = findMovieHelper(root, title);
  if(temp != NULL){
    cout << "Movie Info:" <<  endl;
    cout <<  "=================="  <<  endl;
    cout <<  "Ranking:"  << temp->ranking <<  endl;
    cout <<  "Title  :"  << temp->title <<  endl;
    cout <<  "Year   :"  << temp->year <<  endl;
    cout <<  "rating :"  << temp->rating <<  endl;
  }
  else{
    cout  <<  "Movie not found."  <<  endl ;

  }

}

void queryMovieHelper(MovieNode* currNode, float rating, int year){
  
  if(currNode){
    if(currNode->year > year && currNode->rating >= rating){
      cout << currNode->title << "(" << currNode->year << ") " << currNode->rating << endl;
    }
    queryMovieHelper(currNode->left, rating, year);
    
    queryMovieHelper(currNode->right, rating, year);
  }
  
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  if(root == NULL){
    cout << "Tree is Empty. Cannot query Movies" << endl;
  }
  else{
    cout << "Movies that came out after " << year << " with rating at least " << rating 
      << ":" << endl;
    queryMovieHelper(root, rating, year);
  }
}

float movieCount(MovieNode* currNode){
  int i = 0;
  if(currNode){
    i++;
  }
  
  if(currNode->left != NULL){
    i += movieCount(currNode->left);
  }
  if(currNode->right != NULL){
    i += movieCount(currNode->right);
  }

  return i;
  
  
}

float sumHelper(MovieNode* currNode){
  if(currNode == NULL){
    return 0;
  }
  return (currNode->rating + sumHelper(currNode->left) + sumHelper(currNode->right));
}

void MovieTree::averageRating() {
  //write your code
  if(root == NULL){
    cout << "Average rating:0.0 " << endl;
  }
  else
  {

    float sumRating = sumHelper(root);
    float sumMovies = movieCount(root);
    float avg = (sumRating / sumMovies);
    cout << "Average rating:" << avg << endl;

  }

}





//Zero chance I couldve figured this out myself
// https://www.geeksforgeeks.org/print-all-nodes-between-two-given-levels-in-binary-tree/?ref=rp

void printNodesHelper(MovieNode* root, int level){
  queue<MovieNode*> movies;
  movies.push(root);

  MovieNode* currNode;

  int currLevel = 0;

  while(!movies.empty()){
    
    int size = movies.size();

    while(size != 0){
      currNode = movies.front();
      movies.pop();

      if(currLevel == level){
        cout << "Movie: " << currNode->title << " " << currNode->rating << endl;
      }

      if(currNode->left != NULL){
        movies.push(currNode->left);
      }

      if(currNode->right != NULL){
        movies.push(currNode->right);
      }
      size--;
    }
    currLevel++;

  }

}


void MovieTree::printLevelNodes(int level) {
  //write your code
  printNodesHelper(root, level);
}
