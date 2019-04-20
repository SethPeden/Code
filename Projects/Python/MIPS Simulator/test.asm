.data
# Inputs
A:	.word	2, 3, 4, 5, 6
B:	.word	0
C:	.word	1
X:	.word	3
# Outputs
F:	.alloc	1

.text
			addi	$30, $29,  0			# Setting Frame Pointer
			addi	$29, $29,  -8			# Allocating Space for Function Call
			sw		$31, 24($29)			# Saving RA
			sw		$30, 20($29)			# Saving FP
			jal		Outer					# Calling Outer
			lw		$31, 24($29)			# Restoring RA 
			lw		$20, 20($29)			# Restoring FP
			addi	$29, $29,  8			# Deallocating Space for Function Call 
			jr		$31						# Return to Caller

		# Activation Frame
		# RA, FP
Outer:		addi	$30, $29,  0			# Setting Frame Pointer
			lw		$1,  A($0)				# $1 = A
			lw		$2,  B($0)				# $2 = B
			lw		$3,  C($0)				# $3 = C
			lw		$4,  X($0)				# $4 = X
			addi	$29, $29,  -28			# Allocating Space for Function Call
			sw		$31, 24($29)			# Saving RA
			sw		$30, 20($29)			# Saving FP
			sw		$1,  16($29)			# Loading A
			sw		$2,  12($29)			# Loading B
			sw		$3,  8($29)				# Loading C
			sw		$4,  4($29)				# Loading X
			jal		QuadVal					# Calling QuadVal
			lw		$31, 24($29)			# Restoring RA 
			lw		$20, 20($29)			# Restoring FP 
			lw		$1,  0($29)				# $1 = F 
			sw		$1,  F($0)				# Saving Output 
			addi	$29, $29,  28			# Deallocating Space for Function Call
			jr		$31						# Return to Caller
			
		# Activation Frame
		# RA, FP
		# A, B, C, X
		# F
QuadVal:	addi	$30, $29,  0			# Setting Frame Pointer
			lw		$1,  4($29)				# $1 = X
			lw		$2,  16($29)			# $2 = A
			mult	$2,  $1					# A * X
			mflo	$2						# $2 = A * X
			mult	$2,  $1					# A * X^2
			mflo	$2						# $2 = A * X^2
			lw		$3,  12($29)			# $3 = B
			mult	$3,  $1					# B * X
			mflo	$3						# $3 = B * X
			add		$2,  $2,  $3			# $2 = A * X^2 + B * X
			lw		$3,  8($29)				# $3 = C
			add		$2,  $2,  $3			# $2 = A * X^2 + B * X + C
			sw		$2,  0($29)				# F = A * X^2 + B * X + C
			jr		$31						# Return to Caller