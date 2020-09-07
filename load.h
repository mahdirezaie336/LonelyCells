bool loadMenu(void){
    system("cls");
    FILE *fLoad;        //Checking Existance of Files
    fLoad = fopen("saveFile_ES.bin","rb");
    if(fLoad==NULL) {
        COLOR(RED); printf("Cannot open saveFile_ES.bin"); COLOR(WHITE);
        fflush(stdin); getchar();
        return 0;
    }
    fclose(fLoad);

    fLoad = fopen("saveFile_Cell1.bin","rb");
    if(fLoad==NULL) {
        COLOR(RED); printf("Cannot open saveFile_Cell1.bin"); COLOR(WHITE);
        fflush(stdin); getchar();
        return 0;
    }
    fclose(fLoad);

    fLoad = fopen("saveFile_Cell2.bin","rb");
    if(fLoad==NULL) {
        COLOR(RED); printf("Cannot open saveFile_Cell2.bin"); COLOR(WHITE);
        fflush(stdin); getchar();
        return 0;
    }
    fclose(fLoad);

    if(getMap("map.bin")==0){
        COLOR(RED); printf("Map has problems."); COLOR(WHITE);
    }

    int ESsize,i;
    ES *ESHead=NULL;
    ES temp;
    cell *cell1Head=NULL;
    cell *cell2Head=NULL;
    cell temp2;

    fLoad = fopen("saveFile_ES.bin","rb");
    fread(&ESsize,sizeof(int),1,fLoad);
    for(i=0;i<ESsize;i++){
        fread(&(temp.x),sizeof(int),1,fLoad);
        fread(&(temp.y),sizeof(int),1,fLoad);
        if(E[temp.y][temp.x]%10 != 1){
            COLOR(RED); printf("The map doesn't match with save files. Loading terminated."); COLOR(WHITE);
            fflush(stdin); getchar();
            return 0;
        }
        fread(&(temp.value),sizeof(int),1,fLoad);
        createEnergyStation(&ESHead,temp);
    }
    fclose(fLoad);

    fLoad = fopen("saveFile_cell1.bin","rb");
    fread(&ESsize,sizeof(int),1,fLoad);
    for(i=0;i<ESsize;i++){
        fread(&(temp2.x),sizeof(int),1,fLoad);
        fread(&(temp2.y),sizeof(int),1,fLoad);
        fread(&(temp2.energy),sizeof(int),1,fLoad);
        fread(temp2.name,sizeof(char),6,fLoad);
        if(E[temp2.y][temp2.x]/10==0) E[temp2.y][temp2.x]+=10;
        else{
            COLOR(RED); printf("Wrong file!"); COLOR(WHITE);
            fflush(stdin); getchar();
            return 0;
        }
        createCell(&cell1Head,temp2);
    }
    fclose(fLoad);

    fLoad = fopen("saveFile_cell2.bin","rb");
    fread(&ESsize,sizeof(int),1,fLoad);
    for(i=0;i<ESsize;i++){
        fread(&(temp2.x),sizeof(int),1,fLoad);
        fread(&(temp2.y),sizeof(int),1,fLoad);
        fread(&(temp2.energy),sizeof(int),1,fLoad);
        fread(temp2.name,sizeof(char),6,fLoad);
        if(E[temp2.y][temp2.x]/10==0) E[temp2.y][temp2.x]+=20;
        else{
            COLOR(RED); printf("Wrong file!"); COLOR(WHITE);
            fflush(stdin); getchar();
            return 0;
        }
        createCell(&cell2Head,temp2);
    }
    int turn2;
    fread(&turn2,sizeof(int),1,fLoad);
    fclose(fLoad);



    if(cell2Head==NULL) singlePlayerMenu(cell1Head,ESHead);
    else multiPlayerMenu(cell1Head,cell2Head,ESHead,turn2);
    return 1;
}

bool save(cell *cell1Head, cell *cell2Head, ES *ESHead, int turn2){

    int cell1Num=0,cell2Num=0,ESNum=0;
    cell *cur1=cell1Head;
    cell *cur2=cell2Head;
    ES *cur3=ESHead;

    for(;cur1!=NULL;cell1Num++,cur1=cur1->next);
    for(;cur2!=NULL;cell2Num++,cur2=cur2->next);
    for(;cur3!=NULL;ESNum++,cur3=cur3->next);

    int i;
    FILE *fSave;
    fSave = fopen("saveFile_Cell1.bin","wb");

    cur1=cell1Head;
    fwrite(&cell1Num,sizeof(int),1,fSave);
    for(i=0;i<cell1Num;i++){
        fwrite(&(cur1->x),sizeof(int),1,fSave);
        fwrite(&(cur1->y),sizeof(int),1,fSave);
        fwrite(&(cur1->energy),sizeof(int),1,fSave);
        fwrite(cur1->name,sizeof(char),6,fSave);
        cur1=cur1->next;
    }
    fclose(fSave);

    fSave = fopen("saveFile_Cell2.bin","wb");
    cur2=cell2Head;
    fwrite(&cell2Num,sizeof(int),1,fSave);
    for(i=0;i<cell2Num;i++){
        fwrite(&(cur2->x),sizeof(int),1,fSave);
        fwrite(&(cur2->y),sizeof(int),1,fSave);
        fwrite(&(cur2->energy),sizeof(int),1,fSave);
        fwrite(cur2->name,sizeof(char),6,fSave);
        cur2=cur2->next;
    }
    fwrite(&turn2,sizeof(int),1,fSave);
    fclose(fSave);

    fSave = fopen("saveFile_ES.bin","wb");
    cur3=ESHead;
    fwrite(&ESNum,sizeof(int),1,fSave);
    for(i=0;i<ESNum;i++){
        fwrite(&(cur3->x),sizeof(int),1,fSave);
        fwrite(&(cur3->y),sizeof(int),1,fSave);
        fwrite(&(cur3->value),sizeof(int),1,fSave);
        cur3=cur3->next;
    }
    fclose(fSave);

    display();
    printf("\nSaved Successfully!\n");
    fflush(stdin); getchar();

    return 1;
}
