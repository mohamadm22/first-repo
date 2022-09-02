/*
 * LNKDLST_int.h
 *
 *  Created on: Aug 14, 2022
 *      Author: user
 */

#ifndef APPLICATION_LNKDLST_LNKDLST_INT_H_
#define APPLICATION_LNKDLST_LNKDLST_INT_H_

typedef struct Node{
	u08 HorzintalIndex;
	u08 VerticalIndex;
	struct Node* next;
}node;

node* CreatFirstNode(void);
void CreatNode(node* Low);


#endif /* APPLICATION_LNKDLST_LNKDLST_INT_H_ */
