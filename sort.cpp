#include <iostream>
#include <vector>

using namespace std;

void gnome_sort(vector<int>& masive){

    for(int i = 1; i < masive.size(); ){

        if (i != 0 && masive[i] < masive[i-1]){
            int tmp = masive[i];
            masive[i] = masive[i-1];
            masive[i-1] = tmp;
            i--;
        }
        else
            i++;
    }
}

int main(){

    vector<int> masive = {9, 0, 11, 4, -5, 69, -666};

    gnome_sort(masive);

    for(int a : masive)
        cout << a << " ";
    cout << endl;

    return 0;
}

