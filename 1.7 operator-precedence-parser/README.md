# Operator Precedence Parser
## Grammar
    E   ->  E+E|ExE|i
## Operator Precedence Table
|**i**|**+**|**x**|**$**
|-----|----|-----|-----
**i**||>|>|>
**+**|<|>|<|>
**x**|<|>|>|>
**$**|<|<|<|
## Example 1
#### Input (*stdin*)
```i+ixi$```
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