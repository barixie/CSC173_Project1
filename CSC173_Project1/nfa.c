#include "nfa.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "IntHashSet.h"
#include "LinkedList.h"

NFA new_NFA(int nstates){
	NFA this=(NFA)malloc(sizeof(struct NFA));
	this->TotalStates=nstates;
	this->Accept=(int *)malloc(nstates*sizeof(int));
	this->AcceptIndex=0;
	for(int i=0;i<this->TotalStates;i++){
		this->TransitionTable[i]=(IntHashSet*)malloc(128*sizeof(IntHashSet));
	}
	for(int i=0;i<this->TotalStates;i++){
		for(int x=0;x<128;x++){
			this->TransitionTable[i][x]=new_IntHashSet(nstates);
		}
	}
	return this;
}
void NFA_free(NFA nfa)
{
    if(nfa==NULL)
        return;
    for(int i=0;i<nfa->TotalStates;i++)
    {
        for(int j=0;j<128;j++)
            IntHashSet_free(nfa->TransitionTable[i][j]);
        free(nfa->TransitionTable[i]);
    }
    free(nfa->TransitionTable);
    free(nfa->Accept);
    free(nfa);
    return;
}
int NFA_get_size(NFA nfa)
{
    return nfa->TotalStates;
}
IntHashSet NFA_get_transitions(NFA nfa, int state, char sym)
{
    if(state>nfa->TotalStates||state<0)
    {
        printf("%s\n","input error");
        return NULL;
    }
    int temp=(int)sym;
    return nfa->TransitionTable[state][temp];
}
void NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
    if(src>nfa->TotalStates||src<0||dst>nfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    int temp=(int) sym;
    IntHashSet_insert(nfa->TransitionTable[src][temp], dst);
}
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst)
{
    if(src>nfa->TotalStates||src<0||dst>nfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    int length=(int) strlen(str);
    for(int i=0;i<length;i++)
    {
        int temp=(int)str[i];
        IntHashSet_insert(nfa->TransitionTable[src][temp], dst);
    }
}
void NFA_add_transition_all(NFA nfa, int src, int dst)
{
    if(src>nfa->TotalStates||src<0||dst>nfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    for(int i=0;i<128;i++)
    {
        IntHashSet_insert(nfa->TransitionTable[src][i], dst);
    }
}
void NFA_add_transition_Except(NFA nfa,int src,char string,int dst)
{
    if(src>nfa->TotalStates||src<0||dst>nfa->TotalStates||dst<0)
    {
        printf("%s\n","input error");
        return;
    }
    for(int i=0;i<128;i++)
    {
        if((int)string==i)
        {
            continue;
        }
        IntHashSet_insert(nfa->TransitionTable[src][i], dst);
    }
}
void NFA_set_accepting(NFA nfa, int state, bool value)
{
    if(value==0)
        return;
    if(state<0||state>nfa->TotalStates)
        return;
    nfa->Accept[nfa->AcceptIndex]=state;
    nfa->AcceptIndex++;
}
 bool NFA_get_accepting(NFA nfa, int state)
{
    for(int i=0;i<nfa->AcceptIndex;i++)
    {
        if(nfa->Accept[i]==state)
            return 1;
    }
    return 0;
}
bool NFA_execute(NFA nfa, char *input)
{
    IntHashSet temp=new_IntHashSet(nfa->TotalStates);
    temp=NFA_get_transitions(nfa, 0, input[0]);
    IntHashSet temp1=new_IntHashSet(nfa->TotalStates);
    IntHashSetIterator iterator;
    int length=(int)strlen(input);
    for(int i=0;i<length;i++)
    {
        iterator=IntHashSet_iterator(temp);
        while(IntHashSetIterator_hasNext(iterator))
        {
            int element=IntHashSetIterator_next(iterator);
            IntHashSet_union(temp1, NFA_get_transitions(nfa, element, input[i]));
        }
        temp=temp1;
        temp1=new_IntHashSet(nfa->TotalStates);
    }
    free(iterator);
    IntHashSet_free(temp1);
    IntHashSetIterator iterator1=IntHashSet_iterator(temp);
    while(IntHashSetIterator_hasNext(iterator1))
    {
        int element1=IntHashSetIterator_next(iterator1);
        if(NFA_get_accepting(nfa, element1)==1)
        {
            free(iterator1);
            IntHashSet_free(temp);
            return 1;
        }
    }
    free(iterator1);
    IntHashSet_free(temp);
    return 0;
}


