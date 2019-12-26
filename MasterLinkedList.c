//Süleyman Barýþ Eser 150116055
#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h>
#include <locale.h>
#include <stdarg.h>
#include <string.h>
#define word_len 80

//downward struct
typedef struct Linked_list{
	char document_Id[word_len];
	int this_doc_num;
	int length_document;
	char category_name[word_len];
	struct Linked_list *nextLinked;
}LL;

//Rightward struct 
typedef struct Master_LL {
	char term_name[word_len];
	int total_num_doc;
	struct Master_LL *next;
	struct Linked_list *nextLinked;
	
} node;


double stringcmp(char s[] , char t[]);
void disc_words(struct Master_LL *head);
void stop_words(struct Master_LL *head);
int doc_len(char name[]);
void turkish(char word[]);
struct Master_LL *add_node(struct Master_LL	*list, struct Master_LL *node , struct Linked_list *a);
void display_list(struct Master_LL *head);


FILE *file;

int main(){
	setlocale(LC_ALL , "Turkish");	//for turkish characters
	node *head, *newNode;
	LL *features;
	head = NULL;
	
	DIR *econ;
	DIR *health;
	DIR *magazin;
	
	FILE *file;
	
	/*Bu FILE *e gibi düþünelim. Klasor okuyunca buna aktaracaz.*/

	struct dirent *sd; 
	
	char name[word_len];
	char word[word_len];	
	char category[word_len];
	char documentId[word_len];
	char ch;
	
	int count = -2;
	int i; 
	int len[30];
	int k = 0;
	
	int c;
	
	//opening directories
	econ=opendir("dataset//econ");
	health=opendir("dataset//health");
	magazin=opendir("dataset//magazin");
	
	//numbers of txt documents in econ
	while((sd=readdir(econ))!=NULL){
		count++;
	}
	
	//name of category
	strcpy(category , "ECONOMY");
	//path of documents
	strcpy(name, "dataset//econ//A.txt");
	strcpy(documentId ,"E.A" );
	

	for(i = 1 ; i <= count ; i++){  
		//15th char will be ýd of document  such as, if i = 1 , then name will be 1.txt
		name[15] = i+48;
		//2th char will be ýd of document ýd
		documentId[2] = i+48;
		file = fopen(name,"r");		//opening files
		k = doc_len(name);		//length of document

		do{
			c = fscanf(file,"%s",word);		//getting words
			turkish(word);					//
			newNode = (node*)malloc(sizeof(node));		//allocating
			features = (LL*)malloc(sizeof(LL));			//allocating
		
		
			if (c != EOF){			//if not end of file
				strcpy(newNode->term_name, word);	
				strcpy(features->category_name , category);
				strcpy(features->document_Id , documentId);
				features->length_document = k;

				features->nextLinked = NULL;		//futures is element of downward struct
				newNode->next = NULL;
				
					if (word[0] != '\0') {
						head = add_node(head, newNode , features);		//insert , add nodes
					}
				}	
			} while (word[0] != '\0' && c != EOF);
			
		fclose(file);	
	}
	
	
	
	count = -2;
	
	strcpy(category , "HEALTH");	

	strcpy(name, "dataset//health//..txt");
	strcpy(documentId ,"H.A" );
	
	while((sd=readdir(health))!=NULL){
		count++;
		}
				
	for(i = 1 ; i <= count ; i++){  
		name[17] = i+48;
		documentId[2] = i+48;
		file = fopen(name,"r");
		k = doc_len(name);
		
			do{
			c = fscanf(file,"%s",word);
			turkish(word);
			newNode = (node*)malloc(sizeof(node));
			features = (LL*)malloc(sizeof(LL));
			
		
			if (c != EOF){
				
				strcpy(newNode->term_name, word);
				strcpy(features->category_name , category);
				strcpy(features->document_Id , documentId);
				features->length_document = k ;

				features->nextLinked = NULL;
				newNode->next = NULL;
				
					if (word[0] != '\0') {
					head = add_node(head, newNode,features);
					}
				}	
			
			} while (word[0] != '\0' && c != EOF);
			
		fclose(file);
	}
		
	strcpy(category , "MAGAZIN");
	//MAGAZIN
	strcpy(name, "dataset//magazin//..txt");
	strcpy(documentId ,"M.A" );

	count=-2;
	
	//numbers of document in the magazin directory
	while((sd=readdir(magazin))!=NULL){
		count++;
	}
	
	
	
	for(i = 1 ; i <= count ; i++){  
		name[18] = i+48;
		documentId[2] = i+48;
		file = fopen(name,"r");
		k = doc_len(name);
		
		do{
			c = fscanf(file,"%s",word);
			
			turkish(word);
			newNode = (node*)malloc(sizeof(node));
			features = (LL*)malloc(sizeof(LL));
		
		
			if (c != EOF){
				strcpy(newNode->term_name, word);
				strcpy(features->category_name , category);
				strcpy(features->document_Id , documentId);
				features->length_document = k;

				features->nextLinked = NULL;
				newNode->next = NULL;
				
					if (word[0] != '\0') {
					head = add_node(head, newNode,features);
					}
				}	
			} while (word[0] != '\0' && c != EOF);
			
		fclose(file);
	}
		
		
	//OUTPUT:
	stop_words(head);
	printf("\n");
	disc_words(head);
	printf("\n\n");
	display_list(head);
	
	
	//close directories
	closedir(econ);
	closedir(health);
	closedir(magazin);
	
	
	return 0;	
}





void disc_words(struct Master_LL *head){
	struct Linked_list *temp1 , *temp2 , *temp3;
	int i = 0;	int k = 0; int l = 0 ;
	
	char *econ[5], *health[5] , *mag[5];	//string arrays
	
	printf("DISCRIMINATING WORDS\n");
	printf("----------------------\n");
	
	while(head){
		if(strcmp(head->nextLinked->category_name , "ECONOMY") == 0 ){	//if category of first element is "ECONOMY"
			temp1 = head->nextLinked;
			
			while(temp1 && strcmp( temp1->category_name , "ECONOMY") == 0){		//while there is no different category
				temp1 = temp1->nextLinked; 
			}
			
			if(i < 5){	//add first 5 words to econ
				if(temp1 == NULL){
					econ[i] = head->term_name;
					i++;
				}
			}
			
		}
		
		if(strcmp(head->nextLinked->category_name , "HEALTH") == 0 ){
			temp2 = head->nextLinked;
			
			while(temp2 && strcmp( temp2->category_name , "HEALTH") == 0){
				temp2 = temp2->nextLinked;
			}
			
			if(k < 5){
				if(temp2 == NULL){
					health[k] = head->term_name;
					k++;
				}
			}
		}
		
		if(strcmp(head->nextLinked->category_name , "MAGAZIN") == 0 ){
			temp3 = head->nextLinked;
			
			while(temp3 && strcmp( temp3->category_name , "MAGAZIN") == 0){
				temp3 = temp3->nextLinked;
			}
			
			if(l < 5){
				if(temp3 == NULL){
				mag[l] = head->term_name;
				l++;
				}
			}
			
		}
		
		head = head->next;
	}	
	printf("ECONOMY : ");
	for(i = 0 ; i < 5; i++){	//print first 5 words
		printf("%s\t" , econ[i]);
	}
	
	printf("\nHEALTH : ");
	for(k = 0 ; k < 5; k++){
		printf("%s\t", health[k]);
	}
	
	printf("\nMAGAZIN : ");
	for(l = 0; l < 5 ; l++){
		printf("%s\t" , mag[l]);
	}
}


void stop_words(struct Master_LL *head){
	printf("STOP WORDS");
	printf("\n-----------\n"); 

	
	struct Linked_list *temp1 , *temp2 , *temp3, *counter;
	int count;
	int i = 0;
	
	while(head){
		temp1 = head->nextLinked;
		temp2 = head->nextLinked;
		temp3 = head->nextLinked;
		
		while(temp2 && strcmp(temp2->category_name , "HEALTH") !=0 ) {	//search if there is a health category
			temp2 = temp2->nextLinked;
		}
		
		while(temp3->nextLinked){	
			temp3 = temp3->nextLinked;
		}
			
		//if category of first element is economy			if there is a health category		if category of last element is magazin	
		if(strcmp(temp1->category_name , "ECONOMY") == 0 && temp2 != NULL &&   strcmp(temp3->category_name , "MAGAZIN") == 0){
			counter = head->nextLinked;
			while(counter){
				count += counter->this_doc_num;		//numbers of term
				counter = counter->nextLinked; 
			}
			
			if(count > 8 && i < 5){
				i++;
				printf("%s\n" , head->term_name);
			
			} 
			
			
			
			count = 0;
		}
			
		
		head = head->next;
	}
		
	
}

//length of document
int doc_len(char name[]){
	FILE *file;
	int c;
	int k = 0;
	char word[word_len];
	
	file = fopen(name , "r");
	
	do{
		c = fscanf(file , "%s" , word );
		if(c != EOF){
			k++;	
		}
		
	}while(c != EOF);
	
	fclose(file);
	
	return k;
}



struct Master_LL *add_node(struct Master_LL	*list, struct Master_LL *node , struct Linked_list *feature){
	struct Master_LL *prev, *next;
	feature->this_doc_num = 1;	//total number of times this term occurs in this document
	node->total_num_doc = 1; 	//total number of documents this term occur
	
	//First element
	if(!list){
		node->nextLinked = feature;
		list = node;
	}
	
	else{
		prev = NULL;
		next = list;
		
		while (next && stringcmp(node->term_name , next->term_name) > 0) {
			prev = next;
			next = next->next;
		}
		
		//last element
		if (!next) {
			node->nextLinked = feature;
			prev->next = node;	//previous element of end of linked list
		}
		
		
		else{
			if(stringcmp(node->term_name , next->term_name) == 0 ){	//if term already exists
				struct Linked_list *otherLinked , *otherLinked2;
				
				otherLinked = next->nextLinked;			//down liked list					
				while(otherLinked->nextLinked && strcmp(feature->document_Id , otherLinked->document_Id) != 0 ){		//continue while document id is not same and struct is not null
					otherLinked = otherLinked->nextLinked;		
				}
			
				if(strcmp(otherLinked->document_Id , feature->document_Id) == 0){	//if there is same txt
					otherLinked->this_doc_num++;	
				}
			
				else if(!otherLinked->nextLinked){		//if there is no same txt
					otherLinked->nextLinked = feature;
				}
				
				
				//number of documents this term occur
				otherLinked2 = next->nextLinked;
				while(otherLinked2 && strcmp(otherLinked->document_Id , feature->document_Id) != 0 ){
					otherLinked2 = otherLinked2->nextLinked;
				}
				
				if(!otherLinked2){
					next->total_num_doc++;	//increment
				}
		

			
				free(node);
			}
			
			else if (prev) {	//add between two term
				node->nextLinked = feature;
				node->next = prev->next;
				prev->next = node;
			}
			else {	//add in front of the list
				node->nextLinked = feature;
				node->next = list;
				list = node;
			}
			
		}
			
	
	}
	return list;
}


void display_list(struct Master_LL *head) {
	struct Master_LL *temp;
	temp = head;
	printf("TERM NAME/NUMBERS OF DOCUMENT---->Document ID/NUMBERS OF THIS DOC OCCUR/Doc Length/CATEGORY NAME\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	while (temp) {
		printf("%s/%d---->", temp->term_name,temp->total_num_doc);
		while(temp->nextLinked){
			printf("%s/%d/%d/%s---->", temp->nextLinked->document_Id , temp->nextLinked->this_doc_num , temp->nextLinked->length_document , temp->nextLinked->category_name );
			temp->nextLinked = temp->nextLinked->nextLinked;
		}
		
		printf("NULL\n||");
		printf("\n\\/\n");
		temp = temp->next;
	}
	printf("NULL");
	
}

void turkish(char word[]){
	int k;
	for(k = 0 ; k<strlen(word) ; k++){
		if(word[k] <= 90 && word[k] >= 65)
			word[k] = word[k] + 32;
		
		if(word[k] == 'Ý')
			word[k] = 'i';
				
		if(word[k] == 'Þ')
			word[k] = 'þ';
				
		if(word[k] == 'Ç')
			word[k] = 'ç';		
				
		if(word[k] == 'Ü')
			word[k] = 'ü';	
				
		if(word[k] == 'Ð')
			word[k] = 'ð';
					
		if(word[k] == 'Ö')
			word[k] = 'ö';				
				
			}
}

//all pasibilities
double stringcmp(char s[] , char t[]){
	int i;
	i = 0;
	
	while(s[i] == t[i]){
		
		
		if(s[i++] == '\0')
			return 0;
	}
	
	if(s[i] == 'ü'){
		if(t[i] == 'ý' || t[i] == 'ç' || t[i] == 'ö' || t[i] == 'þ' || t[i] == 'ð'){
			return( s[i] - t[i] + 200);	
		}
		else{
			return (s[i] - t[i] + 121.5);
		}
	}
	
	else if(t[i] == 'ü'){
		
		if(s[i] == 'ý' || s[i] == 'ç' || s[i] == 'ö' || s[i] == 'þ' || s[i] == 'ð'){
			return( s[i] - t[i] - 200);	
		}
		else{
			return (s[i] - t[i] - 121.5);
		}
		
	}
	
	else if(s[i] == 'þ'){
		if(t[i] == 'ý' || t[i] == 'ç' || t[i] == 'ö' || t[i] == 'ð'){
			return (s[i] - t[i] + 200);
		}
		
		else if(t[i] == 'ü'){
			return (s[i] - t[i] -200);
		}
		
		else{	
			return(s[i] - t[i] + 117.5);
		}
	}
	
	else if(t[i] == 'þ'){
		if(s[i] == 'ý' || s[i] == 'ç' || s[i] == 'ö' || s[i] == 'ð'){
			return (s[i] - t[i] - 200);
		}
		
		else if(s[i] == 'ü'){
			return (s[i] - t[i] + 200);
		}
	
		else{
			return(s[i] - t[i] - 117.5);
		}
	}
	
	else if(s[i] == 'ç'){
	
		if(t[i] == 'ü' || t[i] == 'ð' || t[i] == 'þ' || t[i] == 'ö' || t[i] == 'ý'){
			return (s[i] - t[i] -200);
		}
		
		else{
				return(s[i] - t[i] + 124.5);
		}
	}
	
	else if(t[i] == 'ç'){
		if(s[i] == 'ü' || s[i] == 'ð' || s[i] == 'þ' || s[i] == 'ö' || s[i] == 'ý'){
			return (s[i] - t[i] + 200);
		}
			
		else{
		return(s[i] - t[i] - 124.5);
		}
	}
	
	else if(s[i] == 'ö'){
		
		if(t[i] == 'ý' || t[i] == 'ç' || t[i] == 'ð'){
			return (s[i] - t[i] + 200);
		}
		
		else if(t[i] == 'ü' || t[i] == 'þ'){
			return (s[i] - t[i] -200);
		}
	
		else{
				return(s[i] - t[i] + 121.5);
		}
	
	}
	
	else if(t[i] == 'ö'){
		if(s[i] == 'ý' || s[i] == 'ç' || s[i] == 'ð'){
			return (s[i] - t[i] - 200);
		}
		
		else if(s[i] == 'ü' || s[i] == 'þ'){
			return (s[i] - t[i] + 200);
		}
	
		else{
			return(s[i] - t[i] - 121.5);
		}
	}
	
	else if(s[i] == 'ý'){
		if(t[i] == 'ç' || t[i] == 'ð'){
			return (s[i] - t[i] + 200);
		}
		
		else if(t[i] == 'ü' || t[i] == 'þ' || t[i] == 'ö'){
			return (s[i] - t[i] -200);
		}
		
		else{
			return(s[i] - t[i] + 107.5 );
		}
	}
	
	
	else if(t[i] == 'ý'){
		if(s[i] == 'ç' || s[i] == 'ð'){
			return (s[i] - t[i] - 200);
		}
		
		else if(s[i] == 'ü' || s[i] == 'þ' || s[i] == 'ö'){
			return (s[i] - t[i] + 200);
		}
	
		else{
			return(s[i] - t[i] - 107.5 );
		}
	}
	
	else if(s[i] == 'ð'){
		if(t[i] == 'ç'){
			return (s[i] - t[i] + 200);
		}
		
		else if(t[i] == 'ü' || t[i] == 'þ' || t[i] == 'ö' || t[i] == 'ý'){
			return (s[i] - t[i] -200);
		}
		
		else{
			return(s[i] - t[i] + 119.5);
		}
	}
	
	else if(t[i] == 'ð'){
		if(s[i] == 'ç'){
			return (s[i] - t[i] - 200);
		}
		
		else if(s[i] == 'ü' || s[i] == 'þ' || s[i] == 'ö' || s[i] == 'i'){
			return (s[i] - t[i] + 200);
		}
	
		else{
			return(s[i] - t[i] - 119.5);
		}
		
	}

	return(s[i] - t[i]);	
}

