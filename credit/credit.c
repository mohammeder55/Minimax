#include <stdio.h>
#include <stdbool.h>

long get_long(char *string);
long exponent(int p);
int getDigit(long number, int n);
bool isValid(long n);
int length(long n);
int credit(long number);

char *letter(void)
{
    return "AA";
}

int main(void)
{
    int x = credit(371449635398431);
    printf("%i\n", x);
}

int credit(long number)
{
    // Some info about the number
    int len = length(number);
    int last2Digits = getDigit(number, len) * 10 + getDigit(number, len - 1);

    // If the number is valid according to the algorithm
    if (isValid(number))
    {
        if ( len==15 && (last2Digits==34 || last2Digits==37) )
        {
            return 0;
        }
        else if ( len==16 && last2Digits>50 && last2Digits<56 )
        {
            return 1;
        }
        else if ( (len==16||len==13) && getDigit(number, len)==4 )
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

    return 4;
}

long get_long(char *string)
{
    long out;
    printf("%s", string);
    scanf("%ld", &out);
    return out;
}

int length(long n)
{
    int i=1;
    while (true)
    {
        if(n < exponent(i))
        {
            return i;
        }
        i++;
    }
}

// cheking if it validates the algorithm
bool isValid(long n) 
{
    int sum=0;
    int toBeDoubled;
    // taking both sums
    for (int i=0; i<8; i++)
    {
        sum+=getDigit(n, 2*i+1);
        toBeDoubled=2*getDigit(n, 2*i+2);
        if (toBeDoubled>9)
        {
            sum += getDigit(toBeDoubled, 1)+getDigit(toBeDoubled, 2);
        }
        else
        {
            sum += toBeDoubled;
        }
    }

    int con = sum % 10;

    // cheking the condition
    if (con == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// gets the nth digit of a long
int getDigit(long number, int n)
{
    return (number%exponent(n) - number%exponent(n-1)) / exponent(n-1);
}

// Returns 10^p
long exponent(int p)
{
    long result=1;
    for (int i=0; i<p; i++)
    {
        result *=10;
    }
    return result;
}