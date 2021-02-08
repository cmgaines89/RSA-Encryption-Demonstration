/*
C. Gaines
Program demonstrating RSA encryption
*/

//Libraries
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

//Global Variables
int x, y, n, t, i, flag;
long int e[50], d[50], temp[50], j;
char en[50], m[50];
char msg[128];

//Function Prototypes
int prime(long int);
long int cd(long int);
int prime(long int);
void encryption_key();
void encrypt();
void decrypt();

int main()
{
	cout << "\nPlease enter a prime number: "; //Get first prime (private key)
	cin >> x;

	flag = prime(x); //First prime check

	while (flag == 0) //If user inputs invalid number or character, try again
	{
		cout << "\nInvalid input. Please try again: ";
		cin >> x;
	}

	cout << "\nPlease enter another prime number: "; //Get second prime (public key)
	cin >> y;

	flag = prime(y); //Second prime check

	while (flag == 0 || x == y) //If user inputs invalid number character or same number as first input, try again
	{
		cout << "\nInvalid input. Please try again: ";
		cin >> y;
	}

	cout << "\nEnter the message you would like to encrypt: \n"; //Takes 128 character message
	cin >> msg;

	for (i = 0; msg[i] != NULL; i++) //Fills msg array and m array with users desired message
		m[i] = msg[i];

	n = x * y; //multiplies primes together, where n is the modulus of the private and public key
	t = (x - 1) * (y - 1); //multiplies difference of users primes minus 1, getting totient fuction

	encryption_key(); //Generate encryption key for users message

	cout << "\nPossible values of e and d are:\n";

	for (i = 0; i < j - 1; i++)
		cout << "\n" << e[i] << "\t" << d[i];

	encrypt();
	decrypt();

	return 0;
} //End main

int prime(long int pr) //Function to determine if number is prime
{
	int i;
	j = sqrt(pr);

	for (i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return 0;
	}
	return 1;
}

void encryption_key() //Function to generate RSA encryption key
{
	int k;
	k = 0;

	for (i = 2; i < t; i++)
	{
		if (t % i == 0)
			continue;

		flag = prime(i); //Run prime check again

		if (flag == 1 && i != x && i != y)
		{
			e[k] = i;
			flag = cd(e[k]); //e is meant to be coprime to totient(n) and 1<e<totient(n); e is the public key exponent used for encryption

			if (flag > 0)
			{
				d[k] = flag;
				k++;
			}

			if (k == 99)
				break;
		}
	}
}

long int cd(long int a)
{
	long int k = 1;

	while (1)
	{
		k = k + t;
		if (k % a == 0)
			return(k / a);
	}
}

void encrypt() //Function to encrypt users message
{
	long int pt, ct, key = e[0], k, len; //pt represents plain text, ct represents cipher text
	i = 0;
	len = strlen(msg); //length of the message

	while (i != len)
	{
		pt = m[i]; //gets the plain text that's been stored in array m
		pt = pt - 96;
		k = 1;

		for (j = 0; j < key; j++) //takes plain text and encrypts it using RSA algorithm
		{
			k = k * pt;
			k = k % n;
		}

		temp[i] = k; //stores cipher text in temp array
		ct = k + 96;
		en[i] = ct; //moves cipher text to en array
		i++;
	}

	en[i] = -1;

	cout << "\n\nEncrypted Message: \n"; //prints out the encrypted message stored in array en
	for (i = 0; en[i] != -1; i++)
		cout << en[i];
}

void decrypt() //Function to decrypt users message
{
	long int pt, ct, key = d[0], k;
	i = 0;

	while (en[i] != -1)
	{
		ct = temp[i]; //gets the cipher text stored in the temp array
		k = 1;

		for (j = 0; j < key; j++)
		{
			k = k * ct; //decrypts the cipher text using RSA algorithm
			k = k % n;
		}
		pt = k + 96; //moves text plain text to m array
		m[i] = pt;
		i++;
	}
	m[i] = -1;

	cout << "\n\nDecrypted Message: \n"; //prints out the original message stored in array m
	for (i = 0; m[i] != -1; i++)
		cout << m[i];

	cout << endl;
}
