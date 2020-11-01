//  =======================================================
//  File:       cpp_vgnr.cpp
//  Author:     Rodion "R.Beat" Grinberg (https://rbeat.gq)
//  Date:       1/11/2020 (Final Commit)
//  Desc:       Vigenère Cipher File Encryptor/Decryptor
//  =======================================================

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

FILE * f1;
FILE * f2;
char fname[100];
char key[15];
char c;
int cur = 0;
int fileSelect();
int encrypt();
int decrypt();
int menu();

int fileSelect(int choice) {
  // Common function to get filename and key
  cout << "\n\n File name (Up to 100 characters): ";
  scanf("%s", fname);
  f1 = fopen(fname, "r");
  if (f1 == NULL) {
    // if file cannot be openned (its stream is NULL), then file does not exist.
    cout << "\nError: File not found or its filename is larger than 100 characters." << endl;
    return 0;
  }
  cout << " Key (Up to 15 characters): ";
  // Limit for key is set according to exam requirements.
  scanf("%s", key);

  // Checking choice option from GUI Menu.
  if (choice == 1) {
    decrypt();
  } 
  else {
    encrypt();
  }
  cout << "\nOutput file: output.txt" << endl;
  return 0;
}

int encrypt() {
  string result = "";
  cout << "\n========" << endl;
  cout << "Encrypting..." << endl;
  cout << "\nWas:" << endl;
  f2 = fopen("output.txt", "w");
  while (!feof(f1)) {
    if (fread( & c, 1, 1, f1)) {
      cout << c; // Showing initial character on display ["BEFORE" SHOWCASE]
      if (c >= 33 && c <= 126) {
        /*  All special characters + A~Z, a~z, 0~9
         *  ASCII Table available at https://jbwyatt.com/ascii.html
         */
        if ((c + key[cur] - 33) <= 126) {
          /* Current character from key is being subtracted
           * from current character in file. (In bits from ASCII Table) 
           * Then, a starter character bit (in this case - "!") is being added
           * to compensate the boundaries. If the final result is within 
           * boundaries - then it's good-to-go.
           */
          c = c + key[cur] - 33;
        } 
        else {

          /* If not, the final boundarie character ("~") is being added 
           * in order to compensate the boundaries.
           */
          c = key[cur] + c - 127;

        }

        fprintf(f2, "%c", c);

        // Checking "key" cursor and resetting it if "key" has ended.
        if (cur < strlen(key) - 1) {
          ++cur;
        } 
        else {
          cur = 0;
        }
      }

      if (c == 32) {
        /* "Space" ASCII code is 32
         *
         * I am not encrypting/decrypting spaces, therefore 
         * it does not need any special actions.  
         */
        fprintf(f2, "%c", c);

        // Checking "key" cursor and resetting it if "key" has ended.
        if (cur < strlen(key) - 1) {
          ++cur;
        } 
        else {
          cur = 0;
        }
      }

      result += c; // Saving character for result display ["AFTER" SHOWCASE]
    }
  }

  fclose(f1);
  fclose(f2);
  cout << "\n\n\nDone!" << endl;
  cout << "\nResult: \n" << result << endl;
  cout << "\n========" << endl;
  return 0;
}

int decrypt() {
  string result = "";
  cout << "\n========" << endl;
  cout << "Decrypting..." << endl;
  cout << "\nWas:" << endl;
  f2 = fopen("output.txt", "w");
  cur = 0;
  while (!feof(f1)) {
    if (fread( & c, 1, 1, f1)) {
      cout << c; // Showing initial character on display ["BEFORE" SHOWCASE]
      if (c >= 33 && c <= 126) {
        /*  All special characters + A~Z, a~z, 0~9
         *  ASCII Table available at https://jbwyatt.com/ascii.html
         */
        if ((c - key[cur] + 33) >= 33) {
          /* Current character from key is being subtracted
           * from current character in file. (In bits from ASCII Table) 
           * Then, a starter character bit (in this case - "!") is being added
           * to compensate the boundaries. If the final result is within 
           * boundaries - then it's good-to-go.
           */
          c = c - key[cur] + 33;
        } 
        else {
          /* If not, the final boundarie character ("~") is being added 
           * in order to compensate the boundaries.
           */
          c = c - key[cur] + 127;
        }
        fprintf(f2, "%c", c);

        // Checking "key" cursor and resetting it if "key" has ended.
        if (cur < strlen(key) - 1) {
          ++cur;
        } 
        else {
          cur = 0;
        }
      }
      if (c == 32) {
        /*
         * "Space" ASCII code is 32
         *
         * I am not encrypting/decrypting spaces, therefore 
         * it does not need any special actions.  
         */
        fprintf(f2, "%c", c);

        // Checking "key" cursor and resetting it if "key" has ended.
        if (cur < strlen(key) - 1) {
          ++cur;
        } 
        else {
          cur = 0;
        }

      }
      result += c; // Saving character for result display ["AFTER" SHOWCASE]
    }
  }

  fclose(f1);
  fclose(f2);
  cout << "\n\n\nDone!" << endl;
  cout << "\nResult: \n" << result << endl;
  cout << "========" << endl;
  return 0;

}

int menu() {
  // Logo
  cout << " _       _____   _        ____ \n/ \\ |\\  /  __/  / \\  /|  /  __\n| | //  | |  _  | |\\ ||  |  \\/|\n| \\//   | |_//  | | \\||  |    /\n\\__/    \\____\\  \\_/  \\|  \\_/\\_\nVGNR (Vigenère) Cipher Encryptor/Decryptor\n(c)2020 R.Beat (https://rbeat.gq)" << endl;
  char selection;

  // GUI Menu
  cout << "\n Menu";
  cout << "\n========";
  cout << "\n E - Encrypt";
  cout << "\n D - Decrypt";
  cout << "\n X - Exit";
  cout << "\n\n Enter selection: ";
  cin >> selection;

  // Switch for selecting needed menu option.
  switch (selection) {
  case 'E':
  case 'e': {
    fileSelect(2);
  }
  break;

  case 'D':
  case 'd': {
    fileSelect(1);
  }
  break;

  case 'X':
  case 'x': {
    cout << "\n Bye~";
  }
  break;

  default:
    cout << "\n Invalid selection";
  }
  cout << "\n";
  return 0;
}

int main() {
  // Calling GUI
  menu();
  return 0;
}
