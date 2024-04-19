//
// Created by salah elsayed on 4/19/2024.
//
#include <ctime>
#include <cmath>
#include "Date.h"

Date::Date() :day(0), month(0), year(0) {}    // constructor

bool Date::isLeap(short Year) {
    return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0)); // check if the year is leap or not
}

short Date::numOfLeaps(short Year) {   //count the number of leap years until a specific year
    short ans = 0;
    while (Year--)
        if (isLeap(Year))
            ans++;
    return ans;
}

void Date::getCurrentData() {               // get the current date
    time_t t = time(0);
    tm* now = localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}

short Date::getDifference(short D, short M, short Y) {     //calculate the difference between a given date and the current date
    int firstDateInDays = ((Y - 1) * 365);       // calculate number of days from 1/1/1 to the given date
    if (M > 1) {
        firstDateInDays += monthDays[M - 2];
    }
    firstDateInDays += D;
    firstDateInDays += numOfLeaps(Y - 1);
    if (isLeap(Y) && M > 2)
        firstDateInDays++;

    Date current;
    current.getCurrentData();
    int secondDateInDays = ((current.year - 1) * 365);    // calculate number of days from 1/1/1 to the current date
    if (current.month > 1) {
        secondDateInDays += monthDays[current.month - 2];
    }
    secondDateInDays += current.day;
    secondDateInDays += numOfLeaps(current.year - 1);
    if (isLeap(current.year) && current.month > 2)
        secondDateInDays++;
    return (abs(firstDateInDays - secondDateInDays)); // subtract them to get the difference
}