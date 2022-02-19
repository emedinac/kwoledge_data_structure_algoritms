#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <numeric>

namespace clk = std::chrono;

class Sorting {
private:
    clk::steady_clock::time_point begin_t, end_t;
    void _merge(std::vector<int> &vector, int iBegin, int iMiddle, int iEnd,std::vector<int> original_vector){
        int i = iBegin;
        int j = iEnd;
        for (int k = iBegin; k < iEnd; k++) {
            if (i < iMiddle && (j >= iEnd || original_vector.at(i) <= original_vector.at(j))) {
                vector.at(k) = original_vector.at(k);
                i++;
            } else {
                vector.at(k) = original_vector.at(k);
                j++;
            }
        }
        return;
    }
    void _top_down_split_merge(std::vector<int> &vector, int iBegin, int iEnd, std::vector<int> original_vector){
        if (iEnd - iBegin <= 1)
            return;
        int iMiddle = (iEnd + iBegin) / 2;
        _top_down_split_merge(vector, iBegin, iMiddle, original_vector);
        _top_down_split_merge(vector, iMiddle, iEnd, original_vector);
        _merge(vector, iBegin, iMiddle, iEnd, original_vector);
    }
public:
    float time_measured;
    void compute_time(clk::steady_clock::time_point t1, clk::steady_clock::time_point t2){
        clk::duration<double> time_span = clk::duration_cast<clk::duration<double>>(t2 - t1);
        time_measured = time_span.count();
        //        std::cout<<"Time difference = "<<time_measured<<"[seg]"<<std::endl;
    }
    int by_insertion(std::vector<int> &vector)
    {
        begin_t = clk::steady_clock::now();
        int i = 0;
        int vec_len = vector.size();
        while (i<vec_len){
            int j = i;
            while(j>0 && vector.at(j-1)>vector.at(j)){
                std::swap(vector[j],vector[j-1]);
                j--;
            }
            i++;
        }
        end_t = clk::steady_clock::now();
        compute_time(begin_t,end_t);
        return 0;
    }

    int by_merge(std::vector<int> &vector)
    {
        begin_t = clk::steady_clock::now();
        std::vector<int> original_vector;
        int vec_len = vector.size();
        for (int i = 0; i < vec_len; i++){original_vector.push_back( vector.at(i) );}
        _top_down_split_merge(vector, 0, vector.size(), original_vector);
        end_t = clk::steady_clock::now();
        compute_time(begin_t,end_t);
        return 0;
    }
};

void generate_test(std::vector<int> &reserve_sorted_vector, int power_of_two_vector_lenght){
    for( int i = std::pow(2,power_of_two_vector_lenght); i >=0 ; i-- )
        reserve_sorted_vector.push_back( i );
}

int main() {
    std::vector<int> reserve_sorted_vector;
    std::vector<float> time1, time2;
    float average_time;
    Sorting sort;

    for(int vec_size=3; vec_size<16                                                                                                                                                                                                                         ; vec_size++){
        int vec_len = std::pow(2,vec_size);
        std::cout<<"\nPower 2**"<<vec_size<<" -> Using N elements:"<<vec_len<<std::endl;


        std::cout<<"by_insertion"<<std::endl;
        for(int n=0; n<25; n++){
            generate_test(reserve_sorted_vector, vec_size);
            sort.by_insertion(reserve_sorted_vector);
            time1.push_back(sort.time_measured);
            reserve_sorted_vector.clear();
        }
        average_time = std::accumulate(time1.begin(), time1.end(), 0.0) / time1.size();
        std::cout<<"Average time:"<<average_time<<" seg"<<std::endl;


        std::cout<<"by_merge"<<std::endl;
        for(int n=0; n<25; n++){
            generate_test(reserve_sorted_vector, vec_size);
            sort.by_merge(reserve_sorted_vector);
            time2.push_back(sort.time_measured);
            reserve_sorted_vector.clear();
        }
        average_time = std::accumulate(time2.begin(), time2.end(), 0.0) / time2.size();
        std::cout<<"Average time:"<<average_time<<" seg"<<std::endl;


        std::cout << std::endl;
        time1.clear();
        time2.clear();
    }
    return 0;
}
