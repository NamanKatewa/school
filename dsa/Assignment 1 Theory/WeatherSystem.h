#ifndef WEATHER_SYSTEM_H
#define WEATHER_SYSTEM_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>

const int WS_START_YEAR = 1950;
const int WS_END_YEAR = 2025;
const double WS_SENTINEL_VALUE = -999.0;

class WeatherSystem {
private:
    double** weatherData;
    int numYears;
    int numCities;
    int baseYear;
    std::vector<std::string> cities;
    std::map<std::string, int> cityIndexMap;

    int getYearIndex(int year) const;
    int getCityIndex(const std::string& city) const;

public:
    WeatherSystem(int startYear, int endYear, const std::vector<std::string>& cityList);

    ~WeatherSystem();

    void loadFromCSV(const std::string& filename);
    void insertData(int year, const std::string& city, double temperature, bool verbose = true);
    void deleteData(int year, const std::string& city);
    double retrieveData(int year, const std::string& city) const;

    void printRowMajor() const;
    void printColumnMajor() const;
    void generateSparsityReport() const;
    
};

#endif
