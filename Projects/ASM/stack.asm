.data
Input:	.word	-10
Output:	.alloc	1

.text

		lw		$4,  Input($0)			# loading input value

		# Push
		addi	$29, $29, -4			# increment stack pointer
		sw		$31, 0($29)				# push caller
		
		jal		Abs						# $4 = |$4|
		
		# Pop
		lw		$31, 0($29)				# pop caller
		addi	$29, $29, 4				# decrement stack pointer
		
		sw		$4,  Output($0)			# saving output value
		
		jr		$31						# return to caller
		
		# Calculates the absolute value of $4. Overwrites $4 and $5.
Abs:	slti	$5,	 $4,  0				# $5 = $4 < 0
		beq		$5,  $0,  EndAbs		# if (!($4 < 0)) then jump to EndAbs
		sub		$4,  $0,  $4			# $4 = -$4
EndAbs: jr		$31						# return to caller