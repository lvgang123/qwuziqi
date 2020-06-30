#ifndef AIDO_H
#define AIDO_H

/**
 * AI下棋Demo 整理:lvgang 2020-6-30
 */
#include "chead.h"

using namespace std;

class AIDO
{
public:
    static AIDO *Instance();
    explicit AIDO();
    ~AIDO();

private:
    static unique_ptr<AIDO> self;

    vChess* LcoalvChess;

public:
    string test();
    void setConnInfo(vChess* inchess);

};

#endif // AIDO_H
