#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class KBC {
    int money;
    int safeMoney;
    int used50, usedPoll, usedCall, usedExpert;

    int prizeLadder[7] = {1000, 2000, 3000, 5000, 10000, 20000, 40000};

public:
    KBC() {
        money = 0;
        safeMoney = 0;
        used50 = usedPoll = usedCall = usedExpert = 0;
    }

    void showLadder() {
        cout << "\n--- Prize Ladder ---\n";
        cout << "Q1 -> 1000\nQ2 -> 2000\nQ3 -> 3000 (Safe)\nQ4 -> 5000\nQ5 -> 10000\nQ6 -> 20000 (Safe)\nQ7 -> 40000\n";
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

    bool askQuestion(string q, string o1, string o2, string o3, string o4, int correct, int qNo) {
        int ans;
        int prize = prizeLadder[qNo - 1];

        cout << "\nQ" << qNo << ": " << q << " (Rs." << prize << ")\n";
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

            if(qNo == 3 || qNo == 6) {
                safeMoney = money;
                cout << " Safe Level Reached! Rs." << safeMoney << endl;
            }

            return true;
        } else {
            cout << "Wrong Answer!\n";
            cout << "You drop to Rs." << safeMoney << endl;
            money = safeMoney;
            cout << "Final Winning: Rs." << money << endl;
            return false;
        }
    }

    void start() {
        showLadder();

        ifstream file("questions.txt");

        if(!file) {
            cout << "Error: questions.txt not found!\n";
            return;
        }

        string questions[50];
        string line;
        int count = 0;

        while(getline(file, line)) {
            questions[count++] = line;
        }

        // Shuffle
        for(int i = 0; i < count; i++) {
            int r = rand() % count;
            swap(questions[i], questions[r]);
        }

        for(int i = 0; i < 7 && i < count; i++) {
            string temp = questions[i];

            string q, o1, o2, o3, o4;
            int correct;

            q = temp.substr(0, temp.find("|"));
            temp = temp.substr(temp.find("|") + 1);

            o1 = temp.substr(0, temp.find("|"));
            temp = temp.substr(temp.find("|") + 1);

            o2 = temp.substr(0, temp.find("|"));
            temp = temp.substr(temp.find("|") + 1);

            o3 = temp.substr(0, temp.find("|"));
            temp = temp.substr(temp.find("|") + 1);

            o4 = temp.substr(0, temp.find("|"));
            temp = temp.substr(temp.find("|") + 1);

            correct = stoi(temp);

            if(!askQuestion(q, o1, o2, o3, o4, correct, i + 1))
                return;
        }

        cout << "\n Congratulations! You won Rs." << money << endl;
    }
};

int main() {
    srand(time(0));

    cout << "WELCOME TO KBC GAME\n";
    cout << "----------------------\n";

    KBC game;
    game.start();

    return 0;
}
