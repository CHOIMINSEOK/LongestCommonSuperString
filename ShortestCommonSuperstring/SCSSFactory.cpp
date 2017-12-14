//
//  SCSSFactory.cpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 13/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include "SCSSFactory.hpp"

Graph superStringGraph(INPUT_SIZE);

ostream &operator<<(std::ostream &os, SCSSFactory::SuperStringSets const &m) {
    return os << "leftString : " << m.leftStringIdx << ", rightString : " << m.rightStringIdx << ", intersectionNum : " << m.intersectionNum;
}

SCSSFactory::SuperStringSets::SuperStringSets(int leftStringIdx, int rightStringIdx, int intersectionNum) {
    this->leftStringIdx   = leftStringIdx;
    this->rightStringIdx  = rightStringIdx;
    this->intersectionNum = intersectionNum;
}

SCSSFactory::SCSSFactory(vector<string> v) {
    sort(v.begin(), v.end(), [](const string &l, const string &r) { return l.size()<r.size(); });

    inputs = removeSubstrings(v);
    MatrixSize = (int)inputs.size();
    initIntersectionMatrix();
    
    // 아무 겹침이 없는 string은 따로 저장해뒀다가 마지막 superstring에 붙입니다.
    inputs = removeNoIntersectionString(inputs);
    MatrixSize = (int)inputs.size();
    initIntersectionMatrix();
    
    doGreedyMethod();
    showAll(inputs);
}

void SCSSFactory::doGreedyMethod() {
    processingBuffer = inputs;
    
    for (int i=0; i<MatrixSize-1; i++) {
        superstringSets.push_back(getNextMaxInMatrix());
    }
    
    for (vector<SuperStringSets>::size_type i=0; i < superstringSets.size(); i++) {
        cout << superstringSets.at(i) << endl ;
//        SuperStringSets tmp = superstringSets.at(i);
//
//        int leftStringIdx = tmp.leftStringIdx;
//        int rightStringIdx = tmp.rightStringIdx;
//
//        string mergedString = mergeByOverlapping(processingBuffer.at(leftStringIdx), processingBuffer.at(rightStringIdx), tmp.intersectionNum);
//
//        processingBuffer[leftStringIdx] = mergedString;
//        processingBuffer[rightStringIdx] = mergedString;
//
//        LongestCommonSuperString = mergedString;
        
//        cout << mergedString << endl;
    }
    
    SuperStringSets s = findNextSet(superStringGraph.getFirstSetIdx());
    cout << s << endl;
    LongestCommonSuperString = mergeByOverlapping(processingBuffer.at(s.leftStringIdx), processingBuffer.at(s.rightStringIdx), s.intersectionNum);
    
    for (vector<SuperStringSets>::size_type i=0; i < superstringSets.size()-1; i++) {
        s = findNextSet(s.rightStringIdx);
        cout << s << endl;
        LongestCommonSuperString = mergeByOverlapping(LongestCommonSuperString, processingBuffer.at(s.rightStringIdx), s.intersectionNum);
    }
    
    // TODO : 하나도 안겹치는거 추가할 것
}

SCSSFactory::SuperStringSets SCSSFactory::getNextMaxInMatrix() {
    int maxRow, maxCol;
    int maxVal = -1;
    for (int i=0; i<MatrixSize; i++) {
        for (int j=0; j<MatrixSize; j++) {
            // TODO : add filter to prevent cycle
            if (intersectoinMatrix[i][j] > maxVal && (i != j) && !contains(rowAlreadyIncluded, i) && !contains(colAlreadyIncluded, j) && !isCircle(i, j))  {
                maxVal = intersectoinMatrix[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    
    // right -> left로의 directed graph
    superStringGraph.addEdge(maxCol, maxRow);
    rowAlreadyIncluded.push_back(maxRow);
    colAlreadyIncluded.push_back(maxCol);
    
    return SuperStringSets(maxRow, maxCol, maxVal);
}

string SCSSFactory::mergeByOverlapping(string leftString, string rightString, int interval) {
    leftString.replace(leftString.size()-interval, interval, rightString);
    
    return leftString;
}

void SCSSFactory::initIntersectionMatrix() {
    for (int i=0; i<MatrixSize; i++) {
        for (int j=0; j<MatrixSize; j++) {
            if (i==j) continue;
            intersectoinMatrix[i][j] = getIntersectionNum(inputs.at(i), inputs.at(j));
        }
    }
}

// TODO : 이거 다바꿔야함
int SCSSFactory::getIntersectionNum(const string &l, const string &r) {
    vector<int>::iterator maxIdx;
    int num = 0, tmpNum = 0;
    vector<int> nums;
    bool isCollision = false;
    int smallerSize = (l.size()>r.size()) ? r.size() : l.size();
    
    nums.push_back(tmpNum);
    for (int i=1; i<smallerSize; i++) {
        for (int j=0; j<i; j++) {
            if (l[l.size()-i+j] == r[j]) tmpNum++;
            else {
                isCollision = true;
                break;
            };
        }
        if (!isCollision) nums.push_back(tmpNum);
        
        tmpNum = 0;
        isCollision = false;
        
    }
    
//    for (vector<int>::size_type i=0; i < nums.size(); i++) {
//        cout << nums.at(i) << " ";
//    }
//    cout << endl;
    
    maxIdx = max_element(nums.begin(), nums.end());
    num = *maxIdx;
//    if (num==0) cout << l << " <==> " << r << "\ninter : " << num <<endl;
//    else cout << l.substr(0, l.size()-num) << "[" << l.substr(l.size()-num, num) << "]"
//        << " <==> "
//        << "[" << r.substr(0, num) << "]" << r.substr(num, r.size()-num) << "\ninter : " << num <<endl;

    return num;
}

vector<string> SCSSFactory::removeNoIntersectionString(vector<string> v) {
    for (int i=0; i<MatrixSize; i++) {
        int j=0;
        for (; j<MatrixSize; j++) if (intersectoinMatrix[i][j] != 0 || intersectoinMatrix[j][i] != 0) break;
        
        if (j == MatrixSize) {
            noIntersectionStrings.push_back(v.at(i));
            v.erase(v.begin()+i);
        }
    }
    return v;
}

vector<string> SCSSFactory::removeSubstrings(vector<string> v) {
    for (vector<string>::size_type i=0; i < v.size(); ) {
        bool isErased = false;
        for (vector<string>::size_type j=i+1; j < v.size();) {
            size_t subsIdx = v.at(j).find(v.at(i));
            string str = v.at(j);
            // TODO : 왜안될까 시발..
//            str.insert(subsIdx, "[");
            str.insert(subsIdx + v.at(i).size(), "]");
            if (subsIdx != string::npos) {
//                cout << v.at(i) << "====>" << str << endl;
                v.erase(v.begin()+i);
                isErased = true;
                continue;
            } else j++;
        }
        if (!isErased) i++;
    }
    return v;
}

void SCSSFactory::showAll(vector<string> v) {
    cout << "INPUT STRINGS ====" << endl;
    for (vector<string>::size_type i=0; i < v.size(); i++) {
        cout << v.at(i) << endl;
    }
    
    cout << "INTERSECTION MATRIX ====" << endl;

    for (int i=0; i<MatrixSize; i++) {
        for (int j=0; j<MatrixSize; j++) {
            cout << setw(3) << intersectoinMatrix[i][j] << " ";
        }
        cout << endl;
    }
//
//    cout << "NO INTERSECTION STRINGS ====" << endl;
//    for (vector<string>::size_type i=0; i < noIntersectionStrings.size(); i++) {
//        cout << noIntersectionStrings.at(i) << endl;
//    }
    
    cout << "LONGEST COMMON SUBSTRING ====" << endl;
    cout << LongestCommonSuperString << endl;
}

bool SCSSFactory::isCircle(int v, int w) {
    superStringGraph.addEdge(v, w);
    if (superStringGraph.isCyclic()) {
        superStringGraph.removeEdge(v, w);
        return true;
    } else {
        superStringGraph.removeEdge(v, w);
        return false;
    }
}

bool SCSSFactory::contains(vector<int> includedIdx, int idx) {
    return (find(includedIdx.begin(), includedIdx.end(), idx) != includedIdx.end());
}

//SCSSFactory::SuperStringSets SCSSFactory::findFirstSet() {
//    for (vector<SuperStringSets>::size_type i=0; i < superstringSets.size(); i++) {
//        vector<SuperStringSets>::iterator it = find_if(superstringSets.begin(), superstringSets.end(), [](SuperStringSets const& s){
//            return find_if(superstringSets.begin(), superstringSets.end(), [set.leftSt](SuperStringSets const& s){
//                return s.rightStringIdx == idx;
//            });
//        });
//    }
//
//    return *it;
//}

bool SCSSFactory::existPreSet(int idx) {
    vector<SuperStringSets>::iterator it = find_if(superstringSets.begin(), superstringSets.end(), [idx](SuperStringSets const& s){
        return s.rightStringIdx == idx;
    });
    return it != superstringSets.end();
}

SCSSFactory::SuperStringSets SCSSFactory::findPreSet(int idx) {
    vector<SuperStringSets>::iterator it = find_if(superstringSets.begin(), superstringSets.end(), [idx](SuperStringSets const& s){
        return s.leftStringIdx == idx;
    });
    return *it;
}

SCSSFactory::SuperStringSets SCSSFactory::findNextSet(int idx) {
    vector<SuperStringSets>::iterator it = find_if(superstringSets.begin(), superstringSets.end(), [idx](SuperStringSets const& s){
        return s.leftStringIdx == idx;
    });
    return *it;
}

