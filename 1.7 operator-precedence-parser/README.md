# Operator Precedence Parser
## Grammar
    E   ->  E+E|ExE|i
## Operator Precedence Table
||**i**|**+**|**x**|**$**
|----|-----|----|-----|-----
**i**||>|>|>
**+**|<|>|<|>
**x**|<|>|>|>
**$**|<|<|<|
## Examples
### 1. Acceptance
#### Input (*stdin*)
```i+ixi```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i+ixi$          Shift
$<i             +ixi$           Reduce
$               +ixi$           Shift
$<+             ixi$            Shift
$<+<i           xi$             Reduce
$<+             xi$             Shift
$<+<x           i$              Shift
$<+<x<i         $               Reduce
$<+<x           $               Reduce
$<+             $               Reduce
$               $               String Accepted
```
### 2. Invalid symbol(*Rejection*)
#### Input (*stdin*)
```i=ixi```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i+i=i$          Shift
$<i             +i=i$           Reduce
$               +i=i$           Shift
$<+             i=i$            Shift
$<+<i           =i$             Symbol not found
```
### 3. Invalid grammar(*Rejection*)
#### Input (*stdin*)
```i+ii```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i+ii$           Shift
$<i             +ii$            Reduce
$               +ii$            Shift
$<+             ii$             Shift
$<+<i           i$              Rejected
```
