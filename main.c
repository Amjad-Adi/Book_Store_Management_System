/*
Name: Amjad Kaher Sadeq Adi
ID: 1230800
Lecture section: 1
Lab section: 1L
*/
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
#define NAMESIZE 50
int enteredId,i,searchedIndex;//Global variables can be used because we have a scanf or loop before using either of them in any function so their initial value will be correct always.
double cost;//Global variable can be used because we have a scanf before using it in any function so its initial value will be correct always.
void uploadDataFile (char [][NAMESIZE],int [],double [],int *);//Function to get all the books data stored in a file.
void displayMainMenu ();//Fuction showing a menu for user to choose from what operation to perform.
void addBook (char [][NAMESIZE],int [],double [],int *);//Function to add a new book to the file.
void removeBook (char [][NAMESIZE],int [],double [],int *);//Function to remove an existing book from the system.
void searchForBook (char [][NAMESIZE],int [],double [],int );//Function that searches for a suggested book.
void updateDataFile (char [][NAMESIZE],int [],double[],int ); //Function to update the data in the file after finishing the user operations.
void printBooks (char [][NAMESIZE],int [],double [],int );//Function to print the Bookstore Data on the console screen.
int binarySearch (int [],int );//Function to do brinary search(Faster than linear search when posible (log(n^2)<n^2).

int main()
{
    char names[MAXSIZE][NAMESIZE];//Intilizing the name 2D array(Array of book names); Storing the names in every row and each coloum in a row having a letter from the name, Maximium letters:49,Maximum names 100  with max size of 100.
    int bins[MAXSIZE],operation,Rsize=0;//Intilizing the bins(Array of IDS) with max size of 100 ID for 100 book, the real size of the array to 0 initially
    double prices[MAXSIZE];//Intilizing the prices(Array of book cost) with max size of 100 cost for 100 book with a type of double
    printf("Welcome to My BookStore Management System:\n\n");//Welcoming message
    uploadDataFile (names,bins,prices,&Rsize);//Get datas from the file into the two arrays.
        do {
                displayMainMenu ();//View the main menu.
                scanf("%d",&operation);//Ask the user to enter a number representinf the operation as the main menu viewed.
                switch (operation)//Compare the entered value as follows:
                {
                    case 1:
                        addBook (names,bins,prices,&Rsize); break;//if the entered value was 1 then add a book.
                    case 2:
                        removeBook (names,bins,prices,&Rsize); break;//if the entered value was 2 then remove a book.
                    case 3:
                        searchForBook (names,bins,prices,Rsize); break;//if the entered value was 3 then search for a a book.
                    case 4:
                        printBooks (names,bins,prices,Rsize); break;//if the entered value was 4 then print the 2 arrays data to the screen.
                    case 5:
                        updateDataFile (names,bins,prices,Rsize); break;//if the entered value was 5 then update the Used file into the new operated values.
                    default:
                        printf("No such operation! Please try again.\n\n");//if any othe number was entered,tell the uer it's wrong and display the main menu again.
                }
        } while (operation!=5);//Check if operation=5,if its equal to 5 then exit the main menu and so the system!
    printf("\nThank you for using My bookStore Managment System. GoodBye.\n");//Printing an exit message
    return 0;
}

void uploadDataFile (char names[][NAMESIZE],int bins[],double prices[],int *size)
{
    FILE *In= fopen("books.txt","r");//Pointer to file "books.txt" in reading position.
        printf("Uploading data file ...\n");
        while (fscanf(In,"%s%d%lf",names[*size],&bins[*size],&prices[*size]) != EOF)//intilize a varizble that gets a value (1) for every number read, while also detecting the End Of File as EOF when no numbers/names was read.
            (*size)++;//Increase the real size of the array by one for every read 3 data.
        fclose(In);//Close the read file.
        printf("Data File uploaded\n\n");
}

void displayMainMenu ()
{
    printf("\nPlease Select an Operation <1-5>:\n1- Add a Book:\n2- Remove a Book:\n3- Search for a Book:\n4- Print Book List:\n5- Exis system:\n\n");//printing main menu.
}

void addBook (char names[][NAMESIZE],int bins[],double prices[],int *size)
{
    if (*size<MAXSIZE)//if the size of the array is more or equal to the max size,then the capacity is full,thus an error is displayed.
    {
        printf("Enter bin number for book\n");
        scanf("%d",&enteredId);//Asking the user to enter the bin of the book.
        for(i=0; enteredId>bins[i]&&i<*size; i++)
            continue;
        if(!(enteredId==bins[i]))
        {
            char enteredName[NAMESIZE];
            printf("Enter name of book\n");
            scanf("%s",enteredName);//Asking the user to enter the name of the book, No need to put & as the name points to enteredID[0] and no need to use gets(enteredName) as the charchter will not contain spaces.
            printf("Enter price of book\n");
            scanf("%lf",&cost);//Asking the user to enter the cost of the book.
            for(int j=*size+1; j>=i; j--)
                {
                    bins[j]=bins[j-1];
                    prices[j]=prices[j-1];
                    strcpy(names[j],names[j-1]);//Function from the string libary that copies the inormation from names[k] to names[k+1](K:*size=-j)
                }
            strcpy(names[i],enteredName);
            bins[i]=enteredId;
            prices[i]=cost;
            /*
            ID=5,bins={2,4,7,8,10},*size=5.
            checking for where the last elment where ID>bins[i] by entenering the first loop until either :
            1)first ID<bins[i]
            2)the end of the array was reached.
            which happens at i=2 in this case:
            Now we have successfully find the index of the elment which should be removed.
            we should check if the last bins[i] it stopped in is the same as the id, if not continue in the second loop:
            {
            In the second loop:(The array should be shifted left size-i times (3 in this example))
            (j=0)bins[5]=bins[4]-->bins={2,4,7,8,10,10}.(j=1)
            (j=1)bins[4]=bins[3]-->bins={2,4,7,8,8,10}.(j=2)
            (j=2)bins[3]=bins[2]-->bins={2,4,7,7,8,10}.(j=3)
            (j=3)-->Get out of the loop.
            }
            then set bins[2]=ID=5
            {2,4,5,7,8,10}
            the same method in brackets happenes for the names and prices array exactly.
            */
            (*size)++;//increaement the size by 1 after it was added;{2,4,7,8,10}-->{2,4,5,7,8,10}(*size=6)
            printf("Book with bin %d has been added\n",enteredId);
        }
        else printf("Book bin number already exist\n");//Error message for entering an inserted id.
    }
    else printf("ERROR! The capacity is full.\n");
}

void removeBook (char names[][NAMESIZE],int bins[],double prices[],int *size)
{
    if (*size)//if the store wasn't empty, a book can be removed.
    {
        printf("Enter bin number for book to remove\n");
        scanf("%d",&enteredId);//Asking the user to enter the bin of the book
        searchedIndex=binarySearch(bins,*size);//Brinary searching for the number and returning the index of it when existince and -1 when not exesting.
            if(searchedIndex!=-1)
            {
                for(;searchedIndex<*size-1;searchedIndex++)
                {
                    strcpy(names[searchedIndex],names[searchedIndex+1]);
                    bins[searchedIndex]=bins[searchedIndex+1];
                    prices[searchedIndex]=prices[searchedIndex+1];
                }
                /*
                ID=5,bins={2,4,5,6,8},*size=5.
                checking for where ID==bins[i] by brinary search which happens at i=2.
                Now we have successfully find the index of the elment which should be removed.
                {
                In the loop:(The array should be shifted left until index size-1 is reached-->(2in this example))
                (i=2)bins[2]=bins[3]-->bins={2,4,6,6,8}.(i=3)
                (i=3)bins[3]=bins[4]-->bins={2,4,6,8,8}.(i=4)
                (i=4)-->Get out of the loop.
                }
                the same method in brackets happenes for the prices array exactly.
                */
                (*size)--;//-->size=4-->bins={2,4,6,8}
                printf("Book with bin %d has been removed\n",enteredId);
            }
        else printf("Book with bin %d doesn't exist\n",enteredId);//Error shown if brinary search function returned -1, So the id that was wanted to be removed doesn't exist.
    }
    else printf("ERROR! There are no books to remove.\n");//if the store was empty, no book can be removed from; thus an error is displayed.
}

void searchForBook (char names[][NAMESIZE],int bins[],double prices[],int size)
{
    if (size)//if the store wasn't empty, a book can be searched for.
    {
        printf("Enter bin number for book to search for\n");
        scanf("%d",&enteredId);//Asking the user to enter the bin of the book
        searchedIndex=binarySearch(bins,size);//Brinary searching for the number and returning the index of it when existince and -1 when not exesting.
        if(searchedIndex!=-1)
            printf(" Name = %-49s\tbin# = %-4d\tprice = %0.2f\n",names[searchedIndex],bins[searchedIndex],prices[searchedIndex]);//printing with good format the gotten data.
        else printf("Book with bin %d does not exist.\n",enteredId);//Error shown if brinary search function returned -1, So the id that was wanted to be searched for doesn't exist.
    }
    else printf("ERROR! There are no books to search for.\n");//if the store was empty, no book can be searched for; thus an error is displayed.
}

void printBooks (char names[][NAMESIZE],int bins[],double prices[],int size)
{
    if(size)//if size not zero true is returned.
    {
        for(int i=0; i<size; i++)
            printf(" Name = %-49s\tbin# = %-4d\tprice = %-4.2f\n",names[i],bins[i],prices[i]);//printing with good format all the data as the up for loop goes.
    }
    else printf("The book list is empty.\n");//if the store was empty, no book can be printed from; thus an error is displayed.
}

void updateDataFile (char names[][NAMESIZE],int bins[],double prices[],int size)
{   FILE *Out= fopen("books.txt","w");//Pointer to file "books.txt" in writing position.
    printf("Updating data file ...\n");
    for(int i=0; i<size; i++)
        fprintf(Out,"%-49s\t%-4d\t%-4.2f\n",names[i],bins[i],prices[i]);//printing with good format all the data as the up for loop goes.
    fclose(Out);//Closing the written on file.
    printf("Data File updated\n");
}

int binarySearch (int bins[],int size)//there is no need to send the id as a parameter as it is a global variable.
{
      for(int low=0,high=size-1,mid=(high+low)/2;low<=high;mid=(high+low)/2)
        if(enteredId==bins[mid])
        return mid;
        else if (enteredId<bins[mid])
            high=mid-1;
        else low=mid+1;
        return -1;
        /*Binary search algorithim:
        suppose the array[10]={1,2,3,4,5,6,7,8,9,10,11,13},size=12-->high=11,id=6
        first find the mid index in the interval:
        which is the index(0+12)/2=6-->has the elment array[6]=7
        compare 7 with the entered id 6,because id is smaller then it make the interval of the elment existing possibiity smaller as high=mid-1=5
        then the existing index interval becomes[0,5]:(0+5)/2=-->mid index 2-->has the elment array[2]=3
        compare 3 with the entered id 6,because id is bigger than it make the interval of the elment existing possibiity smaller as low=mid+1=3
        then the interval becomes[3,5]:(3+5)/2=--> mid index 4-->array[4]=5
        compare 5 with the intered id 6,because id is bigger then it make the interval of the elment existing possibiity bigger as low=mid+1=5
        now the interval becomes[5,5]:(5+5)/2=-->mid index 5-->array[5]=6
        6 and 6 are equal so the index is returned
        if not equal contuine till low goes above high, then the elment we have seearched for doesn't really existis,hence exit the loop returning -1 to show non existing
        */
}
