#ifndef _FUNCTION_H
#define _FUNCTION_H
#include "main.h"

extern cautrucBang bang;
extern cautrucO** motO;

void taomang2chieu();
void xoamang2chieu();
void khoitao(int sodong, int socot, int sobom);
void taobom();
void xuatbom();
void tinhSoBomKe(cautrucO** motO, int dong, int cot);
void moO(cautrucO** motO, cautrucBang& bang, int x, int y);

#endif // _FUNCTION_H
