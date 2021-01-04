/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

// FULLY FUNCTIONAL IN CODE RUNNER. DOES NOT COMPILE FOR SOME REASON.
// LINKED LIST HELP


#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom){
  if(head == NULL){ //Empty List
    head = new CUBuilding;
    head->name = buildingName;
    head->totalRoom = numOfroom;
    head->numberMessages = 0;
    head->next = NULL;
    cout << "adding: " << buildingName << " (HEAD)" << endl;
  }

  else if(previous == NULL)
  {
      CUBuilding* newBuilding = new CUBuilding;
      newBuilding->name = buildingName;
      newBuilding->totalRoom = numOfroom;
      newBuilding->numberMessages = 0;
      newBuilding->next = head;
      head = newBuilding;

      cout << "adding: " << buildingName << " (HEAD)" << endl;
  }

  else{

      CUBuilding* newBuilding = new CUBuilding;
      newBuilding->name = buildingName;
      newBuilding->totalRoom = numOfroom;
      newBuilding->numberMessages = 0;
      newBuilding->next = previous->next;
      previous->next = newBuilding;

      cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    
  }
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
  addBuildingInfo(nullptr, "FLMG" , 2);
  addBuildingInfo(searchForBuilding("FLMG"), "DLC" , 10);
  addBuildingInfo(searchForBuilding("DLC"), "ECOT" , 6);
  addBuildingInfo(searchForBuilding("ECOT"), "CASE" , 5);
  addBuildingInfo(searchForBuilding("CASE"), "AERO" , 4);
  addBuildingInfo(searchForBuilding("AERO"), "RGNT" , 9);

}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
  CUBuilding* crawler = head;
  if(crawler == NULL){
      return crawler;
  }
  while(crawler->name != buildingName){
    if(crawler->next == NULL){
      return NULL;
    }
    crawler = crawler->next;
  }

  return crawler;

}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver) {
  CUBuilding* crawler = head;
  if(crawler == NULL){
    cout << "Empty list" << endl;
    return;
  }
  if(!searchForBuilding(receiver)){
    cout << "Building not found" << endl;
    return;
  }
  if(head->name != receiver){
    while(crawler->name != receiver){
      if(crawler->next == NULL){
        return;
      }
      crawler->message = "available room at " + crawler->name + " is " + to_string(crawler->totalRoom);
      crawler->numberMessages++;
      cout << crawler->name << " [# messages received: " << 
      crawler->numberMessages << "] received: " << crawler->message << endl;
      crawler = crawler->next;
    }
    crawler->message = "available room at " + crawler->name + " is " + to_string(crawler->totalRoom);
    crawler->numberMessages++;
    cout << crawler->name << " [# messages received: " << 
    crawler->numberMessages << "] received: " << crawler->message << endl;
  }
  else{
      crawler->message = "available room at " + crawler->name + " is " + to_string(crawler->totalRoom);
      crawler->numberMessages++;
      cout << crawler->name << " [# messages received: " << 
      crawler->numberMessages << "] received: " << crawler->message << endl;

  }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    CUBuilding* crawler = head;
    if(head == NULL){
      cout << "== CURRENT PATH ==" << endl;
      cout << "nothing in path" << endl << "===" << endl;
    }
    else{
      cout << "== CURRENT PATH ==" << endl;
      while(crawler->next != NULL){
        cout << crawler->name << "(" << crawler->totalRoom << ")" << " -> ";
        crawler = crawler->next;
      }
      
      cout << "NULL" << endl << "===" << endl;
    }
  }


