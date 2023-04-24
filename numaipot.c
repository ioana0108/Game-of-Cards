#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char colors[5] = {'s', 'h', 'c', 'd'}, numbers[14] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
int values[14] = {15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

typedef struct card
{
    char number;
    char color;
    int value;
    struct card *next;
} Deck;

Deck *addCard(Deck *list, char number, char color, int value)
{
    Deck *NewCard = calloc(1, sizeof(Deck));
    if (list == NULL)
    {
        NewCard->number = number;
        NewCard->color = color;
        NewCard->value = value;
        NewCard->next = NULL;

        return NewCard;
    }
    else
    {
        NewCard->number = number;
        NewCard->color = color;
        NewCard->value = value;

        Deck *last = list;

        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = NewCard;
        last = NewCard;

        return list;
    }
}

Deck *initDeck(Deck *list)
{
    int i, j;
    for (i = 0; i < 13; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            list = addCard(list, numbers[i], colors[j], values[i]);
        }
    }
    return list;
}

void afisare(Deck *list, FILE *output)
{
    Deck *contor = list;
    while (contor != NULL)
    {
        fprintf(output, "%c%c ", contor->number, contor->color);
        contor = contor->next;
    }
}

Deck *invert(Deck *initialList, Deck *invertedList)
{
    if (initialList == NULL)
    {
        return NULL;
    }
    else
    {
        invertedList = invert(initialList->next, invertedList);
        invertedList = addCard(invertedList, initialList->number, initialList->color, initialList->value);
    }

    return invertedList;
}

Deck *intercalation(Deck *list)
{
    Deck *copylist;

    copylist = list;

    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        int nr_cards = 0;
        while (copylist != NULL)
        {
            nr_cards++;
            copylist = copylist->next;
        }
        int i;
        copylist = list;
        Deck *list1 = NULL; 
        Deck *list2 = NULL;
        Deck *finalList = NULL;
        for (i = 0; i < (nr_cards / 2); i++)
        {
            list1 = addCard(list1, copylist->number, copylist->color, copylist->value); 
            copylist = copylist->next;                                                  
        }
        for (i = nr_cards / 2; i < nr_cards; i++)
        {
            list2 = addCard(list2, copylist->number, copylist->color, copylist->value); 
            copylist = copylist->next;
        }
        Deck *clist1 = list1, *clist2 = list2;

        for (i = 0; i < nr_cards; i++)
        {
            if (i % 2 == 0)
            {
                finalList = addCard(finalList, clist1->number, clist1->color, clist1->value); 
                clist1 = clist1->next;
            }
            else
            {
                finalList = addCard(finalList, clist2->number, clist2->color, clist2->value);
                clist2 = clist2->next;
            }
        }

        return finalList;
    }
}

Deck *Mongean(Deck *list)
{
    Deck *list1 = NULL, *list2 = NULL; // nu mai aloc pentru ea???

    Deck *copylist = list;

    list1 = addCard(list1, copylist->number, copylist->color, copylist->value);

    copylist = copylist->next;

    list1->next = NULL;

    int i = 1;
    while (copylist != NULL)
    {
        if (i % 2 == 1)
        {
            list1 = addCard(list1, copylist->number, copylist->color, copylist->value);
        }
        copylist = copylist->next;
        i++;
    }
    Deck *clist1 = list1;
    list1 = invert(clist1, list1);

    copylist = list;
    copylist = copylist->next;

    i = 1;
    while (copylist != NULL)
    {
        if (i % 2 == 0)
        {
            list2 = addCard(list2, copylist->number, copylist->color, copylist->value);
        }
        copylist = copylist->next;
        i++;
    }

    while (list2 != NULL)
    {
        list1 = addCard(list1, list2->number, list2->color, list2->value);
        list2 = list2->next;
    }

    Deck *mongeanList = list1;

    return mongeanList;
}

Deck *npiles(Deck *list, int N, int *indexes)
{
    Deck *npilesList = NULL, *clist = list;

    int nr_cards = 0;
    while (clist != NULL)
    {
        nr_cards++;
        clist = clist->next;
    }

    int nr_cards_subdeck = nr_cards / N;

    clist = list;

    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < nr_cards_subdeck * (indexes[i] - 1); j++)
        {
            clist = clist->next;
        }

        for (j = 0; j < nr_cards_subdeck; j++)
        {
            npilesList = addCard(npilesList, clist->number, clist->color, clist->value);

            clist = clist->next;
        }

        clist = list;
    }

    return npilesList;
}

int got_card(char card, int spades, int hearts, int clubs, int diamonds)
{
    if (card == colors[0]) // spades
    {
        if (spades != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (card == colors[1])
    {
        if (hearts != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (card == colors[2])
    {
        if (clubs != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (card == colors[3])
    {
        if (diamonds != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}

char findCard(char last_card_played, int spades, int hearts, int clubs, int diamonds) 
{
    char next_card;
    if (last_card_played == colors[0]) // spades
    {
        if (hearts != 0)
        {
            next_card = colors[1];
        }
        else
        {
            if (clubs != 0)
            {
                next_card = colors[2];
            }
            else
            {
                next_card = colors[3];
            }
        }
    }
    else if (last_card_played == colors[1]) // hearts
    {
        if (clubs != 0)
        {
            next_card = colors[2];
        }
        else
        {
            if (diamonds != 0)
            {
                next_card = colors[3];
            }
            else
            {
                next_card = colors[0];
            }
        }
    }
    else if (last_card_played == colors[2]) // clubs
    {
        if (diamonds != 0)
        {
            next_card = colors[3];
        }
        else
        {
            if (spades != 0)
            {
                next_card = colors[0];
            }
            else
            {
                next_card = colors[1];
            }
        }
    }
    else if (last_card_played == colors[3]) // diamonds
    {
        if (spades != 0)
        {
            next_card = colors[0];
        }
        else
        {
            if (hearts != 0)
            {
                next_card = colors[1];
            }
            else
            {
                next_card = colors[2];
            }
        }
    }

    return next_card;
}

int RollingStone(Deck *list) 
{
    Deck *copy = list;
    Deck *list1 = NULL, *list2 = NULL, *list3 = NULL, *list4 = NULL;

    // am impartit pachetul mare in 4 pachete mai mici pt fiecare jucator
    int i;
    for (i = 0; i < 13; i++)
    {
        list1 = addCard(list1, copy->number, copy->color, copy->value); // nu stiu ce sa returnez ok
        copy = copy->next;
    }

    for (i = 0; i < 13; i++)
    {
        list2 = addCard(list2, copy->number, copy->color, copy->value);
        copy = copy->next;
    }

    for (i = 0; i < 13; i++)
    {
        list3 = addCard(list3, copy->number, copy->color, copy->value);
        copy = copy->next;
    }

    for (i = 0; i < 13; i++)
    {
        list4 = addCard(list4, copy->number, copy->color, copy->value);
        copy = copy->next;
    }

    // numar cate carti de fiecare culoare are fiecare jucator

    int spades_1, diamonds_1, hearts_1, clubs_1, spades_2, diamonds_2, hearts_2, clubs_2, spades_3, diamonds_3, hearts_3, clubs_3, spades_4, diamonds_4, hearts_4, clubs_4;
    spades_1 = diamonds_1 = hearts_1 = clubs_1 = spades_2 = diamonds_2 = hearts_2 = clubs_2 = spades_3 = diamonds_3 = hearts_3 = clubs_3 = spades_4 = diamonds_4 = hearts_4 = clubs_4 = 0;

    Deck *clist1 = list1, *clist2 = list2, *clist3 = list3, *clist4 = list4;
    for (i = 0; i < 13; i++)
    {
        if (clist1->color == colors[0])
        {
            spades_1++;
        }
        else if (clist1->color == colors[1])
        {
            hearts_1++;
        }
        else if (clist1->color == colors[2])
        {
            clubs_1++;
        }
        else if (clist1->color == colors[3])
        {
            diamonds_1++;
        }

        clist1 = clist1->next;
    }
    for (i = 0; i < 13; i++)
    {
        if (clist2->color == colors[0])
        {
            spades_2++;
        }
        else if (clist2->color == colors[1])
        {
            hearts_2++;
        }
        else if (clist2->color == colors[2])
        {
            clubs_2++;
        }
        else if (clist2->color == colors[3])
        {
            diamonds_2++;
        }
        clist2 = clist2->next;
    }

    for (i = 0; i < 13; i++)
    {
        if (clist3->color == colors[0])
        {
            spades_3++;
        }
        else if (clist3->color == colors[1])
        {
            hearts_3++;
        }
        else if (clist3->color == colors[2])
        {
            clubs_3++;
        }
        else if (clist3->color == colors[3])
        {
            diamonds_3++;
        }
        clist3 = clist3->next;
    }

    for (i = 0; i < 13; i++)
    {
        if (clist4->color == colors[0])
        {
            spades_4++;
        }
        else if (clist4->color == colors[1])
        {
            hearts_4++;
        }
        else if (clist4->color == colors[2])
        {
            clubs_4++;
        }
        else if (clist4->color == colors[3])
        {
            diamonds_4++;
        }
        clist4 = clist4->next;
    } 

    int nr_cards_played = 0, nr_cards_1 = 13, nr_cards_2 = 13, nr_cards_3 = 13, nr_cards_4 = 13;

    char next_color;
    char last_color_played = colors[0]; 

    while (nr_cards_1 != 0 && nr_cards_2 != 0 && nr_cards_3 != 0 && nr_cards_4 != 0) 
    {
        
        if (got_card(last_color_played, spades_1, hearts_1, clubs_1, diamonds_1) == 1) 
        {
            next_color = last_color_played; 

            if (next_color == colors[0])
            {
                spades_1--; 
            }
            else if (next_color == colors[1])
            {
                hearts_1--; 
            }
            else if (next_color == colors[2]) 
            {
                clubs_1--;
            }
            else if (next_color == colors[3])
            {
                diamonds_1--;
            }

            nr_cards_1--;
            nr_cards_played++; 

            last_color_played = next_color; 
        }                                   
        else                                
        {
            nr_cards_1 += nr_cards_played; 

            if (last_color_played == colors[0])
            {
                spades_1 += nr_cards_played; 
            }
            else if (last_color_played == colors[1])
            {
                hearts_1 += nr_cards_played;
            }
            else if (last_color_played == colors[2]) 
            {
                clubs_1 += nr_cards_played;
            }
            else if (last_color_played == colors[3])
            {
                diamonds_1 += nr_cards_played; 
            }
            nr_cards_played = 0;
            next_color = findCard(last_color_played, spades_1, hearts_1, clubs_1, diamonds_1); 
            
            if (next_color == colors[0])
            {
                spades_1--; 
            }
            else if (next_color == colors[1])
            {
                hearts_1--;
            }
            else if (next_color == colors[2]) 
            {
                clubs_1--;
            }
            else if (next_color == colors[3])
            {
                diamonds_1--;
            } 

            nr_cards_1--;
            nr_cards_played++;

            last_color_played = next_color; 
        }

        if (got_card(last_color_played, spades_2, hearts_2, clubs_2, diamonds_2) == 1) 
        {
            next_color = last_color_played; 

            if (next_color == colors[0])
            {
                spades_2--;
            }
            else if (next_color == colors[1])
            {
                hearts_2--;
            }
            else if (next_color == colors[2])
            {
                clubs_2--;
            }
            else if (next_color == colors[3])
            {
                diamonds_2--;
            }

            nr_cards_2--;
            nr_cards_played++;

            last_color_played = next_color; 
        }
        else 
        {
            nr_cards_2 += nr_cards_played; 

            if (last_color_played == colors[0])
            {
                spades_2 += nr_cards_played; 
            }
            else if (last_color_played == colors[1])
            {
                hearts_2 += nr_cards_played;
            }
            else if (last_color_played == colors[2]) 
            {
                clubs_2 += nr_cards_played;
            }
            else if (last_color_played == colors[3])
            {
                diamonds_2 += nr_cards_played;
            }
            nr_cards_played = 0;
            next_color = findCard(last_color_played, spades_2, hearts_2, clubs_2, diamonds_2); 

            if (next_color == colors[0])
            {
                spades_2--;
            }
            else if (next_color == colors[1])
            {
                hearts_2--;
            }
            else if (next_color == colors[2])
            {
                clubs_2--;
            }
            else if (next_color == colors[3])
            {
                diamonds_2--;
            }

            nr_cards_2--;
            nr_cards_played++;

            last_color_played = next_color; 
        }

        if (got_card(last_color_played, spades_3, hearts_3, clubs_3, diamonds_3) == 1)
        {
            next_color = last_color_played;

            if (next_color == colors[0])
            {
                spades_3--;
            }
            else if (next_color == colors[1])
            {
                hearts_3--;
            }
            else if (next_color == colors[2])
            {
                clubs_3--;
            }
            else if (next_color == colors[3])
            {
                diamonds_3--;
            }

            nr_cards_3--;
            nr_cards_played++;

            last_color_played = next_color; 
        }                                   
        else
        {
            nr_cards_3 += nr_cards_played;

            if (last_color_played == colors[0])
            {
                spades_3 += nr_cards_played; 
            }
            else if (last_color_played == colors[1])
            {
                hearts_3 += nr_cards_played;
            }
            else if (last_color_played == colors[2]) 
            {
                clubs_3 += nr_cards_played;
            }
            else if (last_color_played == colors[3])
            {
                diamonds_3 += nr_cards_played;
            }
            nr_cards_played = 0;
            next_color = findCard(last_color_played, spades_3, hearts_3, clubs_3, diamonds_3);

            if (next_color == colors[0])
            {
                spades_3--;
            }
            else if (next_color == colors[1])
            {
                hearts_3--;
            }
            else if (next_color == colors[2])
            {
                clubs_3--;
            }
            else if (next_color == colors[3])
            {
                diamonds_3--;
            }

            nr_cards_3--;
            nr_cards_played++;

            last_color_played = next_color;
        }

        if (got_card(last_color_played, spades_4, hearts_4, clubs_4, diamonds_4) == 1)
        {
            next_color = last_color_played;

            if (next_color == colors[0])
            {
                spades_4--;
            }
            else if (next_color == colors[1])
            {
                hearts_4--;
            }
            else if (next_color == colors[2])
            {
                clubs_4--;
            }
            else if (next_color == colors[3])
            {
                diamonds_4--;
            }

            nr_cards_4--;
            nr_cards_played++;

            last_color_played = next_color; 
        }
        else 
        {
            nr_cards_4 += nr_cards_played;

            if (last_color_played == colors[0])
            {
                spades_4 += nr_cards_played; 
            }
            else if (last_color_played == colors[1]) 
            {
                hearts_4 += nr_cards_played;
            }
            else if (last_color_played == colors[2]) 
            {
                clubs_4 += nr_cards_played;
            }
            else if (last_color_played == colors[3])
            {
                diamonds_4 += nr_cards_played; 
            }
            nr_cards_played = 0;
            next_color = findCard(last_color_played, spades_4, hearts_4, clubs_4, diamonds_4);

            if (next_color == colors[0])
            {
                spades_4--;
            }
            else if (next_color == colors[1])
            {
                hearts_4--;
            }
            else if (next_color == colors[2])
            {
                clubs_4--;
            }
            else if (next_color == colors[3])
            {
                diamonds_4--;
            }

            nr_cards_4--;
            nr_cards_played++;

            last_color_played = next_color;
        }
    }

    int player1 = 1, player2 = 2, player3 = 3, player4 = 4;
    if (nr_cards_1 == 0)
    {
        return player1;
    }
    else if (nr_cards_2 == 0)
    {
        return player2;
    }
    else if (nr_cards_3 == 0)
    {
        return player3;
    }
    else if (nr_cards_4 == 0)
    {
        return player4; 
    }
    return 0;
}

int main()
{
    Deck *list = NULL, *arrangedList = NULL;
    list = initDeck(list);
    char *sir = calloc(100, sizeof(char));
    char *sir2;
    int nr, i;

    FILE *input, *output;
    input = fopen("in", "r");
    output = fopen("out", "w");

    fscanf(input, "%s", sir);
    fscanf(input, "%d\n", &nr);
    sir2 = strdup(sir);
    arrangedList = list;

    for (i = 0; i < nr; i++)
    {
        fgets(sir, 100, input);
        if (strstr(sir, "inversare") != NULL)
        {
            arrangedList = invert(arrangedList, arrangedList);
        }
        else if (strstr(sir, "intercalare") != NULL)
        {
            arrangedList = intercalation(arrangedList);
            
        }

        else if (strstr(sir, "mongean") != NULL)
        {
            arrangedList = Mongean(arrangedList);
        }

        else if (strstr(sir, "npiles") != NULL)
        {
            sir = strtok(sir, " ");
            sir = strtok(NULL, " ");
            int nr = atoi(sir);
            int *indexes = calloc(nr, sizeof(int));

            int i;
            for (i = 0; i < nr; i++)
            {
                sir = strtok(NULL, " ");
                indexes[i] = atoi(sir);
            }

            arrangedList = npiles(arrangedList, nr, indexes);
        }
    }
    if (strcmp(sir2, "amestecare") == 0)  
    {
        afisare(arrangedList, output);
    }
    else
    {
        fprintf(output, "%d", RollingStone(arrangedList));
    }
    
    /*free(sir2);
    free(sir); */
    while(list != NULL)
    {
        free(list);
        list = list -> next;
    } 
    /*
    while(arrangedList != NULL)
    {
        free(arrangedList);
        arrangedList = arrangedList -> next;
    } */
    
} 