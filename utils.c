#include "fylib.h"
#include "fyshell.h"

void Getcwd(char *buf, size_t size){
    if(NULL == getcwd(buf, size))
        perror(RED"[ERROR]: getcwd"RESET);
}
void Print_logo(){
printf(G"    █████▒ ▓██   ██▓ \n"
        "   ▓██   ▒  ▒██  ██▒\n"
        "   ▒████ ░   ▒██ ██░\n"
        "   ░▓█▒  ░   ░ ▐██▓░\n"
        "   ░▒█░      ░ ██▒▓░\n"
        "   ▒ ░       ██▒▒▒  \n"
        "    ░       ▓██ ░▒░ \n"
        "    ░ ░     ▒ ▒ ░░  \n"
        "            ░ ░     \n"
        "             ░ ░     \n");
}
void cool_exit(){
        const char *charging[] = {
        "[            ]",
        "[=           ]",
        "[==          ]",
        "[===         ]",
        "[====        ]",
        "[=====       ]",
        "[======      ]",
        "[=======     ]",
        "[========    ]",
        "[=========   ]",
        "[==========  ]",
        "[=========== ]",
        "[===========<0>]",
    };
    const i32 frames = sizeof(charging) / sizeof(charging[0]);

	printf(RED"Shutting down...\n"RESET);

    for (i32 i = 0; i < frames; i++) {
        printf("\r" Y "%s" RESET, charging[i]);
        fflush(stdout);  
        usleep(42133);  
    }
	printf(C"\nEXIT\n"RESET);
	exit(EXIT_SUCCESS);
}
