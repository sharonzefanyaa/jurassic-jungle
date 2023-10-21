#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DINO{
	char name[40]; // KEY
	char type[30];
	long long int age;
	long long int weight;
	char skill[30];
	
	DINO *right, *left;
	int height;
}*root=NULL;

void enter();
void menu(DINO* root);

DINO* createNewDino(char n[], char t[], long long int a, long long int w, char s[]){
	DINO* newDino = (DINO*)malloc(sizeof(DINO));
	
	strcpy(newDino->name, n);
	strcpy(newDino->type, t);
	newDino->age = a;
	newDino->weight = w;
	strcpy(newDino->skill, s);
	
	newDino->right = newDino->left = NULL;
	newDino->height = 1;
	return newDino;
}

int height(DINO* node){
	if(node==NULL) return 0;
	return node->height;
}

int max(int a, int b){
	if(b>a) return b;
	return a;
}

int getBalance(DINO* root){
	if(root==NULL) return 0;
	return height(root->left) - height(root->right);
}

DINO* rightRotate(DINO* root){
	DINO* x = root->left;
	DINO* y = x->right;
	
	// rotate
	x->right = root;
	root->left = y;
	
	// update
	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

DINO* leftRotate(DINO* root){
	DINO* x = root->right;
	DINO* y = x->left;
	
	// rotate
	x->left = root;
	root->right = y;
	
	// update
	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

DINO* insertion(DINO* root, char n[], char t[], long long int a, long long int w, char s[]){
	// validate
	if(root==NULL) return createNewDino(n, t, a, w, s);
	if(strcmp(n, root->name)<0)
		insertion(root->left, n, t, a, w, s);
	else
		insertion(root->right, n, t, a, w, s);
	
	// height
	root->height = max(height(root->left), height(root->right)) + 1;
	
	// balance
	int balance = getBalance(root);
	
	// rotate
	if(balance>1 && strcmp(n, root->left->name)<0){ // left left
		return rightRotate(root);
	}
	if(balance>1 && strcmp(n, root->left->name)>0){ // left right
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance<-1 && strcmp(n, root->right->name)>0){ // right right
		return leftRotate(root);
	}
	if(balance<-1 && strcmp(n, root->right->name)<0){ // right left
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

bool validateName(char name[]){
	int len = strlen(name);
	int space = 0;
	
	// between 10-30 characters
	bool min = len>10;
	bool max = len<30;
	bool length = min && max;
	if(length==false){
		puts("Input must be between 10 and 30 characters (inclusive).");
		return false;
	}
	
	for(int i=0; i<len; i++){
		if(name[i]==' '){
			space++;
		}
	}
	// consists of 3 words
	if(space<2){
		puts("Input must consists of 3 words minimum");
		return false;
	}
	
	// starts with "Super" or "Hyper"
	if(strncmp(name, "Super", 5)!=0 && strncmp(name, "Hyper", 5)!=0) {
		puts("Input must starts with 'Super' or 'Hyper' (case sensitive)");
		return false;
	}
	
	return true;
}

bool validateSkill(char skill[]){
	int len = strlen(skill);
	int space = 0;
	
	// capital
	for(int i=0; i<len; i++){
		bool first = skill[0]>='A' && skill[0]<='Z';
		if(first==false){
			puts("Capital Letter!");
			return false;
		}
		
		if(skill[i]==' '){
			space++;
		}
	}
	
	// 1 word
	if(space>0){
		puts("One Word!");
		return false;
	}
	
	return true;
}

void add(DINO* root){
	char dname[40];
	char dtype[30];
	long long int dage;
	long long int dweight;
	char dskill[30];
	
	// name
	do{
		printf("Input Dinosaur name [10..30 characters]: ");
		scanf("%[^\n]", dname); getchar();
	} while(validateName(dname)==false);
	
	// type
	do{
		printf("Input Dinosaur type [Carnivore | Herbivore | Omnivore]: ");
		scanf("%s", dtype); getchar();
	} while(strcmpi(dtype, "Carnivore")!=0 && strcmpi(dtype, "Herbivore")!=0
	&& strcmpi(dtype, "Omnivore")!=0);
	
	// age
	do{
		printf("Input Dino age [must be greater than 1000]: ");
		scanf("%lld", &dage); getchar();
	} while(dage<1000);
	
	// weight
	do{
		printf("Input Dino weight [must be greater than 10000]: ");
		scanf("%lld", &dweight); getchar();
	} while(dweight<10000);
	
	// skill
	do{
		fflush(stdin);
		printf("Input Dinosaur skill [One Word, Capital] case sensitive: ");
		scanf("%s", dskill); getchar();
	} while(validateSkill(dskill)==false);
	
	root = insertion(root, dname, dtype, dage, dweight, dskill);
	puts("Insert Success.");
}

void preOrder(DINO* root){
	if(root!=NULL){
		printf("%-30s | %-20s | %-12lld | %-16lld | %-20s |\n", root->name, root->type, root->age, root->weight, root->skill);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(DINO* root){
	if(root!=NULL){
		inOrder(root->left);
		printf("%-30s | %-20s | %-12lld | %-16lld | %-20s |\n", root->name, root->type, root->age, root->weight, root->skill);
		inOrder(root->right);
	}
}

void postOrder(DINO* root){
	if(root!=NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%-30s | %-20s | %-12lld | %-16lld | %-20s |\n", root->name, root->type, root->age, root->weight, root->skill);
	}
}

void see(DINO* root){
	char order[5];
	int torder=-1;
	
	do{
		printf("Choose see order [Pre | In | Post]: ");
		scanf("%s", order); getchar();
		if(strcmp(order, "Pre")==0) torder=1;
		else if(strcmp(order, "In")==0) torder=2;
		else if(strcmp(order, "Post")==0) torder=3;
		else torder=-1;
	} while(torder==-1);
	
	printf("%-30s | %-20s | %-12s | %-16s | %-20s |\n", "Dinosaur Name", "Dinosaur Type", "Dinosaur Age", "Dinosaur Weight", "Dinosaur Skill");
	printf("================================================================================================================\n");
	if(torder==1) preOrder(root);
	else if(torder==2) inOrder(root);
	else if(torder==3) postOrder(root);
}

DINO* deletion(DINO* root, char name[]){
	if(root==NULL) return NULL;
	if(strcmp(name, root->name)<0)
		root->left = deletion(root->left, name);
	else if(strcmp(name, root->name)>0)
		root->right = deletion(root->right, name);
	else{
		if(root->left==NULL && root->right==NULL){
			free(root);
			root=NULL;
		}
		else if(root->left!=NULL && root->right==NULL){
			DINO* temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		else if(root->left==NULL && root->right!=NULL){
			DINO* temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		else if(root->left!=NULL && root->right!=NULL){
			DINO* temp = root->left;
			while(temp->right!=NULL){
				temp = temp->right;
			}
			strcpy(root->name, temp->name);
			strcpy(root->type, temp->type);
			root->age = temp->age;
			root->weight = temp->weight;
			strcpy(root->skill, temp->skill);
			
			root->left = deletion(root->left, temp->name);
		}
	}
	
	if(root==NULL) return root;
	
	// height
	root->height = max(height(root->left), height(root->right)) + 1;
	
	// balance
	int balance = getBalance(root);
	
	// rotate
	if(balance>1 && strcmp(name, root->left->name)<0){ // left left
		return rightRotate(root);
	}
	if(balance>1 && strcmp(name, root->left->name)>0){ // left right
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance<-1 && strcmp(name, root->right->name)>0){ // right right
		return leftRotate(root);
	}
	if(balance<-1 && strcmp(name, root->right->name)<0){ // right left
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

DINO* findDino(DINO* root, char name[]){
	if(root==NULL){
		printf("We can't find dino with %s name", name);
		return NULL;
	}
	
	if(strcmp(name, root->name)==0) {
		puts("Remove sucessful.");
		return root;
	}
	if(strcmp(name, root->name)<0) findDino(root->left, name);
	else findDino(root->right, name);
}

void remove(DINO* root){
	char search[40];
	do{
		printf("Input Dino to be find: ");
		scanf("%[^\n]", search); getchar();
	} while(findDino(root, search));
}

DINO* deleteAll(DINO* root){
	if(root!=NULL){
		deleteAll(root->left);
		deleteAll(root->right);
		root->right = root->left = NULL;
		free(root);
		root = NULL;
	}
	return root;
}

void enter(){
	puts("\nPress enter to continue...");
	getchar();
}

void menu(DINO* root){
	int choose;
	
	do{
		system("cls");
		puts("+=======================+");
		puts("|    Jurassic Jungle    |");
		puts("+=======================+");
		puts("| 1. See Dinosaur       |");
		puts("| 2. Add Dinosaur       |");
		puts("| 3. Remove Dinosaur    |");
		puts("| 4. Exit               |");
		puts("+=======================+");
		printf(">> ");
		scanf("%d", &choose); getchar();
	} while(choose<1 || choose>4);
	
	switch(choose){
		case 1:{
			see(root);
			enter();
			menu(root);
			break;
		}
		case 2:{
			add(root);
			enter();
			menu(root);
			break;
		}
		case 3:{
			if(root==NULL)
				puts("There's no dinosaur here!");
			else remove(root);
			enter();
			menu(root);
			break;
		}
		case 4:{
			puts("PROGRAM EXIT");
			deleteAll(root);
			break;
		}
	}
}

int main(){
	menu(root);
	return 0;
}

//2
//Hyper Velociraptor Z
//Omnivore
//1001
//10005
//Running

//2
//Super Tyranosaur X
//Carnivore
//1002
//10010
//Hunting
//
//2
//Super Brontosaurus Y
//Herbivore
//1003
//10015
//Eating
