#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
using namespace std; //Install all necessary header files for our program
#define FAST ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); //for fast I/O in our program

struct Trie { 
	bool EndofWord; 
	unordered_map<char, Trie*> map; 
	int frequency; 
}; //Structure of our Trie 

//This function will create a new Trie node 
Trie* NewNode() 
{ 
	Trie* node = new Trie; 
	node->EndofWord = false; 
	return node; 
} 

//This function will insert a word alongwith its frequency into our dictionary upon call
void insertElement(Trie*& root, const string& str, int frequency) 
{ 	
	if (root == NULL) // If root is null initialize our Dictionary
		root = NewNode(); 

	Trie* temp = root; 
	for (int i = 0; i < str.length(); i++) { 
		char x = str[i]; // access each letter in word

		// If find() reaches end of map,i.e, there is no path, make a new node for this letter 
		if (temp->map.find(x) == temp->map.end()) 
			temp->map[x] = NewNode(); 

		temp = temp->map[x]; 
	} 

	//Now mark it as end of word and map its frequency to it 
	temp->EndofWord = true; 
	temp->frequency = frequency; 
} 

// This function checks the input word in our Trie Dictionary and returns its frequency if it is present 
int checkFrequency(Trie* root, const string& word) 
{ 

	if (root == NULL) // If root is null
		return -1;  //return back as dictionary is empty

	Trie* temp = root; 

	//We search a word in the Trie
	for (int i = 0; i < word.length(); i++) { 
		temp = temp->map[word[i]]; 
		if (temp == NULL) 
			return -1; //return back
	} 

	//return the frequency if its the end of a valid word 
	if (temp->EndofWord) 
		return temp->frequency; 
		
	return -1; //else return back 
} 


int main() {
	FAST
	
	//Read our Dictionary data from a .csv file
    ifstream input_from_file("EnglishDictionary.csv");//read the file
    
    string line, wordToCheck;
    unsigned int count = 0;
    int x, answer;
    Trie* root = NULL; //initialise Trie
    
    cout<<" Welcome to BOBBLE AI !!";
    
    while (getline(input_from_file, line)) //loop till a valid line if input from file
	{
        line += ","; //add "," at end so that we can conveniently collect word and frequency separately from every line in file
        stringstream ss(line); //input line
        string word,nameOfWord;

        while (getline(ss, word, ','))
            {
	            count++;
	            if(count%2 == 1) //first string in every line is a word in dictionary
	            	nameOfWord = word;
	            else //second string in every line is frequency of word
	            {
					x = stoi(word); //convert the frequency from string to integer
		            insertElement(root,nameOfWord,x); //now insert both in our Trie Dictionary
	        	}
        	}	
    }
    
    cout<<"Please enter the words to be checked in Dictionary one by one:";
    
    while(cin >> wordToCheck) //while user is providing inputs accept it
	{
		answer = checkFrequency(root, wordToCheck);
		if(answer == -1)
			cout<<"NO"<<endl;
		else
			cout<<"YES, "<<answer<<endl; 
	}
	
    cout<<"THANK YOU !";
    return 0;
    
}
