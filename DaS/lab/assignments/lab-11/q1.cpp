Task # 1
Suppose you are working on a program that needs to store a large number of strings, with the possibility of
duplicate strings. You decide to use chain hashing to efficiently store and retrieve the strings, but you want
to ensure that collisions are avoided as much as possible. Your hash function simply takes the sum of the
ASCII values of the characters in the string and returns the remainder after dividing by the number of
buckets. You decide to implement the hash table using a linked list for each bucket.
Input and output:
HashTable myhash;
[hine: key is A]
myhash.insert(&quot;A&quot;,&quot;aaaaa&quot;);
myhash.insert(&quot;B&quot;,&quot;bbbbb&quot;);
myhash.insert(&quot;C&quot;,&quot;ccccc&quot;);
myhash.insert(&quot;A&quot;,&quot;zzzzz&quot;);
