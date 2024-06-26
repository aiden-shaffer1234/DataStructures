#include <iostream>
#include <string>
#include "hashtable.h"
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;
using namespace cop4530;

void menu()
{
	std::cout << "\n\n";
	std::cout << "l - Load Dictionary From File" << std::endl;
	std::cout << "a - Add Word" << std::endl;
	std::cout << "r - Remove Word" << std::endl;
	std::cout << "c - Clear HashTable" << std::endl;
	std::cout << "f - Find Word" << std::endl;
	std::cout << "d - Dump HashTable" << std::endl;
	std::cout << "s - HashTable Size" << std::endl;
	std::cout << "w - Write to File" << std::endl;
	std::cout << "x - Exit program" << std::endl;
	std::cout << "\nEnter choice : ";
}

vector<string> findWords(string startWord, HashTable<string> hs, bool isUpper); 

int main(int argc, char* argv[]) {

if(argc == 1) {
	char choice;
	int  size;
	string str;
	string file;
	bool done;	
	cout << "Enter preferred hash table capacity: ";
	cin  >> size;	
	HashTable<std::string> hs(size);
	
	do {
        menu();
        std::cin >> choice;

        switch (choice) 
		{

            case 'l':
                // Code for Load Dictionary From File
				std::cout << "Enter dictionary filename to load from: ";
				cin >> file;
				done = hs.load(file.c_str());

				if(done){
				cout << "successfully loaded" << endl; //change
				} else {
				cout << "Cannot open file " << file << endl;
				}
				
				break;

            case 'a':
				cout << "Enter word: ";
				cin >> str;
						done = hs.insert(str);

				if(done)
				{
						std::cout << "\nWord " << str  << " added"  << std::endl;
						} else {
				cout << "*****: Word already exists.  Could not add" << endl;
				}
				break;

            case 'r':
				cout << "Enter word: ";
                cin >> str;

                done = hs.remove(str);
                if(done) 
                {        
                  std::cout << "\nWord " << str  << " deleted"  << std::endl;
                } else {      
                  cout << "*****: Word not found.  Could not delete" << endl;
                } 
		
				break;
            case 'c':
                // Code for Clear HashTable
				hs.clear();
                std::cout << "Clearing HashTable..." << std::endl;
                break;

            case 'f':
                std::cout << "Enter word: ";
				cin >> str;

				if(hs.contains(str)) std::cout << "\nWord " << str << " found."  << std::endl;
				else 		     std::cout << "\nWord " << str << " not found."  << std::endl;

                break;

            case 'd':
                hs.dump();
                break;

            case 's':
				std::cout << "Size of hashtable: "  << hs.size() << std::endl;
                break;

            case 'w':
                // Code for Write to File
                std::cout << "Enter dictionary file name to write to: ";
				cin >> file;
				done = hs.write_to_file(file.c_str());
				if(done) {
				cout << "Written Successfully" << endl;
				} else {
				cout << "Write failed" << endl;
				}
                break;

            case 'x':
                // Code for Exit program
                std::cout << "Exiting program..." << std::endl;
                break;

            default:
                std::cout << "*****Error: Invalid entry.  Try again." << std::endl;
        }

    } while (choice != 'x');
} else if (argc == 4) {
	HashTable<std::string> hs;
	string dict = argv[1];
	string inFile = argv[2];
	string outFile = argv[3];
	ifstream in;
	ofstream out;
	string input;
	
	bool done = hs.load(dict.c_str());

	if(!done){
		cout << "Failed to load dictionary " << dict << endl;
		return 0;
	}

	in.open(inFile);
	out.open(outFile);

	if(!in.is_open()){
		cout << "Failed to open " << inFile << endl;
		return 0;
	}

	if(!out.is_open()){
		cout << "Failed to open " << outFile << endl;
		return 0;
	}

	while(getline(in, input)){
		string word;
		std::stringstream line(input);
		vector<string> options;

		// isolate the word
		while(line >> word) {
			bool isUpper = false;
			char punct;
			bool hasPunct = false;

			if(isupper(word[0])) isUpper = true;
			if(ispunct(word[word.length() - 1])) {
				// punct = word[word.length() - 1];
				// hasPunct = true;
				word = word.substr(0,word.length()-1);
			}
			string temp = word;
			size_t pos = input.find(word);
			transform(word.begin(), word.end(), word.begin(), ::tolower);

			if(!hs.contains(word))
			{
				transform(word.begin(), word.end(), word.begin(), ::toupper);
				input.replace(pos, word.length(), word);

				cout << input << endl;
				options = findWords(word, hs, isUpper);

				// while choice invalid
				while(true)
				{
					string choice;
					cout << "====================================" << endl;
                                	for(int i = 0; i < options.size(); i++)
                                	{
                                	        cout << i << ") :" << options[i] << endl;
                                	}
					cout << "n (no change) :" << endl;

                                	cout << "====================================" << endl;
					cout << "Your choice: ";

					cin  >> choice;

					if(choice.length() == 1)
					{
						if((choice.length() == 1 && choice == "n") || options.size() == 0) 
						{                       
                            input.replace(pos, word.length(), temp);
							break;                                        
        	            } 
						if(isdigit(choice[0]))
						{
							int i = choice[0] - '0';
							if ( i >= 0 && i < options.size())
							{
								word = options[i];
                        		input.replace(pos, word.length(), word);
								break;         
							}
						}
					}
				}
			}
		}
		out << input << endl;
	}
	out.close();
	in.close();
} else {
     	cout << argv[0] << " dictionary check_file output_file" << endl;
	return 0;
}
}


vector<string> findWords(string startWord, HashTable<string> hs, bool isUpper)
{
	char letter[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	 				   's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	vector<string> ans;
	transform(startWord.begin(), startWord.end(), startWord.begin(), ::tolower);
	
	for (int i = 0; i < startWord.length(); i++)
	{
		string temp = startWord;
		for (int j = 0; j < 26; j++)
		{
			temp[i] = letter[j];
				
			if(true == hs.contains(temp)) 
			{
				if(isUpper) temp[0] = toupper(temp[0]);
				ans.push_back(temp);
				if(ans.size() == 10) {
					return ans;
				}
			}
		}
	}
	
	return ans;
	
}
