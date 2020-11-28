#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "graph.h"
#include "map.h"
#include "point.h"

adrNode AlokNode(int X,MAP M)
/* I.S. X adalah bilangan bulat valid */
/* F.S. Alokasi node dalam graph dengan ID X dan Npred, Trail dan Next diinisialisasikan 0,Nil,dan Nil  */
{
    adrNode P = (adrNode) malloc((sizeof(NodeGraph)+1));
    if(P != Nil){
        IdGraph(P) = X;
        Map(P) = M;
        Trail(P) = Nil;
        NextGraph(P) = Nil;
    }
}
void DealokNode(adrNode P)
/* I.S. adrNode P valid */
/* F.S. Melakukan dealokasi dari P  */
{
    free(P);
}
adrSucc AlokSucc(adrNode Pn)
/* I.S. adrNode Pn valid */
/* F.S. Membuat address P , Mengalokasikan Succ(P) = Pn dan next = Nil */
{
    adrSucc P = (adrSucc) malloc(sizeof(SuccGraph)+1);
    if(P!= Nil){
        Succ(P) = Pn;
        NextSucc(P) = Nil;
    }
}
void DealokSuccNode(adrSucc Pt)
/* I.S. adrSucc Pt valid */
/* F.S. Melakukan dealokasi pada SuccNode Pt */
{
    free(Pt);
}

void ConnectNode(adrNode *P1,adrNode *P2){
  adrSucc S = Trail(*P1);
  while (S!=Nil) S=NextSucc(S); 
  S = AlokSucc(*P2);
  
  S = Trail(*P2);
  while (S!=Nil) S=NextSucc(S);
  S = AlokSucc(*P1);
}

void CreateGraphMap(Graph* G)
/* I.S. Graph terdefinisi dan kosong */
/* F.S. Graph dibuat dengan 4 node yang masing" mempunyai 1 map */
{
    MAP M1,M2,M3,M4,*Mtemp;
    readMap(&M1,&M2,&M3,&M4);
    
    adrNode P = AlokNode(1,M1);
    First(*G) = P;
    for(int i=2; i<=4;i++){
        if(i==2) Mtemp = &M2;
        else if(i==3) Mtemp = &M3;
        else if(i==4) Mtemp = &M4;
        
        AddNodeGraph(G,i,*Mtemp);
    }
}

void AddNodeGraph(Graph *G,int n,MAP M)
/* I.S. Graph terdefinisi, mungkin kosong , n bilangan bulat valid */
/* F.S. Menambahkan Node di ujung graph dengan ID n */
{
    adrNode P = AlokNode(n,M);

    adrNode A = First(*G);
    while(NextGraph(A) != Nil){
        A = NextGraph(A);
    }
    NextGraph(A) = P;
}

void ConnectMap(Graph *G){
  adrNode P,P1,P2;
  for(int i=1;i<=2;i++){
    P = SearchNode(*G,i);

    if(i==1) P1=SearchNode(*G,i+1);
    else P1=SearchNode(*G,i-1);
    P2=SearchNode(*G,i+2);
    
    ConnectNode(&P,&P1);
    ConnectNode(&P,&P2);
  }
}

/* OPERASI SEARCH */
adrNode SearchNode(Graph G, int X){
/* I.S. G berisi minimal 1 elemen, X adalah ID dari salah satu elemen graph */
/* F.S. Mengembalikan adrNode dari elemen dengan ID X */
    boolean found = false;
    adrNode A = First(G);
    while(A != Nil && IdGraph(A) != X){
        A = NextGraph(A);
    }
    if(A != Nil){
        return A;
    }
    else{
        return Nil;
    }
}

void AddLastTrail(Graph *GR, int idB, int Trail){
// I.S. idB, Trail terdefinisi dan ada dalam suatu id graph, trail 
// F.S. Trail dimasukan sebagai trail terakhir di idB
    adrNode P = SearchNode(*GR,idB);
    adrNode PTrail = SearchNode(*GR,Trail);
    adrSucc Pn = AlokSucc(PTrail);
    adrSucc PT = Trail(P);
    if(PT != Nil){
        while(NextSucc(PT) != Nil){
            PT = NextSucc(PT);
        }
        NextSucc(PT) = Pn;
    }
    else{
        Trail(P) = Pn;
    }
}

void PrintCurrMap(Graph GR){
//memprint semua item di graph
    adrNode P = SearchPlayer(GR);
    printMap(Map(P));
}

/* Check Movement */
void move(char input,Graph *GM){
	POINT temp;

    adrNode P = SearchPlayer(*GM);
    MAP M = Map(P);

	int x=PosXPlayer(M),y=PosYPlayer(M);
	if (input=='w') y--;
	else if (input=='a') x--;
	else if (input=='s') y++;
	else if (input=='d') x++;

	temp = MakePOINT(x,y);
	
	if (checkPoint(M,temp)){
		setPoint(&M,'-',PosPlayer(M));
		PosXPlayer(M) = Absis(temp);
		PosYPlayer(M) = Ordinat(temp);
		setPoint(&M,'P',PosPlayer(M));
        Map(P) = M;
	}else printf("That place is occupied");
}

adrNode SearchPlayer(Graph GM){
  adrNode P = First(GM);
  while(P != Nil && !isPlayerHere(Map(P))){
      P = NextGraph(P);
  }
  return P;
}

int main() {
	Graph g;
	CreateGraphMap(&g);
	PrintCurrMap(g);
    move('a',&g);
    PrintCurrMap(g);
}

