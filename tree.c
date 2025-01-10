#include "./headers/tree.h"
#include "./Creating/leaf.c"
#include "./Creating/node.c"
#include "./helpers/helper.c"
#include "./Search_Algorithm/leaf.c"

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
int32 example_leaves(){
    FILE* fd;
    int8 buf[256];
    int32 x,y;
    Leaf* l ;
    Node* n;
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
int main(){
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