//
//  fileStreamUtils.hpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 11/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef fileStreamUtils_hpp
#define fileStreamUtils_hpp

#include <fstream>
#include <functional>
#include <cctype>
#include <locale>
#include "Commons.h"

class fileStreamUtils {
private:
    ifstream fileInputStream;
    ofstream fileOutputStream;
    char* oriFileContents = NULL;
    
public:
    ~fileStreamUtils();
    int openInputStream(string fileName);
    int openOutputStream(string fileName);
    int closeStreams();
    vector<string> getInputs();
    int saveStr(string str);
    
};
#endif /* fileStreamUtils_hpp */
