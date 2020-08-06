**Formal Languages & Compilers: C2Python Transcompiler** <br/> 
C2Python Transcompiler able to translate simple C programs in Python target language, given a set of grammar restrictions on source language.

The lexical analyzer was generated using Flex (the scanner generator) where regular expressions were used to describe the token patterns.

The syntax analyzer was generated using Bison (the parser generator): it builds the parse tree using a bottom-up approach. The sub-C language syntax was developed by scratch.

The semantic analysis phase uses the 'syntax-directed' approach and builds the intermediate representation: an Abstract Syntax Tree (AST).

The interpretation phase uses the generated intermediate representation to execute the C instructions.

It follows the translation phase, based on the intermediate representation created: startinng from restrictions imposed on C language, each construct has been translated in Python language with respect to grammar rules, both C and Python language.


**If you publish any work which uses the code stored in this project, please cite the following creators:** <br/>
Sergio Abascià, Gianluca Azzollini

**Developers** <br/>
Sergio Abascià <br/>
Gianluca Azzollini

**Contacts** <br/>
We are happy to help you with any question. Please contact us on our mails: <br/>
sergio05.abascia@gmail.com <br/>
azzollinigianluca@gmail.com <br/>

<br/>
<br/>
