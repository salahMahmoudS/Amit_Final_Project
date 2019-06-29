/*
 * BitMath.h
 *
 *  Created on: Apr 19, 2019
 *      Author: Al-Hussein
 */

#ifndef BITMATH_H_
#define BITMATH_H_

#define SET_BIT(Reg,BitNum) (Reg = Reg | (1 << BitNum))
#define CLEAR_BIT(Reg,BitNum) (Reg = Reg & (~(1 << BitNum)))
#define TOGGLE_BIT(Reg,BitNum) (Reg = Reg ^ (1 << BitNum))
#define SET_FIRST_NIBBLE(Reg) (Reg = Reg | (0x0F))
#define CLEAR_FIRST_NIBBLE(Reg) (Reg = Reg & (0xF0))
#define SET_SECOND_NIBBLE(Reg) (Reg = Reg | (0xF0))
#define CLEAR_SECOND_NIBBLE(Reg) (Reg = Reg & (0x0F))
#define BIT_IS_SET(Reg,BitNum) (Reg && (1 << BitNum))
#define BIT_IS_CLEAR(Reg,BitNum) (!(Reg && (1 << BitNum)))
#define GET_BIT(Reg,BitNum) ((Reg & (1 << BitNum)) >> BitNum)
#define ROL(Reg,BitNum) (Reg = (Reg << BitNum) | (Reg >> 8-BitNum))
#define ROR(Reg,BitNum) (Reg = (Reg >> BitNum) | (Reg << 8-BitNum))
#define CONC_HELP(a,b,c,d,e,f,g,h) 0b##a##b##c##d##e##f##g##h
#define CONC(a,b,c,d,e,f,g,h) CONC_HELP(a,b,c,d,e,f,g,h)

#endif /* BITMATH_H_ */
