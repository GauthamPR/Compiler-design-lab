# First and Follow

## Example 1

#### Input (*input.txt*)
```
9
S=aBDh
B=cC
C=bC
C=ε
D=EF
E=g
E=ε
F=f
F=ε
```
#### Output (*stdout*)
```
First of S:
 a
First of B:
 c
First of C:
 b ε
First of D:
 ε g f
First of E:
 g ε
First of F:
 f ε
------------------------------

Follow of S:
 $
Follow of B:
 g f h
Follow of C:
 g f h
Follow of D:
 h
Follow of E:
 f h
Follow of F:
 h
------------------------------
 ```

## Example 2

#### Input (*input.txt*)
```
5
S=(L)
S=a
L=SE
E=,SE
E=ε
```
#### Output (*stdout*)
```
First of S:
 ( a
First of L:
 ( a ε
First of E:
 , ε
------------------------------

Follow of S:
 $ , )
Follow of L:
 )
Follow of E:
 )
------------------------------
 ```