# c-palindrome-cousin-pi

> The first challenge launched by [SigmaGeek](https://sigmageek.com/) worth the prize of **U$ 2,000** (two thousand dollars),<br/> 
Find large palindromic prime numbers in the decimal expansion of π (PI).

## Tools 1 ##

utility kit that processes data returns exact result.


### single thread ###

```
make single-run
```

#### multi thread ####

```
make multi-run
```

##### to stop #####

```
make multi-kill
```

## Tools 2 ##

a utility to explore palindrome independently.

### compile ###

```
docker run -v $(pwd):/app -w /app/tools2 -t ibmjava:8-sdk-alpine javac TierThree.java
```

### run ###

```
docker run -v $(pwd):/app -w /app/tools2 -t ibmjava:8-sdk-alpine java TierThree
```
