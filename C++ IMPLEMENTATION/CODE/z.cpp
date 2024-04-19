#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Fills Z array for given string str[]
void getZarr(const string& str, vector<int>& z) {
    int n = str.length();
    int l = 0, r = 0, k = 0;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && str[r - l] == str[r])
                r++;
            z[i] = r - l;
            r--;
        } else {
            k = i - l;
            if (z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while (r < n && str[r - l] == str[r])
                    r++;
                z[i] = r - l;
                r--;
            }
        }
    }
}

// Prints all occurrences of pattern in text using Z algorithm
void search(const string& text, const string& pattern) {
    string concat = pattern + "$" + text;
    int l = concat.length();
    vector<int> z(l, 0);
    getZarr(concat, z);
    for (int i = 0; i < l; ++i) {
        if (z[i] == pattern.length())
            cout << "Pattern found at index " << i - pattern.length() - 1 << endl;
    }
}

int main() {
    string file_path;
    cout << "Enter the path to the file containing both text and pattern: ";
    cin >> file_path;

    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "File not found. Please check the file path." << endl;
        return 1;
    }

    string text, pattern;
    getline(file, text); // Assuming the first line contains text
    getline(file, pattern); // Assuming the second line contains pattern

    search(text, pattern);

    return 0;
}
