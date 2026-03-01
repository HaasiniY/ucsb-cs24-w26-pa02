// Winter'24
// Instructor: Diba Mirza
// Student name: Haasini Yakkala
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <chrono>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    set<Movie> movies_order;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movies_order.insert(Movie(movieName, movieRating));
    }

    movieFile.close();

    vector<Movie> movies;
    for(const Movie& m : movies_order){
        movies.push_back(m);
    }

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            for(auto m : movies_order){
                cout << m.getName() << ", " << m.getRating() << endl;
            }

            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    unordered_map<string, priority_queue<Movie, vector<Movie>, CompareMovieRating>> map;
    //auto start = chrono::high_resolution_clock::now();
    orderMovieRating(prefixes, movies, map);
    //auto end = chrono::high_resolution_clock::now();

    //auto duration = chrono::duration_cast<chrono::milliseconds>(end - start); 
    //cout << "Runtime: " << duration.count() << " ms" << endl;

    for(const string &prefix : prefixes){
        auto pq = map[prefix];

        if (pq.empty()) { 
            cout << "No movies found with prefix " << prefix << endl; 
            continue;
        }

        while(!pq.empty()){
            Movie m = pq.top();
            pq.pop();
            cout << m.getName() << ", " << m.getRating() << endl;
        }
        cout << endl;
    }
    
 
    for(const string &prefix : prefixes){
        auto pq = map[prefix];

        if(pq.empty()){
            continue;
        }

        if(!pq.empty()){
            Movie m = pq.top();
            cout << "Best movie with prefix " << prefix << " is: " << m.getName() << " with rating " << std::fixed << std::setprecision(1) << m.getRating() << endl;
        }
    }
    

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    //cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    //cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
Part 3a: 
Time Complexity: O(m * n * (l * log k))

Adding each movie in the text file into the binary tree is O(n log n).
Putting the movies from the binary tree into a vector is O(n).
Putting each movie into the hash map requires reading the movies for every prefix.
To check if a movie matches a prefix is O(l).
Adding a movie into the priority queue is O(log k).
In the worst case, if every movie is matched to a prefix, the time complexity is O(m * n * (l * log k)).
Printing the movies for each prefix is O(m * k log k).

The term that has the highest effect is O(m * n * (l * log k)).

Running Times:
input_20_random.csv: 14 ms
input_100_random.csv: 45 ms
input_1000_random.csv: 446 ms
input_76920_random.csv: 53160 ms

Part 3b:
Space Complexity: O(n + m + m * k)

The movies are at first stored in a set which is O(n) and then copied into a vector O(n).
The prefixes are stored in a vector which is O(m).
The hash map stores the movies that match a prefix into a priority queue, which would be O(m * k).

Part 3c:

My algorithm from part 2 was designed in a way that would minimize time complexity. 
I decided that using a hash map and priority queue would use a large amount of memory,
so I did not try to minimize space complexity as well. I tried to make the implementation
complexity more simpler by using different data structures to handle the data in a straightforward
manner.
My target complexities are having a low time complexity and low implementation complexity.
I aimed for a low time complexity, but could not achieve a low space complexity. The space
required to implement the algorithm was high, as I stored the movies using different data structures.
Rather than reducing the number of data structures used to store and sort through the data,
I utilized the specific aspects of each data structure to order the data and access it. For
example, I knew a priority queue for each prefix would require a lot of space, but I wanted to 
take advantage of the max heap charactistic to sort through the movies by rating.

*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}