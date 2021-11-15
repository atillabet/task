#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int n = 5;

bool check(int arr[n][n], int n, int x_curent, int y_curent, int x_previous, int y_previous, int check_status, vector<vector<int>> pas) {
    if (check_status == 0) {
        if (n > 50 || n < 2) {
            throw out_of_range("Index out of range");
        }
        if (arr[0][0] != 1 || arr[n - 1][n - 1] != 1) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!(arr[i][j] == 0 || arr[i][j] == 1)) {
                    throw invalid_argument("wrong data");
                }
            }
        }
        pas.clear();
    }
    vector<vector<int>> passed;
    vector<int> temp;
    temp.push_back(x_curent);
    temp.push_back(y_curent);
    passed.push_back(temp);
    temp[0] = x_previous;
    temp[1] = y_previous;
    passed.push_back(temp);
    while (!(x_curent == n - 1 && y_curent == n - 1)) {
        int cur = 0;
        int avaible[3];
        if (x_curent + 1 != n && x_curent + 1 != x_previous && arr[y_curent][x_curent + 1] == 1) {
            avaible[cur] = 4;
            cur++;
        }
        if (x_curent - 1 >= 0 && x_curent - 1 != x_previous && arr[y_curent][x_curent - 1] == 1) {
            avaible[cur] = 2;
            cur++;
        }
        if (y_curent - 1 >= 0 && y_curent - 1 != y_previous && arr[y_curent - 1][x_curent] == 1) {
            avaible[cur] = 1;
            cur++;
        }
        if (y_curent + 1 != n && y_curent + 1 != y_previous && arr[y_curent + 1][x_curent] == 1) {
            avaible[cur] = 3;
            cur++;
        }

        if (cur == 0) {
            return false;
        }
        else if (cur == 1) {
            x_previous = x_curent;
            y_previous = y_curent;
            if (avaible[0] % 2 == 0) {
                x_curent += avaible[0] - 3;
            }
            else {
                y_curent += avaible[0] - 2;
            }
            temp[0] = x_curent;
            temp[1] = y_curent;
            if (find(passed.begin(), passed.end(), temp) != passed.end()) {
                return false;
            }
            passed.push_back(temp);
        }
        else if(cur > 1){
            temp[0] = x_curent;
            temp[1] = y_curent;
            if (find(pas.begin(), pas.end(), temp) != pas.end()) {
                return false;
            }
            pas.push_back(temp);
            for (int i = 0; i < cur; i++) {
                int tempx, tempy;
                tempx = x_curent;
                tempy = y_curent;
                if (avaible[i] % 2 == 0) {
                    tempx += avaible[i] - 3;
                }
                else {
                    tempy += avaible[i] - 2;
                }
                if (check(arr, n, tempx, tempy, x_curent, y_curent, 1, pas) == true) {
                    return true;
                }
            }
            return false;
        }
        else {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<vector<int>> arr;
    int temp1[n][n] = {1, 0, 1, 1, 1,
                      1, 0, 1, 0, 1,
                      1, 1, 1, 0, 1,
                      1, 0, 1, 0, 0,
                      1, 0, 1, 0, 1};
    vector<vector<int>> pas;
    try {
        cout << check(temp1, 1, 0, 0, 0, 0, 0, pas) << endl;
    }
    catch (out_of_range e){
        cout << e.what() << endl;
    }
    try {
        cout << check(temp1, 52, 0, 0, 0, 0, 0, pas) << endl;
    }
    catch (out_of_range e) {
        cout << e.what() << endl;
    }
    temp1[0][1] = 2;
    try {
        cout << check(temp1, 5, 0, 0, 0, 0, 0, pas) << endl;
    }
    catch (invalid_argument e) {
        cout << e.what() << endl;;
    }
    int temp2[n][n] = { 0, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1 };
    cout << check(temp2, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp3[n][n] = { 1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 1, 1, 1, 0};
    cout << check(temp3, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp4[n][n] = { 1, 0, 1, 1, 1,
                      1, 0, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 0, 0, 0, 0,
                      1, 1, 1, 1, 1 };
    cout << check(temp4, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp5[n][n] = { 1, 0, 1, 1, 1,
                      1, 0, 1, 1, 1,
                      1, 1, 1, 1, 1,
                      1, 0, 0, 0, 1,
                      1, 1, 1, 1, 1 };
    cout << check(temp5, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp6[n][n]={ 1, 0, 1, 1, 1,
                      1, 0, 1, 1, 1,
                      1, 0, 1, 1, 1,
                      0, 1, 0, 0, 0,
                      1, 1, 1, 1, 1 };
    cout << check(temp6, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp7[n][n]={ 1, 0, 0, 1, 1,
                      1, 0, 1, 0, 1,
                      1, 1, 1, 0, 1,
                      1, 0, 0, 0, 0,
                      1, 1, 1, 0, 1 };
    cout << check(temp7, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp8[n][n] = { 1, 1, 1, 0, 1,
                      1, 0, 1, 0, 1,
                      1, 1, 1, 0, 1,
                      0, 0, 0, 0, 0,
                      1, 1, 1, 0, 1 };
    cout << check(temp8, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp9[n][n] = { 1, 1, 1, 1, 1,
                        1, 0, 1, 0, 1,
                        1, 1, 1, 1, 1,
                        0, 0, 0, 0, 0,
                        1, 1, 1, 0, 1 };
    cout << check(temp9, 5, 0, 0, 0, 0, 0, pas) << endl;

    int temp10[n][n] = { 1, 1, 1, 1, 1,
                        1, 0, 1, 0, 1,
                        1, 1, 1, 1, 1,
                        1, 0, 1, 0, 1,
                        1, 1, 1, 1, 1 };
    cout << check(temp10, 5, 0, 0, 0, 0, 0, pas) << endl;
}