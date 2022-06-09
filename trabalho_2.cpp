#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define EXIT_CODE_ERROR 1
#define EXIT_CODE_SUCCESS 0
#define QUANTITY_REGISTER 1001
#define LIMIT_YEARS 100
#define LIMIT_RATINGS 50
using namespace std;

void error (string message) {
    cout << message << endl;
    exit(EXIT_CODE_ERROR);
}

typedef struct {
    string title;
    string rating;
    string ratingLevel;
    int ratingDescription;
    int releaseYear;
    int userRating;
    int userRatingSize;
} Movies;

// checa se uma string com uma representacao de inteiro valida
bool checkstringtoint (string number) {
    int i = 0;
    while (number[i] != '\0') {
        if (number[i] < 48 || number[i] > 57) return false;
        i++;
    }
    return true;
}
// wrapper to stoi
int wrapper_stoi (string number) {
    if (!checkstringtoint(number))  return 0;
    return stoi(number);
}


// verifica registro duplicados e filtra
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

int filter_registers (Movies filter[], Movies source[], int qtn_registers) {
    int k = 0;
    for (int i = 0; i < qtn_registers; i++)
    {
        if (!exists(filter, qtn_registers, source[i])) {
            filter[k] = source[i];
            k++;
        }
    }
    return k;
}
// verifica registro duplicados e filtra

/** EXERCICIO 2 */
typedef struct {
    string rating;
    int count;
    void *next = NULL;
} NodeRating;

typedef struct {
    int year;
    NodeRating node;
} Year;

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

int populateYears (int years[], Movies source[], int qtn_years) {
    int j = 0;
    for (int i = 0; i < qtn_years; i++) {
        int year = source[i].releaseYear;
        if (!existYears(years, qtn_years, year)) {
            years[j] = year;
            j++;
        }
    }
    return j;
}

int populateRatings (string ratings[], Movies source[], int qtn_ratings) {
    int k = 0;
    for (int i = 0; i < qtn_ratings; i++) {
        string rating = source[i].rating;
        if (!existRating(ratings, qtn_ratings, rating)) {
            ratings[k] = rating;
            k++;
        }
    }
    return k;
}

void populateyearsStructNodes (Year yearsStruct[], NodeRating node_ratings[], int allYears[], string allRatings[], Movies movies[], int limit_years, int limit_ratings, int qtn_registers) {
    NodeRating *node;
    int last_node_ratings_index = 0;
    for (int i = 0; i < limit_years; i++) {
        if (!allYears[i]) break;
        yearsStruct[i].year = allYears[i];
        yearsStruct[i].node = node_ratings[last_node_ratings_index];
        node = &yearsStruct[i].node;
        for (int j = 0; j < limit_ratings; j++) {
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
    for (int i = 0; i < limit_years; i++) {
        for (int j = 1; j < qtn_registers; j++) {
            if (movies[j].releaseYear == yearsStruct[i].year) {
                nodeRatingPointer = &yearsStruct[i].node;
                while (nodeRatingPointer->next != NULL) {
                    if (nodeRatingPointer->rating == movies[j].rating) {
                        nodeRatingPointer->count++;
                        break;
                    }
                    nodeRatingPointer = (NodeRating *) nodeRatingPointer->next;
                }
            }
        }    
    }
}

void printTotalMoviesEachYearForRating (Year yearsStruct[], int allYears[], string allRatings[], int limit_years, int limit_ratings) {
    cout << '\t';
    for (int i = 0; i < limit_ratings; i++) {
        cout << left << setw(10) << allRatings[i] << setw(10);
    }
    cout << endl;

    NodeRating *aux;
    for (int i = 0; i < limit_years; i++) {
        if (allYears[i] == 0)  break;
        cout << setw(10) << yearsStruct[i].year << setw(10);
        aux = &yearsStruct[i].node;
        while (aux->next != NULL) {
            cout << setw(10) << aux->count << setw(10);
            aux = (NodeRating *) aux->next;
        }
        cout << endl;
    }
}

/** EXERCICIO 2 */

int main () {
    string filename = "netflix_all.csv";

    ifstream file_read(filename, ios::in);

    if (!file_read.is_open()) {
        error("Erro ao abrir o arquivo, o programa não pode continuar");
    }

    Movies buffer_movies[QUANTITY_REGISTER];
    int indice = 0;

    // limpar o primeiro registro (cabecalho)
    getline(file_read, buffer_movies[indice].title);

    string title;
    string rating;
    string ratingLevel;
    string ratingDescription;
    string releaseYear;
    string userRating;
    string userRatingSize;

    while (!file_read.eof()) {
        getline(file_read,title,';');
        getline(file_read,rating,';');
        getline(file_read,ratingLevel,';');
        getline(file_read,ratingDescription,';');
        getline(file_read,releaseYear,';');
        getline(file_read,userRating,';');
        getline(file_read,userRatingSize,';');

        buffer_movies[indice].title = title;
        buffer_movies[indice].rating = rating;
        buffer_movies[indice].ratingLevel = ratingLevel;
        buffer_movies[indice].ratingDescription = wrapper_stoi(ratingDescription);
        buffer_movies[indice].releaseYear = wrapper_stoi(releaseYear);
        buffer_movies[indice].userRating = wrapper_stoi(userRating);
        buffer_movies[indice].userRatingSize = wrapper_stoi(userRatingSize);

        indice++;
    }

    Movies movies[QUANTITY_REGISTER];
    int quantidade_registros = filter_registers(movies,buffer_movies, QUANTITY_REGISTER);

    /**======== EXERCICIO 2  ========*/
    int allYears[LIMIT_YEARS];
    string allRatings[LIMIT_RATINGS];

    int qtn_years = populateYears(allYears, movies, LIMIT_YEARS);
    int qtn_ratings = populateRatings(allRatings, movies, LIMIT_RATINGS);
    orderYearsDesc(allYears, LIMIT_YEARS);


    Year yearsStruct[LIMIT_YEARS];


    NodeRating node_ratings[LIMIT_RATINGS * LIMIT_YEARS];

    //populateyearsStructNodes(Year yearsStruct[], NodeRating node_ratings[], int allYears[], string allRatings[], Movies movies[], int limit_years, int limit_ratings, int qtn_registers)
    populateyearsStructNodes(yearsStruct, node_ratings, allYears, allRatings, movies, LIMIT_YEARS, LIMIT_RATINGS, QUANTITY_REGISTER);

    //printTotalMoviesEachYearForRating (Year yearsStruct[], int allYears[], string allRatings[], int limit_years, int limit_ratings);
    // printTotalMoviesEachYearForRating(yearsStruct, allYears, allRatings, LIMIT_YEARS, LIMIT_RATINGS);
    /**======== EXERCICIO 2  ========*/


    file_read.close();

    return EXIT_CODE_SUCCESS;
}