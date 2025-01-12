/* book_linked_list.c */

/*
        Book Database
  ---------------------------------
    1. Create a database for the books
    2. Need to have Title, number of Pages, price, author and published date;
    3. Add and remove book
    4. Find the book by Title
    5. Find the book by Title and Update the Title
    6. List all books
    7. Prevent duplicate books from adding
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Book {
    char title[56];
    int pages;
    char author[32];
    int price;
    struct tm publishDate;
    struct Book* next;
} Book;

/* function prototypes */
Book* createBook(const char* title, int pages, const char* author, int price, Date* publishDate);
void insertBook(Book** head, Book* newBook);
Book* findBookByTitle(Book* head, const char* key);
void updateTitle(Book* book, const char* newTitle);
void removeBook(Book** head, Book* book);
void listAllBooks(Book* head);
void getBookInfo(Book* book);
char* trim(char* str);

Book* head = NULL;

/* main */
int main(){
    Date date1 = {1, 8, 1990};
    Date date2 = {21, 11, 2008};
    Date date3 = {15, 4, 2015};

    insertBook(&head, createBook("Harry potter", 2000, "J.K Rowling", 560, &date1));
    insertBook(&head, createBook("Game of thrones", 3400, "James Gosling", 1800, &date2));
    insertBook(&head, createBook("Lord of the rings", 5000, "Aneesha Rama", 3470, &date3));

    Book* book = findBookByTitle(head, "Harry potter");
    removeBook(&head, book);
    listAllBooks(head);


}

/* create book */
Book* createBook(const char* title, int pages, const char* author, int price, Date* publishDate){
   Book* book = (Book*)malloc(sizeof(Book));
   if (!book) {
       fprintf(stderr, "Memory allocation failed\n");
       return NULL;
   }
   memset(book, 0, sizeof(Book));
   if(head != NULL){
       Book* existingBook = findBookByTitle(head, title);
       if(existingBook){
           printf("Book with title '%s' is already exist\n", title);
           free(book);
           return NULL;
       }
   }
   printf("Creating the book with title: '%s'\n", title);
   strncpy(book->title, title,55);
   book->title[55] = '\0';
   book->pages = pages;
   strncpy(book->author, author, 31);
   book->author[31] = '\0';
   book->price = price;
   book->publishDate.tm_mday = publishDate->day;
   book->publishDate.tm_mon = publishDate->month - 1;
   book->publishDate.tm_year = publishDate->year - 1900;
   book->next = NULL;

   return book;
}

/* insert book to the database */
void insertBook(Book** head, Book* newBook){
    if(*head == NULL){
        *head = newBook;
        return;
    }
    Book* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newBook;
}

/* remove the book with title */
void removeBook(Book** head, Book* book){
    if(*head == NULL){
        printf("Invalid: %s\n", (book == NULL) ? "No book found" : "Empty list");
        return;
    }

    if(*head == book){
        *head = book->next;
        free(book);
        printf("Successfully removed the book\n");
        return;
    }

    Book* current = *head;
    while(current != NULL){
        if(current->next == book){
            current->next = book->next;
            free(book);
            break;
        }
        current = current->next;
    }

    printf("Successfully removed the book\n");
}


/* find a book by title */
Book* findBookByTitle(Book* head, const char* key) {
    Book* book = NULL;

    if (head == NULL || key == NULL) {
        printf("Invalid input: %s\n", (key == NULL) ? "null key" : "empty list");
        return NULL;
    }

    char* keyCopy = strdup(key);
    if (!keyCopy) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    char* trimmedKey = trim(keyCopy);

    Book* current = head;
    while (current != NULL) {
        if (strcmp(current->title, trimmedKey) == 0) {
            book = current;
            break;
        }
        current = current->next;
    }

    if (book == NULL) {
        printf("Book not found with title: '%s'\n", trimmedKey);
    }

    free(keyCopy);
    return book;
}

/* updated the title */
void updateTitle(Book* book, const char* newTitle){
    if(book == NULL){
        printf("No book found\n");
        return;
    }
    char* oldTitle = strdup(book->title);
    strncpy(book->title, newTitle, 55);
    book->title[55] = '\0';
    if (strlen(newTitle) > 55) {
            printf("Warning: The new title was truncated to fit the buffer size.\n");
    }
    printf("Successfully updated title from '%s' to '%s'\n", oldTitle, newTitle);
    free(oldTitle);
}

/* list all books */
void listAllBooks(Book* head){
    if(head == NULL){
        printf("No books found\n");
        return;
    }

    while(head != NULL){
        printf("Title: '%s'\n", head->title);
        printf("Author: '%s'\n", head->author);
        printf("Price: %d\n", head->price);
        printf("Pages: %d\n", head->pages);
        printf("Published on: '%d-%d-%d'\n", head->publishDate.tm_mday, (head->publishDate.tm_mon + 1), (head->publishDate.tm_year + 1900));
        printf("----------------------------------\n");
        head = head->next;
    }
}

void getBookInfo(Book* book){
    if(book){
        printf("Title: '%s'\n", book->title);
        printf("Author: '%s'\n", book->author);
        printf("Price: %d\n", book->price);
        printf("Pages: %d\n", book->pages);
        printf("Published on: '%d-%d-%d'\n", book->publishDate.tm_mday, (book->publishDate.tm_mon + 1), (book->publishDate.tm_year + 1900));
        printf("----------------------------------\n");
    }
}

char* trim(char* str){
    char* end;

    while(isspace((unsigned char)*str)){
        str++;
    }

    if(*str == '\0'){
        return str;
    }

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)){
        end--;
    }

    *(end+1) = '\0';

    return str;
}
