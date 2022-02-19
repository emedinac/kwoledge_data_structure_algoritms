#include <iostream>
#include <vector>
#include <cmath>

class Sorting {
  private:
    float running_time = 0;
  public:
    int by_insertion(std::vector<int> vector)
    {
        return 0;
    }
    int by_merge(std::vector<int> vector)
    {
        return 0;
    }
};

int main() {
    std::vector<int> reserve_sorted_vector;
    for( int i = 3; i <= std::pow(2,32); i++ )
        reserve_sorted_vector.push_back( i );

    Sorting sort;
    sort.by_insertion(reserve_sorted_vector);

    return 0;
}
