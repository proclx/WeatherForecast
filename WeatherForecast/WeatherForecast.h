#pragma once
#include <string>
#include <iostream>

namespace Months
{
    enum class Month
    {
        January = 1, February, March, April, May, June, July, August, September, October, November, December
    };

    std::ostream& operator<<(std::ostream& os, const Month& month);
}

class WeatherForecast
{
private:
	std::string           weekDay;
	unsigned           dayOfMonth;
    Months::Month           month;
    double          dayTempreture;
    double  amountOfPrecipitation;
public:
    WeatherForecast(const std::string& wD, unsigned dOM, const Months::Month& m, double dT, double aOP);
    WeatherForecast() = default;
    WeatherForecast(const WeatherForecast&) = default;
    ~WeatherForecast() = default;
    void Print(std::ostream& os) const;
    void Read(std::istream& is);

    class CompareByDate
    {
    public:
        bool operator()(const WeatherForecast& WF1, const WeatherForecast& WF2) const;
    };
    class CompareByTempreture
    {
    public:
        bool operator()(const WeatherForecast& WF1, const WeatherForecast& WF2) const;
    };

    template<typename Comp = CompareByDate>
    bool Compare(const WeatherForecast& WF, const Comp& cmp = Comp()) const
    {
        return cmp(*this, WF);
    }

    bool operator<(const WeatherForecast& WF) const;
    const std::string& WeekDay() const;
    unsigned DayOfMonth() const;
    const Months::Month& Month() const;
    double Tempreture() const;
    double Precipitations() const;
    double& Tempreture();
    double& Precipitations();
};

std::ostream& operator<<(std::ostream& os, const WeatherForecast& WF);
std::istream& operator>>(std::istream& is, WeatherForecast& WF);
