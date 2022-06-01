#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define LIMIT_REGISTERS 1002
#define LIMIT_YEARS 100
#define LIMIT_RATINGS 50
#define EXIT_SUCCES 0

using namespace std;

typedef struct {
    string rating;
    int count;
    void *next = NULL;
} NodeRating;

typedef struct {
    int year;
    NodeRating node;
} Year;


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

bool existRating (string ratings[], int n, string search) {
    for (int i = 0; i < n; i++) {
        if (ratings[i] == search) {
            return true;
        }
    }
    return false;
}

void orderYearsDesc (int years[], int n) {
    int aux = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (years[i] > years[j]) {
                aux = years[j];
                years[j] = years[i];
                years[i] = aux;
            }
        }
    }
}

int main () {
    Movies netflix[LIMIT_REGISTERS];

    int allYears[LIMIT_YEARS];

    string allRatings[LIMIT_RATINGS];

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

    // initializer register 1
    for (int i = 1, j = 0, k = 0; i < LIMIT_REGISTERS; i++) {
        int year = stoi(netflix[i].releaseYear);
        if (!existYears(allYears, LIMIT_YEARS, year)) {
            allYears[j] = year;
            j++;
        }

        string rating = netflix[i].rating;
        if (!existRating(allRatings, LIMIT_RATINGS, rating)) {
            allRatings[k] = rating;
            k++;
        }
    }

    orderYearsDesc(allYears, LIMIT_YEARS);

    Year yearsStruct[LIMIT_YEARS];

    NodeRating *node;

    NodeRating node_ratings[LIMIT_RATINGS * LIMIT_YEARS];

    int last_node_ratings_index = 0;
    for (int i = 0; i < LIMIT_YEARS; i++) {
        if (!allYears[i]) break;
        yearsStruct[i].year = allYears[i];
        yearsStruct[i].node = node_ratings[last_node_ratings_index];
        node = &yearsStruct[i].node;
        for (int j = 0; j < LIMIT_RATINGS; j++) {
            last_node_ratings_index++;
            if (allRatings[j] == "") {
                node->next = NULL;
                break;
            }
            node->rating = allRatings[j];
            node->next = &node_ratings[last_node_ratings_index];
            node = (NodeRating *) node->next;
        }
    }

    NodeRating *nodeRatingPointer;
    for (int i = 0; i < LIMIT_YEARS; i++) {
        for (int j = 1; j < LIMIT_REGISTERS; j++) {
            if (stoi(netflix[j].releaseYear) == yearsStruct[i].year) {
                nodeRatingPointer = &yearsStruct[i].node;
                while (nodeRatingPointer->next != NULL) {
                    if (nodeRatingPointer->rating == netflix[j].rating) {
                        nodeRatingPointer->count++;
                        break;
                    }
                    nodeRatingPointer = (NodeRating *) nodeRatingPointer->next;
                }
            }
        }    
    }

    
    // EXIBE O RESULTADO - CORRIGIR FORMATAÇÃO NA IMPRESSÃO - DEIXAR ALINHADO
    cout << '\t';
    for (int i = 0; i < LIMIT_RATINGS; i++) {
        cout << left << setw(10) << allRatings[i] << setw(10);
    }
    cout << endl;

    NodeRating *aux;
    for (int i = 0; i < LIMIT_YEARS; i++) {
        if (allYears[i] == 0)  break;
        cout << setw(10) << yearsStruct[i].year << setw(10);
        aux = &yearsStruct[i].node;
        while (aux->next != NULL) {
            cout << setw(10) << aux->count << setw(10);
            aux = (NodeRating *) aux->next;
        }
        cout << endl;
    }


    return EXIT_SUCCES;
}