.name "Barriere"
.comment "Envoie des torpilles a l'avant et se protege avec des barrieres a l'avant et a l'arriere"

		and	r6, %0, r6
		zjmp %:init

# On bombarde derriere notre programme

arriere:	ld	%-5, r5
		ld	%1024,r4
arriere2:	ld	%-5, r3
arriere_live:	live %42
		sti	r4, %:arriere, r3
		add	r3, r5, r3
		sti	r4, %:arriere, r3
		add	r3, r5, r3
		sti	r4, %:arriere, r3
		add	r3, r5, r3
		sti	r4, %:arriere, r3
		add	r3, r5, r3
		sti	r4, %:arriere, r3
		add	r3, r5, r3
		xor	r3,%-430,r15
		zjmp	%:arriere2
		and	r6, %0, r6
		zjmp	%:arriere_live

fork_arriere:	live	%42
		fork	%:arriere
		zjmp	%:fork_arriere

# On commence les lives en serie
live_live:	live	%42	
	

		xor	r9,%6,r10
		zjmp	%:fork_live
		ld	%6,r9
		and	r6,%0,r6
		zjmp	%:live_live	
		
init:		fork	%:kmissile
		live	%42
		sti	r1, %:arriere_live, %1	
		fork	%:fork_arriere
		live	%42
		sti	r1, %:avant_live, %1
		fork	%:fork_avant
		live	%42
		ld	%1,r9
		and	r6,%0,r6
		zjmp	%:live_live
	
fork_live:	live	%42
		fork	%5454
		live	%42	
		fork	%:fork_live
		live	%42
		zjmp	%:fork_live
	


		zjmp	%-5445

fork_avant:	live	%42
		fork	%:avant
		zjmp	%:fork_avant
	
avant:		ld	%-5, r5
		ld	%12, r4
avant2:		ld	%10, r3
avant_live:	live %1
		sti	r4, %:fin, r3
		sub	r3, r5, r3
		sti	r4, %:fin, r3
		sub	r3, r5, r3
		sti	r4, %:fin, r3
		sub	r3, r5, r3
		sti	r4, %:fin, r3
		sub	r3, r5, r3
		sti	r4, %:fin, r3
		sub	r3, r5, r3
		xor	r3,%435,r15
		zjmp	%:avant2
		and	r6, %0, r6
		zjmp	%:avant_live
fin:		zjmp	%:avant_live
kmissile:	live	%42
		fork	%:kfork1
		live	%42
		fork	%:kfork2
		live	%42
		fork	%:kfork4
		ld	%12,r2
		ld	%192,r5
		and	r6,%0,r6
		zjmp	%:kdebut
		
kfork1:		live	%42
		fork	%:kfork3
		live	%42
		fork	%:kfork6
		ld	%0,r2
		ld	%180,r5
		and	r6,%0,r6
		zjmp	%:kdebut
	
kfork2:		live	%42
		fork	%:kfork5
		live	%42
		ld	%8,r2
		ld	%188,r5
		and	r6,%0,r6
		zjmp	%:kdebut
	
kfork3:		live	%42
		fork	%-88
		ld	%4,r2
		ld	%184,r5
		and	r6,%0,r6
		zjmp	%:kdebut

kfork4:		ld	%16,r2
		ld	%196,r5
		and	r6,%0,r6
		zjmp	%:kdebut

kfork5:		ld	%20,r2
		ld	%200,r5
		and	r6,%0,r6
		zjmp	%:kdebut

kfork6:		ld	%24,r2
		ld	%204,r5
		and	r6,%0,r6
		zjmp	%:kdebut

kdebut:		ld	%:kdebut,r3 
		sti	r3,r5,%:kfin   
		live	%42
		and	r6,%0,r6
kfin:		zjmp	%180





