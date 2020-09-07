void debugPrintE(int n){
    int i,j;
    i = j = 0;
    for(j=0;j<n;j++){
        for(i=0;i<n;i++)
            printf("%d ",E[j][i]);
        printf("\n");
    }
}

void debugPrintList(cell *head){
    if(head==NULL) return;
    cell *cur=head;
    for(;cur!=NULL;cur=cur->next){
        printf("Name: %s\nX = %d\nY = %d\n Enegry = %d\n\n",cur->name,cur->x,cur->y,cur->energy);
    }
}

void debugPrintListES(ES *head){
    if(head==NULL) return;
    ES *cur=head;
    for(;cur!=NULL;cur=cur->next){
        printf("X = %d\nY = %d\n Value = %d\n\n",cur->x,cur->y,cur->value);
    }
}
