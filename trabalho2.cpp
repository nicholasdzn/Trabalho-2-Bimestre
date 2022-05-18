#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using namespace std;

struct Movies {
    string title;
    string rating;
    string ratingLevel;
    string ratingDescription;
    string releaseYear;
    string userRating;
    string userRatingSize;
};

int main() {
    Movies netflix[1002];
    ifstream inMovies("netflix_all.csv", ios::in);

    string title;
    string rating;
    string ratingLevel;
    string ratingDescription;
    string releaseYear;
    string userRating;
    string userRatingSize;

    int i = 0;

    while(!inMovies.eof()){
        getline(inMovies,title,';');
        getline(inMovies,rating,';');
        getline(inMovies,ratingLevel,';');
        getline(inMovies,ratingDescription,';');
        getline(inMovies,releaseYear,';');
        getline(inMovies,userRating,';');
        getline(inMovies,userRatingSize,';');

        netflix[i].title = title;
        netflix[i].rating = rating;
        netflix[i].ratingLevel = ratingLevel;
        netflix[i].ratingDescription = ratingDescription;
        netflix[i].releaseYear = releaseYear;
        netflix[i].userRating = userRating;
        netflix[i].userRatingSize = userRatingSize;

        i++;
    }

    int year;
    year = 2016;
    int yearCount = 0;
    int ratingCount = 0;

    while(year != 1950){
        yearCount = 0;
        for(int i = 1; i <= 1001; i++){
            if(stoi(netflix[i].releaseYear) == year){
                yearCount++;    
            }
        }
        if(yearCount == 0){
            continue;
        }
        else{
            cout << "Ano: " << year << " Quantidade: " << yearCount << endl;
            year--;
        }
    }

}