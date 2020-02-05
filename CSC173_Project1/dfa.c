#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nfa.h"
#include "IntHashSet.h"
#include "LinkedList.h"
#include <math.h>
DFA new_DFA(int nstates){
    DFA dfa= (DFA)malloc(sizeof(struct DFA));
    dfa->TotalStates=nstates;
    dfa->Accept=(int *)malloc(sizeof(int)*nstates);
    dfa->AcceptIndex=0;
    for(int i=0;i<dfa->TotalStates;i++)
    {
        dfa->TransitionTable[i]=malloc(sizeof(int)*128);
    }
    for(int i=0;i<dfa->TotalStates;i++)
    {
        for(int j=0;j<128;j++)
        {
            dfa->TransitionTable[i][j]=-1;
        }
    }
    return dfa;
}
void DFA_free(DFA dfa)
{
    if(dfa==NULL)
        return;
    for(int i=0;i<dfa->TotalStates;i++)
    {
        int* rowTable=dfa->TransitionTable[i];
        free(rowTable);
    }
    free(dfa->TransitionTable);
    free(dfa->Accept);
    free(dfa);
    return;
}
int DFA_get_size(DFA dfa)
{
    return dfa->TotalStates;
}
int DFA_get_transition(DFA dfa, int src, char sym)
{
     if(src>dfa->TotalStates||src<0)
     {
         printf("%s\n","input error");
         return -1;
     }
    int temp=(int)sym;
    return dfa->TransitionTable[src][temp];
}
void DFA_set_transition(DFA dfa, int src, char sym, int dst)
{
    if(src>dfa->TotalStates||src<0||dst>dfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    int temp=(int)sym;
    dfa->TransitionTable[src][temp]=dst;
    return;
}
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst)
{
    if(src>dfa->TotalStates||src<0||dst>dfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    int length=(int) strlen(str);
    for(int i=0;i<length;i++)
    {
        int temp=(int)str[i];
        dfa->TransitionTable[src][temp]=dst;
    }
}
void DFA_set_transition_all(DFA dfa, int src, int dst)
{
    if(src>dfa->TotalStates||src<0||dst>dfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    for(int i=0;i<128;i++)
    {
        dfa->TransitionTable[src][i]=dst;
    }
}
void DFA_set_accepting(DFA dfa, int state, bool value)
{
    if(value==0)
        return;
    if(state<0||state>dfa->TotalStates)
        return;
    dfa->Accept[dfa->AcceptIndex]=state;
    dfa->AcceptIndex++;
}
bool DFA_get_accepting(DFA dfa, int state)
{
    for(int i=0;i<dfa->AcceptIndex;i++)
    {
        if(dfa->Accept[i]==state)
            return 1;
    }
    return 0;
}
bool DFA_execute(DFA dfa, char *input)
{
    int temp=DFA_get_transition(dfa, 0, input[0]);
    int length=(int)strlen(input);
    for(int i=1;i<length;i++)
    {
        temp=DFA_get_transition(dfa, temp, input[i]);
        if(temp==-1)
            return false;
    }
    return DFA_get_accepting(dfa, temp);
}
void DFA_print(DFA dfa)
{
    printf("DFA printing\n It has %d states\n with following acctping states:",dfa->TotalStates);
    for (int i = 0; i < dfa->TotalStates; i++)
    {
        if(dfa->TransitionTable[i])
            printf("%d ",i );
    }
    printf("\n");
    printf("Print transition\n");
    printf("State 1 ---input---> State 2");
    for (int i = 0; i < DFA_get_size(dfa); i++)
    {
        for (int j = 0; j < 128; j++)
        {
            printf("State %d ---    %c---> State %d",i,j, dfa->TransitionTable[i][j] );
            printf("\n");
        }
    }
}
bool ifContains(LinkedList list,IntHashSet set){//find if the list contain the set and return boolean
    LinkedListIterator iterator = LinkedList_iterator(list);
    while (LinkedListIterator_hasNext(iterator)) {
        IntHashSet temp = LinkedListIterator_next(iterator);
        if(IntHashSet_equals(temp,set)){
            free(iterator);
            return 1;
        }
    }
    free(iterator);
    return 0;
}
int findindex(LinkedList list, IntHashSet set){//find the set in the list and return the count number
    int count=0;
    LinkedListIterator iterator = LinkedList_iterator(list);
    while (LinkedListIterator_hasNext(iterator)) {
        IntHashSet temp = LinkedListIterator_next(iterator);
        if(IntHashSet_equals(temp,set)==true){
            free(iterator);
            return count;
        }
        count++;
    }
    free(iterator);
    return -1;
}

DFA Convert(NFA nfa)
{
    DFA this=(DFA)malloc(sizeof(struct DFA));
    this->TotalStates=(int)pow(2,nfa->TotalStates);
    this->Accept=(int *)malloc(this->TotalStates*sizeof(int));
    this->AcceptIndex=0;
    for(int i=0;i<this->TotalStates;i++){
        this->TransitionTable[i]=malloc(128*sizeof(int));
    }
    for(int i=0;i<this->TotalStates;i++){
        for(int x=0;x<128;x++){
            this->TransitionTable[i][x]=-1;
        }
    }
    IntHashSet temp=new_IntHashSet(nfa->TotalStates);
    IntHashSet result=new_IntHashSet(nfa->TotalStates);
    IntHashSet start=new_IntHashSet(nfa->TotalStates);
    
    LinkedList Transfer=new_LinkedList();
    int count=0;
    IntHashSet_insert(start,0);
    LinkedList_add_at_end(Transfer,start);
    
    LinkedListIterator iterator1 = LinkedList_Reverse_iterator(Transfer);
    
    while (LinkedListIterator_hasNext(iterator1)){
        temp=LinkedListIterator_next(iterator1);
        IntHashSetIterator iterator2 = IntHashSet_iterator(temp);
        IntHashSetIterator iterator3 = IntHashSet_iterator(result);
        for(int i=0;i<128;i++){
            while (IntHashSetIterator_hasNext(iterator2)) {
                int element = IntHashSetIterator_next(iterator2);
                IntHashSet_union(result,nfa->TransitionTable[element][i]);
            }
            iterator2 = IntHashSet_iterator(temp);
            if(IntHashSet_isEmpty(result)==true){
                
                continue;
            }
            if(ifContains(Transfer,result)==false){
                LinkedList_add_at_end(Transfer,result);
                iterator1 = LinkedList_Reverse_iterator(Transfer);
            }
            iterator3 = IntHashSet_iterator(result);
            while(IntHashSetIterator_hasNext(iterator3)){
                int element = IntHashSetIterator_next(iterator3);
                for(int i=0;i<nfa->AcceptIndex;i++){
                    if(element==nfa->Accept[i]){
                        this->Accept[this->AcceptIndex]=findindex(Transfer,result);
                        this->AcceptIndex++;
                        break;
                    }
                }
            }
            this->TransitionTable[count][i]=findindex(Transfer,result);
            result=new_IntHashSet(nfa->TotalStates);
        }
        free(iterator3);
        free(iterator2);
        count++;
    }
    free(iterator1);
    LinkedList_free(Transfer,false);
    IntHashSet_free(temp);
    IntHashSet_free(result);
    return this;
}


