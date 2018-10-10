.data
X:	.word	100
Y:	.alloc	1

.text
			lw		$1,  X($0)				# Load Input 
			
			addi	$29, $29, -20			# Allocating Space for Function Call
			
			sw		$31, 12($29)			# RA = $31 
			addi	$30, $29,  0			# Setting Current Frame Pointer
			sw		$30, 8($29)				# FP = $30
			sw		$1,  4($29)				# X = $1
			
			jal		Fact					# Call Fact
			
			lw		$1,  0($30)				# $1 = Y 
			sw		$1,  Y($0)				# Save Output
			
			lw		$31, 12($29)			# Restoring RA
			lw		$30, 8($29)				# Restoring FP
			
			addi	$29, $29, 20			# Deallocating Space for Locals and Function Call	
			
			jr		$31						# Return to Caller

			# Activation Frame
			# Caller
			# 	RA, FP (Bookeeping)
			# 	X (Inputs)
			# 	Y (Outputs)
			# Callee
			#	A (Locals)
Fact:		addi	$30, $29, 0				# Setting Frame Pointer
		
			lw		$1,  4($30)				# $1 = X	 
			slti	$2,  $1,  0				# $2 = X < 0
			beq		$2,  $0,  Good			# if (X >= 0) then Jump to Good
			sw		$0,  0($30)				# Y = 0 
			jr		$31						# Return to Caller
		
Good:		slti	$2,  $1,  2				# $2 = X < 2
			beq		$2,  $0,  Recursive		# if (X >= 2) then Jump to Recursive
			addi	$1,  $0,  1				# $1 = 1
			sw		$1,  0($30)				# Y = 1 
			jr		$31						# Return to Caller
	
Recursive:	addi	$29, $29, -4			# Allocating Space for Locals
	
			sw		$1,  0($29)				# A = $1
			
			addi	$29, $29, -16			# Allocating Space for Function Call
			 
			sw		$31, 12($29)			# RA = $31 
			sw		$30, 8($29)				# FP = $30
			addi	$1,  $1,  -1			# $1--
			sw		$1,  4($29)				# X = --A 
			
			jal		Fact					# Call Fact
			
			lw		$1,  0($30)				# $1 = Fact(Y - 1)
			
			lw		$31, 12($29)			# Restoring RA
			lw		$30, 8($29)				# Restoring FP
			
			addi	$29, $29, 16			# Deallocating Space for Function Call
			
			lw		$2,  0($29)				# $2 = A
			mult	$1,  $2					# (Y - 1) * A
			mflo	$1						# $1 = (Y - 1) * A
			
			addi	$29, $30, 0				# Deallocating Space for Locals
			
			sw		$1,  0($30)				# Y = (Y - 1) * A
			
			jr		$31						# Return to Caller