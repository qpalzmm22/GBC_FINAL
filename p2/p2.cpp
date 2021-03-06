/* ## 구간합
 *  
 * 보안이는 구간합 또한 사랑한다. 
 *
 *
 */

// (1 ~ n -1) : test case time 


#include <stdio.h>
#include <vector>

using namespace std;


vector<long long> prefix_Sum(vector<int> arr, int num_query, vector <pair <int, int> > query){
        int arr_size = arr.size();
        vector<long long> sum(arr_size);
        vector<long long> result;


        for(int i = 0; i < num_query; i++){
                int low = query[i].first;
                int high = query[i].second;
                long long subSum = 0;

                for(int j = low; j <= high; j++){
                        subSum += arr[j];
                }

                result.push_back(subSum);
                
        }
        return result;
}
