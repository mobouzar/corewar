.name		"Sliders"
.comment	"And the winner is ..."

		      sti	r1,	%156,	%1
		      sti	r1,	%108,	%1
		      sti	r1,	%109,	%1
		      sti	r1,	%181,	%1
		      sti	r1,	%213,	%1
		      sti	r1,	%214,	%1
		      sti	r1,	%89,	%1
		      sti	r1,	%341,	%1
		       ld	%48,	r14
		       ld	%4,	r4
		       ld	%48	,r6
		       ld	%48,	r13
		       ld	%108,	r8
		       ld	%330,	r9
		     add	r8,	r9,	r8
		       ld	%92,	r12
		     sub	r12,	r8,	r12

		    live	%42
		     fork	%270

		    live	%42
		     fork	%21

		    live	%42
		     fork	%59
		       ld	%0,	r15
		     zjmp	%95

		       ld	%0,	r2

		    live	%42
		   ldi	%-12,	r2	,r3
		     sti	r3	,r8	,r2
		     add	r2,	r4,	r2
		     xor	r13,	r2	,r7
		     zjmp	%415
		       ld	%0	,r15

		     zjmp	%-36

		       ld	%0,	r10

		    live	%42
		   ldi	%-12	,r10,	r11
		     sti	r11	,r12,	r10
		     add	r10,	r4,	r10
		     xor	r6,	r10,	r7
		     zjmp	%-361
		       ld	%0,	r15
	     zjmp	%-36

		    live	%42
		     fork	%-97

		    live	%42
		     fork	%-59
		       ld	%0,	r15
		     zjmp	%-23

		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		    live	%42
		     zjmp	%-120

		    live	%42
		     fork	%-128
		       ld	%0	,r15
		     zjmp	%-15
