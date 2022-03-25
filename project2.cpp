/*
* AUTHORS:  KAIJ SPENCER, DEVEN SWEET, DAVID ENE-ITA
*/


#include <iostream>
using namespace std;

bool isWrongFormat(string s);

int main() {

    const int ROW_SIZE = 10, COL_SIZE = 10;
    int num_array[ROW_SIZE][COL_SIZE] = {0};
    int disp_array[ROW_SIZE][COL_SIZE] = {0};

    string email;

    cin >> email;

    if (isWrongFormat(email)) {
        cout << "Email could not be verified." << endl;
        return 0;
    }

    cout << "Email has been verified!" << endl;

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