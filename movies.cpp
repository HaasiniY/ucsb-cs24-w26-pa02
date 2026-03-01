#include "movies.h"
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Movie::Movie(string n, double r) : name(n), rating(r) {};

bool Movie::operator<(const Movie& other) const{
    if(name == other.name){
        return rating < other.rating;
    }
    return name < other.name;
}

string Movie::getName() const{
    return name;
}

double Movie::getRating() const{
    return rating;
}

void orderMovieRating(const vector<string> & pre, const vector<Movie>& movie, 
        unordered_map<string, priority_queue<Movie, vector<Movie>, CompareMovieRating>>& map){

    unordered_set<string> uniquePrefixes(pre.begin(), pre.end());

    for(const string& p: uniquePrefixes){
        int len = p.length();

        for(const Movie &m : movie){
            const string& name = m.getName();
            
            if(name.size() >= len && name.compare(0, len, p) == 0){
                map[p].push(m);
            }
        }
    }
}