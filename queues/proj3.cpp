#include "Queue.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;
using namespace cop4530;

int main()
{
    //objects
    ifstream in;
    int numCities;

    // first input and initialization of city array
    in.open("proj3.input");
    in >> numCities;
    in.ignore();
    
    // objects for BFS
    vector<vector<int>> connections(numCities);
    vector<vector<int>> costs(numCities);
    string places[numCities]; 
    unordered_map<string, int> cityIndex; // needed for the input from user

    /*
        Populate map and print locations
    */
    cout << numCities << " cities:" << endl;
    for(int i = 0; i < numCities; i++)
    {
        string city; //temp

        //populate map and strings
        getline(in, city);
        places[i] = city;
        transform(city.begin(), city.end(), city.begin(), ::tolower);
        cityIndex[city] = i;

        //print cities
        cout << "     " << places[i] << endl;
    }

    /*
        i) Populate the cost and connections vector
       ii) Print the connections and their costs

       uses 2 2d vectors and a string array;
    */
    int input;

    cout << "\ndirect flights between cities" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < numCities; i++)
    {
        cout << places[i] << ":" << endl;
        for(int j = 0; j < numCities; j++)
        {
            
            in >> input;
            if(input > 0)
            {
                cout << "     " << places[j] << ", $" << input << endl;
                costs[i].push_back(input);
                connections[i].push_back(j);
            }
        }
    }
    cout << "-----------------------------\n" << endl;
    

    /*
        Breath First Search

         i) loop until told not to
        ii) initialize the necessary variable to track the BFS
            a) queue
            b) 3 arrays to track if it was seen, what the connections are, and the costs
            c) a found and index variable to track the index that the target is stored in if found
            d) start and destination location strings
       iii) start the BFS
    */

    bool continueLoop = true;
    while(continueLoop == true) // loop  (i)
    {
        // Declarations and initializations (ii)
        Queue<int> BFS; 
        int targetFoundIndex = -1;          // saves index of number stored in the track array to backtrack
        bool found = false;                  //tracks if the number was found
        bool seen[numCities];
        int track[numCities];
        int costArr[numCities];
        string source       = "";
        string destination  = "";


        // Populates the seen to prevent false positives
        for (int i = 0; i < numCities; i++) 
        {
            seen[i] = false;
        }

        // Prompt user and store start location and desired destination
        cout << "Source city : ";
        getline(cin, source);
        transform(source.begin(), source.end(), source.begin(), ::tolower);

        cout << "Destination city : ";
        getline(cin, destination);
        transform(destination.begin(), destination.end(), destination.begin(), ::tolower);

        cout << "finding min_hop route...." << endl;
        
        // Populate the BFS and set the target

        //populate if cities exist
        int start   = 0;
        int target  = 0;
        if(cityIndex.find(source) != cityIndex.end() && cityIndex.find(destination) != cityIndex.end())
        {
            start           = cityIndex[source];
            target          = cityIndex[destination];
            track[start]    = start;
            costArr[start]  = 0;
            BFS.push(start);
        }
        
        // Start BFS

        while(!BFS.empty() && found == false)
        {
            int node    = BFS.front(); //parent node
            seen[node]  = true;      // set parent node to seen

            for (int i = 0; i < connections[node].size(); i++)
            {
                int num     = connections[node][i]; // isolate the destination its parrent connects to
                int cost    = costs[node][i];      // isolate the cost of the connection

                // see if the destination has been viewed before
                if(seen[num] == false) 
                {
                    //track data
                    track[num]      = node;
                    costArr[num]    = cost;
                    seen[num]       = true;

                    // populate BFS and track the depth
                    BFS.push(num);
                    
                    //check if the destination in question is the desired one
                    if(num == target) // success;
                    {
                        targetFoundIndex    = num;
                        found               = true;
                        break;
                    }
                }
            }

            // move on and forget front node as it is not important now
            BFS.pop(); 
        }

        

        /*
            Creating/Isolating the path
            i)  Work backwards through cost and track array
                a) involves initializing variables to track

            ii) Track path and overallCost with a vector and int
                a) this acts as a stack and reverses the path from dest --> start to start --> dest

            iii) print the results and empty the results vector

            iv)  check if they want another path and act accordingly
        */
        
        // i.a) initalize to store results
        vector<string> results;
        int overallCost = 0;
        bool finished   = false;

        if(targetFoundIndex != -1) // find path if destinations were found
        {
            //  i) and ii) tracking cost and path
            while(finished == false)
            {
                results.push_back(places[targetFoundIndex]);
                overallCost += costArr[targetFoundIndex];

                if(targetFoundIndex == track[targetFoundIndex])
                {
                    finished = true;
                } 

                targetFoundIndex = track[targetFoundIndex];
            }

            // ii) and iii) empty vector and print results
            while(results.empty() == false)
            {
                cout << results.back();
                results.pop_back();

                if(results.size() > 0)
                {
                    cout << " -> ";
                } else {
                    cout << ", $" << overallCost << endl;
                }
        }
        } else {
            if(cityIndex.find(source) == cityIndex.end())
            {
                cout << "   path not found, source city, " << source << ", not on the map" << endl;
            } else {
                cout << "   path not found, destination city, " << destination << ", not on the map" << endl;
            }
        }

        // iv) check if they want to continue
        char ans;
        cout << "Search another route? (Y/N) ";
        cin  >> ans;
        cin.ignore();

        ans = tolower(ans);

        if(ans == 'n') continueLoop = false;
    }

    in.close();
    return 0;
}