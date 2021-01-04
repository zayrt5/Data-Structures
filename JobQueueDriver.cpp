/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

// Did not finish second case-- couldnt code runner check it. kms


#include "JobQueue.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	JobQueue jobs;
	string s_input;
	int input;
	bool quit = false;
	while(!quit){
		menu();
		getline(cin, s_input);
		try{
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            input = 10;
        }

		switch (input)
		{
		case 1:
		{
			cout << "Enter the number of jobs to be created" << endl;
			string s_newJobs;
			string inString;
			getline(cin, s_newJobs);
			int newJobs = stoi(s_newJobs);
			for(int i  = 0; i < newJobs; i++){
				cout << "job" << i + 1 << ":" <<  endl;
				getline(cin, inString);
				jobs.enqueue(inString);
			}
			break;
		}
		case 2:
			cout << "Enter the number of jobs to be dispatched:" << endl;
			string s_in = getline(cin, s_in);
			int outJobs = stoi(s_in);
			int j = 0
			while(!jobs.isEmpty() && j != outJobs){
				jobs.dequeue();
				j++;
			}
			cout << "No more jobs to dispatch from queue" << endl;

			break;


		case 3:
		{
		cout << "Number of jobs in the queue:" << jobs.queueSize() << endl;
		quit = true;
		break;
		
		}

		

		default:
			cout << "Invald input" << endl;
			break;
		}
	}
}
