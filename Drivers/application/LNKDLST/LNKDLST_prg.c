/*
 * LNKDLST_prg.c
 *
 *  Created on: Aug 14, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"LNKDLST_int.h"


node* CreatFirstNode(void)
{
	node* head = (node*) malloc(sizeof(node));
	head->next=NULL;
	return head;
}

void CreatNode(node* Low)
{
	node* Link = (node*) malloc(sizeof(node));
	Link->next=Low;
	Low=Link;
}
