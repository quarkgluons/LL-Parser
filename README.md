This is an implementation of the predictive parser (LL1)

The input to the program should be like:
   ~$	./executable <inputFile>

<inputFile> name in our case is productions.txt

the inputFile will contain productions of the grammar of the form 

S->ASb
A->   a
B  -> b


if any variable contain multiple productions then they must be written on different lines like:

S->Sa
S->a

imp: S->Sa | a   (this form is not supported)

Epsilon productions are represented by:

S->#
thiisis it
