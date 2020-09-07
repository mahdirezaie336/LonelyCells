void singlePlayerMenu(cell *head,ES *ESHead){

    int cellNum;
    if(head==NULL && ESHead==NULL){     //checking if function is called by load or not
        system("cls");
        int i,j,k;
        if(getMap("map.bin")==0) return;
        int n=mapSize;
        if(n<0) return;

        printf("Please enter number of cells: ");   //Getting number of cells
        scanf("%d",&cellNum);
        if(cellNum==0){
            COLOR(RED); printf("No cells. So there is no life here!\n"); COLOR(WHITE);
            fflush(stdin); getchar();
            return;
        }
        if(cellNum>=n*n){
            COLOR(RED); printf("Cells overflew!\n"); COLOR(WHITE);
            fflush(stdin); getchar();
            return;
        }

        findEnegryStations(&ESHead);    //getting energy stations from map

        for(i=0;i<cellNum;i++){     //Generating Cells
            while(1){           //Random Positioning Cells
                j=rand()%n;
                k=rand()%n;
                if(E[k][j]%10==3) continue; //this line doesn't let generate in forbidden blocks
                if(E[k][j]/10==0) break;  //this line doesn't let generate on other cells
            }
            E[k][j]+=10;
            cell temp;
            temp.x=j;
            temp.y=k;
            temp.energy=0;
            randString(5,temp.name);
            createCell(&head,temp);
            //debugPrintList(head);
        }
    }

    while(1){       //game loop begins
        int choseCell;
        display();
        printf("\nPlease choose one of your cells:\n\n");
        cellNum = displayChooseCellMenu(head);
        scanf("%d",&choseCell);
        if(choseCell > cellNum || choseCell < 1) continue;

        cell *cur = head;
        for(int i=1;i<choseCell;i++,cur=cur->next);
        bool changed = 1;
        while(1){
            bool flag = 0;
            if(changed){
                display();
                printf("\n[1] Move\n[2] Split a Cell\n[3] Boost Energy\n[4] Save\n[5] Multiple Move\n[0] Cancel\n[9] Exit to Main Menu\n");
            }
            changed = 0;
            fflush(stdin);
            switch(_getch()-'0'){
            case 1:
                flag = moveMenu(cur,1);
                changed = 1;
                break;
            case 2:
                flag = splitMenu(&head,cur,1);
                changed = 1;
                break;
            case 3:
                flag = boostEnergyMenu(cur,ESHead);
                changed = 1;
                break;
            case 4:
                flag = save(head,NULL,ESHead,1);
                changed = 1;
                break;
            case 5:
                flag = multipleMove(cur,1);
                changed = 1;
                break;
            case 0:
                flag = 1;
                break;
            case 9:
                system("cls");
                return;
            }
            if(flag) break;
        }
    }
}
