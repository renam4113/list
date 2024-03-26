#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct point{
int key;
struct point* next;
struct point* back;
};

bool addToHead(struct point **list, int x){
struct point *PtrIx = (struct point*) malloc(sizeof(struct point));
if (PtrIx){
PtrIx->key = x;
PtrIx->next = NULL;
if (*list == NULL) *list = PtrIx;
else{
PtrIx->next = *list;
*list = PtrIx;
}
PtrIx -> back = NULL;
return true;
}
return false;
}

bool addToTail(struct point **list, int x){
struct point *PtrIx = (struct point*) malloc(sizeof(struct point));
if (PtrIx && list){
PtrIx -> key = x;
PtrIx -> next = NULL;
if (*list == NULL){
*list = PtrIx;
PtrIx -> back = NULL;
}
else{
struct point *current = *list;
for (; current -> next; current = current -> next);
current -> next = PtrIx;
PtrIx -> back = current;
}
return true;
}
return false;
}

bool addList(struct point **list, int x, int n, bool Flag){
if(list){

if(n == 0 && Flag){
bool flag = addToHead(list, x);
if(flag) return true;
else return false;
}

struct point *current = *list;
int i = 0;
for(; current -> next && i < n; i++) current = current -> next;

if(current -> next == NULL){
bool flag = addToTail(list, x);
if(flag) return true;
else return false;
}

else{
struct point *ptrIx = (struct point*)malloc(sizeof(struct point));
if(ptrIx){
ptrIx -> key = x;
if (Flag){
ptrIx -> next = current;
current -> back -> next = ptrIx;
current -> back = ptrIx;
}
else{
ptrIx -> next = current -> next;
current -> next -> back = ptrIx;
current -> next = ptrIx; 
}
return true;
}
else return false;
}
}
return false;
}

void delLast(struct point **list){
struct point *current = *list;
for(;current->next; current = current -> next);
current -> back -> next = NULL;
free(current);
}

struct point *find(int n, struct point **list){
struct point* current = *list;
for(;current -> next || current -> key != n; current = current -> next);
if (current -> next == NULL && current -> key != n) return NULL;
else return current;
}

int getValue(struct point *list, int n){
struct point *current = list;
for(int i = 0; i < n; i++){
current = current -> next;
}
return current -> key;
}

void ClearList(struct point **list){
if(*list){
struct point *current = *list;
for(; current -> next; current = current -> next);
while( current -> back){
current = current -> back;
free(current -> next);
}
free(current);
*list = NULL;
}
}

void delByPosition(struct point **list, int n){
if(*list){
struct point *current = *list;
for(int i = 0; i < n; i++) current = current -> next;
current -> back -> next = current -> next;
current -> next -> back = current -> back;
free(current);
}
}

void delHead(struct point **list){
struct point *current = *list;
*list = (*list) -> next;
(*list) -> back = NULL;
free(current);
}

struct point* GetPoint(struct point **list, int n){

if(*list != NULL){
struct point* current = *list;
for(int i = 0; i < n && current -> next; i++) current = current -> next;
if(n == 0){
if((*list) -> next){
(*list) -> next -> back = NULL;
*list = (*list) -> next;
}
else *list = NULL;
}
else{
if(current -> next != NULL){
current -> back -> next = current -> next;
current -> next -> back = current -> back;
}
else{
current -> back -> next = NULL;
}
}
current -> back = NULL;
current -> next = NULL;
return current;
}
return NULL;
}

void delBefore(struct point **list, int n){
if(n == 0) delHead(list);

else {
struct point *current = *list;
for(int i = 0;current -> next && i < n - 1; i++) current = current -> next;
if(current -> next){
current -> back -> next = current -> next;
current -> next -> back = current -> back;
free(current);
}
else delLast(list);
}
}

void listprint(struct point *list){

if (list){
struct point *current = list;

while(current ->
next){
printf("%d ", current-> key);
current = current -> next;
}
printf("%d", current -> key);
}
else printf("list is empty");
}

void UniqueAndOthers( struct point **Sx, struct point **tx, struct point **sx, int n){

int Tab[256] = {0};
struct point *ptrlist = NULL;
struct point *ptrList = NULL;

for(int i = 0 ; i < n; i++){

int k =
getValue(*Sx,0);
struct point *current = GetPoint(Sx, 0);
if(Tab[k] == 0){
Tab[k]++;

if(*tx == NULL){
*tx = current;
ptrlist = current;
}

else{
current -> back = ptrlist;
ptrlist -> next = current;
ptrlist = ptrlist -> next;
}

}

else{
if(Tab[k] == 1){
if(*sx == NULL){
*sx = current;
ptrList = current;
}
else{
current -> back = ptrList;
ptrList -> next = current;
ptrList = ptrList -> next;
}
Tab[k]++;
}
else free(current);
}
}
}

int main(){

struct point *head = NULL;

int n = 0;

printf("kol-vo chisel : ");
scanf("%d", &n);

for (int i = 0; i < n; i++){
int k = 0;
scanf("%d", &k);
addToTail(&head, k);
}

listprint(head);
printf("\nlist1 :\n");

struct point *list = NULL;
struct point *List = NULL;
UniqueAndOthers(&head, &list, &List, n);

listprint(list);
printf("\nlist2 :\n");
listprint(List);

ClearList(&list);
ClearList(&List);

}