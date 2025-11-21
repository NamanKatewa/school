#include "WeatherSystem.h"
#include "colors.h"
#include <algorithm>

WeatherSystem::WeatherSystem(int startYear, int endYear, const std::vector<std::string>& cityList)
    : baseYear(startYear), cities(cityList) {
    
    numYears = endYear - startYear + 1;
    numCities = cities.size();

    for (int i = 0; i < numCities; ++i) {
        cityIndexMap[cities[i]] = i;
    }

    weatherData = new double*[numYears];
    for (int i = 0; i < numYears; ++i) {
        weatherData[i] = new double[numCities];
        // Initialize with sentinel value
        for (int j = 0; j < numCities; ++j) {
            weatherData[i][j] = WS_SENTINEL_VALUE;
        }
    }
}

WeatherSystem::~WeatherSystem() {
    for (int i = 0; i < numYears; ++i) {
        delete[] weatherData[i];
    }
    delete[] weatherData;
}

int WeatherSystem::getYearIndex(int year) const {
    if (year < baseYear || year >= baseYear + numYears) {
        return -1;
    }
    return year - baseYear;
}

int WeatherSystem::getCityIndex(const std::string& city) const {
    auto it = cityIndexMap.find(city);
    if (it == cityIndexMap.end()) {
        return -1;
    }
    return it->second;
}

void WeatherSystem::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << Color::BOLD << Color::RED << "Error: Could not open file " << filename << Color::RESET << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string yearStr, city, tempStr;

        std::getline(ss, yearStr, ',');
        std::getline(ss, city, ',');
        std::getline(ss, tempStr, ',');

        try {
            int year = std::stoi(yearStr);
            double temperature = std::stod(tempStr);
            insertData(year, city, temperature, false);
        } catch (const std::invalid_argument& e) {
            std::cerr << Color::BOLD << Color::RED << "Warning: Invalid data format in CSV line: " << line << Color::RESET << std::endl;
        }
    }
    file.close();
    std::cout << Color::BOLD << Color::GREEN << "Data loaded successfully from " << filename << Color::RESET << std::endl;
}

void WeatherSystem::insertData(int year, const std::string& city, double temperature, bool verbose) {
    int yearIdx = getYearIndex(year);
    int cityIdx = getCityIndex(city);

    if (yearIdx != -1 && cityIdx != -1) {
        weatherData[yearIdx][cityIdx] = temperature;
        if (verbose) {
            std::cout << Color::BOLD << Color::GREEN << "Data inserted for Year " << year << ", City " << city << "." << Color::RESET << std::endl;
        }
    } else {
        if (verbose) {
            std::cerr << Color::BOLD << Color::RED << "Warning: Could not insert data for Year " << year << ", City " << city << ". Invalid year or city." << Color::RESET << std::endl;
        }
    }
}

void WeatherSystem::deleteData(int year, const std::string& city) {
    int yearIdx = getYearIndex(year);
    int cityIdx = getCityIndex(city);

    if (yearIdx != -1 && cityIdx != -1) {
        weatherData[yearIdx][cityIdx] = WS_SENTINEL_VALUE;
        std::cout << Color::BOLD << Color::GREEN << "Data for Year " << year << ", City " << city << " deleted." << Color::RESET << std::endl;
    } else {
        std::cerr << Color::BOLD << Color::RED << "Warning: Could not delete data for Year " << year << ", City " << city << ". Invalid year or city." << Color::RESET << std::endl;
    }
}

double WeatherSystem::retrieveData(int year, const std::string& city) const {
    int yearIdx = getYearIndex(year);
    int cityIdx = getCityIndex(city);

    if (yearIdx != -1 && cityIdx != -1) {
        return weatherData[yearIdx][cityIdx];
    } else {
        std::cerr << "Warning: Could not retrieve data for Year " << year << ", City " << city << ". Invalid year or city." << std::endl;
        return WS_SENTINEL_VALUE;
    }
}



void WeatherSystem::printRowMajor() const {
    const int columnWidth = 20;
    const int cityChunkSize = 10;
    int numCityChunks = (numCities + cityChunkSize - 1) / cityChunkSize;

    for (int chunk = 0; chunk < numCityChunks; ++chunk) {
        int startCity = chunk * cityChunkSize;
        int endCity = std::min(startCity + cityChunkSize, numCities);

        std::cout << "\n" << Color::BOLD << Color::YELLOW << "--- Row-Major Traversal (Cities " << startCity + 1 << " to " << endCity << ") ---" << Color::RESET << "\n";
        
        // Header
        std::cout << Color::BOLD << Color::CYAN;
        std::cout << std::left << std::setw(columnWidth) << "Year/City";
        for (int j = startCity; j < endCity; ++j) {
            std::cout << std::left << std::setw(columnWidth) << cities[j];
        }
        std::cout << Color::RESET << "\n";

        // Data
        for (int i = 0; i < numYears; ++i) {
            std::cout << std::left << std::setw(columnWidth) << (baseYear + i);
            for (int j = startCity; j < endCity; ++j) {
                if (weatherData[i][j] != WS_SENTINEL_VALUE) {
                    std::cout << Color::GREEN << std::left << std::fixed << std::setprecision(2) << std::setw(columnWidth) << weatherData[i][j] << Color::RESET;
                } else {
                    std::cout << Color::RED << std::left << std::setw(columnWidth) << "N/A" << Color::RESET;
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void WeatherSystem::printColumnMajor() const {
    const int columnWidth = 20;
    const int yearChunkSize = 10;
    int numYearChunks = (numYears + yearChunkSize - 1) / yearChunkSize;

    for (int chunk = 0; chunk < numYearChunks; ++chunk) {
        int startYear = chunk * yearChunkSize;
        int endYear = std::min(startYear + yearChunkSize, numYears);

        std::cout << "\n" << Color::BOLD << Color::YELLOW << "--- Column-Major Traversal (Years " << (baseYear + startYear) << " to " << (baseYear + endYear - 1) << ") ---" << Color::RESET << "\n";

        // Header
        std::cout << Color::BOLD << Color::CYAN;
        std::cout << std::left << std::setw(columnWidth) << "City/Year";
        for (int i = startYear; i < endYear; ++i) {
            std::cout << std::left << std::setw(columnWidth) << (baseYear + i);
        }
        std::cout << Color::RESET << "\n";

        // Data
        for (int j = 0; j < numCities; ++j) {
            std::cout << std::left << std::setw(columnWidth) << cities[j];
            for (int i = startYear; i < endYear; ++i) {
                if (weatherData[i][j] != WS_SENTINEL_VALUE) {
                    std::cout << Color::GREEN << std::left << std::fixed << std::setprecision(2) << std::setw(columnWidth) << weatherData[i][j] << Color::RESET;
                } else {
                    std::cout << Color::RED << std::left << std::setw(columnWidth) << "N/A" << Color::RESET;
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void WeatherSystem::generateSparsityReport() const {
    int filledCells = 0;
    int totalCells = numYears * numCities;

    for (int i = 0; i < numYears; ++i) {
        for (int j = 0; j < numCities; ++j) {
            if (weatherData[i][j] != WS_SENTINEL_VALUE) {
                filledCells++;
            }
        }
    }

    int emptyCells = totalCells - filledCells;
    double sparsityPercentage = (static_cast<double>(emptyCells) / totalCells) * 100.0;

    std::cout << "\n" << Color::BOLD << Color::YELLOW << "--- Sparsity Report ---" << Color::RESET << "\n";
    std::cout << Color::CYAN << "Total Cells: " << Color::RESET << totalCells << std::endl;
    std::cout << Color::GREEN << "Filled Cells: " << Color::RESET << filledCells << std::endl;
    std::cout << Color::RED << "Empty Cells (Sentinel Value): " << Color::RESET << emptyCells << std::endl;
    std::cout << Color::MAGENTA << "Sparsity: " << Color::RESET << std::fixed << std::setprecision(2) << sparsityPercentage << "% empty" << std::endl;
    std::cout << "\n";
}
