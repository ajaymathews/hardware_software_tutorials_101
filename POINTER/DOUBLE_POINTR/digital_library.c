#include <stdio.h>
#include <stdlib.h>

int* total_number_of_books; // address of the 1-d array

/* shelf   x=0                x=1          ..    ..      x=shelfnum         
|---------------------|-------------------|-----|----|---------------------|
| NoOf.Books-shelf0   | NoOf.Books-shelf1 | ... |... |totalBooks-nth shelf |  
|---------------------|-------------------|-----|----|---------------------|
*/


int** total_number_of_pages;// address of the 2-d array

/* shelf   x=0                x=1          ..    ..      x=shelfnum         
|---------------------|-------------------|-----|----|---------------------|
| Book:1 - Pageno:y1  | Book:1 - Pageno:y | ... |... | Book:n1 - Pageno:y  |  
|---------------------|-------------------|-----|----|---------------------|
| Book:2 - Pageno:y2  | Book:2 - Pageno:y | ... |... | Book:n2 - Pageno:y  |  
|---------------------|-------------------|-----|----|---------------------| 
| Book:3 - Pageno:y3  | Book:3 - Pageno:y | ... |... | Book:n3 - Pageno:y  |  
|---------------------|-------------------|-----|----|---------------------|
|---------------------|-------------------|-----|----|---------------------|
|---------------------|-------------------|-----|----|---------------------|
| Book:n - Pageno:yn  | Book:n - Pageno:y | ... |... | Book:nn - Pageno:y  |  
|---------------------|-------------------|-----|----|---------------------|

*/

int save_book(int x, int y){
    total_number_of_books[x]++;
    total_number_of_pages[x]= realloc(total_number_of_pages[x],     total_number_of_books[x]*sizeof(int));
    //fun(current pointer, total memory required)

    total_number_of_pages[x][total_number_of_books[x]-1]=y;
    return 0;
}
int main()
{
    int total_number_of_shelves,i;
    scanf("%d", &total_number_of_shelves);
    
    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);
    
    total_number_of_books=(int*)malloc(total_number_of_shelves * sizeof(int));
    total_number_of_pages=(int**)malloc(total_number_of_shelves * sizeof(int*));
    for(i=0;i<=total_number_of_shelves;i++){
        total_number_of_books[i]=0;
    }
    while (total_number_of_queries--) {
        int type_of_query;
        scanf("%d", &type_of_query);
        
        if (type_of_query == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            save_book(x,y);

        } else if (type_of_query == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }
    
    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }
    
    if (total_number_of_pages) {
        free(total_number_of_pages);
    }
    
    return 0;
}