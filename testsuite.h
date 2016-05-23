#ifndef TESTSUITE_H
#define TESTSUITE_H

#include<iostream>
#include<ctime>

static clock_t start_time;
static clock_t end_time;

#define TIME_STARTS() \
    start_time = clock();
#define TIME_UP() \
    end_time = clock();\
    std::cout << "TIME USED: ";\
    std::cout << (double)(end_time-start_time)/CLOCKS_PER_SEC*1000;\
    std::cout << " ms" << std::endl;

#define ASSERT(x) \
    std::cout << "ASSERTION: " << "["#x << "]" ; \
    if(x)\
    {\
        std::cout << " SUCCESS!" << std::endl;\
    }\
    else\
    {\
        std::cout << " FAIL![*****]" << std::endl;\
    }
    
#define ASSERT_EQUAL(a,b) \
    std::cout << "ASSERTION: " << "["#a<<" =="<<" "#b<<"]";\
    if((a)==(b))\
    {\
        std::cout << " SUCCESS!" << std::endl;\
    }\
    else\
    {\
        std::cout << " FAIL![*****]" << std::endl;\
    }
    
#endif // TESTSUITE_H
