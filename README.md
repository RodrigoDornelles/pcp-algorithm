# c-palindrome-cousin-pi

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
