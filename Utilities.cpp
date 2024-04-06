#include "Utilities.h"
#include <cmath>

namespace Utilities{

    double StandardDeviation(int arr[], int size){

        double sum = 0;
        float mean = Mean(arr, size);

        for (int i = 0; i < size; i++){
            sum += pow( ( (float)arr[i] - mean ) , 2);
        }

        return sqrt(sum / (size-1));

    }

    float Mean(int arr[], int size){

        float sum = 0;

        for (int i = 0; i < size; i++){
            sum += (float) arr[i];
        }

        return sum/size;
    }

    int VectorAverage(vector<vector<int>> vec, int r){

        int avg = 0;

        for (int i = 0; i < vec.size(); i++){
            for (int j = 0; j < vec[i].size(); j++){
                avg += vec[i][j];
            }
        }

        return avg / r;
    }

}
