#include "tree.c"
#include "cache22.h"
bool nvalue;
bool cvalue;

int32 handle_hello(Client*,int8*,int8*);

CmdHandler handler[] = {
    {(int8*) "hello",handle_hello},
    {(int8*) "hello",handle_hello}
};
int32 handle_hello(Client* cli,int8* args,int8* folder){
    dprintf(cli->s,"hello back %s",args);
    return 0;
}
Callback getcmd(int8* cmd){
    int16 n,arrlen;
    // printf("ss\n");
    Callback cb=NULL;
    if(sizeof(handler)<16){
        return 0;
    }
    arrlen = sizeof(handler)/16;
    for(int c=0;c<arrlen;c++){
        if(!strcmp((char*)cmd,(char*)handler[c].cmd)){
            cb = handler[c].handler;
            break;
        }
    }
    return cb;
}

void childloop(Client* client){
    int8 buf[256];
    int16 count;
    int8 *p,*f;
    int8 cmd[256],args[256],folder[256];
    zero(buf,255);
    read(client->s,(char *)buf,254);
    count = (int16)strlen((char *)buf);
    if(count>254){
        count = 254;
    }
    //select /USERS/jobj
    //create /Users/logins
    //insert /Users/jobj sdjskl
     for(p = buf;
     (*p)&&(count--)&&
     (*p != ' '&&
     (*p != '\n')&&
     (*p != '\r'));
     p++)
     zero(args,sizeof(args));
     zero(cmd,sizeof(cmd));
     zero(folder,sizeof(folder));
     if(!(*p)||!count){
        strncpy((char*)cmd,(char*)buf,255);
        goto done;
     }
     else if(*p == ' '||*p == '\n'||*p == '\r'){
        *p =0;
        strncpy((char*)cmd,(char*)buf,255);
     }
     for(p++,f =p;
     (*p)&&(count--)&&
     (*p != ' '&&
     (*p != '\n')&&
     (*p != '\r'));
     p++);
     if(!(*p)||!count){
        strncpy((char*)folder,(char*)f,255);
        goto done;
     }
     else if(*p == ' '||*p == '\n'||*p == '\r'){
        *p =0;
        strncpy((char*)folder,(char*)f,255);
     }
     p++;
     if(*p){
        strncpy((char*)args,(char*)p,255);
        for(p = args;
        (*p)&&
        (*p!='\r')&&
        (*p!='\t');
        p++
        );
        *p=0;
     }
    done:
    dprintf(client->s,"cmd:\t%s\n",cmd);
    dprintf(client->s,"folder:\t%s\n",folder);
    dprintf(client->s,"arguments:\t%s",args);
    return;
}
void mainloop(int s){
struct sockaddr_in cli;
int s2;
int16 len;
char* sp;
int16 port;Client* client;pid_t pid;
s2 = accept(s,(struct sockaddr*)&cli,(unsigned int*)&len);
if(s2<0){
    return;
}
port = (int16)htons(cli.sin_port);
sp = inet_ntoa(cli.sin_addr);
printf("%s:%d\n",sp,port);
client = (Client*)malloc(sizeof(Client));
assert(client);
zero((int8*)client,sizeof(Client));
client->s = s2;
client->port = port;
strncpy(client->add,sp,15);
pid = fork();
if(pid !=0){
    free(client);
    return;
}
else{
    dprintf(s2,"100 OK Server connection accepted\n");
    cvalue = true;
    while(cvalue){
        childloop(client);
    }
    close(s2);
    free(client);
    return;
}
return;
}



int initserver(int16 port){
    int sockid;
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(HOST);
    sockid = socket(AF_INET,SOCK_STREAM,0);
    assert(sockid>0);

    if(bind(sockid,(struct sockaddr*)&sock,sizeof(sock))!=0){
        printf("error");
        exit(0);
    }
    listen(sockid,20);
    printf("Server listening on %s %d\n",HOST,port);
    fflush(stdout);

    return sockid;
}


int main(int argc,char* argv[]){
    char* sport;
    int16 port;
    if(argc<2){
        sport = PORT;
    }
    else{
        sport = argv[1];
    }
    // Callback x;
    // x = getcmd((int8*)"hello");
    // printf("%p\n",x);
    // return 0;
    port = (int16)atoi(sport);
   int s = initserver(port);
   nvalue = true;
while (nvalue){
    mainloop(s);
}
printf("CLOSING DOWN");
close(s); 
}



#pragma GCC diagnostic pop