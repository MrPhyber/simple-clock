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
*    this list of conditions ad the following disclaimer in the documentation
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

#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>

#include "../include/clock.h"

static void* clock_fn(void *unused)
{
        char hour[6];
        time_t timer;
        char *time_string;
        unused = NULL;

        for(uint32_t h;;)
        {
                timer = time(NULL);
                time_string = ctime(&timer);
                hour[0] = time_string[11];
                hour[1] = time_string[12];
                hour[2] = time_string[14];
                hour[3] = time_string[15];
                hour[4] = time_string[17];
                hour[5] = time_string[18];

                h = atoi(hour);
                print_numbers(h);
                puts("Press ENTER to quit");
                system("sleep 1");
                system("clear");

                pthread_testcancel();
        }

        return NULL;
}

int main()
{
        char c;
        pthread_t clock;
        system("clear");

        pthread_create(&clock, NULL, clock_fn, NULL);

        fscanf(stdin, "%c", &c);
        if((c == '\n') || (c == EOF))
        {
                pthread_cancel(clock);
                pthread_join(clock, NULL);
                return 0;
        }
}
