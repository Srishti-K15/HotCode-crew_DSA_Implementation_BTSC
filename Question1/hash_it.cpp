#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>

using namespace std;

// Function to calculate the SHA-256 hash of a string
string hash(const string& message) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, message.c_str(), message.length());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setfill('0') << setw(2) << (int)hash[i];
    }
    return ss.str();
}

int main() {
    string message;

    // Get the message from the user
    cout << "Enter the message: ";
    getline(cin, message);

    // Finding Alice's hash
    string aliceHash = hash(message);
    cout << "Alice's hash: " << aliceHash << endl;

    // Finding Bob's hash
    string bobHash = hash(message);
    cout << "Bob's hash: " << bobHash << endl;

    if (aliceHash == bobHash) {
        cout << "Transmission not tempered" << endl;
    } else {
        cout << "Transmission Tempered" << endl;
    }

    return 0;
}