#include <iostream>
#include <cmath>

using namespace std;

string encrypt(string input);
string reverse(string input, int start_point);
void swap(string &input, int index);
string get_input();

int main() {

    string main_str = get_input();
    cout << encrypt(main_str) << endl;

    return 0;
}

string get_input() {

    string input;
    getline(cin, input);
    return input;
}

string encrypt(string input) {

    if (input.size() == 1) return input;

    int split_point = floor(input.size() / 2);

    string one = input.substr(0, split_point);
    string two = input.substr(split_point, input.size() - 1);

    string one_rev = reverse(one, 0);
    string two_rev = reverse(two, 0);

    return encrypt(two_rev) + encrypt(one_rev);
}

string reverse(string input, int start_point) {

    if (input.size() == 1) return input;
    if (start_point == floor(input.size() / 2)) return input;

    swap(input, start_point);

    return reverse(input, start_point + 1);
}

void swap(string &input, int index) {

    char temp = input[(input.size() - 1) - index];
    input[(input.size() - 1) - index] = input[index];
    input[index] = temp;
}