#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <cctype>
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
    year = 2017;
    int yearCount = 0;
    int ratingCount = 0;

    while(year != 1){
        yearCount = 0;
        for(int i = 1; i <= 1001; i++){
            if(stoi(netflix[i].releaseYear) == year) yearCount++;    
        }
        if(yearCount == 0){
            year--;
            continue;
        }
        cout << "Ano: " << year << " Quantidade: " << yearCount << endl;
        year--;
    }
    //=======================================================================

    //exercicio 5
    int violenceCount = 0;
    int foundViolence;
    int foundNsfw;
    int nsfwCount = 0;
    year = 2022;
    
    //loop começando em 2022 e sendo iterado ate chegar em 1, percorrendo por todos os filmes
    while(year != 1){
        for(int i = 1; i <= 1001; i++){
            if(stoi(netflix[i].releaseYear) == year){
                foundViolence = netflix[i].ratingLevel.find("violence");
                foundNsfw = netflix[i].ratingLevel.find("sexual");
                if(foundViolence != -1){
                    violenceCount++;
                }else if(foundNsfw != -1){
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
    string search;
    cout << "Digite um titulo que deseja encontrar: " << endl;
    getline(cin, search);

    int foundSearch;
    int searchCount = 0;

    for(int i = 1; i <= 1001; i++){
        foundSearch = netflix[i].title.find(search);
        if(foundSearch != -1){
            cout << netflix[i].title << " |  faixa etaria: " << netflix[i].rating << " | descricao: " << netflix[i].ratingLevel << endl;
            searchCount++;
        }
    }

    if(searchCount == 0){
        cout << "Nao foi encontrado nenhum titulo !";
    }
}