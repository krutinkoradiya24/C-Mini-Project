#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class KBC {
    int money;
    int used50, usedPoll, usedCall, usedExpert;

public:
    KBC() {
        money = 0;
        used50 = usedPoll = usedCall = usedExpert = 0;
    }

    void showLadder() {
        cout << "\n--- Prize Ladder ---\n";
        cout << "Q1 -> 1000\nQ2 -> 2000\nQ3 -> 3000\nQ4 -> 5000\nQ5 -> 10000\nQ6 -> 20000\nQ7 -> 40000\n";
        cout << "---------------------\n";
    }
   void showLifelines() {
        cout << "\nAvailable Lifelines:\n";
        if(!used50) cout << "1. 50-50\n";
        if(!usedPoll) cout << "2. Audience Poll\n";
        if(!usedCall) cout << "3. Phone a Friend\n";
        if(!usedExpert) cout << "4. Expert Advice\n";
    }
    void lifeline(int correctOption) {
        int life;
        showLifelines();
        cin >> life;

        if(life == 1 && !used50) {
            used50 = 1;
            cout << "Options left: " << correctOption << " and ";
            if(correctOption == 1) cout << "2\n";
            else cout << "1\n";
        }
        else if(life == 2 && !usedPoll) {
            usedPoll = 1;

            cout << "Audience Poll:\n";

            cout << "Option " << correctOption << " -> 60%\n";

            if(correctOption != 1)
                cout << "Option 1 -> 20%\n";

            if(correctOption != 2)
                cout << "Option 2 -> 20%\n";
        }

        else if(life == 3 && !usedCall) {
            usedCall = 1;
            cout << "Friend says option " << correctOption << "\n";
        }

        else if(life == 4 && !usedExpert) {
            usedExpert = 1;
            cout << "Expert suggests option " << correctOption << "\n";
        }

        else {
            cout << "Invalid or already used lifeline!\n";
        }
    }

    bool askQuestion(string q, string o1, string o2, string o3, string o4, int correct, int prize) {
        int ans;
        cout << "\n" << q << " (Rs." << prize << ")\n";
        cout << "1. " << o1 << "\t\t2. " << o2 << endl;
        cout << "3. " << o3 << "\t\t4. " << o4 << endl;

        cout << "Press 9 for lifeline\n";
        cin >> ans;

        if(ans == 9) {
            lifeline(correct);
            cout << "Enter your answer: ";
            cin >> ans;
        }

        if(ans == correct) {
            money += prize;
            cout << "Correct! You won Rs." << prize << endl;
            cout << "Total Winning: Rs." << money << endl;
            return true;
        } else {
            cout << "Wrong Answer! Final Winning: Rs." << money << endl;
            return false;
        }
    }
    void start() {
        showLadder();

        if(!askQuestion("Q1: How many days in a week?", "5","6","7","8", 3, 1000)) return;
        if(!askQuestion("Q2: Which color is sky?", "Green","Blue","Red","Yellow", 2, 2000)) return;
        if(!askQuestion("Q3: 5 + 3 = ?", "6","7","8","9", 3, 3000)) return;
        if(!askQuestion("Q4: Which animal barks?", "Cat","Dog","Cow","Goat", 2, 5000)) return;
        if(!askQuestion("Q5: Which fruit is yellow?", "Apple","Banana","Grapes","Mango", 2, 10000)) return;
        if(!askQuestion("Q6: How many months in a year?", "10","11","12","13", 3, 20000)) return;
        if(!askQuestion("Q7: Which is a programming language?", "HTML","C++","CSS","Photoshop", 2, 40000)) return;
        cout << "\nCongratulations! Final Winning: Rs." << money << endl;
    }
};

int main() {
    srand(time(0));
    cout << "WELCOME TO KAUN BANEGA CROREPATI GAME\n";
    cout << "----------------------\n";
    KBC game;
    game.start();
    return 0;
}