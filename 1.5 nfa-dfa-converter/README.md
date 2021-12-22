# NFA to DFA converter

## Example

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
NFA
---

State value: 0
-------------------
Symbol: a
Next state: 1
Symbol: #
Next state: 2

State value: 1
-------------------
Symbol: b
Next state: 1
Symbol: b
Next state: 3

State value: 2
-------------------
Symbol: #
Next state: 1
Symbol: a
Next state: 3

State value: 3
-------------------
Symbol: a
Next state: 2

DFA
---

State value: 0
-------------------
Symbol: a
Next state: 0
Symbol: b
Next state: 0

State value: 6
-------------------
Symbol: a
Next state: 8
Symbol: b
Next state: 10

State value: 7
-------------------
Symbol: a
Next state: 10
Symbol: b
Next state: 10

State value: 8
-------------------
Symbol: a
Next state: 6
Symbol: b
Next state: 0

State value: 10
-------------------
Symbol: a
Next state: 6
Symbol: b
Next state: 10
 ```