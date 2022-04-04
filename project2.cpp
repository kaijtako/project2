/*
* AUTHORS:  KAIJ SPENCER, DEVEN SWEET, DAVID ENE-ITA
*/


#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

// Values for rows and columns; constant sizes set the highest bounds for row and column size
const int ROW_SIZE = 10, COL_SIZE = 10;
// Number of rows and columns the user selects (set in main)
int rows = 0, cols = 0;

// The list of coordinate combinations that have been checked (used to prevent double guessing)
string checked[50];

// Checks the format of the email, returns true if it is incorrect
bool isWrongFormat(string);

// Displays the values of the array that is passed as input as a matrix
void display(int array[][COL_SIZE]);

// Checks for repeated combinations, returns true if a match is found
bool checkRepeat(int, int, int, int);

// Sets the values of the arrays to random numbers, or to -1 for the display array
void initialize(int array[ROW_SIZE][COL_SIZE], int option = -1) {
    bool doRand = false; // If true, each element will be a random value from 1 to 20
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

    int points = 10;

    // Seeds the random sequence so that the game will be random each time
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
        cin >> cols;

        if (rows > ROW_SIZE || cols > COL_SIZE) {
            cout << "Row and column numbers cannot exceed 10. Please try again." << endl;
        }
    } while (rows > ROW_SIZE || cols > COL_SIZE);

    initialize(disp_array);
    initialize(num_array, 1);

    display(disp_array);

    int coord1, coord2; // Coordinates of the first selection
    int coord3, coord4;// Coordinates of the second selection
    char repeat; // This is used when asking the user to continue the game.

    do { // Game Begins Here
        cout << "Choose coordinates to check: ";
        cin >> coord1 >> coord2;

        if (coord1 > rows || coord2 > cols) { // Check if coordinates are in bounds
            cout << "Selection out of bounds. Please try again." << endl;
            continue;
        }

        disp_array[coord1][coord2] = num_array[coord1][coord2];
        display(disp_array); // reveal the first selection

        cout << "Select another coordinate to compare to: ";
        cin >> coord3 >> coord4;

        if (coord3 > rows || coord4 > cols) { // Check if coordinates are in bounds
            cout << "Selection out of bounds. Please try again." << endl;
            continue;
        }

        if (coord1 == coord3 && coord2 == coord4) { // Check if the same coordinate is used twice
            cout << "You cannot use the same coordinate twice. Please try again." << endl;
            continue;
        }

        if (checkRepeat(coord1, coord2, coord3, coord4)) { // Check if the combination is repeated
            cout << "You have already selected this coordinate. Try a new one." << endl;
            continue;
        }

        if (num_array[coord1][coord2] == num_array[coord3][coord4]) {
            cout << "Match found! +2 Points" << endl;
            disp_array[coord3][coord4] = num_array[coord3][coord4];
            display(disp_array);
            points += 2;
        } else {
            cout << "They don't match. -1 Point." << endl;
            points -= 1;
        }

        if (points == 0) {
            cout << "It looks like you've run out of points. GAME OVER." << endl;
            break;
        }

        cout << "You currently have " << points << " points. Do you wish to continue (Y/N)? ";
        cin >> repeat;

    } while(toupper(repeat) != 'N'); // Game ends if the user selects 'N'

    cout << "You ended the game with " << points << " points. This will be sent to your email: " << email << endl;

    return 0;
} // End of main()

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
} // end of isWrongFormat()

void display(int array[ROW_SIZE][COL_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}

bool checkRepeat(int coord1, int coord2, int coord3, int coord4) {
    // The coordinates the user input in string format
    string coords = to_string(coord1) + ' ' + to_string(coord2) + ',' + to_string(coord3) + ' ' + to_string(coord4);
    // The coordinates the user input in reverse order (to prevent double guessing)
    string coordsBack = to_string(coord3) + ' ' + to_string(coord4) + ',' + to_string(coord1) + ' ' + to_string(coord2);

    for(int i = 0; i < 50; i++) {
        if(checked[i] == coords || checked[i] == coordsBack) {
            return true;
        } else if (checked[i] == "") {
            checked[i] = coords;
            break;
        }
    }

    return false;
}