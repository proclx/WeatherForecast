#include "WeatherForecast.h"

WeatherForecast::WeatherForecast(const std::string& wD, unsigned dOM, const Months::Month& m, double dT, double aOP)
	: weekDay(wD), dayOfMonth(dOM), month(m), dayTempreture(dT), amountOfPrecipitation(aOP)
{
}

void WeatherForecast::Print(std::ostream& os) const
{
	os << "Forecast for " << weekDay << ", " << dayOfMonth << " of " << month << ", tempreture will be " <<
		dayTempreture << " degrees, amount of precipitation expected to be " << amountOfPrecipitation << '\n';
}

void WeatherForecast::Read(std::istream& is)
{
	int _month;
	is >> weekDay >> dayOfMonth >> _month >> dayTempreture >> amountOfPrecipitation;
	month = Months::Month(_month);
}

bool WeatherForecast::operator<(const WeatherForecast& WF) const
{
    return Compare(WF);
}

const std::string& WeatherForecast::WeekDay() const
{
    return weekDay;
}

unsigned WeatherForecast::DayOfMonth() const
{
    return dayOfMonth;
}

const Months::Month& WeatherForecast::Month() const
{
    return month;
}

double WeatherForecast::Tempreture() const
{
    return dayTempreture;
}

double WeatherForecast::Precipitations() const
{
    return amountOfPrecipitation;
}

double& WeatherForecast::Tempreture()
{
    return dayTempreture;
}

double& WeatherForecast::Precipitations()
{
    return amountOfPrecipitation;
}

bool WeatherForecast::CompareByDate::operator()(const WeatherForecast& WF1, const WeatherForecast& WF2) const
{
	return (WF1.month == WF2.month) && (WF1.dayOfMonth < WF2.dayOfMonth) || (WF1.month < WF2.month);
}

std::ostream& Months::operator<<(std::ostream& os, const Month& month)
{
    switch (month) 
    {
    case Month::January: os << "January"; break;
    case Month::February: os << "February"; break;
    case Month::March: os << "March"; break;
    case Month::April: os << "April"; break;
    case Month::May: os << "May"; break;
    case Month::June: os << "June"; break;
    case Month::July: os << "July"; break;
    case Month::August: os << "August"; break;
    case Month::September: os << "September"; break;
    case Month::October: os << "October"; break;
    case Month::November: os << "November"; break;
    case Month::December: os << "December"; break;
    }
    return os;
}

bool WeatherForecast::CompareByTempreture::operator()(const WeatherForecast& WF1, const WeatherForecast& WF2) const
{
    return WF1.dayTempreture < WF2.dayTempreture;
}

std::ostream& operator<<(std::ostream& os, const WeatherForecast& WF)
{
    WF.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, WeatherForecast& WF)
{
    WF.Read(is);
    return is;
}