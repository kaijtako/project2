/*
* AUTHORS:  KAIJ SPENCER, DEVEN SWEET, DAVID ENE-ITA
*/


#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int ROW_SIZE = 10, COL_SIZE = 10;

bool isWrongFormat(string);
//void initialize(int array[][10], int, int, int = -1);
void display(int array[][COL_SIZE], int, int);
void checkRepeat();

void initialize(int array[ROW_SIZE][COL_SIZE], int rows, int cols, int option = -1) {
    bool doRand = false;
    if (option != -1) {
        doRand = true;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = doRand ? rand() % 20 + 1 : -1;
        }
    }
}

int main() {

    int num_array[ROW_SIZE][COL_SIZE];
    int disp_array[ROW_SIZE][COL_SIZE];

    int rows = 0, columns = 0;
    int points = 10;

    srand(time(NULL));

    string email;

    do {
        cout << "Please enter your email address: " << endl;
        cin >> email;

        if (isWrongFormat(email)) {
            cout << "Email could not be verified." << endl;
            email = "";
        }

    } while (email == "");

    cout << "Email has been verified!" << endl;

    do {
        cout << "Please enter row size: " << endl;
        cin >> rows;

        cout << "Please enter Column size: " << endl;
        cin >> columns;

        if (rows > ROW_SIZE || columns > COL_SIZE) {
            cout << "Row and column numbers cannot exceed 10. Please try again." << endl;
        }
    } while (rows > ROW_SIZE || columns > COL_SIZE);

    initialize(disp_array, rows, columns);
    initialize(num_array, rows, columns, 1);

    display(disp_array, rows, columns);

    return 0;
}

bool isWrongFormat(string s) {
    int atSymbols = 0;
    int dotSymbols = 0;
    bool alphaBetween = false;

    for(int i = 0; i < s.size(); i++) {
        if (s[i] == '@') {
            atSymbols++;
            if (atSymbols > 1) {
                cout << "No more than one '@' (at) allowed." << endl;
                return true; // too many @s
            }
            continue;
        }
        if (s[i] == '.') {
            dotSymbols++;
            if (atSymbols == 1 && alphaBetween == false) {
                cout << "Email must have at least 1 alphanumeric character between '@' and '.'" << endl;
                return true;
            }
            if (dotSymbols > 1) {
                cout << "No more than one '.' (dot) allowed." << endl;
                return true; // too many dots
            }
            continue;
        }
        if ((isalpha(s[i]) || isdigit(s[i])) && atSymbols == 1 && dotSymbols == 0) {
            alphaBetween = true;
            continue;
        }
        if ((isalpha(s[i]) || isdigit(s[i]))) {
            continue;
        } else {
            cout << "Only alphanumeric characters are allowed." << endl;
            return true;
        }

    }

    if (atSymbols != 1 || dotSymbols != 1) {
        cout << "Must contain an '@' and '.'" << endl;
        return true;
    }

    return false;
}

void display(int array[ROW_SIZE][COL_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}