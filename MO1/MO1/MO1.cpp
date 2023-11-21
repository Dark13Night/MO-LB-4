#include <iostream>
#include <iomanip> 
#include <vector>
#include <map>
#include <limits>

using namespace std;

vector<double> normalizeWeigth(vector<double> weigths) {
    double sum = 0.0;
    for (double weight : weigths) {
        sum += weight;
    }

    vector<double> normalizedWeights(weigths.size());

    for (int i = 0; i < weigths.size(); i++) {
        normalizedWeights[i] = weigths[i] / sum;
    }

    return normalizedWeights;
}

double Max(vector<vector<double>>& A, int j) {
    double max = numeric_limits<double>::lowest();
    for (vector<double>& doubles : A) {
        if (doubles[j] > max) {
            max = doubles[j];
        }
    }
    return max;
}

double Min(vector<vector<double>>& A, int j) {
    double min = numeric_limits<double>::max();
    for (vector<double>& doubles : A) {
        if (doubles[j] < min) {
            min = doubles[j];
        }
    }
    return min;
}

string runChangeMethod(vector<vector<double>>& A, vector<double>& weigth, vector<double>& minimalValue, vector<string>& alternative) {
    vector<double> normalWeigth = normalizeWeigth(weigth);
    cout << "Normalized weights: ";
    for (double val : normalWeigth) {
        cout << val << " ";
    }
    cout << endl;
    int columns = A[0].size();

    int index = -1;
    for (int i = 0; i < minimalValue.size(); i++) {
        if (minimalValue[i] == 1) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return "";
    }

    vector<double> maxFound(columns);
    vector<double> minFound(columns);
    for (int j = 0; j < columns; j++) {
        maxFound[j] = Max(A, j);
        minFound[j] = Min(A, j);
    }

    cout << "Max and min:\n" << "Max: ";
    for (double val : maxFound) {
        cout << val << " ";
    }
    cout << "\nMin: ";
    for (double val : minFound) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Normalized matrix A:" << endl;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < columns; j++) {
            if (j != index && j < A[i].size()) {
                A[i][j] = (A[i][j] - minFound[j]) / (maxFound[j] - minFound[j]);
            }
        }
        for (double val : A[i]) {
            cout << setw(10) << val << " ";
        }
        cout << endl;
    }

    vector<int> indexes;
    for (int i = 0; i < A.size(); i++) {
        bool isMax = true;
        for (int j = 0; j < columns; j++) {
            if (j < A[i].size() && A[i][j] != maxFound[j] && A[i][j] >= maxFound[j] * minimalValue[j]) {
                isMax = false;
                break;
            }
        }
        if (isMax) {
            indexes.push_back(i);
        }
    }

    if (indexes.empty()) {
        return "";
    }

    map<int, double> value;
    for (int i : indexes) {
        double val = 0;
        bool hasZero = false;
        for (int j = 0; j < columns; j++) {
            if (j != index && j < A[i].size()) {
                if (A[i][j] == 0) {
                    hasZero = true;
                    break;
                }
                val += A[i][j] * normalWeigth[j];
            }
        }
        if (!hasZero) {
            value.insert(pair<int, double>(i, val));
        }
    }

    double maxVal = numeric_limits<double>::lowest();
    int maxIndex = -1;
    for (const pair<int, double>& entry : value) {
        if (entry.second > maxVal) {
            maxVal = entry.second;
            maxIndex = entry.first;
        }
    }

    if (maxIndex == -1) {
        return "";
    }

    return alternative[maxIndex];
}

int main() {
    vector<vector<double>> A = {
        {7, 5, 3, 7},
        {9, 8, 2, 8},
        {5, 6, 7, 7},
        {6, 3, 6, 5},
    };
    vector<double> w = { 6, 6, 4, 8 };
    vector<double> d = { 0.5, 0.4, 0.2, 1};
    vector <string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" };
    string result = runChangeMethod(A, w, d, alternative);
    cout << "Result: " << result;
    return 0;

}