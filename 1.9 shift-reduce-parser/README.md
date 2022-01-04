# Shift Reduce Parser
## Grammar
    S   ->  S+S
    S   ->  SxS
    S   ->  i
## Examples
### 1. Acceptance
#### Input (*stdin*)
```i+ixi```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i+ixi$          Shift
$i              +ixi$           Reduce S->i
$S              +ixi$           Shift
$S+             ixi$            Shift
$S+i            xi$             Reduce S->i
$S+S            xi$             Reduce S->S+S
$S              xi$             Shift
$Sx             i$              Shift
$Sxi            $               Reduce S->i
$SxS            $               Reduce S->SxS
$S              $               String Accepted
```
### 2. Invalid symbol(*Rejection*)
#### Input (*stdin*)
```i=ixi```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i=ixi$          Shift
$i              =ixi$           Reduce S->i
$S              =ixi$           Shift
$S=             ixi$            Shift
$S=i            xi$             Reduce S->i
$S=S            xi$             Shift
$S=Sx           i$              Shift
$S=Sxi          $               Reduce S->i
$S=SxS          $               Reduce S->SxS
$S=S            $               Unaccepted
```
### 3. Invalid grammar(*Rejection*)
#### Input (*stdin*)
```i+ii```
#### Output (*stdout*)
```
Stack           Input           Operation
-----------------------------------------
$               i+ii$           Shift
$i              +ii$            Reduce S->i
$S              +ii$            Shift
$S+             ii$             Shift
$S+i            i$              Reduce S->i
$S+S            i$              Reduce S->S+S
$S              i$              Shift
$Si             $               Reduce S->i
$SS             $               Unaccepted
```
