#include "tree.h"
Tree root = {
    .n = {
    .tag = (TagRoot|TagNode),
    .north = (Node*)&root,
    .west = 0,
    .east = 0,
    .path = "/"
    }
};
void zero(int8 *str,int16 size){
int8* p;
int16 n;
for(n=0,p=str;n<size;p++,n++){
    *p=0;
}
return;
};
Leaf* find_leaf_linear(int8* path,int8* key){
Node* n = find_node_linear(path);
Leaf *l,*ret;
if(!n){
    return (Leaf*)0;
}
for(ret = (Leaf*)0,l = n->east;l;l = l->east){
    if(!strcmp((char*)l->key, (char*)key)){
        ret = l;
        break;
    }
}
return ret;
}
int8* lookup_linear(int8* path,int8* key){
    Leaf* p = find_leaf_linear(path,key);
    return (p)?p->value:(int8*)"Not Found";
}
Node* find_node_linear(int8* path){
    Node* p,*ret;
    for(p = (Node*)&root,ret=(Node*)0;p;p=p->west){
        if(!strncmp((char*)p->path,(char*)path,255)){
            ret=p;
            break;
        }
    }
    return ret;
}



void print_tree(int fd,Tree* _root){
    int8 indentation=0;
    int8 buf[256];
    int16 size;
    Node* n;
    Leaf* l,*last;
    for(n = (Node*)_root;n;n=n->west){
        Prints(indent(indentation++));
        Prints(n->path);
        Prints("\n");
        if(n->east){
            last = find_last_linear(n);
            if(last){
            for(l = last;
            (Node*)l!=n;
            l=(Leaf*)l->west){
                Prints(indent(indentation));
                Prints(n->path);
                Prints("/");
                Prints(l->key);
                Prints(" -> '");
                write(fd,l->value,sizeof(l->value));
                Prints("'\n");
            }
        }
        }
    }
    return;

}


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


Node* create_node(Node* parent,int8* path){
Node* n;
int16 size = sizeof(Node);
assert(parent);
n = (Node*)malloc(size);
zero((int8*)n,size);
parent->west = n;
n->tag = TagNode;
n->north = parent;
strncpy((char*)n->path,(char*)path,255);
return n;
}
Leaf* find_last_linear(Node* parent){
    Leaf* l;
    assert(parent);
    errno = NoError;
    if(!parent->east){
        return (Leaf*)0;
    }
    for(l = (Leaf *)parent->east;l->east;l = l->east);
    assert(l);
    return l;

}
Leaf* create_leaf(Node* parent,int16 count,int8* value,int8* key){
    Leaf* l;
    Leaf* new;
    int16 size;
    assert(parent);
    l = find_last_linear(parent);
    size = sizeof(struct s_leaf);
    new = (Leaf*)malloc(size);
    if(!l){
        parent->east=new;
    }
    else{
        l->east = new;
    }
    zero((int8*)new,size);
    new->tag = TagLeaf;
    new->west = (!l)?(Tree*)parent:(Tree*)l;
    key[strcspn((char*)key, "\n")] = 0;
    strncpy((char*)new->key,(char*)key,127);
    new->value = (int8*)malloc(count);
    zero(new->value,count);
    strncpy((char*)new->value,(char*)value,count);
    new->size = count;
return new;
}

Tree* example_tree(){
    int8 c;
    Node*n,*p;
    int8 path[256];
    zero(path,255);
    int32 x;
    for(n = (Node*)&root,c='a';c<='z';c++){
        x = (int32)strlen((char*)path);
        *(path+x++) = '/';
        *(path+x) = c;
        p = n;
        n = create_node(p,path);
    }
    return &root;
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

int32 example_leaves(){
    FILE* fd;
    int8 buf[256];
    int32 x,y;
    Leaf* l ;
    Node* n;
    int8 c;
    int8* path,*val;
    fd = fopen(EXAMPLEFILE,"r");
    assert(fd);
    zero(buf,256);
    y=0;
    while(fgets((char*)buf,255,fd)){
        x = (int32)strlen((char*)buf);
        buf[strcspn((char*)buf, "\n")] = 0;
        buf[x-2] = '\0';
        zero(path,256);
        path = example_path(*buf);
        n = find_node_linear(path);

        if(!n){
            zero(buf,256);
            continue;
        }
        val = duplicate(buf);
        l = create_leaf(n,(int16)strlen((char*)val),val,buf);
       y++;
       zero(buf,256);
       zero(val,256);
    }
    fclose(fd);
    return y;

}
int8* example_path(int8 path){
    int32 x;
    static int8 buf[256];
    int8 c;
    zero(buf,256);
    for(c = 'a';c<=path;c++){
        x = (int32)strlen((char*)buf);
        *(buf+x++) = '/';
        *(buf+x) = c;
    }
    return buf;
}
int main_tree(){
    Tree* example;
    example = example_tree();
    printf("populating tree\n");
    fflush(stdout);
    int32 value = example_leaves();
    if(!value){
        perror("Leaf are not built");
    }
    printf("%d",value);
    int8 * val = lookup_linear((int8*)"/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z",(int8*)"z");
    printf("%s\n",val);
    return 0;
}