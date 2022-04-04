
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h> 


void printerror(){
printf("bstsort [-c] [-l] [-o output_file_name] [input_file_name]");
}


struct node{ //NODES
        void * value;
        struct node *left;
        struct node *right;
};


void freetree(struct node** leaf){
if(*leaf != NULL){
freetree(&(*leaf)->left);
freetree(&(*leaf)->right);
free((*leaf)->value);
free((*leaf));
}
}


//ALLOWS CALLING OF COMPARE
typedef int (*Compare)(const void *, const void *);

//INSERT FUNCTION
void insert(void* key, struct node** leaf, Compare cmp){
int res;
if(*leaf == NULL){
	*leaf = (struct node*) malloc(sizeof(struct node));
	(*leaf)->value = malloc(strlen(key) + 1);
	strcpy((*leaf)->value,key);
	(*leaf)->left = NULL;
	(*leaf)->right = NULL;
}else{
	res = cmp(key,(*leaf)->value);
	if(res < 0){
	insert(key,&(*leaf)->left,cmp);
	}else if(res > 0){
	insert(key,&(*leaf)->right,cmp);
	}else{
	//KEY IS ALREADY IN TREE
	}
}
}

//COMAPRES NODE VALUES
int cmp(char *a, char *b){
if(a == NULL || b == NULL){
printf("Null pointer error\n");
}
int len;
int diff = 0;

	if(strlen(a) <= strlen(b)){
	len = strlen(a);
	}else{
	len = strlen(b);
	}

//change var names
	for(int j = 0; j < len; j++){
	int c1 = a[j] - '0';
	int c2 = b[j] - '0';

	diff = c1 - c2;
		if(diff != 0){
		break;
		}
	}
return diff;
}



char sortedstrings[20][20];
int loop = 0;

//PRINTS BST
void printorder(struct node *root){

if(root != NULL){
printorder(root->left);
printf("%s\n", root->value);
strcpy(sortedstrings[loop], root->value);
loop++;
printorder(root->right);
}
}


int main(int argc, char **argv){

int lflag = 0;
int cflag = 0;
int option;
int index;
int i = 0;
int select = 0;
int checkcap; 
int checklower;
int arrsize = 0;
int inputfileflag = 0;
char outputfilename[15];
char inputfilename[15];
char filetext[10];
char strings[10][10];
char temp[10][10];
FILE *fp;

//BST
struct node *treeroot = NULL;


//NON OPTION INPUT
for(index = optind; index < argc; index++){
strcpy(inputfilename, argv[index]);
inputfileflag++;
}

while ((option = getopt(argc, argv, "clo:")) != -1 ){
	
switch (option){
	
case 'c': //UPPER CASE CHARACTERS ONLY
cflag = 1;
if(select == 0){//ONLY C OR L NOT AND
if(access (inputfilename, F_OK) == 0){ //IF FILE EXISTS
fp = fopen(inputfilename,"r+");
		
//READS FILE TILL END OF FILE AND INSERTS WORD INTO ARRAY
	
while(fscanf(fp, "%19s",filetext) != EOF){ //SCANS WORD BY WORD FROM FILE AND READS INTO A STRING ARRAY UNTIL END OF FILE

	for(i = 0; i < strlen(filetext) - 1; i++){ //CAPITAL CHECKER

		if(isupper(filetext[i]) > 0){
		checkcap = 0;
		}else{
		checkcap = 1;
		break;
		}
	}

	if(checkcap == 0){ //PASSED TEST
	strcpy(strings[i], filetext);
	i++;
	arrsize++;
	//INSERTS UPPERCASE WORDS AFTER CHECKING
	insert(filetext, &treeroot, ((Compare)cmp));
	}

	if(checkcap == 1){
	i++;
	}
}
//PRINTS TREE	
printorder(treeroot);
select = 1;

}else{ //STANDARD INPUT FOR C
int j = 0;
int inputs;
char holder[10];
char filename[20] = "defaultfile.txt";

//USER INPUT CREATES A FILE WITH A DEFAULT NAME TO STORE STDIN
fp = fopen(filename, "w+");
printf("How many strings will you enter?: ");
scanf("%d", &inputs);

	for(i = 0; i < inputs; i++){
	scanf("%s", &temp[i]);
	strcpy(holder, temp[i]);
	fputs(holder, fp);
	fputs("\n",fp);
	}
fclose(fp);

//FILE READING
fp = fopen(filename, "r+");

while(fscanf(fp, "%19s",filetext) != EOF){ //SCANS WORD BY WORD FROM FILE AND READS INTO A STRING ARRAY UNTIL END OF FILE
        for(i = 0; i < strlen(filetext) - 1; i++){ //CAPITAL CHECKER

                if(isupper(filetext[i]) > 0){
                checkcap = 0;
                }else{
                checkcap = 1;
                break;
                }
        }

        if(checkcap == 0){ //PASSED CAPITALIZATION TEST
        strcpy(strings[i], filetext);
        i++;
        arrsize++;
        //INSERTS UPPERCASE WORDS AFTER CHECKING
        insert(filetext, &treeroot, ((Compare)cmp));
        }

        if(checkcap == 1){
        i++;
        }
}
//PRINTS TREE
printf("\n");
printorder(treeroot);
select = 1;
}
}
break;



case 'l':
lflag = 1;
if(select == 0){//COMPARES STRINGS IN LOWER CASE

if(access (inputfilename, F_OK) == 0){ //IF FILE EXISTS
fp = fopen(inputfilename,"r+");

//READS FILE TILL END OF FILE AND INSERTS WORD INTO ARRAY

arrsize = 0;

while(fscanf(fp, "%19s",filetext) != EOF){ //SCANS WORD BY WORD FROM FILE AND READS INTO A STRING ARRAY UNTIL END OF FILE

//IF STATEMENT TO FILTER ONLY LOWER
for(i = 0; i < strlen(filetext) - 1; i++){

	if(isupper(filetext[i]) == 0){
	checklower = 1;
	}else{
	checklower = 0;
	break;
	}
}

if(checklower == 1){
//WORD IS FULL LOWERCASE
strcpy(strings[i], filetext);
i++;
arrsize++;
//INSERTS LOWERCASE WORDS AFTER CHECKING
insert(filetext, &treeroot, ((Compare)cmp));
}

if(checklower == 0){//skips uppercase
i++;
}
}

//PRINTS TREE
printorder(treeroot);

}else if(inputfileflag > 1){ //STANDARD INPUT FOR L
int j = 0;
int inputs;
char holder[10];
char filename[20] = "defaultfile.txt";

//USER INPUT CREATES A FILE WITH A DEFAULT NAME TO STORE STDIN
fp = fopen(filename, "w+");
printf("How many strings will you enter?: ");
scanf("%d", &inputs);
        for(i = 0; i < inputs; i++){
        scanf("%s", &temp[i]);
        strcpy(holder, temp[i]);
        fputs(holder, fp);
        fputs("\n",fp);
        }
fclose(fp);
//FILE READING
fp = fopen(filename, "r+");

while(fscanf(fp, "%19s",filetext) != EOF){ //SCANS WORD BY WORD FROM FILE AND READS INTO A STRING ARRAY UNTIL END OF FILE
        for(i = 0; i < strlen(filetext) - 1; i++){ //CAPITAL CHECKER
                if(isupper(filetext[i]) == 0){
                checklower = 1;
                }else{
                checklower = 0;
                break;
                }
        }
        if(checklower == 1){ //PASSED TEST
        strcpy(strings[i], filetext);
        i++;
        arrsize++;
        //INSERTS LOWERCASE WORDS AFTER CHECKING
        insert(filetext, &treeroot, ((Compare)cmp));
        }
        if(checklower == 0){
        i++;
        }
}
//PRINTS TREE
printf("\n");
printorder(treeroot);
select = 1;
}
break;
}

case 'o': //BOTH CASE COMPARISON AND OUTPUT FILE CREATION

//INPUT FILE
if((strlen(argv[index - 2])) > 2){
if((cflag == 0) && (lflag == 0)){
fp = fopen(inputfilename, "r+");
	while(fscanf(fp, "%19s", filetext) != EOF){ //READS FROM INPUT FILE
		strcpy(strings[i], filetext);
		i++;
		arrsize++;
		//INSERTS ALL STRINGS REGARDLESS OF CAPS
		insert(filetext, &treeroot, ((Compare)cmp));
	}
//OUTPUTS TREE
printf("\n");
printorder(treeroot);
fclose(fp);
}
}else{//STANDARD INPUT FOR O
int j = 0;
int inputs;
char holder[10];
char filename[20] = "defaultfile.txt";

//USER INPUT CREATES A FILE WITH A DEFAULT NAME TO STORE VALUES
fp = fopen(filename, "w+");
printf("How many strings will you enter?: ");
scanf("%d", &inputs);
        for(i = 0; i < inputs; i++){
        scanf("%s", &temp[i]);
        strcpy(holder, temp[i]);
        fputs(holder, fp);
        fputs("\n",fp);
        }
fclose(fp);
//FILE TO BE READ
fp = fopen(filename, "r+");
while(fscanf(fp, "%19s",filetext) != EOF){ //SCANS WORD BY WORD FROM FILE AND READS INTO A STRING ARRAY UNTIL END OF FILE
        
	for(i = 0; i < strlen(filetext) > 0; i++){
	strcpy(strings[i], filetext);
	arrsize++;
        //INSERTS WORDS
        insert(filetext, &treeroot, ((Compare)cmp));
	}

}//OUTPUTS TREE
printf("\n");
printorder(treeroot);
fclose(fp);
}
//GRABS OUTPUTFILENAME
strcpy(outputfilename, optarg);

printf("File named %s was created\n", outputfilename);
fp = fopen(outputfilename, "w");

	for(i = 0; i < arrsize; i++ ){
	fputs(sortedstrings[i], fp);
	fputs("\n", fp);
	}

break;

default: //PRINTS USAGE WHEN INCORRECT ARGUMENTS PASSED
printerror();
break;

}
}

//DELETES TREE AND FREES MEMORY
freetree(&treeroot);

exit(0);
}
