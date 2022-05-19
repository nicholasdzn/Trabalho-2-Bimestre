#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
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
    //exercicio 1
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
    //=========================================================

    //exercicio 3
    int year;
    year = 2017;
    int yearCount = 0;
    int ratingCount = 0;

    while(year != 1975){
        yearCount = 0;
        for(int i = 1; i <= 1001; i++){
            if(stoi(netflix[i].releaseYear) == year) yearCount++;    
        }
        year--;
        if(yearCount == 0){
            continue;
        }
        cout << "Ano: " << year << " Quantidade: " << yearCount << endl;
    }
    //=======================================================================

    //exercicio 5
    //contador de filmes violentos
    int violenceCount = 0;
    //contador de filmes com sexual content
    int nsfwCount = 0;
    year = 2017;
    
    //loop começando em 2017 (filme mais novo em registro) e sendo iterado ate chegar em 1975 (filme mais antigo regitrado)
    while(year != 1975){
        for(int i = 1; i <= 1001; i++){
            if(stoi(netflix[i].releaseYear) == year){
                //filmes violentos estao entre 90 e 100 de rating description
                if(stoi(netflix[i].ratingDescription) >= 90 && stoi(netflix[i].ratingDescription) <= 100){
                    violenceCount++;
                //filmes com sexual content estao acima de 110 de rating description
                }else if(stoi(netflix[i].ratingDescription) >= 110){
                    nsfwCount++;
                }
            }
        }
        //iterador negativo
        year--;
    }

    cout << "Filmes Violentos: " << violenceCount << " porcentagem: " << (100*violenceCount)/1000 << "%" << endl;
    cout << "Filmes contendo sexual content: " << nsfwCount << " porcentagem: " << (100*nsfwCount)/1000 << "%" << endl;
    //=========================================================================

}