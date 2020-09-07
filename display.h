char checkBlock(int i, int j, int z){
    int m = E[j][i*2+z];

    switch(m/10){
    case 0:
        break;
    case 1:
        COLOR(MAGENTA);
        return 'X';
    case 2:
        COLOR(YELLOW);
        return 'Y';
    case 3:
        COLOR(BG_YELLOW);
        return m%10==1?'e':m%10==2?'m':m%10==3?'-':' ';
    }

    switch(m%10){
    case 1:
        COLOR(BG_BLUE);
        return 'e';
    case 2:
        COLOR(BG_GREEN);
        return 'm';
    case 3:
        COLOR(BG_WHITE);
        return '-';
    case 4:
        return ' ';
    }
    return ' ';
}

void display(void){
    int n = mapSize;
    system("cls");
    int i,j;
    char c;
    int m = n/2;

    for(i=0;i<m;i++) printf("---   ");
    if(n%2!=0) printf("---");
    printf("\n");

    for(j=0;j<n;j++){
        for(i=0;i<m;i++){
            c = checkBlock(i,j,0);
            printf(" %c ",c);
            COLOR(WHITE);
            printf("---");
        }
        if(n%2!=0){
            c = checkBlock(i,j,0);
            printf(" %c ",c);
            COLOR(WHITE);
        }
        printf("\n");
        for(i=0;i<m;i++){
            printf("---");
            c = checkBlock(i,j,1);
            printf(" %c ",c);
            COLOR(WHITE);
        }
        if(n%2!=0) printf("---");
        printf("\n");
    }

    for(i=0;i<m;i++) printf("   ---");
    if(n%2!=0) printf("   ");
    printf("\n");
    //debugPrintE(mapSize);
}

int displayChooseCellMenu(cell *head){
    cell *cur=head;
    int i=1;
    for(;cur!=NULL;cur=cur->next,i++){
        printf("[%d] %s (%d,%d) Energy = %d",i,cur->name,cur->x,mapSize-1-cur->y,cur->energy);
        if(E[cur->y][cur->x]%10==1){
            COLOR(BLUE);
            printf("  Is on Energy Block");
            COLOR(WHITE);
        }
        if(E[cur->y][cur->x]%10==2){
            COLOR(GREEN);
            printf("  Is on Mitosis Block");
            COLOR(WHITE);
        }
        printf("\n");
    }
    printf(">");
    return i-1;
}
