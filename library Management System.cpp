#include<stdio.h>
#include <time.h>
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void add_books();
void search_books();
void delete_books();
void view_books();
void edit_books();
void return_books();
void issue_books();
void view_issue();
void search_menu();
void search_category();
void create_account();
void menu_student();
void menu_librarian();
void acc_login();
void acc_menu();
void search_category();

typedef struct {
    int yyyy;
    int mm;
    int dd;
} Date;


Date duedate;


struct books {
    int isbn; 
    char bookName[50];
    int total_copy;
    int available;
    int book_status;
    char category[30];
    int edition;
};

struct books_issue {
    int isbn; 
    char studentID[50];
    Date Issue_date;
    Date return_date;
};

struct person {
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
    int type_account;
    int status;
};

void printMessageCenter(const char* message) {
    int length =0;
    int position = 0;
    length = (78 - strlen(message))/2;//calculate how many space need to print
    printf("\t\t\t");
    for(position =0 ; position < length ; position++)
    {
        printf(" ");
    }
    printf("%s",message);
}

void headMessage(const char *message)
{
    system("cls");
    printf("\n\t\t\t#########################################################################");
    printf("\n\t\t\t############                                                 ############");
    printf("\n\t\t\t############   [][]  E-Library management System [][]        ############");
    printf("\n\t\t\t############                                                 ############");
    printf("\n\t\t\t#########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

void add_books() {
    FILE *outfile;
    int i=0;
    int num;
    headMessage("ADD BOOKS: ");
    struct books Book[50];
    char temp;
    outfile = fopen ("book.txt", "a");// open file for writing
    if (outfile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    do{
    	printf("\n\n\n\t\t\t\tEnter ISBN = ");
    	scanf("%d",&(Book[i]).isbn);
    	num = (Book[i].isbn>0)&&(Book[i].isbn<100001);
    	if(!num) {
            printf("\n\t\t\t\tEnter valid input");
            fflush(stdin);
        }
    } while(!num);
    printf("\t\t\t\tBook Name  = ");
    scanf("%s",Book[i].bookName);
    do	{
    	printf("\t\t\t\tTotal number of copies  (Integers Only) = ");
    	scanf("%d",&(Book[i]).total_copy);
    	num = (Book[i].total_copy>0)&&(Book[i].total_copy<101);
    	printf("\n%d",num);
    	if(!num) {
            printf("\n\t\t\t\tEnter valid input");
            fflush(stdin);
        }
    }while(!num);
    Book[i].available = Book[i].total_copy;
    Book[i].book_status=1;
    	printf("\t\t\t\tCategory  = ");
    	scanf("%c",&temp);
    	scanf("%[^\n]",Book[i].category);
    	do{
    		printf("\t\t\t\tEdition  (Integers Only) = ");
    		scanf("%d",&(Book[i]).edition);
    		num = (Book[i].edition>0)&&(Book[i].edition<100);
    		printf("\n%d",num);
    		if(!num) {
            printf("\n\t\t\t\tEnter valid input");
            //scanf("%c",&temp);
            fflush(stdin);
        }
    } while(!num);
    fwrite (&(Book[i]), sizeof(struct books), 1, outfile);// write structures to file
    if(fwrite != 0)
        printf("\n\t\t\t\tcontents to file written successfully !\n");
    else
        printf("\n\t\t\t\terror writing file !\n");
    fclose (outfile);
    i++;
    getch();
    system("cls");
}
void return_books() {
	headMessage("RETURN BOOK");
    struct books Book[50];
    struct books_issue issue[50];
    struct books out_Book[50];
    struct books_issue out_issue[50];
    FILE *booksfile,*issuefile,*out_booksfile,*out_issuefile;
    int check_book,check_issue1,check_issue2;
    int i=0;
    int k=0;
    int status;
    int book_id,j;
    char student_id[50];
    int found =0;
    	issuefile = fopen("issue.txt", "r+");
    	printf ("\n\n\n\t\t\t\tEnter Student ID: ");
    	scanf("%s",student_id);
    	printf ("\t\t\t\tEnter Book ID  (Integers Only): ");
    	scanf("%d",&book_id);
    while(fread(&(issue[i]), sizeof(struct books_issue), 1, issuefile)) {
    	out_issue[i]=issue[i];
		check_issue1 = strcmpi(student_id,issue[i].studentID);
		check_issue2 = book_id-issue[i].isbn;
    if((!check_issue1)&&(!check_issue2)&&(!out_issue[i].return_date.dd)) {
	    found = 1;
	    do{
        	printf("\n\t\t\t\tReturn Date(dd/mm/yyyy)  = ");
        	scanf("%d/%d/%d",&out_issue[i].return_date.dd,&out_issue[i].return_date.mm,&out_issue[i].return_date.yyyy);
        	if(!status) {
            	printf("\n\t\t\tPlease enter a valid date.\n");
        	}
        } while(!status);
        printf("\t\t\t\tDue Date(dd/mm/yyyy)  = %d/%d/%d",duedate.dd,duedate.mm,duedate.yyyy);
        	if(out_issue[i].return_date.dd==duedate.dd)    printf("\n\n\t\t\t\tReturned on time!");
        	if(out_issue[i].return_date.dd!=duedate.dd)    printf("\n\n\t\t\t\tPassed the due date!");

        booksfile = fopen("book.txt", "r+");
        j=0;
        while(fread(&(Book[j]), sizeof(struct books), 1, booksfile))
		{
		    out_Book[j]=Book[j];
            check_book= book_id-Book[j].isbn;

            if(!check_book)
		    {
		        out_Book[j].available++;
		    }
		    j++;
		}
		fclose(booksfile);
	}
	i++;
	k++;
	}
fclose(issuefile);
if(found)
{
    out_booksfile=fopen("book.txt","w+");
    fwrite(&out_Book,sizeof(struct books),j,out_booksfile);
    fclose(out_booksfile);

    out_issuefile = fopen("issue.txt","w+");
    fwrite(&out_issue,sizeof(struct books_issue),i,out_issuefile);
    fclose(out_issuefile);
}
else
    printf("\n\n\t\t\t\tBook Not Issued to Student");
getch();
}
void view_issue() {
	headMessage("VIEW ISSUED BOOKS");
	FILE *infile;
	struct books_issue issue;
	infile = fopen ("issue.txt", "r");
	int i=1;
	if (infile == NULL) {
        fprintf(stderr,"\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }
	printf("\n\n");
	while(fread(&issue, sizeof(struct books_issue), 2, infile)) {
        printf("\n\t\t\tSerial no. %d",i);
        printf ("\n\t\t\t\tBook ID = %d ",issue.isbn);
		printf ("\n\t\t\t\tStudent ID = %s ",issue.studentID);
		printf ("\n\t\t\t\tIssued Date = %d/%d/%d ",issue.Issue_date.dd,issue.Issue_date.mm,issue.Issue_date.yyyy);
		printf ("\n\t\t\t\tReturn Date = %d/%d/%d ",issue.return_date.dd,issue.return_date.mm,issue.return_date.yyyy);
        i++;
        printf("\n");
	}
	fclose(infile);
	getch();
	system("cls");
}

void search_menu() {
    int choice = 0;
    do{
        headMessage("SEARCH BOOKS MENU");
        printf("\n\n\n\t\t\t1.Search by Book Name");
        printf("\n\t\t\t2.Search by Category");
        printf("\n\t\t\t0.Back to Main Menu");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            search_books();
            break;
        case 2:
            search_category();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n");
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }//Switch Ended
    } while(choice!=0);//Loop Ended
}

void view_books() {
	headMessage("VIEW BOOKS");
	FILE *infile;
	struct books Book;
	infile = fopen ("book.txt", "r");
	int i=1;
		if (infile == NULL) {
        	fprintf(stderr, "\n\n\n\t\t\tError opening file\n");
        	exit (1);
    	}
		printf("\n\n");
	while(fread(&Book, sizeof(struct books), 1, infile)) {
    	if(Book.book_status) {
        	printf("\n\t\t\tSerial no. %d",i);
        	printf ("\n\t\t\t\tBook ID = %d ",Book.isbn);
			printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
			printf ("\n\t\t\t\tCategory = %s ",Book.category);
			printf ("\n\t\t\t\tEdition = %d ",Book.edition);
			printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
			printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
        	printf("\n");
        	i++;
    		}
		}
	fclose(infile);
	getch();
	system("cls");
}

void menu_student() {
	int choice = 0;
    do{
        headMessage("STUDENT MAIN MENU");
        printf("\n\n\n\t\t\t1.Search Books");
        printf("\n\t\t\t2.View Books");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            search_menu();
            break;
        case 2:
            view_books();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }//Switch Ended
    }while(choice!=0); //Loop Ended
}
void edit_books() {
	headMessage("EDIT BOOK RECORD");
    FILE *editfile;
    struct books Book[50];
    struct books out[50];
    char userbook[50];
    int check_book;
    int i=0;
    char temp;
    char temp_2;
    if (editfile == NULL) {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }
    printf ("\n\n\n\t\t\t\tEnter Book Name for Editing: ");
    scanf("%c",&temp);
    scanf("%[^\n]",userbook);
    editfile = fopen ("book.txt", "r+");
    int flag = 1;
    int found = 0;
    int num;
	while(fread(&(Book[i]), sizeof(struct books), 1, editfile)) {
    	out[i]=Book[i];
		check_book = strcmpi(userbook,Book[i].bookName);
		if( (Book[i].book_status) && (flag) && (!check_book)  ) {
        found = 1;
		printf ("\n\t\t\t\tBook Found !");
		printf ("\n\n\t\t\t\tBook ID = %d ",Book[i].isbn);
		printf ("\n\t\t\t\tBook Name = %s ",Book[i].bookName);
		printf ("\n\t\t\t\tCategory = %s ",Book[i].category);
		printf ("\n\t\t\t\tEdition = %d ",Book[i].edition);
		printf ("\n\t\t\t\tTotal copies = %d ",Book[i].total_copy);
		printf ("\n\t\t\t\tAvailable Copies = %d ",Book[i].available);
        int edit_choice;
        while(flag) {
            printf("\n\n\t\t\t\t1.Update Category");
            printf("\n\t\t\t\t2.Update Edition");
            printf("\n\t\t\t\t3.Exit");
            printf("\n\n\t\t\t\tEnter choice:");
            scanf("%d",&edit_choice);
            switch(edit_choice) {
            case 1:
                printf("\n\t\t\t\tEnter new category:  ");
                scanf("%c",&temp_2);
                scanf("%[^\n]",out[i].category);
                break;
            case 2:

                do{
                printf("\n\t\t\t\tEnter new edition  (Integers only) :  ");
                scanf("%d",&out[i].edition);
                num = (out[i].edition>0)&&(out[i].edition<100);
                printf("\n%d",num);

                if(!num)
                {
                    printf("\n\t\t\t\tEnter valid input");
                    fflush(stdin);
                }
                }
                while(!num);
                printf("serial number: %d", i);
                break;
            case 3:
                flag=0;

                break;
            default:
                printf("\n\t\t\t\tEnter 1 /2 /3");
            }
        }
	}
	i++;
	}

    fclose(editfile);
    if(found)
    {
        editfile=fopen("book.txt","w+");
        fwrite(&out,sizeof(struct books),i,editfile);
        fclose(editfile);
    }
    else
        printf("\n\n\t\t\t\tBook Not Found");
    getch();
    system("cls");

}

void menu_librarian() {
    int choice = 0;
    do{
        headMessage("LIBRARIAN MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Book");
        printf("\n\t\t\t2.Search Book");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Edit Book");
        printf("\n\t\t\t5.Delete Book");
        printf("\n\t\t\t6.Issue Book");
        printf("\n\t\t\t7.Return Book");
        printf("\n\t\t\t8.View Issued Books");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            add_books();
            break;
        case 2:
            search_menu();
            break;
        case 3:
            view_books();
            break;
        case 4:
            edit_books();
            break;
        case 5:
            delete_books();
            break;
        case 6:
            issue_books();
            break;
        case 7:
            return_books();
            break;
        case 8:
            view_issue();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }//Switch Ended
    } while(choice!=0);//Loop Ended
getch();
}

void issue_books() {
    headMessage("ISSUE BOOK");
    struct books Book[50];
    struct books out[50];
    struct books_issue issue;
    FILE *booksfile, *issuefile, *outfile;
    int check_book;
    int i = 0;
    char temp;
    char userbook[50];
    booksfile = fopen("book.txt", "r+");
    printf("\n\n\n\t\t\t\tEnter Book Name for Issuing: ");
    scanf("%c", &temp);
    scanf(" %[^\n]", userbook);
    int found = 0;

    while (fread(&(Book[i]), sizeof(struct books), 1, booksfile)) {
        if (Book[i].book_status && Book[i].available > 0) {
            check_book = strcmpi(userbook, Book[i].bookName);
            out[i] = Book[i];
            if (check_book == 0) {
                found = 1;
                out[i].available--;

                issuefile = fopen("issue.txt", "a+");
                issue.isbn = Book[i].isbn;

                printf("\n\t\t\t\tStudent ID: ");
                scanf("%s", issue.studentID);

                printf("\t\t\t\tIssue Date (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &issue.Issue_date.dd, &issue.Issue_date.mm, &issue.Issue_date.yyyy);

                issue.return_date.dd = 0;
                issue.return_date.mm = 0;
                issue.return_date.yyyy = 0;

                // Calculate due date
                int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                int daysToAdd = 20;

                duedate.dd = issue.Issue_date.dd + daysToAdd;
                duedate.mm = issue.Issue_date.mm;
                duedate.yyyy = issue.Issue_date.yyyy;

                if (duedate.dd > daysInMonth[duedate.mm - 1]) {
                    duedate.dd -= daysInMonth[duedate.mm - 1];
                    duedate.mm++;
                    if (duedate.mm > 12) {
                        duedate.mm = 1;
                        duedate.yyyy++;
                    }
                }

                printf("\t\t\t\tDue Date (dd/mm/yyyy): %d/%d/%d\n", duedate.dd, duedate.mm, duedate.yyyy);
                getch();

                fwrite(&issue, sizeof(struct books_issue), 1, issuefile);
                fclose(issuefile);
            }
        }
        i++;
    }

    fclose(booksfile);

    if (found) {
        outfile = fopen("book.txt", "w+");
        fwrite(&out, sizeof(struct books), i, outfile);
        fclose(outfile);
    } else {
        printf("\n\n\t\t\t\tBook Not Found");
    }
    getch();
}

void acc_login() {
    FILE *infile;
    char login_username[30];
    char login_password[20];
    int pass_check,user_check;
    headMessage("ACCOUNT LOGIN");
    struct person inp[50];
    int c=0,i=0;
    infile = fopen("account.txt", "r");
    if(infile == NULL) {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }
    printf("\n\n\n\t\t\t\tUsername:");
    scanf("%s",login_username);
    printf("\n\t\t\t\tPassword:");
    scanf("%s",login_password);
    while(fread(&(inp[i]), sizeof(struct person), 1, infile)) {
		user_check=strcmp(inp[i].username,login_username);
		pass_check=strcmp(inp[i].password,login_password);
	 	if((!user_check)&&(!pass_check)&&(inp[i].status)) {
			c=1;
			printf("\n\n\t\t\t\tLogin successful !");
			time_t t;   // not a primitive datatype
    		time(&t);
    		printf("\n\t\t\t\tYou are logging in at (date and time): %s", ctime(&t));
    	getch();
			if(inp[i].type_account==1) {
	 			menu_librarian();
	 		}
			if(inp[i].type_account==2) {
	 			menu_student();
	 			}
			}
		i++;
	}
    if(!c) {
    	printf("\n\n\t\t\t\tLogin failed ,Retry !");
    	getch();
    	}
	fclose(infile);
}

void acc_menu() {
    int choice=0;
    do{
        headMessage("*******WELCOME TO THE LOGIN/SIGN UP PORTAL************");
        printf("\n\n\n\t\t\t1.Login");
        printf("\n\t\t\t2.Sign-Up");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            acc_login();
            break;
        case 2:
            create_account();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n");
            time_t t;   // not a primitive datatype
            time(&t);
            printf("\n\t\t\t\tYou are logging out at (date and time): %s", ctime(&t));
            getch();
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }//Switch Ended
    }while(choice!=0);//Loop Ended
}

void search_category() {
	headMessage("SEARCH BOOKS");
	FILE *infile;
	struct books Book;
	char userbook[50];
	int check_book;
	char temp;
	if(infile == NULL) {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    	}
	printf ("\n\n\n\t\t\t\tEnter category for searching: ");
	scanf("%c",&temp);
	scanf("%[^\n]",userbook);
	infile = fopen ("book.txt", "r");// Open person.dat for reading
	int found = 0;
		while(fread(&Book, sizeof(struct books), 1, infile)) {
			check_book = strcmpi(userbook,Book.bookName);
				if(Book.book_status) {
          			if(check_book!=NULL) {
						printf("\n\n\n\t\t\t\t Book Found !");
            			printf("\n\n\t\t\t\tBook ID = %d ",Book.isbn);
            			printf("\n\t\t\t\tBook Name = %s ",Book.bookName);
            			printf("\n\t\t\t\tCategory = %s ",Book.category);
            			printf("\n\t\t\t\tEdition = %d ",Book.edition);
            			printf("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
            			printf("\n\t\t\t\tAvailable Copies = %d ",Book.available);
            			found = 1;
        					}
					}
				}
	fclose(infile);
	if(!found)
		printf("\n\n\t\t\t\tBook Not Found");
	getch();
	system("cls");
}
void create_account() {
    FILE *outfile;
    headMessage("Create Account");
    struct person inp[50];
    int i=0;
    outfile = fopen ("account.txt", "a");// open file for writing
    	if(outfile == NULL) {
        	fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        	exit(1);
    			}
    	printf("\n\n\n\t\t\t\t Please enter Username:");
    	scanf("%s",inp[i].username);
		printf("\n\t\t\t\tPlease enter Password:");
    	scanf("%s",inp[i].password);
    	int validaccount = 1;
    while (validaccount) {
        printf("\n\t\t\t\tSign Up as \n\t\t\t\t1. Librarian\n\t\t\t\t2. Student\n\t\t\t\t");
        scanf("%d",&inp[i].type_account);
        if((inp[i].type_account<1) || (inp[i].type_account>2)) {    
			printf("\n\t\t\t\tEnter valid account type!");
		} else {
            inp[i].status = 1;
            fwrite(&(inp[i]), sizeof(struct person), 1, outfile);// write struct to file
            if(fwrite != 0)
				printf("\n\t\t\t\tcontents to file written successfully !\n");
			else
                printf("\n\t\t\t\terror writing file !\n");
            validaccount = 0;
        }
    } fclose (outfile);
    i=i+1;
    getch();
    system("cls");
}
void search_books() {
	headMessage("SEARCH BOOKS");
	FILE *infile;
	struct books Book;
	char userbook[50];
	int check_book;
	char temp;
	if(infile == NULL) {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }
	printf ("\n\n\n\t\t\t\tEnter Book Name for searching: ");
	scanf("%c",&temp);
	scanf("%[^\n]",userbook);
	//scanf("%s",userbook);
	infile = fopen ("book.txt", "r");// Open person.dat for reading
	int found = 0;
	while(fread(&Book, sizeof(struct books), 1, infile)) {
		check_book = strcmp(userbook,Book.bookName);
         if (Book.book_status && check_book == 0) {
				printf("\n\n\n\t\t\t\t Book Found !");
            	printf ("\n\n\t\t\t\tBook ID = %d ",Book.isbn);
            	printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
            	printf ("\n\t\t\t\tCategory = %s ",Book.category);
            	printf ("\n\t\t\t\tEdition = %d ",Book.edition);
            	printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
            	printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
            	found = 1;
        	}
	}
	fclose(infile);
		if(!found)  
			printf("\n\n\t\t\t\tBook Not Found");
	getch();
	system("cls");
}	
void delete_books() {
	headMessage("DELETE BOOK");
    FILE *infile;
    struct books Book[50];
    struct books out[50];
    char userbook[50];
    int check_book;
    int i=0;
    char temp;
		if(infile == NULL) {
        	fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        	exit (1);
    		}
		printf ("\n\n\n\t\t\tEnter Book Name for Deleting: ");
		scanf("%c",&temp);
		scanf("%[^\n]",userbook);
	int found = 0;
		infile = fopen ("book.txt", "r+");// Open person.dat for reading
	while(fread(&(Book[i]), sizeof(struct books), 1, infile)) {
    	out[i]=Book[i];
		check_book = strcmpi(userbook,Book[i].bookName);
			if((Book[i].book_status) && (!check_book) ) {
				printf("\n\n\t\t\t\tBook Found !");
        		found = 1;
				printf("\n\n\t\t\t\tISBN = %d ",Book[i].isbn);
				printf("\n\t\t\t\tBook Name = %s ",Book[i].bookName);
				printf("\n\t\t\t\tCategory = %s ",Book[i].category);
				printf("\n\t\t\t\tEdition = %d ",Book[i].edition);
				printf("\n\t\t\t\tTotal copies = %d ",Book[i].total_copy);
				printf("\n\t\t\t\tAvailable Copies = %d ",Book[i].available);
        		out[i].book_status=0;
			}
		i++;
	}
	fclose(infile);
	if(found) {	
		infile=fopen("book.txt","w+");
		fwrite(&out,sizeof(struct books),i,infile);
		fclose(infile);
		}
	else
    	printf("\n\n\t\t\t\tBook Not Found");
	getch();
	system("cls");
}

int main() {
	acc_menu();	
	return 0;
}
