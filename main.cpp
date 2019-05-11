#include <iostream>
#include <math.h>
#include <stdlib.h>
 
// Calculates the length of the number 
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
 
// Utility function to add the individual bits of a number
// and replace that position with the new number i.e the sum
void addBits(int Arr[], int i) {
  int sum = 0;
  while(Arr[i] != 0) {
    sum += Arr[i] % 10;
    Arr[i] /= 10;
  }
  Arr[i] = sum;
}
 
// Calculates the sum of the final array //
int findSum(int arr[], int n) {
  int sum = 0;
  for(int i = 0; i < n; ++i) sum += arr[i];
  return sum;
}
 
// Luhn Algorithm //
bool luhn(int Array[], int num, int n) { 
  for(int i = n - 2; i >= 0; i = i - 2) {
    // Double every second digit from right //
    Array[i] *= 2; 
    // If the product has more than two digits then add the individual digits
    // using addBits() function //
    if(numLen(Array[i] >= 2)) addBits(Array, i);  
  }
     
  // Find the sum of the final array //
  int modSum = findSum(Array, n);
  return (modSum % 10 == 0)? true : false;
 
}
 
// Finds the starting digit(s) of the CC //
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
  
  // To convert the command line args to unsigned long long //
  char* pend; 
  // Holds the credit card number to be verfied //
  unsigned long long number = std::strtoull(argv[1], &pend, 10);
  int noOfDigits = numLen(number);
  unsigned long long divisor = pow(10, (noOfDigits - 1));
   
  // Card Number Length Check //
  if(noOfDigits < 13 || noOfDigits > 16) {
    std::cout<<"\n Card Length Error! \n";
    exit(0);
  }
 
  // Gets the starting digits (1 or 2) from the number 
  // for the identification of the card //
  int digits = getStartDigits(number, divisor);
  int numArray[noOfDigits]  = {0};
      
  // Fill the array with each digit of the number //
  fillNumArray(numArray, number, noOfDigits);
 
  // Check whether the card is valid or not //
  bool isValid = luhn(numArray, number, noOfDigits);
 
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
