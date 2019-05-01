; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
		
star	DCB "*.***"
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec

	PUSH {LR, R0}
	SUB SP, #8 		;allocating num
	
	CMP R0, #10		;comparing input with 10
	BLO Print		;if number is lesser than 10, then print to screen
	
	MOV R1, #10
	UDIV R2, R0, R1		;divided input by 10 and stores quotient into R2
	BL FindRemainder	
	STR R0, [SP]		;storing remainder in stack
	
	MOV R0, R2			;moving quotient into R0
	BL LCD_OutDec
	LDR R0, [SP]		;loads value 
	
Print
	ADD R0, R0, #0x30
	BL ST7735_OutChar	;calling 
	
	ADD SP, #8
	POP {LR, R0}

	BX  LR
	
	
FindRemainder
	UDIV R3, R0, R1
	MUL R1, R3, R1
	SUB R0, R0, R1
	BX LR 

;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix

	PUSH {R4, LR}

	MOV R1, #9999
	CMP R0, R1
	BHI NotInRange
	
	SUB SP, #8	;allocating num
	
	STR R0, [SP] ;storing R0 in stack
	
	MOV R1, #1000
	UDIV R0, R1	;dividing to get thousandths place
	ADD R0, #0x30	;converting to ASCII character
	BL ST7735_OutChar
	
	MOV R0, #0x2E
	BL ST7735_OutChar	;printing the period
	
	LDR R0, [SP]
	MOV R1, #1000
	BL FindRemainder	;finding modulus
	
	MOV R1, #100		
	UDIV R0, R1		;dividing to get hundredths place
	ADD R0, #0x30	;converting to ASCII character
	BL ST7735_OutChar
	
	LDR R0, [SP]
	MOV R1, #100
	BL FindRemainder ;finding modulus
	
	MOV R1, #10
	UDIV R0, R1		;dividing to get tenths place
	ADD R0, #0x30	;converting to ASCII character
	BL ST7735_OutChar
	
	LDR R0, [SP]
	MOV R1, #10
	BL FindRemainder 
	
	ADD R0, #0x30
	BL ST7735_OutChar
	
	ADD SP, #8
	BX LR
	
NotInRange
	LDR R0, =star
	BL ST7735_OutString
	
	POP {R4, PC}
	BX LR

 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
