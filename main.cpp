#include <fstream>
#include <iterator>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <stdlib.h>
#include <cmath>

using namespace std;
ifstream cin("a.in");
ofstream cout("a.out");
ofstream fout("b.out");
ofstream gout("c.out");
char linie[220];
map <string,string> Var;
map <string,string> :: iterator it;


bool opens(char* p);
bool closes(char* p);

/// doar pentru interpretare cod
void interpret(char *&p);
void numar(char *p,string &thenr);
void skipspace(char *&p);
void variabila_op(char *&p, string &name);
bool scan(char *&p);

bool casecondition(char *&p, string &cond);
bool repetacondition(char *&p, string &cond);
bool panacandcondition(char *&p, string &cond);
bool switchcondition(char *&p, string &cond);
bool ifcondition(char *&p, string &cond);
bool elsecondition(char *&p, string &cond);
bool newvalueof(char *&p, string &name, string &nr);
bool print(char *&p);
void variabila(char *&p, string &name, bool ok);
bool whilecondition(char *&p, string &cond);
bool forcondition(char *&p, string &cond);
///
inline void string_to_char(char siraux[100], string AUX);
inline void dfs_tree(char * &a, int id);
int erori=0;
bool operator_(char ch);

int dad_proccess[100100];

int nrElemente, nrLinii = -1;
int height=600, width=800;

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

struct buton
{
    dreptunghi D;
    int culoare;
    char text[20];
};

buton B[4], M[3];
int nrButoane=3;

struct nod
{
    int ordine;
    int linie;
    char informatie[100]; /// ce se afiseaza
    nod* copii[10];
    int InstrCases[110]; /// cate ce am vorbit de fiecare caz
    char condCases[110][110];
    int nrCopii=0;
    int xStanga=100, xDreapta=900;
    /// 1: atribuire, 2: scan, 3: print, 4: if, 5: while, 6: for
    int tip; //0-instr simpla 1 for/while 2 if 3 do while 4 switch case
    int InstrElse=0,cazDefault=0; // pt if else si case
};
struct each_line
{
    string name;
    nod treaba_mea;
    //string proccesses[11];
    //string cases[11]; /// daca e switch da inca nu merge
    int type; /// 1: atribuire, 2: scan, 3: print, 4: if, 5: while, 6: for, 7:switch, 8:case 9:else
};
int viz[100100];
int CODCUERORI;
void adaugaFiu_v2(nod* &a, char s[100], int id);
vector <int> Each_level[10010];

int Ind_pe_nivel[11111];
inline void dfs_debug(nod * &Aa);
inline void make_tree();
void dfs_init_NIV(int node_curr);
void transform_in_arbore_else();
vector <each_line> Lines;
vector <int> edges[100100];
void dfs_parginv(int nodulet);
vector <int> parginv;
int NIV_init[1001001];
nod* radacina = new nod;
int root=1;
char auxlinie[11100];
void transform_in_arbore_switch();
void transform_in_arbore_dowhile();
inline void buildnecessities();
inline void scan_of_initial_file();
void mainAdia();


bool apartine(punct P, dreptunghi D);
void deseneazaMeniul();
void deseneazaButoane();
int butonAles();
int derulare();
int inapoiLaMeniu();
void contur();
void fundal();
void adaugaFiu(nod* &a, char s[100]);
int dfs(nod* a);
void numarareLinii(nod* &a);
void incadrareCopii(nod* &a);
void linieMaxima(nod* a, int &x);
void desen(nod* a);
void desen1(nod* a);
void desen2(nod* a);
void desen3(nod* a);
void desen4(nod* a);
void scrie(nod* a);
void deseneaza(nod* a);
void parcurgere(nod* a, int x);
void ruleaza();

int main()
{
    mainAdia();
    ruleaza();
    return 0;
}

bool apartine(punct P, dreptunghi D)
{
    return D.SS.x<=P.x && P.x<=D.DJ.x && D.SS.y<=P.y && P.y<=D.DJ.y;
}

void deseneazaMeniul()
{
    setlinestyle(0,1,3);
    setfillstyle(SOLID_FILL,BLACK);
    for (int i=1; i<=nrButoane; i++)
    {
        B[i].D.SS.x = 400;
        B[i].D.DJ.x = 600;
        B[i].D.SS.y= 260 + (i - 1)*70 ;
        B[i].D.DJ.y= 260 + (i-1)*70 + 60;
        switch(i)
        {
        case 1:
            strcpy(B[i].text,"Diagrama");
            break;
        case 2:
            strcpy(B[i].text,"Cod");
            break;
        case 3:
            strcpy(B[i].text,"Iesire");
            break;
        }
        setcolor(BLUE);
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        //bar(B[i].D.SS.x,B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        setbkcolor(BLACK);
        setcolor(RED);
        settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
        settextjustify(1,1);
        outtextxy(B[i].D.SS.x+100,B[i].D.SS.y+40,B[i].text);
    }
    setlinestyle(0,1,1);
}

void deseneazaButoane()
{
    setfillstyle(SOLID_FILL, BLACK);
    M[0].D.SS.x = 250;
    M[0].D.DJ.x = 450;
    M[0].D.SS.y= 20;
    M[0].D.DJ.y= 80;

    M[1].D.SS.x = 550;
    M[1].D.DJ.x = 750;
    M[1].D.SS.y= 20;
    M[1].D.DJ.y= 80;

    M[2].D.SS.x = 920;
    M[2].D.DJ.x = 980;
    M[2].D.SS.y= 300;
    M[2].D.DJ.y= 500;

    setcolor(BLUE);
    for(int i=0;i<=2;i++)
        rectangle(M[i].D.SS.x, M[i].D.SS.y,M[i].D.DJ.x,M[i].D.DJ.y);
    setbkcolor(BLACK);
    setcolor(RED);
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    outtextxy(M[0].D.SS.x+100,M[0].D.SS.y+40, "Sus");
    outtextxy(M[1].D.SS.x+100,M[1].D.SS.y+40, "Jos");
    settextstyle(EUROPEAN_FONT, VERT_DIR, 4);
    outtextxy(M[2].D.DJ.x - 20, M[2].D.DJ.y - 95, "Meniu");
}

int butonAles()
{
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x=mousex();
        p.y=mousey();
        for (int i=1; i<=nrButoane; i++)
            if (apartine(p,B[i].D))
                return i;
    }
    return 0;
}

int derulare()
{
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        if(p.x >= 250 && p.x <= 450 && p.y >= 20 && p.y <= 80)
            return 1;
        if(p.x >= 550 && p.x <= 750 && p.y >= 20 && p.y <= 80)
            return -1;
    }
    return 0;
}

int inapoiLaMeniu()
{
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        if(p.x >= 920 && p.x <= 980 && p.y >= 260 && p.y <= 460)
            return 1;
    }
    return 0;
}

void contur()
{
    setcolor(WHITE);
    line(100,100,900,100);
    line(900,100,900,700);
    line(900,700,100,700);
    line(100,700,100,100);
}

void fundal()
{
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,1000,100);
    bar(0,701,1000,720);
}

int dfs(nod* a)
{
    if(a==NULL)
        return 0;
    else
    {
        int x=0;
        if(a->tip == 2)
        {
            int liniiIf=0,liniiElse=0;
            for(int i=1;i<=a->nrCopii-(a->InstrElse);i++)
                liniiIf+=1+dfs(a->copii[i]);
            for(int i=a->nrCopii-(a->InstrElse)+1;i<=a->nrCopii;i++)
                liniiElse+=1+dfs(a->copii[i]);
            x = max(liniiIf,liniiElse);
            return x;
        }
        if(a->tip == 4)
        {
            int liniiCazuri[10]={0};
            int k=1;
            for(int i=1;i<=a->InstrCases[0];i++)
            {
                int j;
                for(j=k;j<=a->InstrCases[i] + k -1;j++)
                    liniiCazuri[i]+=1+dfs(a->copii[j]);
                k=j;

            }
            int maximLinii=liniiCazuri[1];
            for(int i=2;i<=a->InstrCases[0];i++)
                if(liniiCazuri[i]>maximLinii)
                    maximLinii=liniiCazuri[i];
            return maximLinii;
        }
        if(a->tip == 3 && a->nrCopii == 0)
            ++x;
        for(int i=1;i<=a->nrCopii;i++)
        {
            if(a->copii[i]->tip == 4 && a->copii[i]->nrCopii > 2)
                x+=2+dfs(a->copii[i]);
            else
                x+=1+dfs(a->copii[i]);
        }
        return x;
    }
}

void numarareLinii(nod* &a)
{
    if(a!=NULL)
    {
        switch(a->tip)
        {
        case 1:
        {
            ++nrLinii;
            a->linie=nrLinii;
            for(int i=1;i<=a->nrCopii;i++)
                numarareLinii(a->copii[i]);
            break;
        }
        case 2:
        {
            ++nrLinii;
            a->linie=nrLinii;
            int x = nrLinii;
            for(int i=1;i<=a->nrCopii-(a->InstrElse);i++)
                numarareLinii(a->copii[i]);
            int y = nrLinii;
            nrLinii = x;
            for(int i=a->nrCopii-(a->InstrElse)+1;i<=a->nrCopii;i++)
                numarareLinii(a->copii[i]);
            nrLinii = max(y,nrLinii);
            break;
        }
        case 3:
        {
            for(int i=1;i<=a->nrCopii;i++)
                numarareLinii(a->copii[i]);
            if(a->nrCopii == 0)
            {
                nrLinii+=2;
                a->linie=nrLinii;
            }
            else
            {
                ++nrLinii;
                a->linie=nrLinii;
            }
            break;
        }
        case 4:
        {
            if(a->nrCopii > 2)
            {
                nrLinii+=2;
                a->linie = nrLinii - 1;
            }
            else
            {
                nrLinii++;
                a->linie = nrLinii;
            }
            int x = nrLinii;
            int nrLiniiMax = nrLinii;
            int k=1;
            for(int i=1;i<=a->InstrCases[0];i++)
            {
                int j;
                for(j=k;j<=a->InstrCases[i] + k -1;j++)
                    numarareLinii(a->copii[j]);
                k=j;
                if(nrLinii>nrLiniiMax)
                    nrLiniiMax=nrLinii;
                nrLinii=x;
            }
            nrLinii=nrLiniiMax;
            break;
        }
        default:
        {
            ++nrLinii;
            a->linie=nrLinii;
            for(int i=1;i<=a->nrCopii;i++)
                numarareLinii(a->copii[i]);
        }
        }
    }
}

void incadrareCopii(nod* &a)
{
    if(a!=NULL)
    {
        switch(a->tip)
        {
        case 1:
        {
            for(int i=1;i<=a->nrCopii;i++)
            {
                a->copii[i]->xStanga = a->xStanga+width/35;
                a->copii[i]->xDreapta = a->xDreapta;
                incadrareCopii(a->copii[i]);
            }
            break;
        }
        case 2:
        {
            for(int i=1;i<=a->nrCopii-(a->InstrElse);i++)
            {
                a->copii[i]->xStanga = a->xStanga;
                a->copii[i]->xDreapta = a->xStanga + (a->xDreapta - a->xStanga)/2;
                incadrareCopii(a->copii[i]);
            }
            for(int i=a->nrCopii-(a->InstrElse)+1;i<=a->nrCopii;i++)
            {
                a->copii[i]->xStanga = a->xStanga + (a->xDreapta - a->xStanga)/2;
                a->copii[i]->xDreapta = a->xDreapta;
                incadrareCopii(a->copii[i]);
            }
            break;
        }
        case 3:
        {
            for(int i=1;i<=a->nrCopii;i++)
            {
                a->copii[i]->xStanga = a->xStanga+width/35;
                a->copii[i]->xDreapta = a->xDreapta;
                incadrareCopii(a->copii[i]);
            }
            break;
        }
        case 4:
        {
            if(a->nrCopii>0)
            {
                int y = a->InstrCases[0];
                int latimeColoana = (a->xDreapta - a->xStanga) / y;
                int k=1;
                for(int i=1;i<=y;i++)
                {
                    int j;
                    for(j=k;j<= a->InstrCases[i] + k - 1;j++)
                    {
                        a->copii[j]->xStanga = a->xStanga + (i-1)*latimeColoana;
                        a->copii[j]->xDreapta = a->xStanga + i*latimeColoana;
                        incadrareCopii(a->copii[j]);
                    }
                    k=j;
                }
            }
            break;
        }
        default:
        {
            for(int i=1;i<=a->nrCopii;i++)
            {
                a->copii[i]->xStanga = a->xStanga;
                a->copii[i]->xDreapta = a->xDreapta;
                incadrareCopii(a->copii[i]);
            }
        }
        }
    }
}

void linieMaxima(nod* a, int &x)
{
    if(a!=NULL)
    {
        if(a->linie > x)
            x = a->linie;
        for(int i=1;i<=a->nrCopii;i++)
            linieMaxima(a->copii[i],x);
    }
}

void desen(nod* a)
{
    setcolor(WHITE);
    line(a->xStanga, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*(a->linie - 1));
    line(a->xStanga, 100 + height/15*a->linie, a->xDreapta, 100 + height/15*a->linie);

    line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*a->linie);
    line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*a->linie);
}

void desen1(nod* a)
{
        setcolor(WHITE);
        line(a->xStanga, 100 + height/15*(a->linie-1), a->xDreapta, 100 + height/15*(a->linie-1));
        line(a->xStanga,100 + height/15*(a->linie+dfs(a)), a->xDreapta, 100 + height/15*(a->linie+dfs(a)));
        line(a->xStanga+width/35, 100 + height/15*a->linie, a->xStanga+width/35, 100 + height/15*(a->linie + dfs(a)));
        line(a->xStanga+width/35, 100 + height/15*a->linie, a->xDreapta, 100 + height/15*a->linie);

        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*a->linie);
        line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*a->linie);
}

void desen2(nod* a)
{
        setcolor(WHITE);
        line(a->xStanga, 100 + height/15*(a->linie-1), a->xDreapta, 100 + height/15*(a->linie-1));
        line(a->xStanga, 100 + height/15*a->linie, a->xDreapta, 100 + height/15*a->linie);
        line(a->xStanga, 100 + height/15*(a->linie + dfs(a)), a->xDreapta, 100 + height/15*(a->linie + dfs(a)));
        int xMijl = a->xStanga + (a->xDreapta - a->xStanga)/2;

        line(a->xStanga, 100 + height/15*(a->linie-1), xMijl, 100 + height/15*a->linie);
        line(xMijl, 100 + height/15*a->linie, a->xDreapta, 100 + height/15*(a->linie-1));
        line(xMijl, 100 + height/15*a->linie, xMijl, 100 + height/15*(a->linie + dfs(a)));

        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*a->linie);
        line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*a->linie);
}

void desen3(nod* a)
{
    setcolor(WHITE);
    if(a->nrCopii)
    {
        line(a->xStanga, 100 + height/15*(a->copii[1]->linie - 1), a->xDreapta, 100 + height/15*(a->copii[1]->linie - 1));
        line(a->xStanga, 100 + height/15*(a->linie), a->xDreapta, 100 + height/15*(a->linie));
        line(a->xStanga+width/35, 100 + height/15*(a->copii[1]->linie - 1), a->xStanga+width/35, 100 + height/15*(a->linie - 1));
        line(a->xStanga+width/35, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*(a->linie - 1));
    }
    else
    {
        line(a->xStanga, 100 + height/15*(a->linie - 2), a->xDreapta, 100 + height/15*(a->linie - 2));
        line(a->xStanga, 100 + height/15*(a->linie), a->xDreapta, 100 + height/15*(a->linie));
        line(a->xStanga+width/35, 100 + height/15*(a->linie - 2), a->xStanga+width/35, 100 + height/15*(a->linie - 1));
        line(a->xStanga+width/35, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*(a->linie - 1));
    }
    line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*a->linie);
    line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*a->linie);
}

void desen4(nod* a)
{
    setcolor(WHITE);
    if(a->nrCopii > 2)
    {
        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*(a->linie-1));
        line(a->xStanga, 100 + height/15*(a->linie + 1), a->xDreapta, 100 + height/15*(a->linie + 1));
        line(a->xStanga, 100 + height/15*(a->linie + 1 + dfs(a)), a->xDreapta, 100 + height/15*(a->linie + 1 + dfs(a)));

        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga +(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault), 100 + height/15*(a->linie + 1));
        line(a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault), 100 + height/15*(a->linie + 1), a->xDreapta, 100 + height/15*(a->linie - 1));
        for(int i=1;i<a->nrCopii;i++)
        {
            line(a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*i, 100 + height/15*(a->linie - 1), a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*i, 100 + height/15*(a->linie + 1 + dfs(a)));
        }
        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*(a->linie + 1));
        line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*(a->linie + 1));
    }
    else
    {
        line(a->xStanga, 100 + height/15*(a->linie-1),a->xDreapta, 100 + height/15*(a->linie-1));
        line(a->xStanga, 100 + height/15*a->linie, a->xDreapta, 100 + height/15*a->linie);
        line(a->xStanga, 100 + height/15*(a->linie+dfs(a)), a->xDreapta, 100 + height/15*(a->linie+dfs(a)));

        line(a->xStanga, 100 + height/15*(a->linie-1), a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault),100 + height/15*(a->linie));
        line(a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault), 100 + height/15*(a->linie), a->xDreapta, 100 + height/15*(a->linie-1));
        for(int i=1;i<a->nrCopii;i++)
        {
            line(a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*i, 100 + height/15*(a->linie - 1), a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*i, 100 + height/15*(a->linie + dfs(a)));
        }
        line(a->xStanga, 100 + height/15*(a->linie - 1), a->xStanga, 100 + height/15*a->linie);
        line(a->xDreapta, 100 + height/15*(a->linie - 1), a->xDreapta, 100 + height/15*a->linie);
    }
}

void scrie(nod* a)
{
    if(a->tip == 2)
    {
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
        //if(a->xDreapta - a->xStanga < 200)
            //settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
        settextjustify(1,1);
        outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/20, 100 + height/15*(a->linie - 1) + height/14*4/5,"Yes");
        outtextxy(a->xDreapta - (a->xDreapta - a->xStanga)/20, 100 + height/15*(a->linie - 1) + height/14*4/5,"No");
    }
    if(a->tip == 4)
    {
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
        int poly[6];
        char caz[2] = "A";
        char litera[2];
        sscanf(caz, "%s", litera);
        settextjustify(1,2);
        if(a->nrCopii > 2)
        {
            poly[0] = a->xStanga;
            poly[1] = 100 + height/15 * (a->linie - 1);
            poly[2] = a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault);
            poly[3] = 100 + height/15*(a->linie + 1);
            poly[4] = a->xDreapta;
            poly[5] = 100 + height/15 * (a->linie - 1);

            setfillstyle(SOLID_FILL,BLACK);
            fillpoly(3,poly);

            if(a->cazDefault)
            {
                outtextxy(a->xDreapta - (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 1) + height/14*4/3,"D");
                for(int i=0;i<a->InstrCases[0] - 1;i++)
                {
                    outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*i + (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 1) + height/14*4/3, litera);
                    litera[0]++;
                }
            }
            else
            {
                for(int i=0;i<a->InstrCases[0];i++)
                {
                    outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*i +  (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 1) + height/14*4/3,litera);
                    litera[0]++;
                }
            }
        }
        else if(a->nrCopii > 0)
        {
            poly[0] = a->xStanga;
            poly[1] = 100 + height/15 * (a->linie - 1);
            poly[2] = a->xStanga+(a->xDreapta - a->xStanga)/(a->InstrCases[0])*(a->InstrCases[0] - a->cazDefault);
            poly[3] = 100 + height/15*a->linie;
            poly[4] = a->xDreapta;
            poly[5] = 100 + height/15 * (a->linie - 1);

            setfillstyle(SOLID_FILL,BLACK);
            fillpoly(3,poly);

            if(a->cazDefault)
            {
                outtextxy(a->xDreapta - (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 1) + height/15/2,"D");
                for(int i=0;i<a->InstrCases[0] - 1;i++)
                {
                    outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*i + (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 1) + height/15/2, litera);
                    litera[0]++;
                }
            }
            else
            {
            for(int i=0;i<a->InstrCases[0];i++)
            {
                outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*i +  (a->xDreapta - a->xStanga)/a->InstrCases[0]/20, 100 + height/15*(a->linie - 2) + height/14*4/3,litera);
                litera[0]++;
            }
            }
        }

    }
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    switch (a->tip)
    {
    case 2:
    {
        //int poly[6];
        //poly[0] = a->xStanga;
        //poly[1] = 100 + height/15*(a->linie - 1);
        //poly[2] = a->xStanga;
        //poly[3] = 100 + height/15*a->linie;
        //poly[4] = a->xStanga + (a->xDreapta - a->xStanga)/2;
        //poly[5] = 100 + height/15*a->linie;
        //setfillstyle(SOLID_FILL,LIGHTRED);
        //fillpoly(3,poly);

        //setbkcolor(LIGHTRED);
        settextjustify(1,1);
        outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/2, 100 + height/15*(a->linie - 1) + height/15*3/5, a->informatie);


        setbkcolor(BLACK);
        setfillstyle(SOLID_FILL,BLACK);
        break;
    }
    case 3:
    {
        settextjustify(1,1);
        outtextxy( a->xStanga + (a->xDreapta - a->xStanga)/2, 100 + height/15*(a->linie - 1) + height/15*7/10, a->informatie);
        break;
    }
    case 4:
    {
        if(a->cazDefault)
        {
            settextjustify(1,1);
            if(a->nrCopii > 2)
                outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*(a->InstrCases[0] - 1), 100 + height/15*a->linie, a->informatie);
            else
                outtextxy(a->xStanga + (a->xDreapta - a->xStanga)/a->InstrCases[0]*(a->InstrCases[0] - 1), 100 + height/15*(a->linie - 1) + height/15*3/5, a->informatie);
        }
        else
        {
            settextjustify(1,1);
            if(a->nrCopii > 2)
                outtextxy(a->xDreapta - (a->xDreapta - a->xStanga)/a->InstrCases[0]/2 , 100 + height/15*a->linie - height/15/5, a->informatie);
            else
                outtextxy(a->xDreapta - (a->xDreapta - a->xStanga)/a->InstrCases[0]/2 , 100 + height/15*(a->linie - 1) + height/15*3/5, a->informatie);
        }
        break;
    }
    default:
    {
        //int poly[8];
        //poly[0] = a->xStanga;
        //poly[1] = 100 + height/15*(a->linie - 1);
        //poly[2] = a->xStanga;
        //poly[3] = 100 + height/15*a->linie;
        //poly[4] = a->xDreapta;
        //poly[5] = 100 + height/15*a->linie;
        //poly[6] = a->xDreapta;
        //poly[7] = 100 + height/15*(a->linie - 1);
        //setfillstyle(SOLID_FILL,LIGHTBLUE);
        //fillpoly(4,poly);

        //setbkcolor(LIGHTBLUE);
        settextjustify(1,1);
        outtextxy( a->xStanga + (a->xDreapta - a->xStanga)/2, 100 + height/15*(a->linie - 1) + height/15*7/10, a->informatie);

        setbkcolor(BLACK);
        setfillstyle(SOLID_FILL,BLACK);
    }
    }
}

void deseneaza(nod* a)
{
    if(CODCUERORI == 1)
    {
        setbkcolor(BLACK);
        setcolor(WHITE);
        settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
        settextjustify(1,1);
        outtextxy(500,400, "CODUL CONTINE ERORI!");

        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
        settextjustify(1,1);
    }
    if(a!=NULL && CODCUERORI == 0)
    {
        /*if(a->linie <= 0 && a->tip > 0)
        {
            if(dfs(a) + a->linie > 0)
            {
                int nrLiniiDiferenta = dfs(a) + a->linie;
                if(a->tip == 1)
                    line(a->xStanga+width/35, 100, a->xStanga+width/35, 100 + height/15*nrLiniiDiferenta);
                if(a->tip == 2)
                    line(a->xStanga, 100, a->xStanga, 100 + height/15*nrLiniiDiferenta);
                if(a->tip == 4)
                {
                    if(a->nrCopii > 2)
                        line(a->xStanga, 100, a->xStanga, 100 + height/15*(nrLiniiDiferenta + 1));
                    else
                    {
                        if(a->nrCopii > 0)
                            line(a->xStanga, 100, a->xStanga, 100 + height/15*nrLiniiDiferenta);
                    }
                }

            }
        }*/
        if( a->linie <= 15 || (a->linie == 0 && a->tip == 4 && a->nrCopii > 2))
        {
            switch(a->tip)
            {
            case 1:
            {
                desen1(a);
                break;
            }
            case 2:
            {
                desen2(a);
                break;
            }
            case 3:
            {
                desen3(a);
                break;
            }
            case 4:
            {
                desen4(a);
                if(a->linie == 0 && a->nrCopii > 2)
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(0,0,1000,100);
                }
                if(a->linie == 15)
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(0,701,1000,720);
                }

                break;
            }
            default:
                desen(a);
            }
            scrie(a);
            for(int i=1;i<=a->nrCopii;i++)
                deseneaza(a->copii[i]);
        }
        else
        {
            for(int i=1;i<=a->nrCopii;i++)
                deseneaza(a->copii[i]);
        }
    }
}

void parcurgere(nod* a, int x)
{
    if(a!=NULL)
    {
        a->linie+=x;
        for(int i=1;i<=a->nrCopii;i++)
            parcurgere(a->copii[i],x);
    }
}

void stergeArbore(nod *a)
{
    if(a!=NULL)
    {
        for(int i=0;i<a->nrCopii;i++)
            stergeArbore(a->copii[i]);
        delete a;
    }
}

void ruleaza()
{
    numarareLinii(radacina);
    incadrareCopii(radacina);

    initwindow(1000, 720);
    deseneazaMeniul();
    int comanda, butonul_apasat, meniu;
    do
    {
        butonul_apasat=butonAles();
        if(butonul_apasat == 1)
        {
            cleardevice();
            deseneaza(radacina);
            contur();
            fundal();
            deseneazaButoane();
            int directie;
            do{
            directie = derulare();
            if(directie == 1 && radacina->linie < 0)
            {
                parcurgere(radacina,directie);
                cleardevice();
                deseneaza(radacina);
                contur();
                fundal();
                deseneazaButoane();
            }
            if(directie == -1)
            {
                int ultimaLinie = 0;
                linieMaxima(radacina,ultimaLinie);
                if(ultimaLinie > 15)
                {
                    parcurgere(radacina,directie);
                    cleardevice();
                    deseneaza(radacina);
                    contur();
                    fundal();
                    deseneazaButoane();
                }
            }
            meniu = inapoiLaMeniu();
            if(meniu)
            {
                cleardevice();
                deseneazaMeniul();
            }
            }while(!meniu);
        }
        if(butonul_apasat == 2)
        {
            FILE *fptr;
            fptr = fopen("C:\\Users\\adria\\OneDrive\\Desktop\\IPproiect\\codAdia\\a.in","w");
            if(fptr == NULL)
            {
                printf("Error!");
                exit(1);
            }
            char s[220];
            printf("%s\n","Introduceti codul: ");
            while (1) {
                if (fgets(s, 220, stdin) == NULL)
                printf("Input Error...\n");
            else {
                char* q;
                for (q = s; (*q != '\n') && isspace(*q); q++)
                    ;
                if (*q == '\n')
                    break;
                else
                    fputs(s,fptr);
                }
            }
            fclose(fptr);
            closegraph();
            printf("%s\n","Codul a fost introdus");
        }
    }
    while (butonul_apasat!=3);
    //getch();
    closegraph();
}


inline void buildnecessities()
{
    for(int i=2; i<Lines.size(); ++i)
        edges[dad_proccess[i]].push_back(i);

    NIV_init[0]=0;
    dfs_init_NIV(0);

    Ind_pe_nivel[0]=0;
    Each_level[0].push_back(0);
    for(int i=2; i<Lines.size(); i++)
    {
        Each_level[NIV_init[i]].push_back(i);
        Ind_pe_nivel[i]=Each_level[NIV_init[i]].size()-1;
    }

}


inline void scan_of_initial_file()
{
    dad_proccess[1]=0;
    int ind=2, ok=0;
    Lines.push_back({"linielibera",0});
    Lines.push_back({"linielibera",0});

    int clk=0, nropen=0; /// clk=0 daca executa in acelasi fir mai multe instr, 1 daca doar 1; nropen= nr {

    root=0;
    while(cin.getline(linie,220))
    {
        strcpy(auxlinie,linie);
        char *ptr, *cptr;

        ptr=linie;
        cptr=ptr;

        if(closes(cptr))
        {
            nropen--;
            if(clk==1 || nropen<=0)
            {

                    CODCUERORI=1;
                    gout<<erori<< "> ";
                    gout << __LINE__ <<endl;
                    erori++;

                fout<<"}"<<'\n';

            }
            else
            {
                root=dad_proccess[root];
                clk=0;
            }
            ptr++;
        }
        if(Lines.size()>0 && (Lines[Lines.size()-1].type>=4))
        {
            if(opens(cptr))
            {
                nropen++;
                clk=0;
                skipspace(ptr);
                ptr++;
            }
            else
                clk=1;
            //cout<<"!> "<<ok<<" "<<ptr<<'\n';
            root=ind-1;
        }
        interpret(ptr);
        if(clk==1)
        {
            dad_proccess[ind]=root;
            clk=0;
            root=dad_proccess[root];
        }
        else
        {
            dad_proccess[ind]=root;
        }
        ind++;
    }
    if(nropen!=0)
    {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        gout<<"{"<<'\n';
    }
}


queue <int> qids;

void dfs_init_NIV(int node_curr)
{
    for(auto nxt_node:edges[node_curr])
    {
        NIV_init[nxt_node]=NIV_init[node_curr]+1;
        dfs_init_NIV(nxt_node);
    }
}
void dfs_parginv(int nodulet)
{
    for(auto nxt: edges[nodulet])
        dfs_parginv(nxt);
    parginv.push_back(nodulet);
}

void transform_in_arbore_dowhile()
{
    parginv.clear();
    dfs_parginv(0);

    int node_do=0;
    for(auto i: parginv)
        if(Lines[i].type==-1)
        {
             node_do=Each_level[NIV_init[i]][Ind_pe_nivel[i]-1];
             Lines[node_do].name=Lines[node_do].name+" "+Lines[i].name;
             ///am atasat conditia la do
             ///acum sterg nod ul cu conditia
             Lines[i].name="linielibera";

             int tata_i=dad_proccess[i];
                for(int j=0; j<edges[tata_i].size(); j++)
                    if(edges[tata_i][j]==i)
                    {
                        for(int k=j+1; k<edges[tata_i].size(); k++)
                            edges[tata_i][k-1]=edges[tata_i][k];
                        edges[tata_i].pop_back();
                        break;
                    }
                ///scot nod ul cu conditia din tatal lui (cum ar veni cel cu pana cand)
                edges[i].clear();
        }
}

void transform_in_arbore_else()
{
// am verificat Ind_pe_nivel si Each_level si sunt corecte
///
    int node_if;
    int nrchildren=0;
    ///intai caut else urile
    parginv.clear();
    dfs_parginv(0);

    for(auto i: parginv)
        if(Lines[i].type==9) ///atunci e else :0
        {
            //gout<<i<<'\n'; corect
            ///if ul de care e legat e fix in stanga lui pe nivel din costr arb
            ///bag tot subarb else in if da numar copii lui else
            /// nr copii else = edges[i].size() 🙂
            Lines[i].name="linielibera"; ///ii neg existenta else ului ca sa nu il adaug in arb
            ///acum ii pun copii la if
            node_if=Each_level[NIV_init[i]][Ind_pe_nivel[i]-1];

            if(node_if<0)
            {
                CODCUERORI=1;
                gout<<erori<< "> ";
                gout << __LINE__ <<endl;
                erori++;
            }
            else
            {
                nrchildren=0;
                for(int j=0; j<edges[i].size(); j++)
                    if(Lines[edges[i][j]].type)
                    {
                        nrchildren++;
                        edges[node_if].push_back(edges[i][j]);
                        dad_proccess[edges[i][j]]=node_if;

                    }

                Lines[node_if].treaba_mea.InstrElse=nrchildren;
                gout<<node_if<<' '<<nrchildren<<'\n';
                ///pun copii lui else la if

                int tata_i=dad_proccess[i];
                for(int j=0; j<edges[tata_i].size(); j++)
                    if(edges[tata_i][j]==i)
                    {
                        for(int k=j+1; k<edges[tata_i].size(); k++)
                            edges[tata_i][k-1]=edges[tata_i][k];
                        edges[tata_i].pop_back();
                        break;
                    }
                ///scot nod ul cu else din tatal lui
                edges[i].clear();
            }
        }

}

void transform_in_arbore_switch()
{
    char sirulet[110];
    vector <int> edges_aux;
    int indcase, nrchildcases;

    parginv.clear();
    dfs_parginv(0);

    for(auto i:parginv)
        if(Lines[i].type==7)
        {
            edges_aux.clear();
            indcase=1;
            nrchildcases=0;
            for(auto nxt_node:edges[i])
                if(Lines[nxt_node].type==8)
                {
                    sirulet[0]='\0';
                    nrchildcases=0;
                    for(auto childcase:edges[nxt_node])
                        if(Lines[childcase].type!=0)
                        {
                            nrchildcases++;
                            if(Lines[childcase].name.find("default")!=0)
                                Lines[i].treaba_mea.cazDefault=1;
                            edges_aux.push_back(childcase);
                        }
                    string_to_char(sirulet,Lines[nxt_node].name);
                    strcpy(Lines[i].treaba_mea.condCases[indcase],sirulet);
                    Lines[i].treaba_mea.InstrCases[indcase]=nrchildcases;
                    edges[nxt_node].clear();
                    indcase++;
                }
            if(indcase==1)
            {
                CODCUERORI=1;
                gout<<erori<< "> ";
                gout << __LINE__ <<endl;
                erori++;
            }
            Lines[i].treaba_mea.InstrCases[0]=indcase-1;
            edges[i].clear();
            for(auto node:edges_aux)
                edges[i].push_back(node);
        }
}
inline void string_to_char(char siraux[100], string AUX)
{
    for(int i=0; i<AUX.length(); ++i)
    {
        siraux[i]=AUX[i];
        siraux[i+1]='\0';
    }

}

inline void dfs_tree(nod * &Aa, int id)
{
    char siraux[100];
    for(auto nxtnod:edges[id])
        if(!viz[nxtnod])
        {
            viz[nxtnod]=1;
            siraux[0]=NULL;
            string_to_char(siraux,Lines[nxtnod].name);
            if(!strstr(siraux,"linielibera"))
            {

                adaugaFiu_v2(Aa,siraux,nxtnod);
                dfs_tree(Aa->copii[Aa->nrCopii], nxtnod);
            }

        }
}

inline void dfs_debug(nod * &Aa)
{
    char siraux[100];
    fout<<Aa->informatie<<' '<<Aa->tip<<">  ";
    for(int i=1; i<=Aa->nrCopii; ++i)
        fout<<(Aa->copii[i])->informatie<<" | ";
    if(Aa->tip==2)
        fout<<endl<<"IF "<<Aa->InstrElse<<'\n';
    if(Aa->tip==4)
    {
        fout<<endl<<"SWITCH "<<Aa->InstrCases[0]<<" => ";
        for(int i=1; i<=Aa->InstrCases[0]; ++i)
            fout<<Aa->InstrCases[i]<<' ';
    }
    fout<<'\n';
    for(int i=1; i<=Aa->nrCopii; ++i)
        dfs_debug(Aa->copii[i]);

}

inline void make_tree()
{
    radacina->ordine=0;
    radacina->linie=-1;
    strcpy(radacina->informatie,"main");
    radacina->nrCopii=0;
    radacina->tip=0;
    radacina->xStanga=100;
    radacina->xDreapta=900;
    qids.push(0);
    viz[0]=1;

    dfs_tree(radacina,0);
    dfs_debug(radacina);

}

void adaugaFiu_v2(nod* &a, char s[100], int id)
{
    ++nrElemente;

    ++a->nrCopii;
    a->copii[a->nrCopii]=new nod;

    a->copii[a->nrCopii]->ordine=nrElemente;
    strcpy(a->copii[a->nrCopii]->informatie,s);
    a->copii[a->nrCopii]->nrCopii=0;
    a->copii[a->nrCopii]->cazDefault=Lines[id].treaba_mea.cazDefault;
    a->copii[a->nrCopii]->InstrElse=Lines[id].treaba_mea.InstrElse;

    if(strstr(a->copii[a->nrCopii]->informatie,"if"))
    {
        a->copii[a->nrCopii]->tip=2;
    }
    else if(strstr(a->copii[a->nrCopii]->informatie,"for") || strstr(a->copii[a->nrCopii]->informatie,"while"))
    {
        a->copii[a->nrCopii]->tip=1;
    }
    else if(strstr(a->copii[a->nrCopii]->informatie,"do"))
    {
        a->copii[a->nrCopii]->tip=3;
    }
    else if(strstr(a->copii[a->nrCopii]->informatie,"switch"))
    {
        a->copii[a->nrCopii]->tip=4;
        for(int i=0; i<=100; ++i)
        {
            a->copii[a->nrCopii]->InstrCases[i]=Lines[id].treaba_mea.InstrCases[i];
            strcpy(a->copii[a->nrCopii]->condCases[i],Lines[id].treaba_mea.condCases[i]);
        }
        //gout<<id<<' '<<a->copii[a->nrCopii]->InstrCases[0]<<'\n';
    }
    else if(!strstr(a->copii[a->nrCopii]->informatie,"linielibera"))
    {
        // a->nrCopii--;
        a->copii[a->nrCopii]->tip=0;
    }
    else a->nrCopii--;
}
bool opens(char * p)
{
    skipspace(p);
    if(*p =='{')
        return 1;
    return 0;
}

bool closes(char *p)
{
    skipspace(p);
    if(*p =='}')
        return 1;
    return 0;
}

each_line currline;

void interpret(char *&p)
{
    char *c;
    int k=0;
    c=p;
    //// currline.nrCopii=0;
    // for(int i=0; i<10; i++)
    //   currline.cases[i].clear();
    if(scan(c))
    {
        string nume;
        nume[0]='\0';
        variabila(c,nume,0);
        //cout<<"scan "<<nume<<'\n';
        currline.name="scan "+ nume;
        currline.type=2;
        Lines.push_back(currline);
        return ;
    }
    c=p;
    if(print(c))
    {
        string nume;
        nume.clear();
        variabila_op(c,nume);
        it=Var.find(nume);
        /*if(it!=Var.end())
            cout<<"print "<<(it->second)<<'\n';
        else cout<<"print "<<nume<<'\n';
        */
        currline.name="print "+ nume;
        currline.type=3;
        Lines.push_back(currline);
        //cout<<"print "<<nume<<'\n';
        return ;
    }
    c=p;
    string nume;
    nume.clear();
    string numarul;
    numarul.clear();
    if(newvalueof(c, nume, numarul))
    {
        variabila_op(c,numarul);
        Var.insert({nume,numarul});
        // cout<<nume<<" becomes "<<numarul<<'\n';

        currline.name=nume+"="+numarul;
        currline.type=1;
        Lines.push_back(currline);
        return ;
    }
    c=p;
    nume.clear();
    if(ifcondition(c,nume))
    {
        // cout<<"daca "<<nume<<" atunci e bine "<<'\n';

        currline.name="if "+nume;
        currline.type=4;
        Lines.push_back(currline);
        return ;
    }

    c=p;
    nume.clear();
    if(whilecondition(c,nume))
    {
        //cout<<"cat timp "<<nume<<" se va repeta "<<'\n';

        currline.name="while "+nume;
        currline.type=5;
        Lines.push_back(currline);
        return ;
    }

    c=p;
    nume.clear();
    if(forcondition(c,nume))
    {
        // cout<<"pentru "<<nume<<" se va repeta "<<'\n';

        currline.name="for "+nume;
        currline.type=6;
        Lines.push_back(currline);
        return ;
    }

    c=p;
    nume.clear();
    if(elsecondition(c,nume))
    {
        currline.name="altfel";
        currline.type=9;
        Lines.push_back(currline);
        return ;
    }

    c=p;
    nume.clear();
    if(switchcondition(c,nume))
    {
        currline.name="switch " + nume;
        currline.type=7;
        Lines.push_back(currline);
        return ;
    }

    c=p;
    nume.clear();
    if(casecondition(c,nume))
    {
        currline.name="case "+ nume;
        currline.type=8;
        Lines.push_back(currline);
        return ;

    }
    c=p;
    nume.clear();
    if(repetacondition(c,nume))
    {
        currline.name="do";
        currline.type=5;
        Lines.push_back(currline);
        return ;

    }
    c=p;
    nume.clear();
    if(panacandcondition(c,nume))
    {
        currline.name=nume;
        currline.type=-1;
        Lines.push_back(currline);
        return ;

    }

    c=p;
    nume.clear();
    if(*p!='\0' && *p!=' ' && *p!='\t' && *p!='}' && *p!='{')
    {
        {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
    }
    else
    {
        skipspace(p );
        if(*p!='\0' && *p!=' ' && *p!='\t' && *p!='}' && *p!='{')
        {
            CODCUERORI=1;
            gout<<p<<'\n';
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
    }
    currline.name="linielibera";
    currline.type=0;
    Lines.push_back(currline);
}

void numar(char *p,string &thenr)
{
    int nr=0;
    skipspace(p);
    thenr.clear();
    while(*p!='\0' && (strchr("0123456789",*p)||operator_(*p)))
    {
        thenr.push_back(*p);
        p++;
    }
}

void skipspace(char *&p)
{
    while(*p!='\0' && *p==' ')
        p++;
}
bool operator_(char ch)
{
    char interzis[16]="+-<>&*()!@#$%^/";
    if(strchr(interzis, ch)!=NULL)
        return 1;
    return 0;
}

void variabila(char *&p, string &name, bool ok)
{
    int lg=0;
    name.clear();
    skipspace(p);
    while(*p!='\0' && *p!=' ' && !operator_(*p))
    {
        name.push_back(*p);
        p++;
    }
    if(ok==0)
        return;
    /*while(*p!='\0' && *p!=',')
        p++;
    if(*p==',')
    {
        p++;
        skipspace(p);
    }*/
}
bool panacandcondition(char *&p, string &cond)
{

    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;

    while(*p!='\0' && lg<4)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"pana"))
    {
        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);

        i[0]='\0';
        lg=0;

        while(*p!='\0' && lg<4)
        {
            i[lg++]=*p;
            p++;
            i[lg]='\0';
        }

        if(strstr(i,"cand"))
        {

            if(*p!='\0' && *p!=' ' && *p!='\t')
                return 0;
            variabila_op(p,cond);
            skipspace(p);

            if(*p!='\0' && *p!=' ' && *p!='\t')
                return 0;
            return 1;
        }
        {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
        return 0;
    }
    return 0;

}
bool repetacondition(char *&p, string &cond)
{
    skipspace(p);

    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<6)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"repeta"))
    {
        skipspace(p);

        skipspace(p);
        while(*p!='\0' && isalpha(*p))
            p++;
        return 1;
    }
    return 0;
}

bool switchcondition(char *&p, string &cond)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<6)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"switch"))
    {
        skipspace(p);
        variabila_op(p,cond);
        skipspace(p);
        if(*p!=' ' && *p!='\0' && *p!='\t' && *p!='\n')
        {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
        return 1;
    }
    return 0;

}


bool casecondition(char *&p, string &cond)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<4)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"case"))
    {
        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);
        variabila_op(p,cond);
        skipspace(p);
        if(*p!=' ' && *p!='\0' && *p!='\t' && *p!='\n')
        {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
        return 1;
    }
    return 0;

}


void variabila_op(char *&p, string &name)
{
    int lg=0;
    name.clear();
    skipspace(p);
    while(*p!='\0' && *p!=' ')
    {
        name.push_back(*p);
        p++;
    }

    return ;
    /*while(*p!='\0' && *p!=',')
        p++;
    if(*p==',')
    {
        p++;
        skipspace(p);
    }*/
}

bool elsecondition(char *&p, string &cond)
{

    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<6)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"altfel"))
    {
        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);

        return 1;
    }
    return 0;

}

bool ifcondition(char *&p, string &cond)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<4)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"daca"))
    {
        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);
        variabila_op(p,cond);
        skipspace(p);

        skipspace(p);
        if(*p!=' ' && *p!='\0' && *p!='\t' && *p!='\n')
        {
            CODCUERORI=1;
            gout<<erori<< "> ";
            gout << __LINE__ <<endl;
            erori++;
        }
        return 1;
    }
    return 0;

}

bool whilecondition(char *&p, string &cond)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;

    while(*p!='\0' && lg<8)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"cat timp"))
    {

        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);
        variabila_op(p,cond);
        skipspace(p);
        while(*p!='\0' && isalpha(*p))
            p++;
        return 1;
    }
    return 0;

}

bool forcondition(char *&p, string &cond)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;

    while(*p!='\0' && lg<7)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"pentru "))
    {

        if(*p!='\0' && *p!=' ' && *p!='\t')
            return 0;
        skipspace(p);
        variabila_op(p,cond);
        skipspace(p);
        while(*p!='\0' && isalpha(*p))
            p++;
        return 1;
    }
    return 0;

}
bool print(char *&p)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(*p!='\0' && lg<6)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(strstr(i,"scrie "))
        return 1;
    return 0;
}
bool scan(char *&p)
{
    skipspace(p);
    char i[10];
    i[0]='\0';
    int lg=0;
    while(lg<8)
    {
        i[lg++]=*p;
        p++;
        i[lg]='\0';
    }
    if(*p!='\0' && strstr(i,"citeste "))
        return 1;
    return 0;
}

bool newvalueof(char *&p, string &name, string &nr)
{
    variabila(p,name,0);
    skipspace(p);
    if(*p=='<' && *(p+1)=='-')
    {
        p+=2;
        return 1;
    }
    return 0;
}

void mainAdia()
{
        scan_of_initial_file();
    for(int i=2; i<Lines.size(); ++i)
    {
        cout<<i<<" "<<Lines[i].name<<"> ";
        for(auto nxt:edges[i])
            cout<<nxt<<' ';
        cout<<'\n';
    }

    buildnecessities();
    transform_in_arbore_dowhile();
    transform_in_arbore_else();
    transform_in_arbore_switch();
    for(int i=0; i<Lines.size(); ++i)
    {
        cout<<i<<" > ";
        for(auto nxt: edges[i])
            cout<<nxt<<' ';
        cout<<endl;
    }


    make_tree();
    gout<<CODCUERORI<<'\n';
    /* */
    /*
        nod *ptr;
        ptr=prim;
        viz[0]=2;
        nod * currnode=new nod;
        qnodes.push()
        while(!qnodes.empty())
        {
            currnode=qnodes.back();
            qnodes.pop();
            cout<<currnode->info<<" "<<Lines[currnode->info].name<<" > ";
            for(int i=1; i<=currnode->nrCopii; ++i)
                if((viz[(currnode->copii[i]).info]==1)
                {
                    viz[(currnode->copii[i]).info]=2;
                    qnodes.push(currnode->copii[i]);
                }
        }*/
}
