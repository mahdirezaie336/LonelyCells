void multiPlayerMenu(cell *head1, cell* head2, ES *ESHead, int turn){

    int p1CellNum,p2CellNum;
    if(head1==NULL){
        system("cls");
        int i,j,k;
        char address[40]="map.bin";
        if(getMap(address)==0) return;
        int n=mapSize;
        if(n<0) return;

        printf("Please enter number of 1st player's cells ");   //Getting number of cells
        COLOR(MAGENTA); printf("(will show as X): "); COLOR(WHITE);
        scanf("%d",&p1CellNum);
        printf("Please enter number of 2nd player's cells ");
        COLOR(YELLOW); printf("(will show as Y): "); COLOR(WHITE);
        scanf("%d",&p2CellNum);

        if(p1CellNum==0 && p2CellNum==0){
            COLOR(RED); printf("No cells. So there is no life here!\n"); COLOR(WHITE);
            fflush(stdin); getchar();
            return;
        }
        if(p1CellNum + p2CellNum >= n*n){
            COLOR(RED); printf("Cells overflew!\n"); COLOR(WHITE);
            fflush(stdin); getchar();
            return;
        }

        findEnegryStations(&ESHead);    //getting energy stations from map

        for(i=0;i<p1CellNum;i++){     //Generating 1st Player Cells
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
            createCell(&head1,temp);
        }
        for(i=0;i<p2CellNum;i++){     //Generating 2nd Player Cells
            while(1){           //Random Positioning Cells
                j=rand()%n;
                k=rand()%n;
                if(E[k][j]%10==3) continue; //this line doesn't let generate in forbidden blocks
                if(E[k][j]/10==0) break;  //this line doesn't let generate on other cells
            }
            E[k][j]+=20;
            cell temp;
            temp.x=j;
            temp.y=k;
            temp.energy=0;
            randString(5,temp.name);
            createCell(&head2,temp);
        }
    }

    while(1){       //game loop begins

        while(1){       //1st Player Turn
            if(turn==2){
                turn=0;
                break;
            }
            int choseCell;
            display();

            printf("\nPlease choose one of your cells:\n\n");
            COLOR(MAGENTA);
            printf("1st Player:\n");
            COLOR(WHITE);
            p1CellNum = displayChooseCellMenu(head1);
            scanf("%d",&choseCell);
            if(choseCell > p1CellNum || choseCell < 1){
                printf("Wrong Selection!\n");
                fflush(stdin);
                getche();
                continue;
            }
            display();

            cell *cur = head1;
            for(int i=1;i<choseCell;i++,cur=cur->next);
            bool changed = 1,flag,flag2;
            while(1){
                flag = 0;flag2 = 0;
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
                    flag = splitMenu(&head1,cur,1);
                    changed = 1;
                    break;
                case 3:
                    flag = boostEnergyMenu(cur,ESHead);
                    changed = 1;
                    break;
                case 4:
                    flag2 = save(head1,head2,ESHead,1);
                    changed = 1;
                    break;
                case 5:
                    flag = multipleMove(cur,1);
                    changed = 1;
                    break;
                case 0:
                    flag2 = 1;
                    break;
                case 9:
                    system("cls");
                    return;
                }
                if(flag || flag2) break;
            }
            if(flag2) continue;
            if(flag) break;
        }

        while(1){       //2nd Player Turn
            int choseCell;
            display();

            printf("\nPlease choose one of your cells:\n\n");
            COLOR(YELLOW);
            printf("2nd Player:\n");
            COLOR(WHITE);
            p2CellNum = displayChooseCellMenu(head2);
            scanf("%d",&choseCell);
            if(choseCell > p2CellNum || choseCell < 1){
                printf("Wrong Selection!\n");
                fflush(stdin);
                getche();
                continue;
            }
            display();

            cell *cur = head2;
            for(int i=1;i<choseCell;i++,cur=cur->next);

            bool changed = 1,flag,flag2;
            while(1){
                flag = 0;flag2 = 0;
                if(changed){
                    display();
                    printf("\n[1] Move\n[2] Split a Cell\n[3] Boost Energy\n[4] Save\n[5] Multiple Move\n[0] Cancel\n[9] Exit to Main Menu\n");
                }
                changed = 0;
                fflush(stdin);
                switch(_getch()-'0'){
                case 1:
                    flag = moveMenu(cur,2);
                    changed = 1;
                    break;
                case 2:
                    flag = splitMenu(&head2,cur,2);
                    changed = 1;
                    break;
                case 3:
                    flag = boostEnergyMenu(cur,ESHead);
                    changed = 1;
                    break;
                case 4:
                    flag2 = save(head1,head2,ESHead,2);
                    changed = 1;
                    break;
                case 5:
                    flag = multipleMove(cur,2);
                    changed = 1;
                    break;
                case 0:
                    flag2 = 1;
                    break;
                case 9:
                    system("cls");
                    return;
                }
                if(flag || flag2) break;
            }
            if(flag2) continue;
            if(flag) break;
        }

    }
}
