//
// Created by jurandi on 21-06-2023.
//
/*
MIT License
Copyright (c) 2023 OUI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef COTP_GENERATOR
#define COTP_GENERATOR

#ifndef SHA_256_H
#define SHA_256_H
#include "dependencies/sha256/sha-256.h"
#include "dependencies/sha256/sha-256.c"
#endif

#include "imports.h"
#include "extras/extras.h"
#include "time_calc/calc_time.h"

#include "CTopKeyAttributes/CTopKeyAttributes.h"
#include "COTPKey/COTPKey.h"

#include "extras/extras.c"
#include "time_calc/calc_time.c"
#include "CTopKeyAttributes/CTopKeyAttributes.c"
#include "COTPKey/COTPKey.c"
#endif