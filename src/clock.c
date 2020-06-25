/*
* SPDX-License-Identifier: BSD-2-Clause
*
* Copyright (c) 2020, Paolo Giorgianni <pdg@ologantr.xyz>
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other mateials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../include/clock.h"
#include <stdio.h>
#include <stdlib.h>

static inline void get_bits(uint4_t x, uint1_t *v)
{
        for (int i = 0, j = 3; i < 4; i++, j--)
                v[i].v = (x.v >> j) & 1;
        return;
}

uint1_t L0 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = ((!n[0].v) & n[2].v) |
                ((!n[0].v) & n[1].v & n[3].v) |
                (n[0].v & (!n[1].v) & (!n[2].v)) |
                ((!n[1].v) & (!n[2].v) & (!n[3].v));
        return res;
}

uint1_t L1 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = ((!n[0].v) & (!n[1].v)) |
                ((!n[0].v) & (!n[2].v) & (!n[3].v)) |
                (n[2].v & (!n[0].v) & n[3].v) |
                (n[0].v & (!n[1].v) & (!n[2].v));
        return res;
}

uint1_t L2 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = ((!n[0].v) & (!n[2].v)) |
                ((!n[0].v) & n[3].v) |
                ((!n[1].v) & (!n[2].v)) |
                ((!n[0].v) & n[1].v & n[2].v);
        return res;
}

uint1_t L3 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = (n[0].v & (!n[1].v) & (!n[2].v)) |
                ((!n[0].v) & n[1].v & n[3].v & (!n[2].v)) |
                ((!n[0].v) & (!n[1].v) & n[2].v) |
                ((!n[0].v) & n[2].v & (!n[3].v)) |
                ((!n[0].v) & (!n[1].v) & (!n[3].v));
        return res;
}

uint1_t L4 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = (n[2].v & (!n[0].v) & (!n[3].v)) |
                ((!n[1].v) & (!n[2].v) & (!n[3].v));
        return res;
}

uint1_t L5 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = (n[0].v & (!n[1].v) & (!n[2].v)) |
                ((!n[0].v) & (!n[2].v) & (!n[3].v)) |
                ((!n[0].v) & (!n[2].v) & n[1].v) |
                ((!n[0].v) & n[1].v & (!n[3].v));
        return res;
}

uint1_t L6 (uint4_t x)
{
        uint1_t n[4];
        uint1_t res;
        get_bits(x, n);
        res.v = ((!n[0].v) & (!n[1].v) & n[2].v) |
                (n[0].v & (!n[1].v) & (!n[2].v)) |
                ((!n[0].v) & n[1].v & (!n[2].v)) |
                ((!n[0].v) & n[2].v & (!n[3].v));
        return res;
}

void print_numbers(uint32_t x)
{
        /* 6 digits, 7 segments */
        uint1_t values_v[6][7];
        uint4_t tmp_4;
        uint32_t tmp_32 = x;

        for (uint32_t i = 6; i-- > 0;)
        {
                tmp_4.v = tmp_32 % 10;
                values_v[i][0] = L0(tmp_4);
                values_v[i][1] = L1(tmp_4);
                values_v[i][2] = L2(tmp_4);
                values_v[i][3] = L3(tmp_4);
                values_v[i][4] = L4(tmp_4);
                values_v[i][5] = L5(tmp_4);
                values_v[i][6] = L6(tmp_4);
                tmp_32 /= 10;
        }


        for (uint32_t i = 0; i < 6; ++i)
                printf(" %c  ", (values_v[i][0].v == 1) ? '_' : ' ');

        putchar('\n');

        for (uint32_t i = 0; i < 6; ++i)
                printf("%c%c%c ", (values_v[i][5].v == 1 ? '|' : ' '),
                       (values_v[i][6].v == 1 ? '_' : ' '),
                       (values_v[i][1].v == 1 ? '|' : ' '));

        putchar('\n');

        for (uint32_t i = 0; i < 6; ++i)
                printf("%c%c%c ", (values_v[i][4].v == 1 ? '|' : ' '),
                       (values_v[i][3].v == 1 ? '_' : ' '),
                       (values_v[i][2].v == 1 ? '|' : ' '));

        printf("\n\n");
}
