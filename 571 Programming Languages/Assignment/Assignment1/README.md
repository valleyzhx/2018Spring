# Syntax:
Prog    -> main(){Stmts}
// ?? Prog    -> main(){Stmts} EOL??
Stmts   -> E | Stmt; Stmts
//TODO: hard point, and should include a empty statment | ;
Stmt    -> float Id | Id = E | print Id | {Stmts}
E       -> Float | Id | E - E | E * E| (-Float)
Float   -> digit+ . digit+

# design
leave syntax check to flex .l file

# TODO:
- catch main function token??
- error report, left it all
- scope problem
- don't understand what's .output for??
