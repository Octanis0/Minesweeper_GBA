.GLOBL Ncount 

Ncount: 
MLA r0, r0, r2, r1 						// r0 = a*mapWidth + b 
mov pc, lr


// Ncount converts 2d array coordinates into a 1d array to correspond with drawSprite N numbering
// In other words,
// {{a1, b1, c1}
//  {a2, b2, c2}
//  {a3, b3, c3}}
// is converted to {a1, b1, c1, a2, b2, c2, a3, b3, c3} using x-coordinate + y-coordinate * array_width
