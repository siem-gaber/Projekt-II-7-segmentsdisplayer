
#ifndef HEADER_H_
#define HEADER_H_

#include "timer.h"
#include "wdt.h"
#include "display.h"
#include "button.h"

// Deklarera tre globala knappar (extern).
extern struct button button1;
extern struct button button2;
extern struct button button3;

extern struct timer timer0;
#endif /* HEADER_H_ */