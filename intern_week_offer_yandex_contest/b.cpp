#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

void solution() {
    long long n = 0;
    std::cin >> n;
    
    long long all_sum = 0; 
    long long all_size = 0;    
    std::vector<long long> group_sums(n);    
    std::vector<long long> group_sizes(n);    
    std::vector<long long> medians(n);     
    std::vector<long long> max_elements(n); 
    std::vector<long long> min_elements(n);
    
    for (long long i = 0; i < n; i += 1) {
        long long group_size = 0;
        std::cin >> group_size;
        group_sizes[i] = group_size;
        std::vector<long long> cucumbers(group_size);
        long long group_sum = 0;
        
        for (long long j = 0; j < group_size; j += 1) {
            std::cin >> cucumbers[j];
            group_sum += cucumbers[j];
        }
        
        std::sort(cucumbers.begin(), cucumbers.end());
        long long median = cucumbers[group_size / 2];
        long long min_elem = cucumbers[0];
        long long max_elem = cucumbers.back();
        
        medians[i] = median;
        max_elements[i] = max_elem;
        min_elements[i] = min_elem;
        group_sums[i] = group_sum;
        all_sum += group_sum;
        all_size += group_size;
    }
    
    long long cnt_pots = 0;
    std::cin >> cnt_pots;
    
    std::vector<long long> pots_given(n);
    long long total_given = 0;
    
    for (long long i = 0; i < n; i++) {
        pots_given[i] = medians[i];
        total_given += medians[i];
    }
    
    if (total_given > cnt_pots) {
        long long excess = total_given - cnt_pots;

        std::vector<long long> indices(n);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&](long long a, long long b) {
            return group_sizes[a] < group_sizes[b];
        });
        
        for (long long i : indices) {
            while (pots_given[i] > min_elements[i] && excess > 0) {
                long long minus = std::min(excess, pots_given[i] - min_elements[i]);
                pots_given[i] -= minus;
                excess -= minus;
            }
        }

        for (long long i : indices) {
            if (excess == 0) break;
            if (pots_given[i] > 0) {
                excess -= pots_given[i];
                pots_given[i] = 0;
                
            }
        }
    } else {
        long long remaining_pots = cnt_pots - total_given;

        std::vector<long long> indices(n);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&](long long a, long long b) {
            return group_sizes[a] < group_sizes[b];
        });
        
        for (long long i : indices) {
            while (pots_given[i] < max_elements[i] && remaining_pots > 0) {
                long long increase_amount = std::min(remaining_pots, max_elements[i] - pots_given[i]);
                pots_given[i] += increase_amount;
                remaining_pots -= increase_amount; 
            }
        }
        
        long long min_size_index = std::min_element(group_sizes.begin(), group_sizes.end()) - group_sizes.begin();
        pots_given[min_size_index] += remaining_pots;
    }
    
    for (long long i = 0; i < n; i++) {
        std::cout << pots_given[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solution();
    return 0;
}
