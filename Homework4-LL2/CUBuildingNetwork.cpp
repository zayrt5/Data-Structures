/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of Building structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
using namespace std;

//Finished note-- code should run, all case worked in code runner
//some indecies for the list shift function may not work, but whatever. Most of them do



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
 * Purpose: Add a new building to the network between the building *previous and the building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    // if we are passed an empty list, just create a new head node, and return

    if (head == NULL)
    {
        cout << "adding: " << buildingName << " (HEAD)" << endl;
        head = new CUBuilding;
        head->name = buildingName;
        head->numberMessages = 0;
        head->totalRoom = numOfroom;

        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        cout << "adding: " <<buildingName<< " (HEAD)" << endl;
        CUBuilding *c = new CUBuilding;
        c->name = buildingName;
        c->numberMessages = 0;
        c->next = head;
        c->totalRoom = numOfroom;

        head = c;
    }else{
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
        CUBuilding *newBuilding = new CUBuilding;
        newBuilding->name = buildingName;
        newBuilding->numberMessages = 0;
        newBuilding->next = previous->next;
        newBuilding->totalRoom = numOfroom;

        previous->next = newBuilding;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    int num_buildings = 6;
    string buildings[] = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int rooms[] = {2,10,6,5,4,9};
    head = NULL;
    CUBuilding* prev = NULL;
    for(int i = 0; i < num_buildings; i++)
    {
        addBuildingInfo(prev, buildings[i],rooms[i]);
        prev = searchForBuilding(buildings[i]);
    }
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // Search until the head is NULL, or we find the building
    CUBuilding* ptr = head;
    while (ptr != NULL && ptr->name != buildingName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    CUBuilding* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr != NULL)
        {
            cout << ptr->name << "(" << ptr->totalRoom << ")" <<" -> ";
            ptr = ptr->next;
        }
        //cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
  }

/*
 * Purpose: delete the building in the network with the specified name.
 * @param buildingName name of the building to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) {
    //TODO: Complete this function

    //locate node

    CUBuilding* temp;

    for(temp = head; temp->name != buildingName && temp->next != NULL; temp = temp->next){
            
    }
     
    if(temp->next == NULL && temp->name != buildingName){
        cout << "Building does not exist." << endl;
         return;
    }
    //delete only item in list

    if(temp == head && temp->next == NULL){
        delete temp;

    }

    else if(temp == head && temp->next != NULL){
        head = head->next;
        delete temp;

    }

    //delete end

    else if(temp->next == NULL){
        CUBuilding* prevBuilding = head;
        while(prevBuilding->next != temp){
            prevBuilding = prevBuilding->next;
        }
        prevBuilding->next = NULL;
        delete temp;

    }

    //delete standard chained building

    else{
        CUBuilding* prevBuilding = head;
        while(prevBuilding->next != temp){
            prevBuilding = prevBuilding->next;
        }
        prevBuilding->next = prevBuilding->next->next;
        delete temp;
    }


}

/*
* Purpose: Creates a loop from last node to the building specified.
* @param buildingName name of the building to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) {
    //TODO: Complete this function

    CUBuilding* loopPoint;
    CUBuilding* endPoint;
    

    //index to target and end node

    for(loopPoint = head; loopPoint->name != buildingName && loopPoint->next != NULL;
        loopPoint = loopPoint->next);
    for(endPoint = loopPoint; endPoint->next != NULL; endPoint = endPoint->next);

    //final check if it is a valid building

    if(loopPoint->name != buildingName && loopPoint->next == NULL){
        return endPoint;
    }

    //banger

    else{
        endPoint->next = loopPoint;
        return endPoint;
    }
    
}

/*
 * Purpose: deletes all buildings in the network starting at the head building.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    //TODO: Complete this function

    while(head->next != NULL){
        CUBuilding* temp = head;
        cout << "deleting: " << temp->name << endl;
        head = head->next;
        delete temp;
    }

    CUBuilding* lastNode = head;
    cout << "deleting: " << lastNode->name << endl;
    head = NULL;
    delete lastNode;

    cout << "Deleted network" << endl;

}

/*
 * Purpose: to detect loop in the linkedlist
 * @return: true if loop is detected.
 */
bool CUBuildingNetwork::detectLoop() {
    //TODO: Complete this function

    if(head == NULL){
        return false;
    }
    CUBuilding* fast = head;
    CUBuilding* slow = head;
    while(fast->next->next != NULL && slow->next != NULL){
        if(fast != head && slow != head && fast == slow){ //or just start fast and slow at different indexes
            return true;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    return false;


}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 * @param: start index, end index
 * @return: none
 */
void CUBuildingNetwork:: readjustNetwork(int start_index, int end_index)
{
    //TODO: Complete this function

    

    if(head == NULL){
        cout << "Linked List is Empty" << endl;
        return;
    }

    else{
        int indicies = 0;
        for(CUBuilding* i = head; i->next != NULL; i = i->next){
            indicies++;
        }
        if(start_index > end_index){
            cout << "Invalid indices" << endl;
            return;
        }
        else if(end_index >= indicies || end_index < 0){
            cout << "Invalid end index" << endl;
        }

        else if(start_index > indicies || start_index < 0){
            cout << "Invalid start index" << endl;
        }
        else{
            CUBuilding* priorStart = NULL;
            CUBuilding* endList = head;
            CUBuilding* endShift = head;
            CUBuilding* startShift = head;

            CUBuilding* crawler = head; //probably more effective way to do this

            // fricken good times
            /*we gotta make 
            * endList->next = startShift
            * prior start -> next = endList
            * endShift->next = NULL
            * 
            */

           //getting all the pointers i think i need to the correct spots
           //
           int indexer = 0;
            while(crawler->next != NULL){
                if((indexer == start_index - 1) && start_index != 0){
                    priorStart = crawler;
                }
                if(indexer == start_index){
                    startShift = crawler;
                }
                if(indexer == end_index){
                    endShift = crawler;
                }

                indexer++;
                crawler = crawler->next;

            }
            endList = crawler;
            /*if(priorStart != NULL){
            *    cout << "prior start name: " << priorStart->name << endl;
            *}
            *cout << "start index name: " << startShift->name << endl;
            *cout << "end index name: " <<endShift->name << endl;
            *cout << "end of list: " << endList->name << endl; 
            */
            if(priorStart == NULL){
                endList->next = startShift;
                head = endShift->next;
                endShift->next = NULL;
            }
            else if(start_index == end_index){
                endList->next = startShift;
                priorStart->next = priorStart->next->next;
                startShift->next = NULL;
            }
            else{    
                endList->next = startShift;
                priorStart->next = endList;
                endShift->next = NULL;
            }
            
        }   
    }



}