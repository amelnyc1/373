#include "NFA.h"

using namespace std;
NFA::NFA(string commArg2)
{
	inputString = commArg2;
	//cout << "Snagged inputString: " << inputString << endl;
}

void NFA::processTransTable(string transline)
{
	istringstream ss(transline);
	string temp, trans;
	int start, end;
	int x = 0;
	while(ss >> temp)
	{
		x++;
		if(x == 2)
			start = atoi(temp.c_str());
		else if(x == 4)
			end = atoi(temp.c_str());
		else
			trans = temp;
	}
	transList.push_back({start, trans, end});
	
}	

void NFA::processStateTable(string stateline)
{
	string specQ, temp;
	int state;
	istringstream ss(stateline);
	int i = 0;
	while(ss >> temp)
	{
		i++;
		if(i == 3)
		{
			if(temp == "start")
				specQ = temp;
			else if(temp == "accept")
				specQ = temp;
		}else if(i == 4)
			specQ = "start accept";
		
		if(i == 2)
			state = atoi(temp.c_str());
	}
	stateV.push_back({state, specQ});
}


void NFA::processFile(const string filename)
{
	ifstream nfaDefinition;
	nfaDefinition.open(filename.c_str());
	string oneline, substring;
	
	if(nfaDefinition.is_open())
	{
		while(getline(nfaDefinition, oneline))
		{
			//cout << oneline << endl;
			substring = oneline.substr(0,5);
			if(substring == "state")
			{
				//cout << "Process state" << endl;
				processStateTable(oneline);
			}else
			{
				//cout << "Process transition" << endl;
				//cout << "origin state " << oneline.substr(11, 1) << " ";
				//cout << "input " << oneline.substr(13, 1) << " ";
				//cout << "new state " << oneline.substr(15, 1) << endl; 
				processTransTable(oneline);
			}
		}
	}
	else{

		cerr << "File not found. Exiting." << endl;
		exit(1);
	}	/*for(int i = 0; i < transList.size(); i++)
	{
		cout << "origin state " << transList[i].current << " ";
		cout << "input " << transList[i].input << " ";
		cout << "new state " << transList[i].next << endl;
	
	}

	for(int x = 0; x < stateV.size(); x++)
	{
		cout << "state " << stateV[x].snum << " ";
		cout << "special quality " << stateV[x].specialQuality << endl;
	}*/
	processInput();
}

void NFA::processInput()
{
	string current;
	//Parsing input, and saving special quality	
	for (unsigned int i = 0; i < stateV.size();i++)
	{
		if(stateV[i].specialQuality == "start")
		{
			startStates.push_back(stateV[i].snum);
			//cout << "Found one start state" << endl;
		}
		else if(stateV[i].specialQuality == "accept")
		{
			acceptStates.push_back(stateV[i].snum);
			//cout << "Found one accept state" << endl;
		}
		else if(stateV[i].specialQuality == "start accept")
		{
			startStates.push_back(stateV[i].snum);	
			acceptStates.push_back(stateV[i].snum);
			//cout <<"Found an accept and start state" << endl;
		}			
	}

	//cout << "Finished processing input states" << endl;	

	//Starting recursive call to transition helper
	//At input index 0, and for all start states
	for(unsigned int j = 0; j < startStates.size(); j++)
	{
		/*recursive call to*/
		transitionHelper(0, startStates[j]);
	}
	
	//searching through locations reached, determining whether or not any accept
	//states were reached and setting a flag
	bool accepted = false;
	
	for(auto it = locReached.begin(); it != locReached.end(); it++)
	{
		for(auto acIt = acceptStates.begin(); acIt != acceptStates.end(); acIt++)
		{
			if((*it) == (*acIt))
			{
				accepted = true;
				break;
			}
		}
	}

	
	//Print output  based on accepted or rejected end states	
	vector<int> reachAccStates;
	if(accepted)
	{
		cout << "Accept ";

		for(auto it = locReached.begin(); it != locReached.end(); it++)
		{
			for(auto acIt = acceptStates.begin(); acIt != acceptStates.end(); acIt++)
			{
				if((*it) == (*acIt))
				{
					cout << (*it) << " ";
					//Location reached is an accept state
					//Print or whatever here
				}	
			}
		

		}
	}
	else
	{
		cout << "Reject ";
		for(auto it = locReached.begin(); it != locReached.end(); it++)
		{
			cout <<(*it) << " ";
		}
	}
	cout << endl;	
}

void NFA::transitionHelper(int index, int curState)
{
	vector<transinfo> potTrans;
	string currentInput = inputString.substr(index, 1);	
	//cout << "current state: " << curState << " @ index: " << index << endl;

	if((unsigned)index < inputString.size())
	{
		for(unsigned int p = 0; p < transList.size(); p++)
		{
			if(transList[p].current == curState && transList[p].input == currentInput)
			{	
				//temp = transList[p].current;
				potTrans.push_back(transList[p]);
			}
		}
		if(potTrans.size() > 0)
		{
			for(unsigned int m = 0; m < potTrans.size(); m++)
			{
				int nextState = 0;
				nextState = potTrans[m].next;
				transitionHelper(index+1, nextState);
			}		
		}	
	}
	else{
	//Input string complete, add state to set of end states
	//	cout << "Current state when inserting into set: " << curState << endl;
		locReached.insert(curState);
	}
	return;
	
	/*if statement checking if index > size of inputstring
		check transition table for instances of curState against input
		log all possible transitions in vector
		see if any valid transitions exist
		if none exist print error statements
		if valid transitions exist loop through vector and recursively call each possible transition
	*/
}	
