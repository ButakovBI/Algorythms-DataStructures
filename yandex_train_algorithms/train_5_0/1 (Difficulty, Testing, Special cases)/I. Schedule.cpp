#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    int year = 0;
    std::cin >> year;
    std::vector<std::string> day_names = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    std::vector<std::pair<std::string, int>> months = {
            {"January", 31},
            {"February", 28},
            {"March", 31},
            {"April", 30},
            {"May", 31},
            {"June", 30},
            {"July", 31},
            {"August", 31},
            {"September", 30},
            {"October", 31},
            {"November", 30},
            {"December", 31}
    };
    std::map<std::string, int> days = {
            {"Monday", 52},
            {"Tuesday", 52},
            {"Wednesday", 52},
            {"Thursday", 52},
            {"Friday", 52},
            {"Saturday", 52},
            {"Sunday", 52}
    };
    int totalDays = 365;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        totalDays = 366;
        months[1].second += 1;
    }
    std::vector<int> dates(n);
    for (int i = 0; i < n; ++i) {
        int day = 0;
        std::string month;
        std::cin >> day >> month;
        int sum_days = day;
        for (int j = 0; months[j].first != month; j += 1) {
            sum_days += months[j].second;
        }
        dates[i] = sum_days;
    }
    std::sort(dates.begin(), dates.end());
    std::string firstDayOfYear;
    std::cin >> firstDayOfYear;
    days[firstDayOfYear] += 1;

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days[day_names[(std::find(day_names.begin(), day_names.end(), firstDayOfYear)
        - day_names.begin() + 1) % 7]] += 1;
    }

    int pos_dates = 0;
    int currentDay = std::find(day_names.begin(), day_names.end(), firstDayOfYear)
                             - day_names.begin();
    for (int i = 1; i <= totalDays; ++i) {
        if (n != 0 && i == dates[pos_dates]) {
            pos_dates++;
            days[day_names[currentDay]]--;
        }
        currentDay = (currentDay + 1) % 7;
    }

    int maxDays = 0, minDays = totalDays;
    std::string bestDay, worstDay;

    for (const auto& day : days) {
//        std::cout << day.first << ' ' << day.second << '\n';
        if (day.second >= maxDays) {
            maxDays = day.second;
            bestDay = day.first;
        }
        if (day.second <= minDays) {
            minDays = day.second;
            worstDay = day.first;
        }
    }

    std::cout << bestDay << " " << worstDay << std::endl;

    return 0;
}
