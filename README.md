# c-palindrome-cousin-pi

> The first challenge launched by [SigmaGeek](https://sigmageek.com/) worth the prize of **U$ 2,000** (two thousand dollars),<br/> 
Find large palindromic prime numbers in the decimal expansion of π (PI).

### :pick: Challenge ###

 * **Tier 1** are 9 digits.
 * **Tier 2** are 21 digits.
 * **Tier 3** are many digits as possible.

 
### :toolbox: Features ###

 * CI/CD
 * Unit Tests
 * C library itself
 * CPU Multi-threading
 * Task queue control

### :package: Pesources ####

 * Java 8
 * Assembly amd64 _(linux, macos)_
 * ANSI C _(without standards libs)_
 * Google Storage <https://storage.googleapis.com/pi100t/index.html>

### ####


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
