#include "myGraph.h"

using namespace std;

myGraph::myGraph()
{
	//	Set console style
	system("color DF");

	//	Start program
	dispMenu();
}

void myGraph::dispMenu()
{
	while (exitNow != -1) {
		string open = " WELCOME TO THE WORD LADDER! ";
		//	Display opening menu and options
		for (int i = 0; i < open.size(); i++) {
			cout << open[i];

			Sleep(100);
		}
		cout << " \n\n";

		// cout << " WELCOME TO THE WORD LADDER! \n \n";
		string a1 = " - The goal here is to move from your starting word to your ending word by changing ONLY one letter at a time.";
		string a2 = "   Each new word must also be present in the dictionary to be used.";

		for (int i = 0; i < a1.size(); i++) {
			cout << a1[i];

			Sleep(20);
		}
		cout << endl;
		for (int i = 0; i < a2.size(); i++) {
			cout << a2[i];

			Sleep(20);
		}
		cout << endl;

		system("pause");
		system("cls");
		//cout << " - The goal here is to move from your starting word to your ending word by changing ONLY one letter at a time.\n";
		//cout << "   Each new word must also be present in the dictionary to be used. \n\n";                   
		
		string a3;
		a3 = " Please enter the length of word you wish to use. ";

		for (int i = 0; i < a3.size(); i++) {
			cout << a3[i];

			Sleep(20);
		}
		cout << endl;

		//	Display options
		string menu[9];

		menu[0] = "  --------------------------------------  ";
		menu[1] = " |  Options  |         Result           | ";
		menu[2] = " |**************************************| ";
		menu[3] = " |     4     | Play with 4 letter words | ";
		menu[4] = " |--------------------------------------| ";
		menu[5] = " |     5     | Play with 5 letter words | ";
		menu[6] = " |--------------------------------------| ";
		menu[7] = " |     0     |      Exit Program        | ";
		menu[8] = "  --------------------------------------  ";

		for (int i = 0; i < 9; i++) {
			cout << menu[i] << endl;
		}

		cout << " Choice: ";
		//	Accept user input and select game accordingly
		int wordLength;
		cin >> wordLength;

		//	Load up proper game based on choice
		switch (wordLength)
		{
		case 4:
			readIn(wordLength);
			break;
		case 5:
			readIn(wordLength);
			break;
		case 0:
			cout << " Thank you for playing. \n";
			return;
		default:
			cout << " Entered value is not valid. Please Try again. \n";
			system("cls");
			dispMenu();
			break;
		}

		system("cls");

		//	Begin game process
		startGame(wordLength);
	}

	return;
}

void myGraph::readIn(int wordLength)
{
	ifstream readIn;	//	In stream variable

	
	if (wordLength == 4) {

		/*	LOAD TIME (45s) */
		readIn.open("FourLetterWords.txt");

		////	Verify file is open for use 
		//if (!readIn.is_open()) {	
		//	cout << " ERROR! File is not open and cannot be used. \n";
		//	system("Pause");
		//}
		//else {
		//	cout << " File is open and read to use. \n";
		//	system("Pause");

		string word;	//	String to store words in dictionary
		while (!readIn.eof()) {
			getline(readIn, word);
			dictionary.push_back(word);
		}

		system("cls");
	}
	else if (wordLength == 5) {
		readIn.open("FiveLetterWords.txt");

		////	Verify file is open for use 
		//if (!readIn.is_open()) {
		//	cout << " ERROR! File is not open and cannot be used. \n";
		//	system("Pause");
		//}
		//else {
		//	cout << " File is open and read to use. \n";
		//	system("Pause");
		//}

		string word;	//	String to store words in dictionary
		while (!readIn.eof()) {
			getline(readIn, word);
			dictionary.push_back(word);
		}

		system("cls");
	}
}

vector<string>::iterator myGraph::searchNode(string word)
{
	return find(dictionary.begin(), dictionary.end(), word);
}


void myGraph::startGame(int length)
{
	//	Clear entered words for reuse 
	beggining.clear();
	ending.clear();

	string start, end;
	
	system("cls");
	//	Prompt for input

	if (length == 4) {

		string input[6];

		input[0] = "   Please enter two 4-letter words   ";
		input[1] = "  ---------------------------------- ";
		input[2] = " |  Starting Word  |     ";
		input[3] = " |-----------------|---------------- ";
		input[4] = " |   Ending Word   |     ";
		input[5] = "  ---------------------------------- ";

		cout << input[0] << endl;
		cout << input[1] << endl;
		cout << input[2];	cin >> start;
		cout << input[3] << endl;
		cout << input[4]; cin >> end;
		cout << input[5] << endl;

	}
	else {

		string input[6];

		input[0] = "    Please enter two 5-letter words  ";
		input[1] = "  ----------------------------------- ";
		input[2] = " |  Starting Word  |      ";
		input[3] = " |-----------------|----------------- ";
		input[4] = " |   Ending Word   |      ";
		input[5] = "  ----------------------------------- ";


		cout << input[0] << endl;
		cout << input[1] << endl;
		cout << input[2];	cin >> start;
		cout << input[3] << endl;
		cout << input[4]; cin >> end;
		cout << input[5] << endl;
	}


	//	Track beginning word globally
	beggining = start;

	//	Track ending word globally
	ending = end;

	//	Add prompt for conitinuous errors and back tracking
	if (start.length() != length || end.length() != length) {
		wordErrors++;

		//	Every 3 errors open error menu
		if (wordErrors % 3 == 0) {
			errorMenu();
		}
		system("cls");
		cout << " Error! Please enter a " << length << " letter word ONLY. \n";
		startGame(length);
	}

	//	Verify ending word is in dictionary
	auto endNodeIt = searchNode(end);
	
	if (endNodeIt == dictionary.end()) {
		cout << " Entered ending word is not vaild. Please try again. \n";
		startGame(length);
	}

	//	Print answer
	printAns(findLadders(start, end, dictionary));

	system("Pause");

	//	Open ending menu

	endingMenu(length);	
}

int myGraph::pathLength(string begin, string end, vector<string>& wordList)
{
	//	Create an a local set for removing 
	set<string> myset;
	for (auto i = 0; i < dictionary.size(); i++) {
		myset.insert(dictionary[i]);
	}

	//	Create queue to store path of ladder
	queue<string> ladder;
	ladder.push(begin);
	int depth = 0;

	//	Traverse matrix and track steps with queue
	while (!ladder.empty()) {
		depth++;
		int levelSize = ladder.size();
		
		while (levelSize--) {
			string currWord = ladder.front();
			ladder.pop();

			//	Check for all 1 depth words
			for (int i = 0; i < currWord.length(); i++) {
				string temp = currWord;

				//	Try all possible chars
				for (char c = 'a'; c <= 'z'; c++) {
					temp[i] = c;

					//	Skip same word
					if (currWord.compare(temp) == 0) {
						continue;
					}

					//	EndWord found
					if (temp.compare(end) == 0) {
						return depth + 1;
					}

					//	Continue with path search
					if (myset.find(temp) != myset.end()) {
						ladder.push(temp);
						myset.erase(temp);
					}
				}
			}
		}
	}
}

vector<vector<string>> myGraph::findLadders(string begin, string end, vector<string>& wordList)
{
	//	If not first time run through program, clear ans vector
	if (ans.size() != 0) {
		ans.clear();
	}

	map<string, set<string>> adj;	//	Adjacency LIST
	set<string> dict(dictionary.begin(), dictionary.end());	//	Insert wordlist into SET

	//	Step 1 - Find min-depth using BFS
	queue<string> q;	//	For traversal
	q.push(begin);		//	Push begin word
	map<string, int> visited;	//	Key->String (Node) ... Value->Level (Depth of Traversal)
	visited[begin] = 0;	//	Start Node will always be at level 0
	
	while (!q.empty()) {
		string curr = q.front();
		q.pop();
		string temp = curr;

		//	Traverse all characters in word
		for (int i = 0; i < curr.size(); i++) {
			//	Check full alphabet for success
			for (char x = 'a'; x <= 'z'; x++) {
				
				//	If leter is same as original word, skip
				if (temp[i] == x) {
					continue;
				}

				temp[i] = x;

				//	Check if new word is present in wordlist
				if (dict.count(temp) > 0) {	

					//	Check if word has been visited
					if (visited.count(temp) == 0) {	
						visited[temp] = visited[curr] + 1;
						q.push(temp);
						adj[curr].insert(temp);
					}

					//	If already visited, move down
					else if (visited[temp] == visited[curr] + 1) {
						adj[curr].insert(temp);
					}
				}
			}
			//	Revert back temp to curr
			temp[i] = curr[i];
		}
	}

	//	Step 2 - Find all possible paths at min-depth using DFS
	vector<string> path;
	DFS(begin, end, adj, path);
	return ans;

}

void myGraph::DFS(string& begin, string& end, map<string, set<string>>& adj, vector<string>& path)
{
	//	Push current word
	path.push_back(begin);	

	if (begin == end) {
		ans.push_back(path);
		path.pop_back();
		return;
	}

	for (auto x : adj[begin]) {
		DFS(x, end, adj, path);
	}

	//	Pop current word to backtrack
	path.pop_back();
}

void myGraph::printAns(vector<vector<string>> paths)
{

	if (paths.size() == 0) {
		cout << " No path found between those words. \n";
		return;
	}

	//	Create variable to track smallest path size and index
	auto pathLength = paths[0].size();
	int pathIndex = 0;


	for (int i = 0; i < paths.size(); i++) {
		//	If size is less than pathLength
		//	pathLength equals new size;
		//	Track index value for printing
		if (paths[i].size() < pathLength) {
			pathLength = paths[i].size();
			pathIndex = i;
		}
	}

	////	Verification for shortest path (TESTING ONLY)
	//cout << " All paths: \n";

	//for (int i = 0; i < paths.size(); i++) {
	//	for (int j = 0; j < paths[i].size(); j++) {
	//		cout << " -> " << paths[i][j];
	//	}
	//	cout << endl;
	//	cout << " Depth: " << paths[i].size() << endl;
	//}

	//	Print path and size of path 
	system("cls");

	//	Prompt strings for display loops
	string prompt[3];
	prompt[0] = " Shortest Path between ";
	prompt[1] = " and ";
	prompt[2] = " found is: ";

	//	Display prompts with start and end words
	for (int i = 0; i < prompt[0].size(); i++) {
		cout << prompt[0][i];
		Sleep(20);
	}
	for (int i = 0; i < beggining.size(); i++) {
		cout << beggining[i];	
		Sleep(20);
	}
	for (int i = 0; i < prompt[1].size(); i++) {
		cout << prompt[1][i];
		Sleep(20);
	}
	for (int i = 0; i < ending.size(); i++) {
		cout << ending[i];
		Sleep(20);
	}
	for (int i = 0; i < prompt[2].size(); i++) {
		cout << prompt[2][i];
		Sleep(20);
	}


	for (int i = 1; i < paths[pathIndex].size(); i++) {
		if (i - 1 == 0) {
			cout << "\n " << paths[pathIndex][0];
			Sleep(40);
		}
			
		cout << " -> " << paths[pathIndex][i];
		Sleep(40);
	}
	cout << "\n";

	string steps = " Steps required is: ";
	for (int i = 0; i < steps.size(); i++) {
		cout << steps[i];

		Sleep(20);
	}
	cout << pathLength << endl;

}

void myGraph::endingMenu(int length)
{
	string menu[9];

	menu[0] = "  ---------------------------------------  ";
	menu[1] = " |  Options  |          Result           | ";
	menu[2] = " |***************************************| ";
	menu[3] = " |     1     | Play the same level again | ";
	menu[4] = " |---------------------------------------| ";
	menu[5] = " |     2     |    Return to main menu    | ";
	menu[6] = " |---------------------------------------| ";
	menu[7] = " |     0     |       Exit Program        | ";
	menu[8] = "  ---------------------------------------  ";

	for (int i = 0; i < 9; i++) {
		cout << menu[i] << endl;
	}

	cout << " Choice: ";

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 0:
		system("cls");
		cout << " Thanks for playing! \n";
		//	Set exit variable to exit value to end program
		exitNow = -1;
		dispMenu();
		break;
	case 2:
		system("cls");
		dispMenu();
		break;
	default:
		system("cls");
		startGame(length);
		break;
	}
}

void myGraph::errorMenu()
{
	cout << " You have entered the wrong size of word " << wordErrors << " times now. \n";

	//	Display options

	string menu[9];

	menu[0] = "  ---------------------------------------  ";
	menu[1] = " |  Options  |          Result           | ";
	menu[2] = " |***************************************| ";
	menu[3] = " |     1     | Play the same level again | ";
	menu[4] = " |---------------------------------------| ";
	menu[5] = " |     2     |    Return to main menu    | ";
	menu[6] = " |---------------------------------------| ";
	menu[7] = " |     0     |       Exit Program        | ";
	menu[8] = "  ---------------------------------------  ";

	for (int i = 0; i < 9; i++) {
		cout << menu[i] << endl;
	}

	int choice;
	cout << " Choice: "; cin >> choice; cout << endl;

	switch (choice)
	{
	case 0:
		cout << " Thanks for playing! \n";
		//	Set exit variable to exit value
		exitNow = -1;
		return;
	case 2:
		dispMenu();
		break;
	default:
		cout << " Game will continue. \n";
		break;
	}
}
