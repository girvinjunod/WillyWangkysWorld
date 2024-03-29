/* Realisasi Pohon Wahana */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsTreeEmpty (Tree T){
    return T == Nil;
}
boolean IsTreeOneElmt (Tree T){
    return (!IsTreeEmpty(T) && NbChild(T) == 0);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateTreeEmpty (Tree *T){
    *T = Nil;
}

/****************** Manajemen Memori ******************/
addrNode AlokasiTree (Wahana W){
    addrNode P;
    P = (addrNode) malloc (sizeof(ElmtTree));
    if(P != Nil){
        Parent(P) = Nil;
        InfoTree(P) = W;
        int i;
        for(i=0; i<MaxChildren; i++){
            Children(P)[i] = Nil;
        }
        NbChild(P) = 0;
    }
    return P;
}
void DeAlokasiTree (addrNode P){
    free(P);
}

/* PRIMITIF */
addrNode SearchTree(Tree T, int IDX){
    if(IsTreeEmpty(T)){
        return Nil;
    }else if(ID(InfoTree(T))==IDX){
        return T;
    }else{
        addrNode P = Nil;
        int i=0;
        while(P==Nil && Children(T)[i]!=Nil){   
            P = SearchTree(Children(T)[i], IDX);
            i++;
        }
    }
}

void InsertChild(Tree *T, Tree *SubT){
    Children(*T)[NbChild(*T)] = *SubT;
    NbChild(*T)++;
    Parent(*SubT) = (*T);
}

void PrintChild(Tree T){
	int i;
    for(i=0; i<NbChild(T); i++){
        PrintInfoWahana(InfoTree(Children(T)[i]));
    }
}

void PrintChildrenName(Tree T){
    int i;
    printf("[");
    boolean first = true;
    for(i=0; i<NbChild(T); i++){
        if(first){
            PrintName(InfoTree(Children(T)[i]));
            first = false;
        }else{
            printf(",");
            PrintName(InfoTree(Children(T)[i]));
        }
    }
    printf("]");
}

void MakeWahanaTree(Tree *T, int c){
    Wahana W;
    addrNode P;
    int subc;
    int i;
    for(i=0; i<c; i++){
        ReadWahana(&W);
        P = AlokasiTree(W);
        InsertChild(T, &P);
        subc = ToInt(CKata);
        ADVKATA();
        MakeWahanaTree(&P, subc);
    }
}

void PrintHistory(addrNode P){
    if(Parent(Parent(P)) == Nil){
        PrintName(InfoTree(P));
    }else{
        PrintHistory(Parent(P));
        printf("->");
        PrintName(InfoTree(P));
    }
}
Wahana CopyWahanaID(Tree T, int ID){
    addrNode P = SearchTree(T, ID);
    return CopyWahana(InfoTree(P));
}


