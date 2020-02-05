//
//  main.c
//  Project1
//
//  Created by bari on 2019/9/9.
//  Copyright © 2019 bari. All rights reserved.
//

#include <stdio.h>
#include "dfa.h"
#include <string.h>
#include "nfa.h"

void test(DFA dfa){
    while(true)
    {
        char quit[20]="quit";
        printf("Enter an input (type 'quit' to quit):\n");
        char input[20];
        scanf("%s",input);
        if(strcmp(quit, input)==0)
            break;
        else
        {
            if(DFA_execute(dfa, input)==true)
                printf("Result for input %s: %s\n",input,"True");
            else
                printf("Result for input %s: %s\n",input,"False");
        }
    }
}
void testNFA(NFA nfa){
    while(true){
        char quit[20]="quit";
        printf("Enter an input (type 'quit' to quit):\n");
        char input[20];
        scanf("%s", input);
        if(strcmp(quit,input)==0){
            break;
        }else{
            if(NFA_execute(nfa,input)==true){
                printf("Result for input %s is %s\n",input,"True" );
            }else{
                printf("Result for input %s is %s\n",input,"False" );
            }
        }
    }
}
void testConvert(NFA nfa,DFA dfa){
    while(true){
            printf("Enter an input (type 'quit' to quit):\n");
            char quit[20]="quit";
            char input[30];
            scanf("%s", input);
            if(!strcmp(quit,input)){
                break;
            }else{
                if(NFA_execute(nfa,input)==true){
                    printf("NFA's Result for input %s is accepted.\n",input);
                }else{
                    printf("Result for input %s is rejected.\n",input);
                }
    
                if(DFA_execute(dfa,input)==true){
                printf("DFA's Result for input %s is accepted.\n",input);
                printf("DFA transferred from NFA has %d states.\n", DFA_get_size(dfa));
                }else{
                    printf("Result for input %s is rejected.\n",input);
                }
            }
        }
}
DFA initialcsc173(){
    DFA csc173=new_DFA(7);
    DFA_set_transition(csc173, 0, 'c', 1);
    DFA_set_transition(csc173, 1, 's', 2);
    DFA_set_transition(csc173, 2, 'c', 3);
    DFA_set_transition(csc173, 3, '1', 4);
    DFA_set_transition(csc173, 4, '7', 5);
    DFA_set_transition(csc173, 5, '3', 6);
    DFA_set_accepting(csc173, 6, 1);
    return csc173;
}
DFA initialcat(){
    DFA cat=new_DFA(4);
    DFA_set_accepting(cat, 3, 1);
    DFA_set_transition(cat, 0, 'c', 1);
    DFA_set_transition(cat, 1, 'a', 2);
    DFA_set_transition(cat, 2, 't', 3);
    DFA_set_transition_all(cat, 3, 3);
    return cat;
}
DFA initialbinary(){
    DFA binary=new_DFA(2);
    DFA_set_accepting(binary, 0, 1);
    DFA_set_transition(binary, 0, '0', 1);
    DFA_set_transition(binary, 1, '0', 0 );
    DFA_set_transition(binary, 0, '1', 0);
    DFA_set_transition(binary, 1, '1', 1);
    return binary;
}
DFA initialeven01(){
    DFA even01=new_DFA(4);
    DFA_set_accepting(even01, 0, 1);
    DFA_set_transition(even01, 0, '0', 1);
    DFA_set_transition(even01, 1, '0', 0);
    DFA_set_transition(even01, 0, '1', 2);
    DFA_set_transition(even01, 2, '1', 0);
    DFA_set_transition(even01, 2, '0', 3);
    DFA_set_transition(even01, 3, '0', 2);
    DFA_set_transition(even01, 3, '1', 1);
    DFA_set_transition(even01, 1, '1', 3);
    return even01;
}
DFA initialcontain01(){
    DFA contain01=new_DFA(4);
    DFA_set_accepting(contain01, 3, 1);
    DFA_set_transition(contain01, 0, '1', 1);
    DFA_set_transition(contain01, 0, '0', 2);
    DFA_set_transition(contain01, 1, '1', 1);
    DFA_set_transition(contain01, 1, '0', 2);
    DFA_set_transition(contain01, 2, '0', 2);
    DFA_set_transition(contain01, 2, '1', 3);
    DFA_set_transition(contain01, 3, '0', 3);
    DFA_set_transition(contain01, 3, '1', 3);
    return contain01;
}
NFA initialendcode(){
    NFA endcode = new_NFA(5);
    NFA_add_transition(endcode,0,'c',1);
    NFA_add_transition_all(endcode,0,0);
    NFA_add_transition(endcode,1,'o',2);
    NFA_add_transition(endcode,2,'d',3);
    NFA_add_transition(endcode,3,'e',4);
    NFA_set_accepting(endcode,4,1);
    return endcode;
}
NFA initialcontaincode(){
    NFA containCode=new_NFA(5);
    NFA_add_transition(containCode,0,'c',1);
    NFA_add_transition_all(containCode,0,0);
    NFA_add_transition(containCode,1,'o',2);
    NFA_add_transition(containCode,2,'d',3);
    NFA_add_transition(containCode,3,'e',4);
    NFA_set_accepting(containCode,4,1);
    NFA_add_transition_all(containCode,4,4);
    return containCode;
}
NFA initialWashington(){
    NFA washington=new_NFA(20);
    NFA_set_accepting(washington, 2, 1);
    NFA_set_accepting(washington, 4, 1);
    NFA_set_accepting(washington, 6, 1);
    NFA_set_accepting(washington, 8, 1);
    NFA_set_accepting(washington, 11, 1);
    NFA_set_accepting(washington, 13, 1);
    NFA_set_accepting(washington, 15, 1);
    NFA_set_accepting(washington, 17, 1);
    NFA_set_accepting(washington, 19, 1);
    NFA_add_transition_all(washington, 0, 0);
    NFA_add_transition(washington, 0, 'a', 1);
    NFA_add_transition_Except(washington, 1, 'a', 1);
    NFA_add_transition(washington, 1, 'a', 2);
    NFA_add_transition(washington, 0, 'g', 3);
    NFA_add_transition_Except(washington, 3, 'g', 3);
    NFA_add_transition(washington, 3, 'g', 4);
    NFA_add_transition(washington, 0, 'h', 5);
    NFA_add_transition_Except(washington,5,'h',5);
    NFA_add_transition(washington,5,'h',6);
    NFA_add_transition(washington,0,'i',7);
    NFA_add_transition_Except(washington,7,'i',7);
    NFA_add_transition(washington,7,'i',8);
    NFA_add_transition(washington,0,'n',9);
    NFA_add_transition_Except(washington,9,'n',9);
    NFA_add_transition(washington,9,'n',10);
    NFA_add_transition_Except(washington,10,'n',10);
    NFA_add_transition(washington,10,'n',11);
    NFA_add_transition(washington,0,'o',12);
    NFA_add_transition_Except(washington,12,'o',12);
    NFA_add_transition(washington,12,'o',13);
    NFA_add_transition(washington,0,'s',14);
    NFA_add_transition_Except(washington,14,'s',14);
    NFA_add_transition(washington,14,'s',15);
    NFA_add_transition(washington,0,'t',16);
    NFA_add_transition_Except(washington,16,'t',16);
    NFA_add_transition(washington,16,'t',17);
    NFA_add_transition(washington,0,'w',18);
    NFA_add_transition_Except(washington,18,'w',18);
    NFA_add_transition(washington,18,'w',19);
    return washington;
}
NFA initialbari(){
    NFA bari=new_NFA(5);
    NFA_set_accepting(bari,4,1);
    NFA_add_transition_all(bari,0,0);
    NFA_add_transition(bari,0,'r',1);
    NFA_add_transition_all(bari,1,0);
    NFA_add_transition(bari,1,'o',2);
    NFA_add_transition_all(bari,2,2);
    NFA_add_transition(bari,2,'s',3);
    NFA_add_transition_all(bari,3,3);
    NFA_add_transition(bari,3,'e',4);
    NFA_add_transition_all(bari,4,4);
    return bari;
}
int main(int argc, const char * argv[]) {
    printf("CSC173 Project by Zihan Xie\n");
   
    printf("Test DFA that recognizes exactly 'csc173'\n");
    test(initialcsc173());

    printf("Test DFA that recognizes words start with 'cat'\n");
    test(initialcat());
    
    
    printf("Test a binary input with even number of '0'\n");
    test(initialbinary());
    
    
    printf("Test a binary input with even number of '0'and even number of '1'\n");
    test(initialeven01());
    
    
    printf("Test a binary input contains 01\n");
    test(initialcontain01());
    
    printf("\n\nTesting for NFA\n\n");
    
   
    printf("\nTesting NFA that recognizes ending with eactly strings 'code'.\n");
    testNFA(initialendcode());
    
    
    printf("\nTesting NFA that recognizes string contains 'code'.\n");
    testNFA(initialcontaincode());
    
    
    printf("\nTesting NFA that recognizes string consists of 'washington'.\n");
    testNFA(initialWashington());
    
    
    printf("\nTesting NFA that recognizes the strings contain 'r','o','s','e' in sequence.\n");
    testNFA(initialbari());
    
    DFA DFA_endcode=Convert(initialendcode());
    printf("\n DFA that recognizes strings ending with code.\n");
    testConvert(initialendcode(),DFA_endcode);
    
    DFA DFA_containCode=Convert(initialcontaincode());
    printf("\n DFA that recognizes strings contain with code.\n");
    testConvert(initialcontaincode(),DFA_containCode);
}
