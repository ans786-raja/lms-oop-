#ifndef PREMIUM_STUDENT_H
#define PREMIUM_STUDENT_H
#define implements public  
//Applied LSP
#include "student.h"
class PremiumStudent : implements Student {
private:
    int maxBooks = 5;  // Premium students can borrow up to 5 books

public:
    PremiumStudent(const string& name) : Student() {}
    void BorrowBook();
    

};

#endif 
