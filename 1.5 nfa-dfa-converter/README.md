# NFA to DFA converter
## Examples
### Example-1
#### Input
```
4
7
0 a 1
0 # 2
1 b 1
1 b 3
3 a 2
2 # 1
2 a 3
0
2
2
3
```
#### Output (*stdout*)
```
DFA
---

State value: 0
-------------------
Symbol: a
Next state: 0
Symbol: b
Next state: 0

State value: 6 (final)
-------------------
Symbol: a
Next state: 8
Symbol: b
Next state: 10

State value: 7 (final)
-------------------
Symbol: a
Next state: 10
Symbol: b
Next state: 10

State value: 8 (final)
-------------------
Symbol: a
Next state: 6
Symbol: b
Next state: 0

State value: 10 (final)
-------------------
Symbol: a
Next state: 6
Symbol: b
Next state: 10
 ```
### Example-2
#### Input
```
3
8
0 a 1
0 a 2
0 b 0
0 # 1
1 b 1
1 # 2
2 a 2
2 b 2
0
1
2
```
#### Output (*stdout*)
```
DFA
---

State value: 4 (final)
-------------------
Symbol: a
Next state: 4
Symbol: b
Next state: 4

State value: 6 (final)
-------------------
Symbol: a
Next state: 4
Symbol: b
Next state: 6

State value: 7 (final)
-------------------
Symbol: a
Next state: 6
Symbol: b
Next state: 7
 ```