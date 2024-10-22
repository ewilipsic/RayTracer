text

global start

944%

ロミ 40

38

start:

LDR R4, =N

ADD R5, R4, #4

LDR R4, [R4]

MOV R0, R4

//R5 points to the decimal digits storage location

// R4 holds N

// parameter for DIVIDE goes in RO

BL DIVIDE

STRB R1, [R5, #1]

// Tens digit is in R1

STRB RO, [R5]

// Ones digit is in RO

END:

B

END

/* Subroutine to perform the integer division R0/10.

* Returns: quotient in R1, and remainder in RO

*/

DIVIDE:

MOV R2, #0

CONT:

CMP R0, #10

BLT

DIVEND

SUB R0, #10

ADD R2, #1

B CONT

DIV END:

MOV R1, R2

BX LR

N:

word 76

Digits:

space

4

.end

// return quotient in R1 (remainder is in RO)

// the decimal number to be converted

// storage space for the decimal digits
