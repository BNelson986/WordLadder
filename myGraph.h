#pragma once
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>

class myGraph
{
private:
	std::vector<std::string> dictionary;		//	Vector to store all words in dictionary
	std::set<std::string> mySet;		//	Set of all words
	int wordErrors = 0;				//	Variable to track wrong word length worchoices for possible exiting
	std::vector<std::vector<std::string>> ans;		//	Store all posible paths
	int exitNow = 0;			//	Variable to end program
	std::string beggining, ending;
public:
	myGraph();
	void dispMenu();		//	Func to display user menu
	void readIn(int);		//	Func to read correct file based on choice of word length
	std::vector<std::string>::iterator searchNode(std::string);	//	Func to find if word is present in dictionary
	void startGame(int);		//	Func to start the gameplay
	int pathLength(std::string, std::string, std::vector<std::string>&);	//	Function to find the shortest path bewteen two words
	std::vector<std::vector<std::string>> findLadders(std::string, std::string, std::vector<std::string>&);	//	Find all ladders between two words	
	void DFS(std::string&, std::string&, std::map<std::string, std::set<std::string>>&, std::vector<std::string>&);	//	Perform DFS to return shortest path
	void printAns(std::vector<std::vector<std::string>>);		//	Func to print correct, shortest answer
	void endingMenu(int);		//	Display ending menu after game completes
	void errorMenu();		//	Display error menu if wrong length entered
};

