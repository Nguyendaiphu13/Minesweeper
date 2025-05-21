#include <iostream>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "function.h"
#include "graphics.h"

cautrucBang bang;
cautrucO** motO;

void taomang2chieu() {
    motO = new cautrucO*[bang.dong];
    for (int i = 0; i < bang.dong; i++) {
        motO[i] = new cautrucO[bang.cot];
    }
}

void xoamang2chieu() {
    for (int i = 0; i < bang.dong; i++) {
        delete[] motO[i];
    }
    delete[] motO;
}

void khoitao(int sodong, int socot, int sobom){
    bang.dong = sodong;
    bang.cot = socot;
    bang.bom = sobom;
    bang.soodamo = 0;
    bang.co = 0;
    taomang2chieu();
    taobom();
    tinhSoBomKe(motO,sodong,socot);
}

void taobom() {
    int sobom = bang.bom;
    int xbom, ybom;
    srand(time(NULL));
    while (sobom > 0) {
        xbom = rand() % bang.dong;
        ybom = rand() % bang.cot;
        if (motO[xbom][ybom].ocobom) {
            continue;
        }
        motO[xbom][ybom].ocobom = true;
        sobom--;
    }
}

void xuatbom() {
    for (int i = 0; i < bang.dong; i++) {
        for (int j = 0; j < bang.cot; j++) {
            if (motO[i][j].ocobom) {
                cout << 0;
            } else {
                cout << 1;
            }
        }
    }
}

void tinhSoBomKe(cautrucO** motO, int dong, int cot) {
    for (int i = 0; i < dong; ++i) {
        for (int j = 0; j < cot; ++j) {
            if (motO[i][j].ocobom) {
                motO[i][j].sobomlienke = -1;
                continue;
            }

            int dem = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0){
                        continue;
                    }
                    int ni = i + dx;
                    int nj = j + dy;
                    if (ni >= 0 && ni < dong && nj >= 0 && nj < cot) {
                        if (motO[ni][nj].ocobom)
                            ++dem;
                    }
                }
            }
            motO[i][j].sobomlienke = dem;
        }
    }
}

void moO(cautrucO** motO, cautrucBang& bang, int x, int y) {
    if (x < 0 || x >= bang.cot || y < 0 || y >= bang.dong) return;
    if (motO[y][x].odamo || motO[y][x].ocamco) return;

    motO[y][x].odamo = true;
    bang.soodamo++;

    if (motO[y][x].sobomlienke == 0) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx != 0 || dy != 0)
                    moO(motO, bang, x + dx, y + dy);
            }
        }
    }
}


void camCo(cautrucO** motO, cautrucBang& bang, int x, int y) {
    if (x < 0 || x >= bang.cot || y < 0 || y >= bang.dong) return ;
    if (motO[y][x].odamo) return;
    motO[y][x].ocamco = !motO[y][x].ocamco;
    if (motO[y][x].ocamco){
        bang.co++;
    }
    else{
        bang.co--;
    }
}

bool checkWin(){
    return((bang.bom+bang.soodamo)==(bang.dong*bang.cot));
}
