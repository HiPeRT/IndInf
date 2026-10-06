#include <iostream>
using namespace std;

char *a = "aabbbc";

int sfn(int oldS, char i);
int mfn(int oldS, char i);

int main() {
    int oldState = 0;

    for (int i=0; i<5; i++){
        char c = a[i];
        int newState = sfn(oldState, c);
        int out = mfn(oldState, c);

        cout << "sono nello stato " << oldState << " ho input " << c << " passo nello stato " << newState << " output " << out << endl;

        oldState = newState;

        if (oldState == 3) return 0;
    }
}

int sfn(int oldS, char i) {
    if (oldS == 0 && i == 'a') return 2;
    if (oldS == 0 && i == 'c') return 3;
    if (oldS == 0 && i == 'b') return 1;
    if (oldS == 2 && i == 'a') return 0;
    if (oldS == 1 && i == 'b') return 1;
    if (oldS == 1 && i == 'c') return 3;

    cout << "Errore" << endl;
    exit(1);
}

int mfn(int oldS, char i) {
    if (oldS == 0 && i == 'a') return 4;
    if (oldS == 0 && i == 'c') return 9;
    if (oldS == 0 && i == 'b') return 2;
    if (oldS == 2 && i == 'a') return 5;
    if (oldS == 1 && i == 'b') return 1;
    if (oldS == 1 && i == 'c') return 6;

    cout << "Errore" << endl;
    exit(1);
}
