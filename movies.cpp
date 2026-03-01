#include "movies.h"
#include <string>
#include <queue>
#include <unordered_map>
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
    for(string p: pre){
        for(Movie m : movie){
            string name = m.getName();
            int len = p.length();
            if(name.substr(0,len) == p){
                map[p].push(m);
            }
        }
    }
}