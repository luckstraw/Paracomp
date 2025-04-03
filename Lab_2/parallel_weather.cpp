#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <fstream> // For file handling

#define NUM_DAYS 365 // Number of days in a year

int main() {
    int num_stations;

    // Prompt user for the number of weather stations
    std::cout << "Enter the number of weather stations: ";
    std::cin >> num_stations;

    // Create the temperature matrix dynamically based on user input
    std::vector<std::vector<double>> temperatures(num_stations, std::vector<double>(NUM_DAYS));

    // Fill the matrix with random values (0°C to 40°C)
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < num_stations; i++) {
        for (int j = 0; j < NUM_DAYS; j++) {
            temperatures[i][j] = (rand() % 4000) / 100.0; // Generate random values
        }
    }

    // Initialize variables for calculations
    std::vector<double> avg_temps(num_stations, 0.0);
    double hottest_avg = 0.0, coldest_avg = 40.0, highest_temp = 0.0;
    int highest_station = -1, num_threads_used = 0;

    double start_time = omp_get_wtime(); // Start timer

    // Get the number of threads used
    #pragma omp parallel
    {
        #pragma omp single
        num_threads_used = omp_get_num_threads();
    }

    // Calculate averages and track extreme temperatures
    #pragma omp parallel for
    for (int i = 0; i < num_stations; i++) {
        double sum = 0.0, local_highest_temp = 0.0;

        for (double temp : temperatures[i]) {
            sum += temp;
            if (temp > local_highest_temp) local_highest_temp = temp;
        }

        avg_temps[i] = sum / NUM_DAYS;

        #pragma omp critical
        {
            if (avg_temps[i] > hottest_avg) hottest_avg = avg_temps[i];
            if (avg_temps[i] < coldest_avg) coldest_avg = avg_temps[i];
            if (local_highest_temp > highest_temp) {
                highest_temp = local_highest_temp;
                highest_station = i;
            }
        }
    }

    double end_time = omp_get_wtime(); // End timer

    // Write results to a CSV file
    std::ofstream file("weather_analysis.csv", std::ios::app); // Open file in append mode
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write results in CSV format
    file << num_threads_used << "," << num_stations << "," << (end_time - start_time) << ","
         << hottest_avg << "," << coldest_avg << "," << highest_temp << "," << highest_station << "\n";

    file.close(); // Close the file

    std::cout << "\nResults have been written to weather_analysis.csv\n";

    return 0;
}
