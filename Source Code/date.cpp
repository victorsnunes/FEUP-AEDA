#include "date.h"

const string Date::daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Calculating weekday
int Date::getCCode(int month, bool leap) {
	switch(month) {
	case 1: // January
		if (leap) {return 6;} else {return 0;}
		break;
	case 2: // February
		if (leap) {return 2;} else {return 3;}
		break;
	case 3: // March
		return 3;
		break;
	case 4: // April
		return 6;
		break;
	case 5: // May
		return 1;
		break;
	case 6: // June
		return 4;
		break;
	case 7: // July
		return 6;
		break;
	case 8: // August
		return 2;
		break;
	case 9: // September
		return 5;
		break;
	case 10: // October
		return 6;
		break;
	case 11: // November
		return 3;
		break;
	case 12: // December
		return 5;
		break;
	}
	return 0;
}

bool isLeap(int year) {
	if (year % 400 == 0) {
		return false;
	}
	else if (year % 4 == 0) {
		return true;
	}
	else
		return false;
}

string Date::calculateWeekday(int day, int month, int year) {
	int s = year / 100; // two first digits of the year
	int a = year % 100; // two last digits of the year
	int c = getCCode(month, isLeap(year));
	switch ((((5 * a) / 4) + c + day - (2 * (s % 4)) + 7) % 7) {
	case 0:
		return "Saturday";
		break;
	case 1:
		return "Sunday";
		break;
	case 2:
		return "Monday";
		break;
	case 3:
		return "Tuesday";
		break;
	case 4:
		return "Wednesday";
		break;
	case 5:
		return "Thursday";
		break;
	case 6:
		return "Friday";
		break;
	}
	return NULL;
}

bool validDate(int day, int month, int year) {
	if (month < 1 || month > 12) return false;
	if (year < 1900) return false;
	switch(month) {
		case 1: // January
			if (day < 0 || day > 31) return false;
			break;
		case 2: // February
			if (isLeap(year) && (day < 0 || day > 29)) return false;
			else if (!isLeap(year) && (day < 0 || day > 28)) return false;
			break;
		case 3: // March
			if (day < 0 || day > 31) return false;
			break;
		case 4: // April
			if (day < 0 || day > 30) return false;
			break;
		case 5: // May
			if (day < 0 || day > 31) return false;
			break;
		case 6: // June
			if (day < 0 || day > 30) return false;
			break;
		case 7: // July
			if (day < 0 || day > 31) return false;
			break;
		case 8: // August
			if (day < 0 || day > 31) return false;
			break;
		case 9: // September
			if (day < 0 || day > 30) return false;
			break;
		case 10: // October
			if (day < 0 || day > 31) return false;
			break;
		case 11: // November
			if (day < 0 || day > 30) return false;
			break;
		case 12: // December
			if (day < 0 || day > 31) return false;
			break;
		}
	return true;
}

Date::Date() {

    /* current date/time based on current system */
    time_t now = time(0);

    //We have to break this string information into pieces and store them correctly
    stringstream dateStringStream(ctime(&now));

    string tmp;
    string currentTime;

    dateStringStream >> tmp;

    if(tmp =="Sun")
        weekday = "Sunday";
    if(tmp =="Mon")
        weekday = "Monday";
    if(tmp =="Tue")
        weekday = "Tuesday";
    if(tmp =="Wed")
        weekday = "Wednesday";
    if(tmp =="Thu")
        weekday = "Thursday";
    if(tmp =="Fri")
        weekday = "Friday";
    if(tmp =="Sat")
        weekday = "Saturday";

    dateStringStream >> tmp;

    if(tmp =="Jan")
        month = 1;
    if(tmp =="Feb")
        month = 2;
    if(tmp =="Mar")
        month = 3;
    if(tmp =="Apr")
        month = 4;
    if(tmp =="May")
        month = 5;
    if(tmp =="June")
        month = 6;
    if(tmp =="July")
        month = 7;
    if(tmp =="Aug")
        month = 8;
    if(tmp =="Sept")
        month = 9;
    if(tmp =="Oct")
        month = 10;
    if(tmp =="Nov")
        month = 11;
    if(tmp =="Dec")
        month = 12;

    dateStringStream >> tmp;
    day = stoi(tmp);

    dateStringStream >> currentTime;

    dateStringStream >> tmp;
    year = stoi(tmp);

}

Date::Date(const Date& date) {
    this->setDay(date.getDay());
    this->setMonth(date.getMonth());
    this->setYear(date.getYear());
    this->setWeekday(date.getWeekday());
}

Date::Date(int day, int month, int year) {
    if(validDate(day, month, year)){
    this->day = day;
	this->month = month;
	this->year = year;
    this->weekday = calculateWeekday(day, month, year);
    }
    else{
        throw (InvalidDate(day, month, year));
    }
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

string Date::getWeekday() const {
    return weekday;
}

string Date::getInfo() const {
    stringstream ss;
	ss << day << "/" << month << "/" << year << " - " << weekday;
	return ss.str();
}

void Date::setDay(int day) {
    this->day = day;
}

void Date::setMonth(int month) {
    this->month = month;
}

void Date::setYear(int year) {
    this->year = year;
}

void Date::setDate(string &date) {
    string delimiter = " ";
	int data[3], counter = 0;
	size_t pos = 0;
	string token;
	while ((pos = date.find(delimiter)) != string::npos) {
		token = date.substr(0, pos);
		data[counter] = atoi(token.c_str());
		counter++;
		date.erase(0, pos + delimiter.length());
	}
	this->setDay(data[0]);
	this->setMonth(data[1]);
	this->setYear(data[2]);
}

void Date::setWeekday(string weekday) {
    this->weekday = weekday;
}

string Date::getExtendedDate() const {
    stringstream ss;
	string monthName[] = { "January", "February", "March",
		"April", "May", "June", "July",
		"August", "September", "October",
		"November", "December" };
	ss << this->day << " " << monthName[this->month - 1] << " " << this->year << " - " << this->weekday;
	return ss.str();
}

// calculating adjacent dates
void Date::nextDate(Date &d) {
	int day = d.getDay();
	int month = d.getMonth();
	int year = d.getYear();

	int i = 0;
	while (daysOfTheWeek[i] != d.getWeekday())
	    i++;
	i = (i + 1) % 7;
	d.setWeekday(daysOfTheWeek[i]);

	// Adding one day
	if (validDate(day + 1, month, year)) {
		d.setDay(day + 1);
		//d.setWeekday(calculateWeekday(d.getDay(), d.getMonth(), d.getYear()));
		return;
	}
	// Adding one month
	if (validDate(1, month + 1, year)) {
		d.setDay(1);
		d.setMonth(month + 1);
		//d.setWeekday(calculateWeekday(d.getDay(), d.getMonth(), d.getYear()));
		return;
	}
	// Adding one year
	if (validDate(1, 1, year + 1)) {
		d.setDay(1);
		d.setMonth(1);
		d.setYear(year + 1);
		//d.setWeekday(calculateWeekday(d.getDay(), d.getMonth(), d.getYear()));
		return;
	}
}

void previousDate(Date &d){
	int day = d.getDay();
	int month = d.getMonth();
	int year = d.getYear();

	// Minus one day
	if (validDate(day - 1, month, year)) {
		d.setDay(day - 1);
		return;
	}
	// minus one month
	if (validDate(31, month - 1, year)) {
		d.setDay(31);
		d.setMonth(month - 1);
		return;
	}
	else if (validDate(30, month - 1, year)) {
		d.setDay(30);
		d.setMonth(month - 1);
		return;
	}
	else if (validDate(29, month - 1, year)) {
		d.setDay(29);
		d.setMonth(month - 1);
		return;
	}
	else if (validDate(28, month - 1, year)) {
		d.setDay(28);
		d.setMonth(month - 1);
		return;
	}
	// Minus one year
	if (validDate(31, 12, year - 1)) {
		d.setDay(31);
		d.setMonth(12);
		d.setYear(year - 1);
		return;
	}
}

Date Date::operator++() {
    nextDate(*this);
	return *this;}

Date Date::operator++(int) {
    Date d = *this;
	nextDate(*this);
	return d;
}

Date Date::operator--() {
    previousDate(*this);
	return *this;
}

Date Date::operator--(int) {
    Date d = *this;
	previousDate(*this);
	return d;
}

Date Date::operator + (int days) const {
    Date d(*this);
    while (days--)
        d++;
    return d;
}

Date Date::operator=(const Date& date) {
    this->setDay(date.getDay());
	this->setMonth(date.getMonth());
	this->setYear(date.getYear());
	this->setWeekday(date.getWeekday());
	return *this;
}

bool Date::operator==(const Date& date) const {
    if (this->day == date.day && this->month == date.month && this->year == date.year)
		return true;
	else
		return false;
}

bool Date::operator<(const Date& date) const {
    // check year
	if (this->getYear() < date.getYear()) {
		return true;
	}
	else if (this->getYear() == date.getYear()) {
		// check month
		if (this->getMonth() < date.getMonth()) {
			return true;
		}
		else if (this->getMonth() == date.getMonth()) {
			// check day
			if (this->getDay() < date.getDay())
				return true;
		}
	}
	return false;
}
	  /*************************************************************/
	 /*************************   TIME   **************************/
	/*************************************************************/

Time::Time() {

        /* current date/time based on current system */
        time_t now = time(0);

        //We have to break this string information into pieces and store them correctly
        stringstream dateStringStream(ctime(&now));

        string tmp;
        string currentTime;

        dateStringStream >> tmp;
        dateStringStream >> tmp;
        dateStringStream >> tmp;

        dateStringStream >> currentTime;
        stringstream TimeSS(currentTime);

        getline(TimeSS, tmp, ':');
        hour = stoi(tmp);
        getline(TimeSS, tmp, ':');
        minute = stoi(tmp);

}

Time::Time(const Time& time) {

    this->hour = time.getHour();
    this->minute = time.getMinute();
}

Time::Time(int hour, int minute) {
    //Cheking if time is valid
	if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) throw (InvalidTime(hour, minute));
	else {
		this->hour = hour;
		this->minute = minute;
	}
}

void Time::pickUpTimeDate(Date& date, Time& time) {

    if (time < Time(19, 30)) {
        ++time;
    } else {
        int newMinute = time.getMinute() - 30;
        time = Time (7, newMinute);
        if (date.getWeekday() == "Friday")
            date = date + 3;
        else
            date++;
    }
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

string Time::getInfo() const {
    stringstream ss;
    if (hour < 10)
        ss << "0";
	ss << hour << ":";
    if (minute < 10)
        ss << "0";
    ss << minute;
	return ss.str();
}

string Time::getExtendedTime() const {
    stringstream ss;
	ss << this->hour << " hours and " << this->minute << " min";
	return ss.str();
}

void Time::setHour(int hour) {
    this->hour = hour;
}

void Time::setMinute(int minute) {
    this->minute = minute;
}

Time Time::operator++() {
    //adds 30min
    if(minute >= 30){
        this->hour++;
        this->minute = minute - 30;
    }
    else
        this->minute = minute + 30;

    return *this;
}

Time Time::operator--() {
    //subtracts 30min
    if(minute <= 30){
        this->hour--;
        this->minute = minute + 30;
    }
    else this->minute - 30;

	return *this;
}

Time& Time::operator =(const Time& time) {
    this->hour = time.getHour();
    this->minute = time.getMinute();
	return *this;
}

bool Time::operator==(const Time& time) const {
    if(this->hour == time.getHour() && this->minute == time.getMinute())
        return true;
    return false;
}

bool Time::operator<(const Time& time) const {
    if(this->hour < time.getHour()){
        return true;
    }
    if(this->hour == time.getHour() && this->minute < time.getMinute()){
        return true;
    }
    return false;
}

/***************** EXCEPTIONS ****************/

InvalidDate::InvalidDate(int day, int month, int year) {
    this->day = day;
	this->month = month;
	this->year = year;
}

int InvalidDate::getDay() {
    return this->day;
}

int InvalidDate::getMonth() {
    return this->month;
}

int InvalidDate::getYear() {
    return this->year;
}

InvalidTime::InvalidTime(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
}

int InvalidTime::getHour() {
    return this->hour;
}

int InvalidTime::getMinute() {
    return 0;
}
