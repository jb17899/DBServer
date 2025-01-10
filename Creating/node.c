
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