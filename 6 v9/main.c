
#include "node_neshta.c"

#include<float.h>

/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void printene(){
	print_node( choose_node() );
}

/////////////////////////

void kriteriq1(){
	char*global_nai_malko=NULL;
	for(;;){
		char*nai_malko = NULL;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			char*test = next->ime_otrasul;
			//if( global_nai_malko!=NULL ){
			//	printf("%d %s %s\n", strcmp(test, global_nai_malko), test, global_nai_malko);
			//}
			if( global_nai_malko!=NULL && strcmp(test, global_nai_malko) <= 0 )continue;
			if( nai_malko==NULL || strcmp(test, nai_malko) < 0 ) nai_malko = test;
		}
		if( nai_malko==NULL)break;
		global_nai_malko = nai_malko;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( strcmp(next->ime_otrasul, nai_malko)==0){
				echo("");
				print_node(next);
			}
		}
	}
}


/////////////////////////

void kriteriq2(){
	float baza = float_input("Vevedi dulg: ");
	
	for(struct Node*next = PURVI; next!=NULL ; ){
		float test = next->dulgove;
		if( test > baza){
			struct Node*real_next = next->next;
			echo("Iztrivam:");
			print_node(next);
			delete_node(next);
			next = real_next;
		}else{
			next = next->next;
		}
	}
	
}

/////////////////////////


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na novo predpriqtie");
		echo("2/ Izvejdane na dannite na predpriqtie");
		echo("3/ Predpriqtiqta, sortirani po ime");
		echo("4/ Iztrivane na predpriqtiqta, s golemi dulgove");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				printene();
				break;
			case 3: 
				kriteriq1();
				break;
			case 4: 
				kriteriq2();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



