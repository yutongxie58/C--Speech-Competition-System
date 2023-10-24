//
//  speechManager.hpp
//  SpeechCompetitionSystemBasedOnSTL
//
//  Created by Yutong Xie on 11/4/22.
//

#ifndef speechManager_hpp
#define speechManager_hpp

#include <iostream>
using namespace std;

#include <vector>
#include "speaker.hpp"
#include <map>

class SpeechManager{
public:
    
    SpeechManager();
    
    void Show_Menu();
    
    void Exit_System();
    
    // initialize
    void InitSpeech();
    
    void CreateSpeaker();
    
    void Start_Speech();
    
    void SpeechDraw();
    
    void SpeechContest();
    
    void ShowScore();
    
    void SaveRecord();
    
    void LoadRecord();
    
    void Show_Record();
    
    void Clear_Record();
    
    ~SpeechManager();
    
    //speaker id in first round
    vector<int>v1;
    
    //speaker id in second round
    vector<int>v2;
    
    //speaker id of three winners
    vector<int>vw;
    
    //pair speaker id with Speaker
    map<int, Speaker>mSpeaker;
    
    int round;
    
    bool fileIsEmpty;
    
    map<int, vector<string>>mRecord;
};

#endif /* speechManager_hpp */

