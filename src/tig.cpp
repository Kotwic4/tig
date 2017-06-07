#include <functional>
#include <map>

#include "add.h"
#include "checkout.h"
#include "clone.h"
#include "commit.h"
#include "common.h"
#include "config.h"
#include "diff.h"
#include "help.h"
#include "init.h"
#include "log.h"
#include "pull.h"
#include "push.h"
#include "reset.h"
#include "status.h"

int main(int argc, char *argv[])
{

    if(argc == 1){
        help(0,NULL);
    }
    else{
        std::string str = argv[1];
        int call_argc = argc-2;
        char **call_argv = argv+2;
        if(str == "add"){
            add(call_argc,call_argv);
        }
        else if(str == "checkout"){
            checkout(call_argc,call_argv);
        }
        else if(str == "clone"){
            clone(call_argc,call_argv);
        }
        else if(str == "commit"){
            commit(call_argc,call_argv);
        }
        else if(str == "config"){
            config(call_argc,call_argv);
        }
        else if(str == "diff"){
            diff(call_argc,call_argv);
        }
        else if(str == "help"){
            help(call_argc,call_argv);
        }
        else if(str == "init"){
            init(call_argc,call_argv);
        }
        else if(str == "log"){
            log(call_argc,call_argv);
        }
        else if(str == "pull"){
            pull(call_argc,call_argv);
        }
        else if(str == "push"){
            push(call_argc,call_argv);
        }
        else if(str == "reset"){
            reset(call_argc,call_argv);
        }
        else if(str == "status"){
            status(call_argc,call_argv);
        }
        else {
            printf("Unknown command\n Use tig help for help\n");
        }
    }
    return 0;
}
