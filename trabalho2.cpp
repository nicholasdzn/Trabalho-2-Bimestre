#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#define LIMIT_REGISTERS 1002
#define EXIT_SUCCES 0

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
    Movies netflix[LIMIT_REGISTERS];
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
    //=========================================================

    //exercicio 3  - corrigir - totais não conferem
    int year;
    year = 2022;
    int yearCount = 0;
    int ratingCount = 0;

    while(year != 1){
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
    year = 2022;
    
    //loop começando em 2022 e sendo iterado ate chegar em 1, percorrendo por todos os filmes
    while(year != 1){
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
    
    // exercicio 2
    //=========================================================================




    return EXIT_SUCCES;
}