//
//  SCSSFactory.hpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 13/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef SCSSFactory_hpp
#define SCSSFactory_hpp

#include <algorithm>
#include <iomanip>
#include "Commons.h"
#include "Graph.hpp"

class SCSSFactory {
public:
    /**** optimized solution of superstring ****/
    string LongestCommonSuperString;
    
    class SuperStringSets {
    public: 
        int leftStringIdx, rightStringIdx;
        int intersectionNum;
        SuperStringSets(int leftStringIdx, int rightStringIdx, int intersectioNum);
    };
//    이건 왜안되지..
//public:
//    Graph superStringGraph = Graph(INPUT_SIZE);
    
    // 시작부터 substring으로 합쳐지는 string을 제외한 실제로 matrix에 포함되는 string의 갯수
    int MatrixSize = 0;
    vector<string> inputs;
    vector<string> processingBuffer;
    vector<string> noIntersectionStrings;
    vector<int> colAlreadyIncluded, rowAlreadyIncluded;
    vector<SuperStringSets> superstringSets;
    
    int intersectoinMatrix[INPUT_SIZE][INPUT_SIZE] = {0, };
    
public:
    SCSSFactory(vector<string> v);
    
    void doGreedyMethod();
    void doBranchNBound();
    
    vector<string> removeSubstrings(vector<string> v);
    vector<string> removeNoIntersectionString(vector<string> v);
    
    int getIntersectionNum(const string &l, const string &r);
    void initIntersectionMatrix();
    
    SuperStringSets getNextMaxInMatrix();
    string mergeByOverlapping(string leftString, string rightString, int interval);
    
    
    void showAll(vector<string >);
    
    bool isCircle(int v, int w);
    
    bool contains(vector<int> includedIdx, int idx);
    SuperStringSets findFirstSet();
    SuperStringSets findPreSet(int idx);
    SuperStringSets findNextSet(int idx);
    bool existPreSet(int idx);
};

#endif /* SCSSFactory_hpp */
