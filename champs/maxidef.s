.name " maxidef "
.comment " module de defense"

loop:	live %0
	zjmp %8

gobepc:	st r1,6			# 03 70 01 00 06			5
	live %66		# 01 00 00 00 42			10
	ld -4,r1		# 02 d0 ff fc 01			5
	st r2,-14		# 03 70 02 ff f2			5
	
	ld %0,r5

slide2:	zjmp %-492

slide1: live %1
	st r2,-385
	st r4,-386
defm:	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	st r3,-510
	