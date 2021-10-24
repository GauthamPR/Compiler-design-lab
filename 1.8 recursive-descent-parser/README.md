# Recursive Descent Parser
## Grammar
    E   ->  rE'
    E'  ->  +rE'| ε
## Examples
Input | Output
------|-------
r+r$ | Successfully parsed
chemistry | Unsuccessfully parsed
r+r+r$ | Parsed Successfully
