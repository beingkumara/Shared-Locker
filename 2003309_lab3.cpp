#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ios>

using namespace std;
// The extended Euclidean algorithm uses the result calculated by the recursive call gcd (b% a, a) to update the result of gcd (a, b).
int gcd_find(int first, int second, long long int *x, long long int *y)
{
    if (first == 0)
    {
        *x = 0;
        *y = 1;
        return second;
    }

    long long int x1, y1;
    int gcd_final = gcd_find(second % first, first, &x1, &y1);

    *x = y1 - (second / first) * x1;
    *y = x1;

    return gcd_final;
}
// checkprime -> checks if the number is a prime or a composite
bool checkprime(unsigned long long int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
// primeprod -> calculates the product of the primes, which is fursther used to check if the product of the primes is greater than the locker number.
unsigned long long int primeprod(vector<unsigned long long int> primes)
{
    unsigned long long int prod = 1;
    for (int i = 0; i < primes.size(); i++)
    {
        prod *= primes[i];
    }
    return prod;
}
// getprimes-> calculates the 'siz' number of primes, and when are multipled should give a valu greater than L
vector<unsigned long long int> getprimes(int siz, long long int L)
{
    vector<unsigned long long int> primes;
    int num1 = 2;
    int num2 = (int)pow((float)L, 0.5);

    while (primes.size() != siz - 1)
    {
        if (checkprime(num1) == true)
        {
            primes.push_back(num1);
        }
        num1++;
    }

    if (primeprod(primes) * num2 <= L)
    {
        num2 = L / 2 + 1;
    }

    while (primes.size() != siz)
    {
        if (checkprime(num2))
        {
            primes.push_back(num2);
        }
        num2++;
    }

    return primes;
}

// after_div -> used to calculate the values we end up with after we divide the product of primes with individual primes.
vector<unsigned long long int> after_div(vector<unsigned long long int> primes)
{
    unsigned long long int primes_product = primeprod(primes);
    vector<unsigned long long int> store;
    for (int i = 0; i < primes.size(); i++)
    {
        store.push_back(primes_product / primes[i]);
    }
    cout << endl;
    return store;
}
// c_values -> calculates the coefficients of the gcd equation, ma+nb(say), c_values calculates a and b ( just an example)
vector<long long int> c_values(vector<unsigned long long int> X)
{
    int siz = X.size();
    vector<long long int> c_vals(siz);
    int gcd = gcd_find(X[0], X[1], &c_vals[0], &c_vals[1]);
    for (int i = 2; i < siz; i++)
    {
        long long int coefficient = 1;
        gcd = gcd_find(gcd, X[i], &coefficient, &c_vals[i]);
        for (int j = 0; j < i; j++)
        {
            c_vals[j] *= coefficient;
        }
    }

    return c_vals;
}
/*
CONFIGURE ->
calculates the user keys
writes to a file: locker_id
and adds it to the database
the  write the primes to the file
*/
vector<unsigned long long int> CONFIGURE(string locker_id, int k, long long int L)
{
    vector<unsigned long long int> secondary_keys;
    vector<unsigned long long int> primes = getprimes(k, L);
    for (unsigned long long int num : primes)
        secondary_keys.push_back(L % num);
    ofstream file;
    file.open("configure.txt", ios::app);
    file << locker_id << " "
         << "VALID"
         << " " << k;
    for (unsigned long long int prime : primes)
    {
        file << " " << prime;
    }
    file << endl;
    file.close();
    return secondary_keys;
}

/*
USE ->
Computes the locker number
*/
int USE(string locker_id, vector<unsigned long long int> sec_keys, vector<unsigned long long int> prime)
{
    long long int L = 0;
    vector<unsigned long long int> keep = after_div(prime);
    vector<long long int> c_vals = c_values(keep);
    int k = prime.size();
    for (int i = 0; i < k; i++)
    {
        L += keep[i] * c_vals[i] * sec_keys[i];
        L = L % (long long int)primeprod(prime);
    }

    while (L < 0)
    {
        if (L < 0)
        {
            L = L + primeprod(prime);
        }
        else
        {
            L = L;
        }
    }

    return L;
}
/*
deletelock -> if the delete option is selected , the lock is made invalid
*/
void deletelock(string locker)
{
    ifstream copy("configure.txt");
    string info, line;
    string id;
    while (getline(copy, line))
    {
        istringstream stre(line);
        stre >> id;
        if (id == locker)
        {
            auto pos = line.find("VALID");
            line.replace(pos, 5, "INVALID");
        }
        info += line;
        info += "\n";
    }
    copy.close();

    ofstream file;
    file.open("configure.txt");
    for (char charac : info)
    {
        file << charac;
    }
    file.close();
    cout << "\nSuccessfully deleted";
    return;
}
/*
searchlock ->
reads the data from the file
and if the 'ids' is matched with the id in the file, and if it is valid then
the primes in the same line(in the text file) are stored and returned.
*/
vector<unsigned long long int> searchlock(string ids)
{
    int p;
    ifstream copy;
    string id, line;
    string validity;
    copy.open("configure.txt");
    while (getline(copy, line))
    {
        istringstream stre(line);
        stre >> id >> validity;
        if (id == ids && validity == "VALID")
        {
            stre >> p;
            vector<unsigned long long int> primes(p);
            for (int i = 0; i < p; i++)
            {
                stre >> primes[i];
            }
            cout << endl;
            return primes;
        }
    }
    return {};
}

int main()
{
    int module;
    string locker_id;
    int k;
    long long int L;
    int ifexit = 0;
    while (ifexit != 1)
    {
        cout << "1. Configure : " << endl;
        cout << "2. Use: " << endl;
        cout << "3. Exit: " << endl;
        cin >> module;
        int pick;
        if (module == 1)
        {

            cout << "1. ADD :" << endl;
            cout << "2. Delete: " << endl;
            cout << "3. Return: " << endl;
            cin >> pick;
            if (pick == 1)
            {
                cout << "\nPlease enter the locker id: ";
                cin >> locker_id;
                vector<unsigned long long int> primes = searchlock(locker_id);
                if (primes.size() == 0)
                {
                    cout << "\nPlease enter the number of users: ";
                    cin >> k;
                    cout << "\nEnter the Locker key: ";
                    cin >> L;
                    vector<unsigned long long int> secondary_keys = CONFIGURE(locker_id, k, L);
                    cout << "\nSecondary Keys :\n";
                    for (int i = 0; i < k; i++)
                    {
                        cout << "u" << i + 1 << " = " << setfill('0') << setw(4) << secondary_keys[i] << endl;
                    }
                }
                else
                {
                    cout << "\nLocker_Id confirmed";
                }
            }
            else if (pick == 2)
            {
                cout << "\nPlease enter the Locker id to delete it ";
                cin >> locker_id;
                vector<unsigned long long int> primes = searchlock(locker_id);
                if (primes.size() == 0)
                {
                    cout << "\nID NOT FOUND";
                }
                else
                {
                    deletelock(locker_id);
                }
            }
            else if (pick == 3)
            {
                ifexit = 0;
            }
            else
            {
                ifexit = 1;
            }
        }
        else if (module == 2)
        {
            cout << "\nPleade enter the locker id";
            cin >> locker_id;
            vector<unsigned long long int> primes = searchlock(locker_id);
            if (primes.size())
            {
                cout << "\nPlease enter the number of users: ";
                cin >> k;
                cout << "\nEnter the secondary keys: ";
                vector<unsigned long long int> secondary_keys(k);
                for (int i = 0; i < k; i++)
                {
                    cin >> secondary_keys[i];
                }
                L = USE(locker_id, secondary_keys, primes);
                cout << "\nAccesscode= " << L << endl;
            }
            else
            {
                cout << "\nLocker ID not found";
            }
        }
        else
        {
            ifexit = 1;
        }
    }
    cout << "\nThank you!";

    return 0;
}