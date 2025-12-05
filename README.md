# jnvm
A virtual machine for the Juno programming language, inspired by JVM.

# Example
Let's test this simple Juno program.
```
let a = 10;
let b = 20;
let result = a + b;
```

The following bytecode would be assembled:
```
|  BCI |   INSTRUCTION   |    OPERANDS     |
| 0001 |     bipush      |  immediate 10   |
| 0003 |     istore      |     index 0     |
| 0005 |     bipush      |  immediate 20   |
| 0007 |     istore      |     index 1     |
| 0009 |      iload      |     index 0     |
| 0011 |      iload      |     index 1     |
| 0012 |      iadd       |                 |
| 0014 |     istore      |     index 2     |
```

JNVM offers a nice and simple bytecode disassembler built in. We can see a let expression is boiled down to `bipush` and `istore`.
`bipush` means to push a byte, in this case it's the immediate value `10`, we then store the `int` as a local variable on the current frame at index `0`. `iload`
takes one operand, and that is the index of the local variable.

Here is an abstracted breakdown of what a stack frame looks like:
```
vector local_variables
vector operand_stack
```
These are the two important fields I'll talk about, when the instruction `bipush` is encountered, it'll increment one space ahead to retrieve the instructions operand, in this case it's the `int 10`, this will then push the `int` / `byte` onto the operand stack, the operand stack is where values will live for temporary expressions, such as adding two values. The `istore` instruction pops the operand stack and places that value at an index in the local variable array / vector. The `iload` instruction does the opposite, the `iadd` function will pop the two values off the operand stack, and push its result onto the operand stack.
As of now, a global stack frame is created for development purposes, as functions are introduced, the system will be properly implemented.