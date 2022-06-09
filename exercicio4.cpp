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

bool existYears (int years[], int n, int search) {
    for (int i = 0; i < n; i++) {
        if (years[i] == search) {
            return true;
        }
    }
    return false;
}


void orderMoviesByYearDesc(Movies movies[], int n) {
    Movies aux;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (stoi(movies[i].releaseYear) > stoi(movies[j].releaseYear)) {
                aux = movies[j];
                movies[j] = movies[i];
                movies[i] = aux;
            }
        }
    }
}

void orderMoviesByYearAndRatingScore(Movies movies[], int n, int year) {
    Movies aux;
    for (int i = 1; i < n; i++) {
        if (stoi(movies[i].releaseYear) != year) continue;
        if (movies[i].userRating == "NA" || movies[i].userRating == "") {
            movies[i].userRating = "0";
        }
        for (int j = 1; j < n; j++) {
            if (movies[j].userRating == "NA" || movies[j].userRating == "") {
                movies[j].userRating = "0";
            }
            if (stoi(movies[i].userRating) > stoi(movies[j].userRating)) {
                aux = movies[j];
                movies[j] = movies[i];
                movies[i] = aux;
            }
        }
    }
}

void orderDesc (int vetor[], int n) {
    int aux = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vetor[i] > vetor[j]) {
                aux = vetor[j];
                vetor[j] = vetor[i];
                vetor[i] = aux;
            }
        }
    }
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

    // initializer register 1
    for (int i = 1, j = 0, k = 0; i < LIMIT_REGISTERS; i++) {
        int year = stoi(netflix[i].releaseYear);
        if (!existYears(allYears, LIMIT_YEARS, year)) {
            allYears[j] = year;
            j++;
        }
    }

    orderDesc(allYears, LIMIT_YEARS);

    orderMoviesByYearDesc(netflix, LIMIT_REGISTERS);
    for (int i = 0; i < LIMIT_YEARS; i++) {
        if (allYears[i] == 0) break;
        orderMoviesByYearAndRatingScore(netflix, LIMIT_REGISTERS, allYears[i]);
    }

    string namefile_output = "most_apreciate_moveis_each_year.csv";
    ofstream fileOut(namefile_output, ios::out);

    string temp_title_movie;

    fileOut << "title;" << "rating;" << "ratingLevel;" << "ratingDescription;" << "releaseyear;" << "user rating score;" << "user rating size;";
    for (int i = 0; i < LIMIT_YEARS; i++) {
        if (allYears[i] == 0) break;
        for (int j = 1, k = 0; j < LIMIT_REGISTERS; j++) {
            if (k == TOP_QUANTITY) break;
            if (stoi(netflix[j].releaseYear) != allYears[i]) continue;
            if (temp_title_movie == netflix[j].title) continue;
            temp_title_movie = netflix[j].title;
            fileOut << netflix[j].title << ";";
            fileOut << netflix[j].rating << ";";
            fileOut << netflix[j].ratingLevel << ";";
            fileOut << netflix[j].ratingDescription << ";";
            fileOut << netflix[j].releaseYear << ";";
            fileOut << netflix[j].userRating << ";";
            fileOut << netflix[j].userRatingSize << ";";
            k++;
        }
    }


    return EXIT_SUCCES;
}