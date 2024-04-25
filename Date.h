#ifndef LIBRARY_SYSTEM_PROJECT_DATE_H
#define LIBRARY_SYSTEM_PROJECT_DATE_H
#include <iostream>
class Date {
private:
    const short monthDays[12] = { 31, 59, 90, 120, 151, 181,
                                  212, 243, 273, 304, 334,365 }; //days from the beginning of the year until the month
    bool isLeap(short Year);
    short numOfLeaps(short Year) ;
    short numberOfDaysInMonth(short , short );
public:
    short day, month, year;
    std::string stringDate;
    Date();
    void getCurrentData();
    short getDifference(short D, short M, short Y);
    Date addDate(Date D, short daysToAdd);
    std::string getDateString();


    void operator= (const Date&);

};
#endif //LIBRARY_SYSTEM_PROJECT_DATE_H