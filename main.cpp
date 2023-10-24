//
//  main.cpp
//  SpeechCompetitionSystemBasedOnSTL
//
//  Created by Yutong Xie on 11/4/22.
//

#include <iostream>
using namespace std;

#include "speechManager.hpp"

int main() {
    srand((unsigned int)time(NULL));
    
    SpeechManager sm;
    
    //test
//    for(map<int, Speaker>::iterator it = sm.mSpeaker.begin(); it != sm.mSpeaker.end(); it++){
//        cout << "Speaker Id: " << it->first
//             << " Name: " << it->second.name
//             << " Score: " << it->second.score[0] << endl;
//    }
//    cout << endl;
    
    cout << "Please enter your choice: " << endl;
    int choice = 0;
    
    while(true){
        sm.Show_Menu();
        
        cin >> choice;
        
        switch(choice){
            case 1: //start
                sm.Start_Speech();
                break;
            case 2: //show
                sm.Show_Record();
                break;
            case 3: //clear
                sm.Clear_Record();
                break;
            case 0: //exit
                sm.Exit_System();
                break;
            default:
                cout << "Invalid Input!" << endl;
                break;
        }
    }
    
    return 0;
}


