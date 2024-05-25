#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "WeatherForecast.h"
#include <functional>
#include <algorithm>
#include <numeric>
#include <set>

using Months::Month;

int main()
{
	typedef WeatherForecast WF;
	WF monday{ "Monday", 27, Month(05), 29.5, 0 };
	WF tuesday{ "Tuesday", 28, Month(05), 21, 0.2 };
	WF wednesday{ "Wednesday", 29, Month(05), 22, 0.3 };

	std::cout << std::boolalpha << (monday < tuesday) << std::endl // true
		<< wednesday.Compare(tuesday, [](const WF& WF1, const WF& WF2) { return WF1.Precipitations() < WF2.Precipitations(); }) << std::endl // false
		<< tuesday.Compare(monday, WF::CompareByTempreture()) << std::endl; // true

	std::vector<WF> forecasts;

	std::ifstream fin("Forecasts.txt");
	if (fin.good())
	{
		std::copy(std::istream_iterator<WF>(fin), std::istream_iterator<WF>(), std::back_inserter(forecasts));
	}
	else
	{
		abort();
	}
	fin.close();
	// sort
	std::sort(forecasts.begin(), forecasts.end());
	// print
	std::copy(forecasts.begin(), forecasts.end(), std::ostream_iterator<WF>(std::cout));
	double precipitationsInMay = 0;
	Month target = Month::May;
	// total precipitations in may (there is another, simplier way to do this using std::for_each, but I decided to try with std::accumulate)
	// also there is no need for std::bind, it can be replaced using captured list
	precipitationsInMay = std::accumulate(forecasts.begin(), forecasts.end(), 0.0, 
		std::bind([](double init, const WF& _WF, const Month& target) 
			{ return init + ((_WF.Month() == target) ? _WF.Precipitations() : 0); }, 
			std::placeholders::_1, std::placeholders::_2, target));
	std::cout << "Total precipitations in may: " << precipitationsInMay << std::endl;
	// days without precipitations in may 
	unsigned mayDaysWithoutPrecipitations = 0;
	std::for_each(forecasts.begin(), forecasts.end(), [target, &mayDaysWithoutPrecipitations](const WF& _WF) 
		{ if ((_WF.Month() == target) && (_WF.Precipitations() == 0)) ++mayDaysWithoutPrecipitations; });
	std::cout << "May days with no rain: " << mayDaysWithoutPrecipitations << std::endl;
	// vector with days without precipitations
	std::vector<WF> onlySunnyDays;
	std::copy_if(forecasts.begin(), forecasts.end(), std::back_inserter(onlySunnyDays), [](const WF& _WF)
		{ return _WF.Precipitations() == 0; });
	// sorting theese days using tempreture 
	std::sort(onlySunnyDays.begin(), onlySunnyDays.end(), WF::CompareByTempreture());
	// coldest and hottest day
	std::cout << "Coldest day:\n" << *(--onlySunnyDays.end());
	std::cout << "Hottest day:\n" << onlySunnyDays[0];
	// all tempreture parameters in mondays 
	// set - because we need unique values, comparator for set is WF::CompareByTempreture, to avoid days with the same tempreture
	std::set<WF, WF::CompareByTempreture> onlyMondays;
	std::string targetDay = "Monday";
	std::copy_if(forecasts.begin(), forecasts.end(), std::inserter(onlyMondays, onlyMondays.end()),
		[&targetDay](const WF& _WF) { return _WF.WeekDay() == targetDay; });
	std::cout << "Only mondays and only unique:\n";
	std::copy(onlyMondays.begin(), onlyMondays.end(), std::ostream_iterator<WF>(std::cout));

	return 0;
}