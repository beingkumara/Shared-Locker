The CONFIGURE module takes the number of users k, a locker id, and a key L as input and should generate k secondary keys (u1, u2, . . . , uk) and k distinct prime numbers :  p1, p2, . . . , pk. 

Each secondary key should be a 4 digit number meant for each of those k users, and the primary key L is meant for the locker.

And L < p1 × p2 ×. . .× pk( product of those k primes)

Further, the configuration module writes an entry to the file config.txt where the entry is of the form:

          Locker_id - k , p1 , p2, p3, ....., pk,   where each pi is a prime number.
          
And one can construct a unique L from the sequence(u1, u2, u3, .... , uk), with ui < pi for 1 <= i <= k.

The USE module is supposed to read the locker id and fetch the value of k and the pis from the configuration file config.txt to begin with. 

Further, it queries the users to feed in u1, u2, . . . , uk (order matters) as input. 

The task in hand is to generate L using p1, p2, . . . , pk so as to let the users access the shared locker.


Menu to be displayed to the user:

1. CONFIGURE

2. USE

3. EXIT

 The user mentions the preference ( 1 or 2 or 3)
 
 If the user clicks:
 
 1 - > A new lockerID is entered:
 
Enter a LockerID
 
Enter the number of users
 
Enter a 10 digit Locker Key L
 
 2 - > A locker is deleted:
 
 Enter the Locker ID: 
 
 Output: Entry successfully deleted  /  Invalid Entry
 
 3 - > The program is terminated
