//Name: Haasini Yakkala

#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class Movie{
    public:
        Movie(string n, double r);
        bool operator<(const Movie& other) const;
        string getName()const;
        double getRating() const;
        
    private:
        string name;
        double rating;
};

struct CompareAlpha{
    bool operator()(const Movie& m1, const Movie& m2){
        return m1.getName() > m2.getName();
    }
};

struct CompareMovieRating{
    bool operator()(const Movie& m1, const Movie& m2){
        if(m1.getRating() == m2.getRating()){
            return m1.getName() > m2.getName();
        }
        return m1.getRating() < m2.getRating();
    }
};

void orderMovieRating(const vector<string>& p, const vector<Movie>& movie,
        unordered_map<string, priority_queue<Movie, vector<Movie>, CompareMovieRating>>& map);
