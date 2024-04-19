//
// Created by salah elsayed on 4/19/2024.
//

#ifndef LIBRARY_SYSTEM_PROJECT_DATE_H
#define LIBRARY_SYSTEM_PROJECT_DATE_H
class Date {
private:
    const short monthDays[12] = { 31, 59, 90, 120, 151, 181,
                                  212, 243, 273, 304, 334,365 }; //days from the beginning of the year until the month
    bool isLeap(short Year);
    short numOfLeaps(short Year) ;
public:
    short day, month, year;
    Date();
    void getCurrentData();
    short getDifference(short D, short M, short Y);
};
#endif //LIBRARY_SYSTEM_PROJECT_DATE_H
