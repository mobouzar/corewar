.name	"Leeloo"
.comment "Multipass"

	
begin:	ld %0,r6
jump:	zjmp %:deb

pare:	st r0,:begin -52
	st r0,:begin -44
	st r0,:begin -52
	st r0,:begin -44
	st r0,:begin -52
	st r0,:begin -44
	st r0,:begin -52
	live %1
	st r0,:begin -44
	st r0,:begin -52
	st r0,:begin -44
	st r0,:begin -52
	st r0,:begin -44
	st r0,:begin -52
	st r0,:begin -44
	zjmp %:pare
toto:	st r15,-480
	st r4,-481
	st r7,-482
	st r8,-483
	st r13,-484
	st r14,-485
	zjmp %-510

	

hop:	live %1
	fork %:decal2
	live %1
	ld %0,r2
	zjmp %:decal

	
debut:	st r3,4
fin:

avant:	

#	075103700370075103700771

arriere:

#       08 F4 03 70 03 70 08 F4 03 70


