#include <iostream>
#include <vector>

using namespace std;
typedef vector<long> array;

long multiply(array &input, int current_index, int index = 0);
array new_array(array &input, int index = 0);
void print_array(array input);
array get_input();

int main() {

    array main_array = get_input();
    new_array(main_array);
    print_array(main_array);

    return 0;
}

array get_input() {

    array input_array;
    long input_num;

    while (cin >> input_num)
        input_array.push_back(input_num);

    return input_array;
}

long multiply(array &input, int current_index, int index) {

    if (current_index == index) index++;
    if (index == input.size()) return 1;

    return input[index] * multiply(input, current_index, index + 1);
}

array new_array(array &input, int index) {

    if (index == input.size()) return input;
    long temp = multiply(input, index);
    new_array(input, index + 1);
    input[index] = temp;
    return input;
}

void print_array(array input) {

    for (int index = 0; index < input.size(); ++index) {
        if (index == (input.size() - 1)) cout << input[index] << endl;
        else cout << input[index] << ' ';
    }
}