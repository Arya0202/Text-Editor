#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void printChar(char ch, int n)    //printing characters
{
    while(n--)
    {
        putchar(ch);
    }
}

void title()
{
    system("cls");
    system("COLOR 0B");
    cout<<"\n\n\t";
    printChar('=', 40);
    cout<<" TEXT EDITOR ";
    printChar('=', 40);
    cout<<endl;
}

void gotoxy(int x,int y)
{
    COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);
}

class undoCmd                       //class for undo command
{
    public:
    int lineNumber;
    string text;
    int commandNumber;
    int mLine;
    int nLine;
};

class node                                 //class for nodes
{
    public:
    string data;
    node * next;
};

class linked_list                          //class for linked list
{
public:
    node * head;
    node * tail;
    int numOfLines = 0;
    int next = 1;
    stack <undoCmd> undoStack;
    stack <undoCmd> redoStack;
    ofstream outfile;
    int a[100];

    linked_list()
    {
        int choice = -1;
        head = NULL;
        tail = NULL;
        int prevPagePrinted = 1;

    SetConsoleTitle("TEXT EDITOR | JIIT");
    system("color 0D");                   //setting console color

    // making password protected
    int i, k = 0;
    char pas[6];
    string passw = "12345", p = "";
    gotoxy(42, 8);
    cout<<"\t\tLOGIN";
    gotoxy(42, 10);
    cout<<"____________________________________";
    gotoxy(42, 11);
    cout<<"|\tEnter password :             |";
    gotoxy(42, 12);
    cout<<"|__________________________________|";
    cout<<"\n\t\t\t\t\t";
    gotoxy(65, 11);
    while(k < 5)
    {
        pas[k]=getch();
        cout<<"*";
        k++;
    }
    p = pas;
    if(p.compare(passw) == 0)
    {
        getch();
        system("cls");
        gotoxy(10,3);
        cout<<"<<<< Loading Please Wait >>>>";
        for(i = 0; i < 5; i++)
        {
            cout<<"\t*";
            Sleep(500);
        }

        //printing the welcome message
        cout<<" \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
        cout<<"\n\n\t\t\t\t\t     *                    *";
        cout<<"\n\n\t\t\t\t\t     *       Welcome      *";
        cout<<"\n\n\t\t\t\t\t     *                    *";
        cout<<"\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
        cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
        getch();

    title();

    //printing the team name
    cout<<"\n\n\t\t\t\tLab Final Odd Semester 2022";
    cout<<"\n\n\t\t\t   Team : Arya Bagla , Shaheera Fatima & Anshul\n\n\t\t\t\t  9921103169\t 9921103172\t9921103176";
    cout<<"\n\n\t\t\t Jaypee Institute of Information Technology\n\t\t\t";
    printChar('=',45);
    cout<<"\n\n\n\t\t\t      Press any key to Enter  ";
    getch();

    for(int x = 0; x < 100; x++) //initializing array
        a[x] = 0;

    while(choice != 0)
    {
        title();
        cout<<"\n\t";
        printChar('*',94);
        //printing menu
            cout<<"\n\n\t\t\t\t\tPlease choose the task you want to perform  :\n\n\t\t\t\t\t1. Insert text into Line N"<<endl;
            cout<<"\t\t\t\t\t2. Delete line N\n\t\t\t\t\t3. Swap line N and line M\n\t\t\t\t\t4. Replace text in Line N"<<endl;;
            cout<<"\t\t\t\t\t5. Print all\n\t\t\t\t\t6. Save into a .txt file\n\t\t\t\t\t7. Undo\n\t\t\t\t\t8. Redo"<<endl;
            cout<<"\t\t\t\t\t9. Logout"<<endl<<"\n\t\t\t\t\t";
            cin>>choice;
            cout<<endl;

            switch(choice)
            {
                case 1:                                 //Insertion of a line
            {
                int lineGiven;
                string dataGiven;
                cout<<"\t\t\t\t\tEnter line number you want the text to be placed into : ";
                cin >> lineGiven;
                cout<<"\t\t\t\t\tEnter text : ";
                cin.ignore(1);
                getline(cin,dataGiven);
                dataGiven += "\n";

                if (lineGiven == numOfLines || a[lineGiven - 1] == 1)
                {
                    int ch;
                    cout<<"\t\t\t\t\tEnter 1 to replace the last line, enter 2 to insert a new line : ";
                    cin>>ch;
                    if (ch == 1)
                    {
                        replaceTextInLine(dataGiven,lineGiven);
                    }
                    else if (ch == 2)
                    {
                        addToTail(dataGiven);
                    }
                }
                else if (lineGiven == 1)
                {
                    addToHead(dataGiven);
                }
                else if (lineGiven > numOfLines)
                {
                    insertNext(dataGiven,lineGiven);
                }
                else if (lineGiven < numOfLines)
                {
                    insertTextInBetween(dataGiven,lineGiven);
                }
                a[lineGiven - 1] = 1;
            }
            break;

            case 2:                                            //Deletion of a line
            {
                int lineGiven;
                cout<<"\n\t\t\t\t\tEnter the line you want to delete : ";
                cin>>lineGiven;
                deleteLine(lineGiven);
                Sleep(3000);
            }
            break;

            case 3:                                            //Interchanging two lines
            {
                int lineGiven1;
                int lineGiven2;
                cout<<"\t\t\t\t\tEnter line 1 you want to swap : ";
                cin>>lineGiven1;
                cout<<"\n\t\t\t\t\tEnter line 2 you want to swap : ";
                cin>>lineGiven2;
                moveNtoM(lineGiven1, lineGiven2);
            }
            break;

            case 4:
            {
                int lineGiven;
                string dataGiven;
                cout<<"\t\t\t\t\tEnter line you want to change the content of : ";
                cin>>lineGiven;
                if (lineGiven > numOfLines)
                {
    cout<<"\n\t\t\t\t\tThe line you entered exceeds the existing number of lines..."<<endl;
                }
                else
                {
                    cout<<"\n\t\t\t\t\tEnter the new text : ";
                    cin>>dataGiven;
                    dataGiven += "\n";
                    replaceTextInLine(dataGiven, lineGiven);
                }
            }
            break;

            case 5:                            //Printing the whole list
            {
                printall();
                Sleep(3000);
            }
            break;

            case 6:                            //Saving the list into a txt file
            {
                saveAll();
            }
            break;

            case 7:
            {
                if (undoStack.empty())
                {
                    cout<<"\n\t\t\t\t\tNo command."<<endl;
                    Sleep(3000);
                }
                else
                {
                    undo();
                    Sleep(3000);
                }
            }
            break;

            case 8:
            {
                if (redoStack.empty())
                {
                    cout<<"\n\t\t\t\t\tNo command."<<endl;
                    Sleep(3000);
                }
                else
                {
                    redo();
                    Sleep(3000);
                }
            }
            break;

            case 9:
                {
                    cout<<"\n\n\t\t\t\t\tLOGGING OUT!!!"<<endl;
                    exit(0);
                }
            break;

            default:
                cout<<"\n\t\t\t\t\tInvalid choice !!!"<<endl;
        }
    }
    }
    else
    {
        printf("\n\n\n\n\t\t\t\t\t  Wrong Password .Please try again.\n");
        getch();
    }

        cout<<"\n\t";
        printChar('*',80);

    }

    void addToHead(string dataGiven)                    //this function will add to Head
    {
        if (head == NULL)                //no node, empty linked list
        {
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            head = temp;
            tail = head;
            numOfLines++;
        }
        else                           //one or more than one node
        {
            node * temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            temp->next = head;
            head = temp;
            numOfLines++;
        }

        undoCmd addedToHead;
        addedToHead.lineNumber = 1;
        addedToHead.commandNumber = 1;
        addedToHead.text = dataGiven;
        undoStack.push(addedToHead);
    }

    void undoAddToTail(string dataGiven)                   //an extra function used to add to tail
    {
        if (head == NULL)                     //no node, empty linked list
        {
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            head = temp;
            tail = head;
            numOfLines++;
        }
        else                            //one or more than one node
        {
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            numOfLines++;
        }
    }

    void undoDeleteTail()                                     //an extra function used to delete from tail
    {
        node *temp = head;
        if (head == NULL)
        {
            cout<<"Nothing to be deleted."<<endl;
        }
        else if (head == tail)
        {
            temp = head;
            string backup = temp->data;
            delete(temp);
            head = NULL;
            tail = NULL;
            numOfLines--;
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            delete temp->next;
            temp->next = NULL;
            numOfLines--;
        }
    }

    void addToTail(string dataGiven)                     //this function will add to Tail
    {
        if (head == NULL)                        //no node, empty linked list
        {
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            head = temp;
            tail = head;
            numOfLines++;
        }
        else                       //one or more than one node
        {
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            numOfLines++;
        }

        undoCmd addedToTail;
        addedToTail.lineNumber = 1;
        addedToTail.commandNumber = 8;
        addedToTail.text = dataGiven;
        undoStack.push(addedToTail);
    }

    void deleteHead()    //function used to delete the very first element, update the head
    {
        string backup = head->data;
        node *temp = head;
        node *nextNode = head->next;
        head = nextNode;
        delete(temp);
        numOfLines--;

        undoCmd deletedHead;
        deletedHead.text = backup;
        deletedHead.lineNumber = 1;
        deletedHead.commandNumber = 3;
        undoStack.push(deletedHead);
    }

    void deleteTail()        //function used to delete the very last element, and update the tail
    {
        node *temp = head;
        if (head == NULL)
        {
            cout<<"\n\t\t\t\t\tNothing to be deleted."<<endl;
        }
        else if (head == tail)
        {
            temp = head;
            string backup = temp->data;
            delete(temp);
            head = NULL;
            tail = NULL;
            numOfLines--;

            undoCmd deletedTail;
            deletedTail.text = backup;
            deletedTail.lineNumber = 1;
            deletedTail.commandNumber = 7;
            undoStack.push(deletedTail);
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string backup = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            numOfLines--;

            undoCmd deletedTail;
            deletedTail.text = backup;
            deletedTail.lineNumber = 1;
            deletedTail.commandNumber = 7;
            undoStack.push(deletedTail);
        }
    }

    void insertTextInBetween(string dataGiven, int lineGiven)           //this function will insert text in the given line, and will push all the other lines
    {
        if (lineGiven == 0)
        {
            cout<<"\n\t\t\t\t\tThere's no line 0!!!!\n\t\t\t\t\tInvalid Choice"<<endl;
        }
        else if (lineGiven == 1)
        {
            if (head == NULL)                //no node, empty linked list
            {
                node *temp;
                temp = new node;
                temp->data = dataGiven;
                temp->next = NULL;
                head = temp;
                tail = head;
                numOfLines++;
            }
            else                                        //one or more than one node
            {
                node *temp;
                temp = new node;
                temp->data = dataGiven;
                temp->next = NULL;
                temp->next = head;
                head = temp;
                numOfLines++;
            }
        }
        else
            {
            node * prevNode = head;
            node * nextNode = head;
            node * temp = new node();
            temp->data = dataGiven;
            temp->next = NULL;
            int iterator = 2;
            while(iterator < lineGiven)
            {
                prevNode = prevNode->next;
                nextNode = nextNode->next;
                iterator ++;
            }
            nextNode = nextNode->next;
            prevNode->next = temp;
            temp->next = nextNode;
            numOfLines++;

            undoCmd insertedInBetween;
            insertedInBetween.lineNumber = lineGiven;
            insertedInBetween.commandNumber = 6;
            insertedInBetween.text = dataGiven;
            undoStack.push(insertedInBetween);
        }
    }

    void replaceTextInLine(string dataGiven,int lineGiven)                  //this function will overwrite anything written in the given line
    {
        undoCmd replacedLine;
        if (numOfLines < lineGiven)
        {
            cout<<"\n\t\t\t\t\tThe line you entered exceeds the existing number of      lines..."<<endl;
        }
        else if (lineGiven == 0)
        {
            cout<<"\n\t\t\t\t\tThere's no line 0!!!!\n\t\t\t\t\tInvalid Choice"<<endl;
        }
        else if (numOfLines >= lineGiven )
        {
            node *temp = head;
            int goToLine = 1;
            while(goToLine < lineGiven)
            {
                temp = temp->next;
                goToLine++;
            }
            string backup = temp->data;
            temp->data = dataGiven;    //change what is inside the node number    that has been given as line parameter

            replacedLine.lineNumber = lineGiven;
            replacedLine.text = backup;
            replacedLine.commandNumber = 4;
            undoStack.push(replacedLine);
        }
    }

    void deleteLine(int lineGiven)                    //this function should delete anything in the given line, also decreases the numOfLines
    {
        if (head == NULL)
        {
            cout<<"\n\t\t\t\t\tThere is no line to be deleted/removed."<<endl;
        }
        else if(head == tail)
        {
            node *temp = head;
            delete(temp);
            head = NULL;
            tail = NULL;
            numOfLines--;
        }
        else if(lineGiven == 0)
        {
            cout<<"\n\t\t\t\t\tThere's no line 0!!!!\n\t\t\t\t\tInvalid Choice"<<endl;
        }
        else if(lineGiven == 1)
        {
            string backup = head->data;
            node *temp = head;
            node *nextNode = head->next;
            head = nextNode;
            delete(temp);
            numOfLines--;
            undoCmd headRemoved;
            headRemoved.text = backup;
            headRemoved.lineNumber = 1;
            headRemoved.commandNumber = 12;
            undoStack.push(headRemoved);
        }
        else if(lineGiven == numOfLines)
        {
            node *temp = head;
            undoCmd deletedLine;
            deletedLine.commandNumber = 11;
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string backup = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            numOfLines--;

            deletedLine.text = backup;
            deletedLine.lineNumber = lineGiven;
            undoStack.push(deletedLine);

        }
        else if (lineGiven > numOfLines)
        {
            cout<<"\n\t\t\t\t\tEntered line is larger than existing lines..."<<endl;
        }
        else if (lineGiven < numOfLines)
        {
            undoCmd deletedLine;
            deletedLine.commandNumber = 10;
            node *prevNode = head;
            node *nextNode = head;
            node *temp = head;
            int iterator = 2;
            while(iterator < lineGiven)
            {
                prevNode = prevNode->next;
                nextNode = nextNode->next;
                iterator++;
            }
            nextNode = nextNode->next;
            temp = nextNode;
            nextNode = nextNode->next;
            prevNode->next = nextNode;
            string backup = temp->data;
            delete(temp);
            numOfLines--;
            deletedLine.text = backup;
            deletedLine.lineNumber = lineGiven;
            undoStack.push(deletedLine);
        }
    }

    void insertNext(string dataGiven, int lineGiven)                  //will print /n lines if given line is larger than numOfLines
    {
        undoCmd insertedNext;
        insertedNext.lineNumber = 0;
        insertedNext.text = dataGiven;
        insertedNext.commandNumber = 9;
        if (head == NULL)
        {
            while(numOfLines < lineGiven - 1)
            {
                undoAddToTail("\n");
                insertedNext.lineNumber++;
            }
            undoAddToTail(dataGiven);
        }
        else
        {
            while(numOfLines < lineGiven - 1)
            {
                undoAddToTail("\n");
                insertedNext.lineNumber++;
            }
            undoAddToTail(dataGiven);
        }
        undoStack.push(insertedNext);
    }

    void moveNtoM(int nLineGiven, int mLineGiven)                           //function used to Move line N into line M
    {
        if (nLineGiven == 1)
        {
            string headText = head->data;
            deleteHead();
            insertTextInBetween(headText,mLineGiven);
        }
        else
        {
            node *temp = head;
            int iterator = 1;
            while(iterator < nLineGiven)
            {
                temp = temp -> next;
                iterator++;
            }
            string dataSaved = temp->data;
            deleteLine(nLineGiven);
            insertTextInBetween(dataSaved,mLineGiven);
        }

        undoCmd moveHeadToM;
        moveHeadToM.commandNumber = 2;
        moveHeadToM.nLine = nLineGiven;
        moveHeadToM.mLine= mLineGiven;
        undoStack.push(moveHeadToM);
    }

    int flag = 0;
    void undo()                                                     //function used to undo the last action taken
    {
        flag ++;
        undoCmd temp = undoStack.top();
        if (temp.commandNumber == 1)
        {
            cout<<"\n\t\t\t\t\tAdded To head, removing from head..."<<endl;
            deleteHead();
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 2)
        {
            cout<<"\n\t\t\t\t\tMoved M to N, moving N to M"<<endl;
            moveNtoM(temp.mLine, temp.nLine);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 3)
        {
            cout<<"\n\t\t\t\t\tDeleted head, replacing head..."<<endl;;
            addToHead(temp.text);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 4)
        {
            cout<<"\n\t\t\t\t\tReplaced line, replacing again..."<<endl;
            replaceTextInLine(temp.text,temp.lineNumber);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 5)
        {
            cout<<"\n\t\t\t\t\tInserted to Head, removing from head..."<<endl;
            deleteHead();
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 6)
        {
            cout<<"\n\t\t\t\t\tInserted in between, removing that line..."<<endl;
            deleteLine(temp.lineNumber);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 7)
        {
            cout<<"\n\t\t\t\t\tDeleted Tail, inserting again..."<<endl;
            addToTail(temp.text);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 9)
        {
            cout<<"\n\t\t\t\t\tAdded to tail, removing from tail..."<<endl;
            deleteTail();
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 10)
        {
            int whatever = temp.lineNumber;
            while(whatever >= 0){
                undoDeleteTail();
                whatever--;
            }
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 11)
        {
            cout<<"\n\t\t\t\t\tLine deleted, inserting again..."<<endl;
            insertTextInBetween(temp.text, temp.lineNumber);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 12)
        {
            cout<<"\n\t\t\t\t\tLast line deleted, inserting again..."<<endl;
            addToTail(temp.text);
            redoStack.push(temp);
            undoStack.pop();
        }
        else if (temp.commandNumber == 13)
        {
            cout<<"\n\t\t\t\t\tFirst line deleted, inserting again..."<<endl;
            addToHead(temp.text);
            redoStack.push(temp);
            undoStack.pop();
        }
    }

    void redo()                                                 //function used to redo the last action taken
    {
        if(flag > 0)
        {
            flag --;
            undoCmd temp = redoStack.top();
            if (temp.commandNumber == 1)
            {
                cout<<"\n\t\t\t\t\tReinserting into head..."<<endl;
                addToHead(temp.text);
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 2)
            {
                cout<<"\n\t\t\t\t\tMoved N to M, moving M to N"<<endl;
                moveNtoM(temp.nLine, temp.mLine);
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 3)
            {
                cout<<"\n\t\t\t\t\tAdded To head, removing from head..."<<endl;
                deleteHead();
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 4)
            {
                cout<<"\n\t\t\t\t\tReplaced line, replacing again..."<<endl;
                replaceTextInLine(temp.text,temp.lineNumber);
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 5)
            {
                cout<<"\n\t\t\t\t\tRemoved from Head, reinserting into head..."<<endl;
                addToHead(temp.text);
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 6)
            {
                cout<<"\n\t\t\t\t\tDeleted in between, reinserting that line..."<<endl;
                insertTextInBetween(temp.text, temp.lineNumber);
                undoStack.push(temp);
                redoStack.pop();
            }
            else if (temp.commandNumber == 7)
            {
            cout<<"\n\t\t\t\t\tInserted Tail, removing it..."<<endl;
            deleteTail();
            undoStack.push(temp);
            redoStack.pop();
        }
        else if (temp.commandNumber == 8)
        {
            cout<<"\n\t\t\t\t\tRemoved from tail, adding to tail..."<<endl;
            addToTail(temp.text);
            undoStack.push(temp);
            redoStack.pop();
        }
        else if (temp.commandNumber == 9)
        {
            int number = temp.lineNumber;
            while(number >= 0){
                undoAddToTail(temp.text);
                number--;
            }
            undoStack.push(temp);
            redoStack.pop();
        }
        else if (temp.commandNumber == 10)
        {
            cout<<"\n\t\t\t\t\tLine inserted, deleting it..."<<endl;
            deleteLine(temp.lineNumber);
            undoStack.push(temp);
            redoStack.pop();
        }
        else if (temp.commandNumber == 11)
        {
            cout<<"\n\t\t\t\t\tLast line inserted, deleting it..."<<endl;
            deleteTail();
            undoStack.push(temp);
            redoStack.pop();
        }
        else if (temp.commandNumber == 12)
        {
            cout<<"\n\t\t\t\t\tFirst line inserted, deleting it..."<<endl;
            deleteHead();
            undoStack.push(temp);
            redoStack.pop();
        }
        }
        else
            cout<<"\n\t\t\t\t\tRedo function can't be performed"<<endl;
    }


    void printall()                                                 //function used to print the whole linked list
    {
        node * temp = head;
        int linePrinted = 1;
        int pagePrinted = 2;
        int choice;
        if (head == NULL)
        {
            cout<<"\n\t\t\t\t\tNo elements here!!!"<<endl;
        }
        else{
            while(temp!=NULL)
            {
                if (linePrinted == 1)
                {
                    cout<<"\n\t\t\t\t\t-------------------Page "<<"1"<<"-------------------\n";
                }
                else if ((linePrinted-1) % 10 == 0)
                {
                    cout<<"\n\t\t\t\t\t-------------------Page "<<pagePrinted<<"-------------------\n";
                    pagePrinted++;

                }
                cout<<"\t\t\t\t\t"<<linePrinted<<") "<<temp->data<<endl;
                temp = temp->next;
                linePrinted++;
            }
        }
    }

    void saveAll()                                                  //function to save .txt file
    {
        node * temp = head;
        int linePrinted = 1;
        int pagePrinted = 2;
        string fileName;
        cout<<"\n\t\t\t\t\tEnter the file name : ";
        cin>>fileName;
        fileName += ".txt";
        outfile.open(fileName, ios_base::trunc);
        while(temp!=NULL)
        {
            outfile<<temp->data;
            temp = temp->next;
            linePrinted++;
        }
        outfile.flush();
        outfile.close();
    }
};

int main()
{
    linked_list ourList;
    return 0;
}
