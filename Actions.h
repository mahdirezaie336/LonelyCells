bool getMap(char *address){
    int n=0,i,j;    //n is size of map
    FILE * fmap;
    fmap = fopen(address,"rb");
    if(fmap==NULL){
        COLOR(RED); printf("Cannot open map file.\n"); COLOR(WHITE);
        mapSize = -1;
        return 0;
    }
    fread(&n,sizeof(int),1,fmap);
    if(n>=30 ||  n<0){
        COLOR(RED); printf("Wrong map size!\n"); COLOR(WHITE);
        fflush(stdin);
        getchar();
        return 0;
    }

    for(j=n-1;j>=0;j--){
        for(i=0;i<n;i++){
            if(feof(fmap)){
                COLOR(RED); printf("Map elements doesn't match with size.\n"); COLOR(WHITE);
                mapSize = -1;
                fflush(stdin);
                getchar();
                return 0;
            }
            char c;
            fread(&c,sizeof(char),1,fmap);
            E[j][i]=c-'0';
        }
    }
    fclose(fmap);
    mapSize = n;    //Global output of function
    return 1;       //means process done completely
}

int moveInE(int dx, int dy, int pn, cell *cellp){   //
    int x = cellp->x;
    int y = cellp->y;
    if(x+dx>=0 && x+dx<mapSize && y+dy>=0 && y+dy<mapSize && E[y+dy][x+dx]!=3 && (E[y+dy][x+dx])/10==0){
        E[y][x]-=pn*10;
        E[y+dy][x+dx]+=pn*10;
        cellp->y+=dy;
        cellp->x+=dx;
        SOUND("sounds\\Move.wav");
        return 1;
    }
    SOUND("sounds\\MoveError.wav");
    return 0;
}

bool moveMenu(cell *cellp,int pn){

    while(1){
        int x = cellp->x;
        display();
        printf("   [1]\n[4]   [3]\n[6]   [5]\n   [2]\n[0] Cancel\n");
        bool flag=0;
        fflush(stdin);
        switch(_getch()-'0'){
        case 1:
            flag = moveInE(0,-1,pn,cellp);
            break;
        case 2:
            flag = moveInE(0,+1,pn,cellp);
            break;
        case 3:
            if(x%2==0) flag = moveInE(1,-1,pn,cellp);
            else flag = moveInE(1,0,pn,cellp);
            break;
        case 4:
            if(x%2==0) flag = moveInE(-1,-1,pn,cellp);
            else flag = moveInE(-1,0,pn,cellp);
            break;
        case 5:
            if(x%2==0) flag = moveInE(1,0,pn,cellp);
            else flag = moveInE(1,1,pn,cellp);
            break;
        case 6:
            if(x%2==0) flag = moveInE(-1,0,pn,cellp);
            else flag = moveInE(-1,1,pn,cellp);
            break;
        case 0:
            return 0;
        }
        if(flag) break;
    }
    return 1;
}

int checkChoices(cell *chose){
    int x=chose->x;
    int y=chose->y;
    for(int j=-1;j<2;j++)
        for(int i=-1;i<2;i++)
            if(x+i>=0 && x+i<mapSize && y+j>=0 && y+j<mapSize && E[y+j][x+i]!=3 && (E[y+j][x+i])/10==0){
                if(x%2==0 && (i==-1 || i==1) && j==1) continue;
                if(x%2==1 && (i==-1 || i==1) && j==-1) continue;
                return 1;
            }
    return 0;
}

bool splitMenu(cell **phead, cell *chose, int pn){

    if(E[chose->y][chose->x]%10!=2 || checkChoices(chose)==0 || (chose->energy)<80){ //Checking conditions of splitting
        SOUND("sounds\\Error.wav");
        return 0;
    }

    cell *newCell1,*newCell2,*cur=*phead;   //Creating new cells
    newCell1 = (cell *)malloc(sizeof(cell));
    newCell2 = (cell *)malloc(sizeof(cell));
    *newCell1 = *chose;
    *newCell2 = *chose;
    newCell1->next = newCell2;
    newCell1->energy = 40;
    newCell2->energy = 40;
    randString(5,newCell1->name);
    randString(5,newCell2->name);
    if(*phead!=chose){       //checking if cell is the first element of list or not
        for(;cur->next!=chose;cur=cur->next);      //finding previous cell
        cur->next = newCell1;
    }else{
        *phead = newCell1;
    }
    free(chose);

    while(1){       //random movement of new cell
        int i = rand()%3-1;
        int j = rand()%3-1;
        if((newCell1->x)%2==1 && j==-1 && (i==-1 || i==1)) continue;
        if((newCell1->x)%2==0 && j==1 && (i==-1 || i==1)) continue;
        if(moveInE(i,j,pn,newCell2)==1) break;
    }
    E[newCell1->y][newCell1->x]+=pn*10;
    SOUND("sounds\\Mitosis.wav");
    return 1;
}

void randString(size_t size,char *name) {
    // reserves a place for NULL
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    str[size] = '\0';
    strcpy(name,str);
    free(str);
}

void findEnegryStations(ES **pESHead){
    int i,j,k=0;
    for(j=0;j<mapSize;j++)
        for(i=0;i<mapSize;i++)
            if(E[j][i]%10==1){
                k++;
                ES temp;
                temp.x=i;
                temp.y=j;
                temp.value=100;
                createEnergyStation(pESHead,temp);
            }
}

bool boostEnergyMenu(cell *chosen,ES *ESHead){
    int x = chosen->x;
    int y = chosen->y;
    if(E[y][x]%10!=1){
        SOUND("sounds\\Error.wav");
        return 0;
    }
    ES *cur = ESHead;
    for(;cur!=NULL;cur=cur->next){
        if(cur->x==x && cur->y==y) break;
    }

    display();
    fflush(stdin);
    if(cur->value==0){
        printf("This Energy station has no glucoses.\nPress any key to go back.\n");
        getchar();
        return 0;
    }else{
        int i=0;
        char c;
        while(1){
            display();
            printf("\nPress 'Space' to get 5 glucoses or press 'B' to go back.\nYou can only get 3 times.\n\n");
            printf("Glucoses : %d\n",cur->value);
            printf("Cell's Energy : %d\n",chosen->energy);
            c=getche();
            if(c==' '){
                if(cur->value>=5 && chosen->energy<=95){
                    cur->value-=5;
                    chosen->energy+=5;
                    i++;
                    SOUND("sounds\\BoostEnergy.wav");
                }else SOUND("sounds\\Error.wav");
            }
            if(c=='b' || c=='B' || i==3){
                if(i==0) return 0;
                return 1;
            }
        }
    }
    return 1;
}

bool multipleMove(cell *cellp,int pn){
    bool firstStep = 1;
    while(1){
        int x = cellp->x;
        display();
        printf("   [1]\n[4]   [3]\n[6]   [5]\n   [2]\n[0] Finish\n");
        printf("Energy remaining : %d\n",cellp->energy);
        bool flag=0,flag2=0;
        fflush(stdin);
        if(cellp->energy>=5){
            switch(_getch()-'0'){
            case 1:
                flag = moveInE(0,-1,pn,cellp);
                break;
            case 2:
                flag = moveInE(0,+1,pn,cellp);
                break;
            case 3:
                if(x%2==0) flag = moveInE(1,-1,pn,cellp);
                else flag = moveInE(1,0,pn,cellp);
                break;
            case 4:
                if(x%2==0) flag = moveInE(-1,-1,pn,cellp);
                else flag = moveInE(-1,0,pn,cellp);
                break;
            case 5:
                if(x%2==0) flag = moveInE(1,0,pn,cellp);
                else flag = moveInE(1,1,pn,cellp);
                break;
            case 6:
                if(x%2==0) flag = moveInE(-1,0,pn,cellp);
                else flag = moveInE(-1,1,pn,cellp);
                break;
            case 0:
                flag2 = 1;
                break;
            }
            if(flag && !firstStep) cellp->energy-=5;
            if(flag && firstStep) firstStep = 0;
            if(flag2) break;
        }else{
            if(_getch() == '0') break;
            else SOUND("sounds\\MoveError.wav");
        }

    }
    if(firstStep) return 0;
    return 1;
}





