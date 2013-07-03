#ifndef  HW_SETUP_Define_H_
#define  HW_SETUP_Define_H_

#define HW_DEBUG

#define BUFFER_CTRL_PIN_TOGGLE	_setSR(SFR_P0, _getSR(SFR_P0)^0x0004)
#define BUFFER_CTRL_PIN_HI		_setSR(SFR_P0, _getSR(SFR_P0)|0x0004)
#define BUFFER_CTRL_PIN_LO		_setSR(SFR_P0, _getSR(SFR_P0)&0xFFFB)

#define WAKEUP_PIN_IS_HI		(_getSR(SFR_P0) & 0x0002)
#define WAKEUP_PIN_EDGE_IS_HI	(_getSR(SFR_INTEC) & 0x0002)
#define WAKEUP_PIN_EDGE_TOGGLE	_setSR(SFR_INTEC, _getSR(SFR_INTEC) ^ 0x0002)

#define KEY_PIN_EDGE_LO		_setSR(SFR_INTEC, _getSR(SFR_INTEC) & 0xFFFE)
#define KEY_PIN_IS_HI		(_getSR(SFR_P0) & 0x0001)
#define KEY_PIN_EDGE_IS_HI	(_getSR(SFR_INTEC) & 0x0001)
#define KEY_PIN_EDGE_TOGGLE	_setSR(SFR_INTEC, _getSR(SFR_INTEC) ^ 0x0001)

#define CC2540_RESET_PIN_HI	_setSR(SFR_P0, _getSR(SFR_P0)|0x4000)//_setSR(SFR_P1, _getSR(SFR_P1)|0x0080)
#define CC2540_RESET_PIN_LO	_setSR(SFR_P0, _getSR(SFR_P0)&0xBFFF)//_setSR(SFR_P1, _getSR(SFR_P1)&0xFF7F)

#define MOUTH_PIECE_PIN_TOGGLE	_setSR(SFR_P0, _getSR(SFR_P0)^0x0008)
#define MOUTH_PIECE_PIN_HI		_setSR(SFR_P0, _getSR(SFR_P0)|0x0008)
#define MOUTH_PIECE_PIN_LO		_setSR(SFR_P0, _getSR(SFR_P0)&0xFFF7)

#ifdef HW_DEBUG

#define DEBUG_PINS_ENABLE	_setSR(SFR_P3En, _getSR(SFR_P3En) | 0x0005)
#define DEBUG_PINS_DIR		_setSR(SFR_P3M,  _getSR(SFR_P3M)  | 0x0005)
#define DEBUG_PINS_PULLUP 	_setSR(SFR_P3PH, _getSR(SFR_P3PH) & 0xFFFA)

#define DEBUG_PIN0_TOGGLE	_setSR(SFR_P3, _getSR(SFR_P3)^0x0001)
#define DEBUG_PIN0_HI		_setSR(SFR_P3, _getSR(SFR_P3)|0x0001)
#define DEBUG_PIN0_LO		_setSR(SFR_P3, _getSR(SFR_P3)&0xFFFE)

#define DEBUG_PIN1_TOGGLE	_setSR(SFR_P3, _getSR(SFR_P3)^0x0004)
#define DEBUG_PIN1_HI		_setSR(SFR_P3, _getSR(SFR_P3)|0x0004)
#define DEBUG_PIN1_LO		_setSR(SFR_P3, _getSR(SFR_P3)&0xFFFB)

//#define DEBUG_PIN2_TOGGLE	_setSR(SFR_P3, _getSR(SFR_P3)^0x0010)
//#define DEBUG_PIN2_HI		_setSR(SFR_P3, _getSR(SFR_P3)|0x0010)
//#define DEBUG_PIN2_LO		_setSR(SFR_P3, _getSR(SFR_P3)&0xFFEF)

#else

#define DEBUG_PINS_ENABLE
#define DEBUG_PINS_DIR
#define DEBUG_PINS_PULLUP

#define DEBUG_PIN0_TOGGLE
#define DEBUG_PIN0_HI
#define DEBUG_PIN0_LO

#define DEBUG_PIN1_TOGGLE
#define DEBUG_PIN1_HI
#define DEBUG_PIN1_LO

#define DEBUG_PIN2_TOGGLE
#define DEBUG_PIN2_HI
#define DEBUG_PIN2_LO

#endif

#define T0_PERIOD_SEC	1.000
#define T0_COUNT_VALUE	(u16)(T0_PERIOD_SEC * 46875)
#define T0_ENABLE		_setSR(SFR_T0, _getSR(SFR_T0) | 0x1000)
#define T0_DISABLE		_setSR(SFR_T0, _getSR(SFR_T0) & 0xEFFF)

#define T2_PERIOD_SEC	0.0625
#define T2_COUNT_VALUE	(u16)(T2_PERIOD_SEC * 46875)
#define T2_IS_ENABLE	(_getSR(SFR_T2) & 0x1000)
#define T2_ENABLE		_setSR(SFR_T2, _getSR(SFR_T2) | 0x1000)
#define T2_DISABLE		_setSR(SFR_T2, _getSR(SFR_T2) & 0xEFFF)

void hw_setup(void);

#endif