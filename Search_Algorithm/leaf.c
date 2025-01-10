
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
