#ifndef DATE_H_
#define DATE_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <ctime>

using namespace std;

/**
 * Class Date:
 * This class will store the date we're working on
 */
class Date {

	int day;
	int month;
	int year;
	string weekday;
	static const string daysOfTheWeek[7];

public:

	/**
	 * This constructor store the current date!
	 */
    Date();
    /**
     * Copy constructor
     * @param date
     */
	Date(const Date& date);
	/**
	 * Constructor with 3 arguments (not really used in this project)
	 * @param day Day of the date
	 * @param month Month of the date
	 * @param year Year of the date
	 */
	Date(int day, int month, int year);
	~Date(){};

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	string getWeekday() const;
    /**
     * Date string
     * @return Returns a string of the date object (DD/MM/YYYY)
     */
	string getInfo() const;
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	void setDate(string &date);
	void setWeekday(string weekday);
	string getExtendedDate() const;
	/**
	 * Increases one day
	 * @param d The date of the input, and the output will that date increased by one day
	 */
    static void nextDate(Date &d);
    static int getCCode(int month, bool leap);
    static string calculateWeekday(int day, int month, int year);
    Date operator ++();
    /**
     * Increases one day
     * @return Increses one day of the date object itself
     */
	Date operator ++(int);
	Date operator --();
	Date operator --(int);
	Date operator + (int days) const;
	Date operator =(const Date& date);
	bool operator ==(const Date& date) const;
	bool operator < (const Date& date) const;
};


/**
 * Class Time:
 * This class will store the time we're working on
 */
class Time {
  
	int hour;
	int minute;

public:
    /**
	 * This constructor store the current time!
	 */
	Time();
	/**
	 * Copy constructor
	 * @param time
	 */
	Time(const Time& time);
	/**
	 * Constructor with 2 arguments
	 * @param hour Hours of the time object
	 * @param minute Minutes of the time object
	 */
	Time(int hour, int minute);
	~Time(){};
	/**
	 * This static function calculates the date and time when the order is ready to be picked up.
	 * @param date Inputs the date when then order was made and output the date when the order is ready to be picked up.
	 * @param time Inputs the time when then order was made and output the time when the order is ready to be picked up.
	 */
	static void pickUpTimeDate(Date& date, Time& time);
	int getHour() const;
	int getMinute() const;
    /**
     * Time string
     * @return Returns a string of the time object (HH:MM)
     */
	string getInfo() const;
	string getExtendedTime() const;
	void setHour(int hour);
	void setMinute(int minute);
	/**
	 * This operator increases 30 minutes to the object time
	 * @return The object time itself, increased
	 */
	Time operator ++();
    /**
     * This operator decreases 30 minutes to the object time
     * @return The object time itself, decreased
     */
	Time operator --();
	Time& operator =(const Time& time);
	bool operator ==(const Time& time) const;
	bool operator < (const Time& time) const;
};

/***************** EXCEPTIONS ****************/

/**
 * Exception of Invalid Date. The date that were inputed by the constructor of 3 arguments is invalid
 */
class InvalidDate {

	int day;
	int month;
	int year;

public:

	InvalidDate(int day, int month, int year);
	int getDay();
	int getMonth();
	int getYear();
};


/**
 * Exception of Invalid Time. The time that were inputed by the constructor of 2 arguments is invalid
 */
class InvalidTime {

	int hour;
	int minute;

public:

	InvalidTime(int hour, int minute);
	int getHour();
	int getMinute();
};


#endif /* DATE_H_ */