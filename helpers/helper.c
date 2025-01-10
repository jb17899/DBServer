
int8 *indent(int8 n){
    int8* p;
    static int8 buf[256];
    if(n<1){
        return (int8*)"";
    }
    assert(n<120);
    zero(buf,256);
    int8 i =0;
    for(i=0,p=buf;i<n;i++,p+=2){
        strncpy((char*)p,"  ",2);
    }
    return buf;
}
int8* duplicate(int8* str){
    int16 x,n;
    static int8 buf[256];
    zero(buf,255);
    strncpy((char*)buf,(char*)str,255);
    n = (int16)strlen((char*)buf);
    x = n*2;
    if(x>254){
        return buf;
    }
    else{
        char* val = strdup((char*)buf);
        strncpy((char*)buf+n,(char*)val,255-n);
    }
    return buf;
}
void zero(int8 *str,int16 size){
int8* p;
int16 n;
for(n=0,p=str;n<size;p++,n++){
    *p=0;
}
return;
}