//
// Created by Hussein on 4/19/2024.
//
#include <ctime>
#include <cmath>
#include "Date.h"

using namespace std;

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
    stringDate = std::to_string(day)+"-"+std::to_string(month)+"-"+std::to_string(year);
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

short Date::numberOfDaysInMonth(short M, short Y) {     //return number of days in a given month and year
    if(M<1 || M>12)
        return 0;
    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    return (M==2) ? (isLeap(Y) ? 29: 28) : days[M-1];
}

Date Date::addDate(Date D, short daysToAdd) {   //add some days to a given date and return the new date
    daysToAdd+=D.day;
    while(1){
        if(daysToAdd< numberOfDaysInMonth(D.month,D.year))
            break;
        else
            daysToAdd-= numberOfDaysInMonth(D.month,D.year);

        D.month++;
        if(D.month>12){
            D.month = 1;
            D.year++;
        }
    }
    D.day=daysToAdd;
    return D;
}
void Date::operator= (const Date& obj){
    this->day = obj.day;
    this->month = obj.month;
    this->year = obj.year;
}
string Date::getDateString(){
    return stringDate;
}