/*

XOR decryption
Problem 59

Each character on a computer is assigned a unique code and the preferred
standard is ASCII (American Standard Code for Information Interchange). For
example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII,
then XOR each byte with a given value, taken from a secret key. The advantage
with the XOR function is that using the same encryption key on the cipher text,
restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text
message, and the key is made up of random bytes. The user would keep the
encrypted message and the encryption key in different locations, and without
both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method
is to use a password as a key. If the password is shorter than the message,
which is likely, the key is repeated cyclically throughout the message. The
balance for this method is using a sufficiently long password key for security,
but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case
characters. Using cipher.txt (right click and 'Save Link/Target As...'), a file
containing the encrypted ASCII codes, and the knowledge that the plain text must
contain common English words, decrypt the message and find the sum of the ASCII
values in the original text.


Solution:

107359

*/


#include <stdlib.h>
#include <stdio.h>

int maxLowerCase = 0;
int maxLowerKey[3] = {0};

void copy(char a[], char b[], int len) {
    int i;
    for (i = 0; i < len; i++) {
        b[i] = a[i];
    }
}

void reset(char a[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        a[i] = 0;
    }
}

void print(char decrypted[], int textLen, char key[]) {
    int i = 0;
    for (i = 0; i < textLen; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");
}

void analize(char decrypted[], int textLen, char key[]) {
    int i;
    int lower = 0;

    for (i = 0; i < textLen; i++) {
        if (decrypted[i] >= 97 && decrypted[i] <= 122) {
            lower++;
        }
    }

    if (lower > maxLowerCase) {
        maxLowerCase = lower;
        for (i = 0; i < 3; i++) {
            maxLowerKey[i] = key[i];
        }
    }
}

int readFile(char fileContent[]) {
    FILE *fp;

    fp = fopen("p059_cipher.txt", "r");

    if (!fp) {
        printf("Can't open file p059_cipher.txt!");
        return 0;
    }

    if (!fgets(fileContent, 4000, fp)) {
        printf("Can't read file p059_cipher.txt!");
        return 0;
    }

    fclose(fp);

    return 1;
}

int readContent(char file[], char text[]) {
    int i;
    int n = 0;

    for (i = 0; file[i] != 0; i++) {
        if (file[i] == ',') {
            n++;
        } else {
            if (file[i] < 48 || file[i] > 57) {
                break;
            }
            text[n] = text[n] * 10 + (file[i] - 48);
        }
    }
    return n + 1;
}

void decrypt(char decrypted[], int strLen, char key[], int keyLength) {
    int i;
    int j = 0;
    for (i = 0; i < strLen; i++) {
        decrypted[i] ^= key[j];
        j++;
        if (j >= keyLength) {
            j = 0;
        }
    }
}

int calcASCIISum(char decrypted[], int strLen) {
    int i;
    int sum = 0;
    for (i = 0; i < strLen; i++) {
        sum += decrypted[i];
    }
    return sum;
}

int main() {
    int i, j, k;
    char fileContent[4000] = {0};
    char text[4000] = {0};
    char decrypted[4000] = {0};
    char key[3] = {0};
    int textLen;

    if (readFile(fileContent) == 0) {
        printf("Can't open file!");
        return (EXIT_SUCCESS);
    }

    textLen = readContent(fileContent, text);

    for (i = 97; i <= 122; i++) {
        for (j = 97; j <= 122; j++) {
            for (k = 97; k <= 122; k++) {
                key[0] = i;
                key[1] = j;
                key[2] = k;
                reset(decrypted, textLen);
                copy(text, decrypted, textLen);
                decrypt(decrypted, textLen, key, 3);
                analize(decrypted, textLen, key);
            }
        }
    }

    // print decrypted text with most lowercase letters
    for (i = 0; i < 3; i++) {
        key[i] = maxLowerKey[i];
    }
    reset(decrypted, textLen);
    copy(text, decrypted, textLen);
    decrypt(decrypted, textLen, key, 3);

    printf("DECRYPTED TEXT:\n");
    print(decrypted, textLen, key);
    printf("\n");

    printf("KEY: \n");
    printf("%c%c%c\n", maxLowerKey[0], maxLowerKey[1], maxLowerKey[2]);

    printf("ASCII sum: %d\n", calcASCIISum(decrypted, textLen));

    return (EXIT_SUCCESS);
}