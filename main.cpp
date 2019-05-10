#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <sstream>

int numLen(unsigned long long n) {
  int count = 0;
  while (n != 0) {
    count++;
    n = n / 10;
  }
  return count;
}

// Iterates through the number digit by digit and inserts at end
// in numarray //
void fillNumArray(int nArr[], unsigned long long num, int n) {
  int index = n; 
  while(num != 0) {
    nArr[--index] = num % 10;
    num /= 10;
  }
}

void addBits(int Arr[], int number, int i) {
  int sum = 0;
  while(number != 0) {
    sum += number % 10;
    number /= 10;
  }
  Arr[i] = sum;
}

int findSum(int arr[], int n) {
  int sum = 0;
  for(int i = 0; i < n; ++i) sum += arr[i];
  return sum;
}

bool luhn(int lArray[], int Array[], int num, int n) {
  lArray[n] = {0};
  for(int i = n - 2; i >= 0; i = i - 2) {
    lArray[i] = Array[i] * 2;
    if(numLen(lArray[i] >= 2)) addBits(lArray, lArray[i], i);
  }
  
  for(int i = 0; i < n; ++i) {
    if(lArray[i] == 0) lArray[i] = Array[i];
  }
  
  int modSum = findSum(lArray, n);
  return (modSum % 10 == 0)? true : false;

}

int getStartDigits(unsigned long long num, unsigned long long div) {
  int digits;
  digits = num / div;
  if(digits == 3) {
    div = pow(10, ((numLen(num)) - 2));
    digits = num / div;
  }
  return digits; 
}

int main(int argc, char** argv) {
  
  char* pend;
  // Holds the credit card number to be verfied //
  //unsigned long long number = 79927398713; //379927398713 //
  unsigned long long number = std::strtoull(argv[1], &pend, 10);
  int noOfDigits = numLen(number);
  unsigned long long divisor = pow(10, (noOfDigits - 1));
  
  // Card Number Length Check //
  if(noOfDigits < 10 || noOfDigits > 16) {
    std::cout<<"\n Card Length Error! \n";
    exit(0);
  }

  // Gets the starting digits (1 or 2) from the number 
  // for the identification of the card //
  int digits = getStartDigits(number, divisor);
  int numArray[noOfDigits]  = {0};
  int luhnArray[noOfDigits] = {0};
 
  //std::cout << digits;
  // Fill the array with each digit of the number //
  fillNumArray(numArray, number, noOfDigits);

  // Check whether the card is valid or not //
  bool isValid = luhn(luhnArray, numArray, number, noOfDigits);

  if(isValid) {
    if(digits == 4)
      std::cout << "\n Your Visa card is valid!";
    else if(digits == 5)
      std::cout << "\n Your MasterCard card is valid!";
    else if(digits == 37)
      std::cout << "\n Your American Express card is valid!";
    else if(digits == 6)
      std::cout << "\n Your Discover card is valid!";
    else std::cout << "\n Card is valid but not recognized!";
  } else std::cout << "\n You're a fraud!";

  return 0;

}
