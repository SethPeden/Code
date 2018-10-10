.data
N:	.word 	10
F: 	.alloc	1

.text		
			lw		$1,  N($0)			# Load N
			
			addi	$29, $29, -16		# Allocate Space for Function Call
			sw		$31, 12($29)		# RA = $31
			addi	$30, $29, 0			# FP = SP
			sw		$30, 8($29)			# FP = $30
			sw		$1,  4($29)			# N = $1 
			
			jal		Fibonacci			# Call Fibonacci
			
			lw		$31, 12($29)		# $31 = RA
			lw		$30, 8($29)			# $30 = FP
			lw		$1,  0($29)			# $1 = F
			
			sw		$1,  F($0)			# F = $1
			addi	$29, $29, 16		# Deallocate Space for Function Call
			jr		$31					# Return to Caller

			# Activation Frame
			# RA, FP
			# N (Inputs)
			# F (Outputs)
			# S (Locals)
Fibonacci:	addi	$30, $29, 0			# Setting Frame Pointer
			
			lw		$1,  4($30)			# $1 = N
			slti	$2,  $1,  1			# $2 = N < 1
			bne		$2,  $0,  Zero		# if (N < 1) then Jump to Zero
			
			slti	$2,  $1,  2			# $2 = N == 1
			bne		$2,  $0,  One		# if (N == 1) then Jump to One
			
			# Recursive Value
			addi	$29, $29, -4		# Allocate Space for Locals
			
			# Calc Space for F(N - 1)	
			addi	$29, $29, -16		# Allocate Space for Function Call
			lw		$1,  4($30)			# $1 = N
			addi	$1,  $1,  -1		# $1 = N - 1
			sw		$31, 12($29)		# RA = $31
			sw		$30, 8($29)			# FP = $30
			sw		$1,  4($29)			# N = $1 
			
			jal		Fibonacci			# Call Fibonacci
			
			lw		$31, 12($29)		# $31 = RA
			lw		$30, 8($29)			# $30 = FP
			lw		$1,  0($29)			# $1 = F(N - 1) 
			
			sw		$1,  -4($30)		# S = $1 
			
			# Calc Space for F(N - 2)	
			addi	$29, $29, -16		# Allocate Space for Function Call
			lw		$1,  4($30)			# $1 = N
			addi	$1,  $1,  -2		# $1 = N - 1
			sw		$31, 12($29)		# RA = $31
			sw		$30, 8($29)			# FP = $30
			sw		$1,  4($29)			# N = $1 
			
			jal		Fibonacci			# Call Fibonacci
			
			lw		$31, 12($29)		# $31 = RA
			lw		$30, 8($29)			# $30 = FP
			lw		$1,  0($29)			# $1 = F(N - 2) 
			
			lw		$2,  -4($30)		# $2 = S 
			add		$1,  $1,  $2		# $1 = S + F(N - 2)
			sw		$1,  0($30)			# F = F(N - 1) + F(N - 2)
			
			addi	$29, $30, 0			# Deallocate Space for Locals
			jr		$31					# Return to Caller
			
Zero:		sw		$0,  0($30)			# F = 0
			jr		$31					# Return to Caller

One:		addi	$1,  $0,  1			# $1 = 1
			sw		$1,  0($30)			# F = 1
			jr		$31					# Return to Caller