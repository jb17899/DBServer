
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

