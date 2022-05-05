The CONFIGURE module takes the number of users k, a locker id, and a key L as input and should generate k secondary keys (u1, u2, . . . , uk) and k distinct prime numbers
p1, p2, . . . , pk. 
Each secondary key should be a 4 digit number meant for each of those k users, and the primary key L is meant for the locker.

You may assume L < p1 × p2 ×. . .× pk( product of those k primes)
Further, the configuration module writes an entry to the file config.txt where the entry is of the form:

          Locker_id - k , p1 , p2, p3, ....., pk,   where each pi is a prime number.
          
And one can construct a unique L from the sequence(u1, u2, u3, .... , uk), with ui < pi for 1 <= i <= k.

The USE module is supposed to read the locker id and fetch the value of k and the pis from the configuration file config.txt to begin with. 
Further, it queries the users to feed in u1, u2, . . . , uk (order matters) as input. 

The task in hand is to generate L using p1, p2, . . . , pk so as to let the users access the shared locker.
