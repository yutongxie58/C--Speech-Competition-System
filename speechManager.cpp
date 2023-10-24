//
//  speechManager.cpp
//  SpeechCompetitionSystemBasedOnSTL
//
//  Created by Yutong Xie on 11/4/22.
//

#include "speechManager.hpp"
#include <algorithm>
#include <random>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#define FILENAME "/Users/yutongxie/c++-workspace/SpeechCompetitionSystem/SpeechCompetitionSystem/speech.csv"

SpeechManager::SpeechManager(){
    this->InitSpeech();
    this->CreateSpeaker();
    this->LoadRecord();
}

void SpeechManager::Show_Menu(){
    cout << "***************************************************" << endl;
    cout << "*******  Welcome to Join Speech Competition *******" << endl;
    cout << "************* 1. Start Competition ****************" << endl;
    cout << "************* 2. Show Past Records ****************" << endl;
    cout << "************* 3. Clear All Records ****************" << endl;
    cout << "************* 0. Exit System **********************" << endl;
    cout << "***************************************************" << endl;
    cout << endl;
}

void SpeechManager::Exit_System(){
    cout << "Thank you!" << endl;
    exit(0);
}

void SpeechManager::InitSpeech(){
    this->v1.clear();
    this->v2.clear();
    this->vw.clear();
    this->mSpeaker.clear();
    
    this->round = 1;
    
    this->mRecord.clear();
}

void SpeechManager::CreateSpeaker(){
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0; i < nameSeed.size(); i++){
        string name = "Speaker";
        name += nameSeed[i];
        
        Speaker sp;
        sp.name = name;
        
        for(int j = 0; j < 2; j++){
            sp.score[j] = 0;
        }

        this->v1.push_back(i + 10001);
        
        this->mSpeaker.insert(make_pair(i+10001, sp));
    }
}

void SpeechManager::Start_Speech(){
    //#1 round
    
    //1. draw
    this->SpeechDraw();
    
    //2. contest
    this->SpeechContest();

    //3. show result
    this->ShowScore();
    
    //#2 round
    this->round++;
    
    //1. draw
    this->SpeechDraw();
    
    //2. contest
    this->SpeechContest();

    //3. show result
    this->ShowScore();
    
    //4. save scores to file
    this->SaveRecord();
    
    //refresh
    this->InitSpeech();
    
    this->CreateSpeaker();
    
    this->LoadRecord();
    
    cout << "This Speech Competition is over now!" << endl;
    cout << endl;
}

void SpeechManager::SpeechDraw(){
    cout << "#" << this->round << " round is drawing lots..." << endl;
    cout << "----------------------------------" << endl;
    cout << "#" << this->round << " round order: " << endl;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    if(this->round == 1){
        shuffle(v1.begin(), v1.end(), std::default_random_engine(seed));
        for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
    else{
        shuffle(v2.begin(), v2.end(), std::default_random_engine(seed));
        for(vector<int>::iterator it = v2.begin(); it != v2.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
    
    cout << "-------------------------------------------------------------------------" << endl;
    cout << endl;

}

void SpeechManager::SpeechContest(){
    cout << "------------ #" << this->round << " round now starts ----------" << endl;
    
    multimap<double, int, greater<double>> groupScore;
    
    //speaker quantity: 6 into one group
    int num = 0;
    
    vector<int>vS;
    if(this->round == 1){
        vS = v1;
    }
    else{
        vS = v2;
    }
    
    for(vector<int>::iterator it = vS.begin(); it != vS.end(); it++){
        num++;
        
        deque<double>d;
        for(int i = 0; i < 10; i++ ){
            double score = (rand() % 401 + 600) / 10.f;
//            cout << score << " ";
            d.push_back(score);
        }
//        cout << endl;
        
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front();
        d.pop_back();
        
        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size();
        
//        cout << "Id: " << *it
//             << " Name: " << this->mSpeaker[*it].name
//             << " Average score: " << avg << endl;
        
        this->mSpeaker[*it].score[this->round - 1] = avg;
        
        groupScore.insert(make_pair(avg, *it));
        if(num % 6 == 0){
            cout << "Group #" << num / 6 << " result: " << endl;
            for(multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++){
                cout << "Id: " << it->second
                     << " Name: " << this->mSpeaker[it->second].name
                     << " Score: " << mSpeaker[it->second].score[round - 1] << endl;
            }
            
            int count = 0;
            for(multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++){
                if(this->round == 1){
                    v2.push_back((*it).second);
                }
                else{
                    vw.push_back((*it).second);
                }
            }
            
            groupScore.clear();
            
            cout << endl;
        }
    }
    
    cout << "------------ #" << this->round << " round is over ----------" << endl;
    
    cout << endl;
}

void SpeechManager::ShowScore(){
    cout << "------------ #" << this->round << " round winners ----------" << endl;
    
    vector<int>v;
    if(this->round == 1){
        v = v2;
    }
    else{
        v = vw;
    }
    
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << "Speaker Id: " << *it
             << " Name: " << this->mSpeaker[*it].name
             << " Score: " << this->mSpeaker[*it].score[this->round - 1] << endl;
    }
    cout << endl;
    this->Show_Menu();
}

void SpeechManager::SaveRecord(){
    ofstream ofs;
    ofs.open(FILENAME, ios::out | ios::app);
    
    for(vector<int>::iterator it = vw.begin(); it != vw.end(); it++){
        ofs << *it << "," << this->mSpeaker[*it].score[1] << ",";
    }
    ofs << endl;
    
    ofs.close();
    cout << "Saved Successfully!" << endl;
    
    this->fileIsEmpty = false;
}

void SpeechManager::LoadRecord(){
    ifstream ifs(FILENAME, ios::in);
    
    if(!ifs.is_open()){
        this->fileIsEmpty = true;
//        cout << "File does not exist!" << endl; //test
        ifs.close();
        return;
    }
    
    char ch;
    ifs >> ch;
    if(ifs.eof()){
        this->fileIsEmpty = true;
//        cout << "File is empty!" << endl; //test
        ifs.close();
        return;
    }
    
    //file exists and file is not empty
    this->fileIsEmpty = false;
    
    ifs.putback(ch);
    
    string data;
    int index = 1;
    
    while(ifs >> data){
//        cout << data << endl; //test
        
        vector<string>v;
        
        int pos = -1;
        int start = 0;
        
        while(true){
            pos = data.find(",", start);
            if(pos == -1){ //if not find or reach to the end, break
                break;
            }
            string temp = data.substr(start, pos - start);
//            cout << temp << endl; //test
            v.push_back(temp);
            
            start = pos + 1;
        }
        
        this->mRecord.insert(make_pair(index, v));
        index++;
    }
    ifs.close();
    
    //test
//    for(map<int, vector<string>>::iterator it = mRecord.begin(); it != mRecord.end(); it++){
//        cout << "#" << it->first << " Winner:"
//             << " Id: " << it->second[0] << " Score: " << it->second[1];
//    }
}

void SpeechManager::Show_Record(){
    if(this->fileIsEmpty){
        cout << "File is empty or file does not exist!" << endl;
    }
    else{
        for(map<int, vector<string>>::iterator it = mRecord.begin(); it != mRecord.end(); it++){
            cout << "-------- #" << it->first << " Speech Competition --------" << endl;
            cout << "First Place:" << " Id: " << it->second[0] << " Score: " << it->second[1] << endl;
            cout << "Second Place:" << " Id: " << it->second[2] << " Score: " << it->second[3] << endl;
            cout << "Third Place:" << " Id: " << it->second[4] << " Score: " << it->second[5] << endl;
        }
    }
    cout << endl;

}

void SpeechManager::Clear_Record(){
    cout << "Are you sure to clear the record?" << endl;
    cout << "   1. Yes" << endl;
    cout << "   2. No" << endl;
    
    int choice = 0;
    
    cin >> choice;
    
    if(choice == 1){
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
       
        this->InitSpeech();
        this->CreateSpeaker();
        this->LoadRecord();
        
        cout << "Cleared Successfully!" << endl;
    }
    
    cout << endl;
}

SpeechManager::~SpeechManager(){}

