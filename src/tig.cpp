#include <functional>
#include <map>

#include "commit/add.h"
#include "commit/checkout.h"
#include "web/clone.h"
#include "commit/commit.h"
#include "util/common.h"
#include "util/config.h"
#include "util/diff.h"
#include "util/help.h"
#include "util/init.h"
#include "commit/log.h"
#include "web/pull.h"
#include "web/push.h"
#include "commit/reset.h"
#include "web/server.h"
#include "util/status.h"

int main(int argc, char *argv[])
{

    if(argc == 1){
        help(0,NULL);
    }
    else{
        String str = argv[1];
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
        else if(str == "server"){
            server(call_argc,call_argv);
        }
        else {
            printf("Unknown command\n Use tig help for help\n");
        }
    }
    return 0;
}
