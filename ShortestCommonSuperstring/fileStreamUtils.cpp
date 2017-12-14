//
//  fileStreamUtils.cpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 11/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include "fileStreamUtils.hpp"

//앞에 있는 개행 문자 제거
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

//뒤에 있는 개행 문자 제거
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

//양쪽 끝의 개행 문자 제거
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

int fileStreamUtils::saveStr(string str){
    if (fileOutputStream.is_open()) {
        fileOutputStream << str << endl;
        return 0;
    } else return -1;
}

vector<string> fileStreamUtils::getInputs(){
    vector<string> v;
    string line;
    while (getline(fileInputStream, line)) {
        trim(line);
        v.push_back(line);
    }
    
    return v;
}

int fileStreamUtils::openOutputStream(string fileName){
    fileOutputStream.open(fileName, ios::out);
    if(!fileOutputStream.is_open()) return -1;
    else return 0;
}

int fileStreamUtils::openInputStream(string fileName){
    fileInputStream.open(fileName);
    
    if(fileInputStream.is_open()) return 0;
    else return -1;
}

int fileStreamUtils::closeStreams(){
    fileInputStream.close();
    fileOutputStream.close();
    if(oriFileContents != NULL) delete [] oriFileContents;
    return 0;
}

fileStreamUtils::~fileStreamUtils(){
    closeStreams();
}
