#include <iostream>

#define NOT_FOUND "NOT_FOUND"

using namespace std;

typedef struct data hash_data;

struct data {
    int key_size;
    unsigned long int hash;
    string possible_characters;
};

unsigned long int generateHashPassword(string password);
hash_data get_data();
bool crack_password(hash_data data, string &password, int pass_len, string generated_password = "");

int main() {

    hash_data crack_data = get_data();
    string password;

    crack_password(crack_data, password, crack_data.key_size);

    cout << password << endl;

    return 0;
}

hash_data get_data() {

    hash_data input_data;

    cin >> input_data.key_size;
    cin >> input_data.possible_characters;
    cin >> input_data.hash;

    return input_data;
}

unsigned long int generateHashPassword(string password) {

    return hash<string>()(password);
}

bool crack_password(hash_data data, string &password, int pass_len, string generated_password) {

    if (pass_len == 0) {
        if (data.hash == generateHashPassword(generated_password)) {
            password = generated_password;
            return true;
        } else {
            password = NOT_FOUND;
            return false;
        }
    }

    for (int index = 0; index < (int) data.possible_characters.size(); index++) {
        string pass = generated_password + data.possible_characters[index];
        if (crack_password(data, password, pass_len - 1, pass)) return true;
    }
    return false;
}