//
//  main.cpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 11/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include <thread>
#include <chrono>
#include "Commons.h"
#include "fileStreamUtils.hpp"
#include "SCSSFactory.hpp"

template <typename Duration, typename Function>
void timer(Duration const & d, Function const & f)
{
    thread([d,f](){
        this_thread::sleep_for(d);
        f();
        
    }).join();
}

void hello() { cout << "Hello!\n"; }

int main(int argc, const char * argv[]) {
    fileStreamUtils* fileStream = new fileStreamUtils();
    if(fileStream->openInputStream("input.txt") == -1) {
        cout << "파일을 열 수가 없습니다. " << endl;
    }
    
    SCSSFactory sf = SCSSFactory(fileStream->getInputs());

    cout << "Launched\n";
    timer(chrono::seconds(TIME_LIMIT), &hello);
    
    return 0;
}

