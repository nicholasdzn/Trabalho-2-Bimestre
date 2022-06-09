#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define LIMIT_REGISTERS 1002
#define LIMIT_YEARS 100
#define MAX_RATINGS_SCORE 100
#define TOP_QUANTITY 10
#define EXIT_SUCCES 0

using namespace std;

typedef struct {
    string title;
    string rating;
    string ratingLevel;
    string ratingDescription;
    string releaseYear;
    string userRating;
    string userRatingSize;
} Movies;


bool igualMovie (Movies m1, Movies m2) {
    if (m1.title != m2.title) return false;
    if (m1.rating != m2.rating) return false;
    if (m1.ratingLevel != m2.ratingLevel) return false;
    if (m1.ratingDescription != m2.ratingDescription) return false;
    if (m1.releaseYear != m2.releaseYear) return false;
    if (m1.userRating != m2.userRating) return false;
    if (m1.userRatingSize != m2.userRatingSize) return false;

    return true;
}

bool exists (Movies m[], int n, Movies search) {
    for (int i =0; i < n; i++) {
        if (igualMovie(m[i], search)) return true; 
    }
    return false;
}
int main () {
    Movies netflix[LIMIT_REGISTERS];

    int allYears[LIMIT_YEARS];

    string namefile = "netflix_all.csv";
    ifstream inMovies(namefile, ios::in);

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
    inMovies.close();

    Movies movies_filter[LIMIT_REGISTERS];

    int k = 0;

    for (int i = 1; i < LIMIT_REGISTERS; i++)
    {
        if (!exists(movies_filter, LIMIT_REGISTERS, netflix[i])) {
            movies_filter[k] = netflix[i];
            k++;
        }
    }
    
    for (int i = 0; i < k; i++)
    {
        cout << "Titulo: " << movies_filter[i].title << endl;
        cout << "Rating: " << movies_filter[i].rating << endl;
        cout << "RatingLevel: " << movies_filter[i].ratingLevel << endl;
        cout << "RatingDescription: " << movies_filter[i].ratingDescription << endl;
        cout << "ReleaseYear: " << movies_filter[i].releaseYear << endl;
        cout << "UserRating: " << movies_filter[i].userRating << endl;
        cout << "UserRatingSize: " << movies_filter[i].userRatingSize << endl;
    }
    


    return EXIT_SUCCES;
}