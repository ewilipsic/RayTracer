/* Program that converts a binary number to decimal */ .text .global
start start:
LDR R4, =N ADD R5, R4, #4 LDR R4, [R4]
MOV R0, R4
BL DIVIDE STRB R1, [R5, #1]
STRB R0, [R5] END: B END
/* Subroutine to perform the integer division R0 / 10. * Returns: quotient in R1, and remainder in R0 */
DIVIDE: MOV R2, #0 CONT: CMP R0, #10 BLT DIV END SUB R0, #10 ADD R2, #1 B
CONT
DIV END: MOV R1, R2 BX LR
N: Digits:
.word .space
.end

