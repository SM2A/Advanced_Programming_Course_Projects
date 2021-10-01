#include <iostream>
#include <fstream>

#define ENCRYPT "encrypt"
#define DECRYPT "decrypt"
#define SIMPLE "simple"
#define COMPLICATED "complicated"
#define RAND_RANGE 11

using namespace std;

void read_input_file(string input_file_path, string &input_content);

void write_output_file(string output_file_path, string output_content);

void simple_encrypt(string input_content, string &output_content, string key);

void simple_decrypt(string input_content, string &output_content, string key);

void complicated_encrypt(string input_content, string &output_content, string key);

void complicated_decrypt(string input_content, string &output_content, string key);

int main() {

    string input_content, output_content;
    string mode, type, key, input_file_path, output_file_path;

    cin >> mode
        >> type
        >> key
        >> input_file_path
        >> output_file_path;

    read_input_file(input_file_path, input_content);

    if (mode == ENCRYPT) {
        if (type == SIMPLE) simple_encrypt(input_content, output_content, key);
        else if (type == COMPLICATED) complicated_encrypt(input_content, output_content, key);
    } else if (mode == DECRYPT) {
        if (type == SIMPLE) simple_decrypt(input_content, output_content, key);
        else if (type == COMPLICATED) complicated_decrypt(input_content, output_content, key);
    }

    write_output_file(output_file_path, output_content);

    return 0;
}

void read_input_file(string input_file_path, string &input_content) {

    ifstream input_file(input_file_path, ios::in);
    char ch = 0;
    while (input_file.get(ch)) input_content += ch;
    input_file.close();
}

void write_output_file(string output_file_path, string output_content) {

    ofstream output_file(output_file_path, ios::out);
    output_file << output_content;
    output_file.close();
}

void simple_encrypt(string input_content, string &output_content, string key) {

    int index = 0;

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        int encrypted = (int) input_content[i] + (int) key[index];
        index++;
        output_content += to_string(encrypted);
        output_content += '\n';
    }
}

void simple_decrypt(string input_content, string &output_content, string key) {

    int index = 0;
    string temp;

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        while (input_content[i] != '\n') {
            temp += input_content[i];
            i++;
        }
        char decrypted = (char) (stoi(temp) - (int) key[index]);
        index++;
        output_content += decrypted;
        temp.clear();
    }
}

void complicated_encrypt(string input_content, string &output_content, string key) {

    int index = 0;
    int srand_starting_point = 0;
    for (int i = 0; i < key.size(); i++) srand_starting_point += (int) key[i];
    srand(srand_starting_point);

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        int encrypted = (int) input_content[i] + (rand() % RAND_RANGE);
        index++;
        output_content += to_string(encrypted);
        output_content += '\n';
    }
}

void complicated_decrypt(string input_content, string &output_content, string key) {

    int index = 0;
    string temp;
    int srand_strarting_pint = 0;
    for (int i = 0; i < key.size(); i++) srand_strarting_pint += (int) key[i];
    srand(srand_strarting_pint);

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        while (input_content[i] != '\n') {
            temp += input_content[i];
            i++;
        }
        char decrypted = (char) (stoi(temp) - (rand() % RAND_RANGE));
        index++;
        output_content += decrypted;
        temp.clear();
    }
}