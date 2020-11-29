.name	"Booster !"
.comment "Alors la, si ca marche, trop content !  :)"

boost:	ld %12,r2
	ld %3,r3
	ld %4,r4
	ld %5,r7
	live %556

	#sti r1,%:live1,%1
live1:	live %66


	#sti r1,%:live,%-4
	#ldi %:live,%-2,r6
#0:	live %66
live %565
	# %544456
	# %:numero1
	live %556
#1:	live %66
	# %:numero2
#2:	live %66
#	# %:#0

master:	live %66
	ld %0,r3
	ld %16777216,r6
	live %556
#	ldi %:master,%0,r6
	ld %0,r5
	zjmp %:ready
	live %556

numero1: live %66
	ld %3,r3
	st r3, 5656
	ld %68436,r2
	live %556
	st r2, 4455
#	ldi %:live,%-2,r6


numero2: live %66
	ld %6,r3
	st r6, 4545
	ld %1409680135,r6
	st r6, 454565656

tampon:	#sti r6,r3,r5
live:	#sti r1,r5,r5

ready:	#sti r6,r3,%:ecriture

wait:	live %66
	zjmp %:ecriture
	ld %3,r3
	st r3, 5656
	ld %68436,r2
	live %556
	live %565
	# %544456
	st r2, 4455

ecriture: zjmp %:wait
ld %3,r3
	st r3, 5656
	ld %68436,r2
	live %556



