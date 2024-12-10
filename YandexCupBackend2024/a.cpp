#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::unordered_map<long long, long double> patients;
    long double sum_temperatures = 0.0;
    long long patient_count = 0;
    std::string command = "";
    
    while (std::cin >> command) {
        if (command == "+") {
            long long id = 0;
            long double temp = 0.0;
            std::cin >> id >> temp;
            if (temp < -10.0 || temp > 42.5) {
                continue;
            }
            if (patients.find(id) == patients.end()) {
                patients[id] = temp;
                sum_temperatures += temp;
                patient_count += 1;
            }
        } else if (command == "~") {
            long long id = 0;
            long double temp = 0.0;
            std::cin >> id >> temp;
            if (temp < -10.0 || temp > 42.5) {
                continue;
            }
            if (patients.find(id) != patients.end()) {
                sum_temperatures -= patients[id];
                patients[id] = temp;
                sum_temperatures += temp;
            }
        } else if (command == "-") {
            long long id = 0;
            std::cin >> id;
            if (patients.find(id) != patients.end()) {
                sum_temperatures -= patients[id];
                patients.erase(id);
                patient_count -= 1;
            }
        } else if (command == "?") {
            if (patient_count > 0) {
                std::cout << std::fixed << std::setprecision(9) << (sum_temperatures / patient_count) << std::endl;
            } else {
                std::cout << std::fixed << std::setprecision(9) << 0.0 << std::endl;
            }
        } else if (command == "!") {
            break;
        }
    }

    return 0;
}
