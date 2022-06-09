#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

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

int lengthstring (string str) {
    int i = 0;
    while (str[i++] != '\0') ;
    return i;
}

//string to upper
string toupper (string convert) {
    int n = lengthstring(convert);
    for (int i = 0 ; i < n; i++) {
        if (convert[i] >= 97 && convert[i] <= 122) {
            convert[i] -= 32;
        }
    }
    return convert;
}

//remove /n
string removebreakline (string text) {
    int n = lengthstring(text);
    for (int i = 0; i < n; i++) {
        if (text[i] == '\n')  text[i] = ' ';
    }
    return text;
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


/** EXERCICIO 3 */
int getFirstYear (int allYears[], int qtn_years) {
    int maior = allYears[0];
    for (int i = 1; i < qtn_years; i++) {
        if (allYears[i] > maior)    {
            maior = allYears[i];
        }
    } 
    return maior;
}
int getLastYear (int allYears[], int qtn_years) {
    int menor = allYears[0];
    for (int i = 1; i < qtn_years; i++) {
        if (allYears[i] == 0) break;
        if (menor > allYears[i]) {
            menor = allYears[i];
        }
    }
    return menor;
}
void printYearForYear (Movies movies[], int firstYear, int lastYear, int qtn_registers) {
    int yearCount = 0;
    int ratingCount = 0;

    while(firstYear >= lastYear){
        yearCount = 0;
        for(int i = 1; i <= qtn_registers; i++){
            if(movies[i].releaseYear == firstYear) yearCount++;    
        }
        if(yearCount == 0){
            firstYear--;
            continue;
        }
        cout << "Ano: " << firstYear << " Quantidade: " << yearCount << endl;
        firstYear--;
    }
}
/** EXERCICIO 3 */

/** EXERCICIO 4 */
void orderMoviesByYearDesc(Movies movies[], int n) {
    Movies aux;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (movies[i].releaseYear > movies[j].releaseYear) {
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
        if (movies[i].releaseYear != year) continue;

        for (int j = 1; j < n; j++) {
            if (movies[i].userRating > movies[j].userRating) {
                aux = movies[j];
                movies[j] = movies[i];
                movies[i] = aux;
            }
        }
    }
}

void createFileTopMovies (int allYears[], Movies movies[], int top, int limit_registers, int limit_years) {
    string namefile_output = "most_apreciate_movies_each_year.csv";
    ofstream fileOut(namefile_output, ios::out);

    string temp_title_movie;

    fileOut << "title;" << "rating;" << "ratingLevel;" << "ratingDescription;" << "releaseyear;" << "user rating score;" << "user rating size;";
    for (int i = 0; i < limit_years; i++) {
        if (allYears[i] == 0) break;
        for (int j = 1, k = 0; j < limit_registers; j++) {
            if (k == top) break;
            if (movies[j].releaseYear != allYears[i]) continue;
            if (temp_title_movie == movies[j].title) continue;
            temp_title_movie = movies[j].title;
            fileOut << movies[j].title << ";";
            fileOut << movies[j].rating << ";";
            fileOut << movies[j].ratingLevel << ";";
            fileOut << movies[j].ratingDescription << ";";
            fileOut << movies[j].releaseYear << ";";
            fileOut << movies[j].userRating << ";";
            fileOut << movies[j].userRatingSize << ";";
            k++;
        }
    }
}
/** EXERCICIO 4 */

/** EXERCICIO 5 */
void printInfoViolenteAndSexualContent (Movies movies[], int firstYear, int lastYear, int registers) {
    int violenceCount = 0;
    int foundViolence;
    int foundNsfw;
    int nsfwCount = 0;
    
    //loop começando em firstyear e sendo iterado ate chegar em lastyear, percorrendo por todos os filmes
    while(firstYear >= lastYear){
        for(int i = 1; i <= registers; i++){
            if(movies[i].releaseYear == firstYear){
                foundViolence = movies[i].ratingLevel.find("violence");
                foundNsfw = movies[i].ratingLevel.find("sexual");
                if(foundViolence != -1){
                    violenceCount++;
                } 
                if(foundNsfw != -1){
                    nsfwCount++;
                }
            }
        }
        //iterador negativo
        firstYear--;
    }

    cout << "Filmes Violentos: " << violenceCount << " porcentagem: " << (100*violenceCount)/1000 << "%" << endl;
    cout << "Filmes contendo sexual content: " << nsfwCount << " porcentagem: " << (100*nsfwCount)/1000 << "%" << endl;
}

/** EXERCICIO 5 */

/** EXERCICIO 6 */

void findRegistersByTitle (string search, Movies movies[], int registers) {
    int foundSearch;
    int searchCount = 0;
    search = toupper(search);
    string temp_title;
    for(int i = 1; i <= registers; i++){
        temp_title = toupper(movies[i].title);
        foundSearch = temp_title.find(search);
        if(foundSearch != -1){
            cout << "Titulo: " << removebreakline(movies[i].title) << " | ";
            cout << "Faixa Etaria: " << movies[i].rating << " | ";
            cout << "descricao: " << movies[i].ratingLevel << endl;
            searchCount++;
        }
    }

    if(searchCount == 0){
        cout << "Nao foi encontrado nenhum titulo !" << endl;
    }
}

/** EXERCICIO 6 */

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

    int qtn_years = populateYears(allYears, movies, QUANTITY_REGISTER);
    int qtn_ratings = populateRatings(allRatings, movies, QUANTITY_REGISTER);
    orderYearsDesc(allYears, LIMIT_YEARS);

    Year yearsStruct[LIMIT_YEARS];

    NodeRating node_ratings[LIMIT_RATINGS * LIMIT_YEARS];

    //populateyearsStructNodes(Year yearsStruct[], NodeRating node_ratings[], int allYears[], string allRatings[], Movies movies[], int limit_years, int limit_ratings, int qtn_registers)
    populateyearsStructNodes(yearsStruct, node_ratings, allYears, allRatings, movies, LIMIT_YEARS, LIMIT_RATINGS, QUANTITY_REGISTER);

    //printTotalMoviesEachYearForRating (Year yearsStruct[], int allYears[], string allRatings[], int limit_years, int limit_ratings);
    // printTotalMoviesEachYearForRating(yearsStruct, allYears, allRatings, LIMIT_YEARS, LIMIT_RATINGS);
    /**======== EXERCICIO 2  ========*/

    /**======== EXERCICIO 3  ========*/
    int firstYear = getFirstYear(allYears, LIMIT_YEARS);
    int lastYear = getLastYear(allYears, LIMIT_YEARS);

    // printYearForYear (Movies movies[], int firstYear, int lastYear, int qtn_registers)
    // printYearForYear(movies, firstYear, lastYear, QUANTITY_REGISTER);
    /**======== EXERCICIO 3  ========*/

    /**======== EXERCICIO 4  ========*/
    orderMoviesByYearDesc(movies, QUANTITY_REGISTER);
    for (int i = 0; i < LIMIT_YEARS; i++) {
        if (allYears[i] == 0) break;
        orderMoviesByYearAndRatingScore(movies, QUANTITY_REGISTER, allYears[i]);
    }
    // createFileTopMovies (int allYears[], Movies movies[], int top, int limit_registers, int limit_years)
    // createFileTopMovies(allYears, movies, 10, QUANTITY_REGISTER, LIMIT_YEARS);
    /**======== EXERCICIO 4  ========*/

    /**======== EXERCICIO 5  ========*/
    // printInfoViolenteAndSexualContent(movies, firstYear, lastYear, QUANTITY_REGISTER);
    /**======== EXERCICIO 5  ========*/


    /**======== EXERCICIO 6  ========*/
    string search;
    cout << "Digite um titulo que deseja encontrar: " << endl;
    getline(cin, search);
    
    findRegistersByTitle(search, movies, QUANTITY_REGISTER);
    /**======== EXERCICIO 6  ========*/

    file_read.close();

    return EXIT_CODE_SUCCESS;
}