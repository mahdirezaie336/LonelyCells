bool mapEditorMenu(){
    while(1){
        system("cls");
        printf("[1] Create a new map\n[2] Edit an existing map\n[3] Convert map to text\n[4] Convert text to map\n[0] Back\n");
        fflush(stdin);
        switch(_getch()-'0'){
        case 1:
            createNewMap();
            break;
        case 2:
            editMap();
            break;
        case 3:
            convertMTT();
            break;
        case 4:
            convertTTM();
            break;
        case 0:
            return 0;
        }
    }
    return 1;
}

bool createNewMap(void){
    char name[30];
    FILE *fp;
    while(1){
        printf("Enter name of file: ");
        gets(name);
        fp = fopen(name,"w+b");
        if(fp==NULL){
            COLOR(RED); printf("Wrong file!"); COLOR(WHITE);
            fflush(stdin); getchar();
        }else break;
    }
    while(1){
        printf("Enter size of map: ");
        scanf("%d",&mapSize);
        if(mapSize > 0 && mapSize <= 30) break;
        else{
            COLOR(RED); printf("Wrong size!"); COLOR(WHITE);
            fflush(stdin); getchar();
        }
    }

    emptyMap();

    bool SON;           // save or not
    SON = editorFunc();
    if(SON) saveMap(fp);
    fclose(fp);
    return 1;
}

bool editMap(void){
    char name[30];
    FILE *fp;
    while(1){
        printf("Enter name of file: ");
        gets(name);
        fp = fopen(name,"r+b");
        if(fp==NULL){
            COLOR(RED); printf("Wrong file!"); COLOR(WHITE);
            fflush(stdin); getchar();
        }else break;
    }
    if(getMap(name)==0)
        return 0;

    bool SON;       //save or not
    SON = editorFunc();
    if(SON) saveMap(fp);
    fclose(fp);
    return 1;
}

bool editorFunc(void){
    bool mapChanged = 1;
    int x,y;
    x = y = 0;
    E[0][0]+=30;
    while(1){
        if(mapChanged){
            display();
            printf("'E' : Energy Station\n'M' : Mitosis Block\n'F' : Forbidden Block\n'C' : Clear\n");
            printf("'L' : Quit without Save\n'K' : Save and Quit\n'O' : Change map size\n");
        }
        mapChanged = 0;
        fflush(stdin);
        switch(_getch()){
        case 'w':
        case 'W':    // key up
            mapChanged = moveInE2(&x,&y,0,-1);
            break;
        case 's':
        case 'S':    // key down
            mapChanged = moveInE2(&x,&y,0,1);
            break;
        case 'd':
        case 'D':    // key right
            mapChanged = moveInE2(&x,&y,1,0);
            break;
        case 'a':
        case 'A':    // key left
            mapChanged = moveInE2(&x,&y,-1,0);
            break;
        case 'e':
        case 'E':
            E[y][x]=10*(E[y][x]/10);
            E[y][x]+=1;
            mapChanged=1;
            break;
        case 'm':
        case 'M':
            E[y][x]=10*(E[y][x]/10);
            E[y][x]+=2;
            mapChanged=1;
            break;
        case 'f':
        case 'F':
            E[y][x]=10*(E[y][x]/10);
            E[y][x]+=3;
            mapChanged=1;
            break;
        case 'c':
        case 'C':
            E[y][x]=10*(E[y][x]/10);
            E[y][x]+=4;
            mapChanged=1;
            break;
        case 'l':
        case 'L':
            E[y][x]-=30;
            return 0;
        case 'k':
        case 'K':
            E[y][x]-=30;
            return 1;
        case 'o':
        case 'O':
            printf("Enter new size: ");
            scanf("%d",&mapSize);
            emptyMap();
            E[y][x]+=30;
            mapChanged=1;
            break;
        }
    }
}

bool moveInE2(int *x, int *y, int dx, int dy){
    if(*x+dx>=0 && *x+dx<mapSize && *y+dy>=0 && *y+dy<mapSize){
        E[*y][*x]-=30;
        E[*y+dy][*x+dx]+=30;
        *x+=dx;
        *y+=dy;
        return 1;
    }
    return 0;
}

bool saveMap(FILE *fp){
    int i,j;
    fwrite(&mapSize,sizeof(int),1,fp);
    for(j=mapSize-1;j>=0;j--){
        for(i=0;i<mapSize;i++){
            char c = E[j][i] + '0';
            fwrite(&c,sizeof(char),1,fp);
        }
    }
    printf("\nSaved successfully!\n");
    _getch();
    return 1;
}

void emptyMap(void){
    for(int j=0;j<mapSize;j++)
        for(int i=0;i<mapSize;i++)
            E[j][i] = 4;
}

bool convertMTT(void){
    char in[256],out[256];
    printf("Enter map file name: ");
    gets(in);
    printf("Enter text file name: ");
    gets(out);

    if(getMap(in)==0) return 0;
    FILE *tFile;
    tFile = fopen(out,"w");
    if(tFile == NULL){
        COLOR(RED); printf("Cannot open text file!\n"); COLOR(WHITE);
        return 0;
    }

    int i,j;
    char c;
    int m = mapSize/2;

    for(i=0;i<m;i++) fprintf(tFile,"---   ");
    if(mapSize%2!=0) fprintf(tFile,"---");
    fprintf(tFile,"\n");


    for(j=0;j<mapSize;j++){
        for(i=0;i<m;i++){
            c = checkBlock(i,j,0);
            fprintf(tFile," %c ",c);
            fprintf(tFile,"---");
        }
        if(mapSize%2!=0){
            c = checkBlock(i,j,0);
            fprintf(tFile," %c ",c);
        }
        fprintf(tFile,"\n");
        for(i=0;i<m;i++){
            fprintf(tFile,"---");
            c = checkBlock(i,j,1);
            fprintf(tFile," %c ",c);
        }
        if(mapSize%2!=0) fprintf(tFile,"---");
        fprintf(tFile,"\n");
    }

    for(i=0;i<m;i++) fprintf(tFile,"   ---");
    if(mapSize%2!=0) fprintf(tFile,"   ");
    fprintf(tFile,"\n");
    COLOR(WHITE);
    printf("Done successfuly!\n");
    fflush(stdin);
    fclose(tFile);
    _getch();
    return 1;
}

bool convertTTM(void){
    char in[256],out[256];
    printf("Enter text file name: ");
    gets(in);
    printf("Enter map file name: ");
    gets(out);

    FILE *tFile = fopen(in,"r");
    if(tFile == NULL){
        COLOR(RED); printf("Connot open text file.\n"); COLOR(WHITE);
        fflush(stdin); _getch();
        return 0;
    }

    FILE *bFile = fopen(out,"wb");
    if(bFile == NULL){
        COLOR(RED); printf("Connot open map file.\n"); COLOR(WHITE);
        fclose(tFile);
        fflush(stdin); _getch();
        return 0;
    }

    char fstr[256];
    fgets(fstr,100,tFile);
    if((strlen(fstr)-1)%3!=0){
        COLOR(RED); printf("Wrong Text File.\n"); COLOR(WHITE);
        fclose(tFile);
        fclose(bFile);
        fflush(stdin); _getch();
        return 0;
    }
    int mSize = strlen(fstr)/3;
    if(mSize==0){
        COLOR(RED); printf("Empty or Wrong Text File.\n"); COLOR(WHITE);
        fclose(tFile);
        fclose(bFile);
        fflush(stdin); _getch();
        return 0;
    }

    fseek(tFile,0,SEEK_SET);

    for(int i=0;i<mSize*2+2;i++){
        fgets(fstr,100,tFile);
        if((strlen(fstr)-1)!=mSize*3){
            COLOR(RED); printf("Rows size error!\n"); COLOR(WHITE);
            fclose(tFile);
            fclose(bFile);
            fflush(stdin); _getch();
            return 0;
        }
        for(int j=0;j<mSize*3;j++){
            if(fstr[j]!=' ' && fstr[j]!='-' && fstr[j]!='e' && fstr[j]!='m'){
                COLOR(RED); printf("What does %c mean in file?\n",fstr[j]); COLOR(WHITE);
                fclose(tFile);
                fclose(bFile);
                fflush(stdin); _getch();
                return 0;
            }
        }
    }
    fgets(fstr,3,tFile);
    if(!feof(tFile)){
        COLOR(RED); printf("Too many rows.\n"); COLOR(WHITE);
        fclose(tFile);
        fclose(bFile);
        fflush(stdin); _getch();
        return 0;
    }

    mapSize = mSize;
    emptyMap();

    fseek(tFile,0,SEEK_SET);
    fgets(fstr,100,tFile);

    for(int j=0;j<mapSize;j++){
        fgets(fstr,100,tFile);
        for(int i=0;i<ceil(mapSize/2.0);i++){
            switch(fstr[6*i+1]){
            case ' ':
                E[j][2*i]=4;
                break;
            case '-':
                E[j][2*i]=3;
                break;
            case 'm':
                E[j][2*i]=2;
                break;
            case 'e':
                E[j][2*i]=1;
                break;
            }
        }

        fgets(fstr,100,tFile);
        for(int i=0;i<mapSize/2;i++){
            switch(fstr[6*i+4]){
            case ' ':
                E[j][2*i+1]=4;
                break;
            case '-':
                E[j][2*i+1]=3;
                break;
            case 'm':
                E[j][2*i+1]=2;
                break;
            case 'e':
                E[j][2*i+1]=1;
                break;
            }
        }
    }

    saveMap(bFile);

    fclose(tFile);
    fclose(bFile);
    fflush(stdin);
    getchar();
    return 1;
}






