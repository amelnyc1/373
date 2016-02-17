#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

struct stateinfo{
	int snum;
	std::string specialQuality;
};
struct transinfo{
	int current;
	std::string input;
	int next;
};
class NFA
{
private:
	std::set<int> locReached;
	std::vector<stateinfo> stateV;
	std::vector<transinfo> transList;
	std::string inputString;
	std::vector<int> startStates;
	std::vector<int> acceptStates;
public:

	NFA(std::string commArg2);
	void processTransTable(std::string transline);
	void processStateTable(std::string stateline);
	void processFile(const std::string filename);
	void processInput();
	void transitionHelper(int index, int curState);
	

};
#endif

