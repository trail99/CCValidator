#include <iostream>

int numLen(int n) {
  int count = 0;
  while (n != 0) {
    n = n / 10;
    count++;
  }
  return count+1;
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

int main() {

  // Holds the credit card number to be verfied //
  unsigned long long number = 79927398713;

  int noOfDigits = numLen(number);
  int numArray[noOfDigits];
  int luhnArray[noOfDigits] = {0};
  fillNumArray(numArray, number, noOfDigits);

  bool isValid = luhn(luhnArray, numArray, number, noOfDigits);
  if(isValid) std::cout<<"\n Credit Card is Valid";
  else std::cout<<"\n You're a fraud!";

  return 0;

}
