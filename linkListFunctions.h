void createCell(cell **phead,cell temp){     //creating cells and adding them to end of list
    cell *newCell = (cell *)malloc(sizeof(cell));
    *newCell=temp;
    newCell->next=NULL;
    if(*phead==NULL){
        *phead = newCell;
        return;
    }
    cell *cur = *phead;
    for(;cur->next!=NULL;cur=cur->next);
    cur->next=newCell;
}

void createEnergyStation(ES **phead,ES temp){
    ES *newES = (ES *)malloc(sizeof(ES));
    *newES=temp;
    newES->next=NULL;
    if(*phead==NULL){
        *phead = newES;
        return;
    }
    ES *cur = *phead;
    for(;cur->next!=NULL;cur=cur->next);
    cur->next=newES;
}
