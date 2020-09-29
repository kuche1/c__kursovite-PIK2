
#include "node_neshta.c"



void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}


void iztrivane(){
	char*tursi_se = input("Rejisior: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(tursi_se, next->rejisior)==0 ){
			echo("");
			print_node(next);
			delete_node(next);
		}
	}
}


void izvejdane_podredeno(){
	int GOD_min_godina = 0;
	
	for(;;){
		int min_godina = INT_MAX;
		
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			int test = next->godina;
			if( test <= GOD_min_godina )continue;
			if( test < min_godina ){
				min_godina = test;
			}
		}
		if( min_godina==INT_MAX)break;
		GOD_min_godina = min_godina;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			int test = next->godina;
			if( test == min_godina ){
				echo("");
				print_node(next);
			}
		}
	}
}


void nai_dulug_film(){
	float nai_mnogo = 0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		float test = next-> produljitelnost;
		if( test > nai_mnogo ){
			nai_mnogo = test;
		}
	}
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		float test = next->produljitelnost;
		if( test == nai_mnogo){
			echo("");
			print_node(next);
		}
	}
}




void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na film");
		echo("2/ Iztrivane na filmite na daden rejisior");
		echo("3/ Izvejdane podredeno");
		echo("4/ Nai-produljitelen film");
		
		int izbor = int_input("Izberi opciq: ");
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				iztrivane();
				break;
			case 3: 
				izvejdane_podredeno();
				break;
			case 4: 
				nai_dulug_film();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



