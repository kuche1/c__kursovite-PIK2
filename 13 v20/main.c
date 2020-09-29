
#include "node_neshta.c"



void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}


void promqna_ili_iztrivane(){
	struct Node*node = choose_node();
	
	for(;;){
		int choice = int_input("1 - promqna /n 2 - iztrivane \n >");
		if(choice==1){
			delete_node(node);
			dobavqne();
		}else if(choice==2){
			delete_node(node);
		}else{
			echo("Nevaliden izbor");
			continue;
		}
		break;
	}
	
}


void izvejdane(){
	
	char LEKAR[50] = "";
	str__input_capital_up_to_50("Lekar: ", LEKAR);
	
	uint GOD_min = 0;
	
	for(;;){
		uint min = UINT_MAX;
		
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( strcmp(LEKAR, next->data. lekar)!=0 ) continue;
			uint test = next->data. vuzrast;
			if( test <= GOD_min )continue;
			if( test < min ){
				min = test;
			}
		}
		if( min==UINT_MAX)break;
		GOD_min = min;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( strcmp(LEKAR, next->data. lekar)!=0 ) continue;
			uint test = next->data. vuzrast;
			if( test == min ){
				echo("");
				print_node(next);
			}
		}
	}
}

void izvejdane2(){
	uint min_vuzrast = uint_input("Minimalna vuzrast: ");
	uint max_vuzrast = uint_input("Maximalna vuzrast: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		uint vuzrast = next->data.vuzrast;
		if( min_vuzrast <= vuzrast || vuzrast <= max_vuzrast ){
			echo("");
			print_node(next);
		}
	}
}


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na pacient");
		echo("2/ Iztrivane ili promqna");
		echo("3/ Izvejdane podredeno, sprqmo lekar");
		echo("4/ Izvejdane sprqmo vuzrast");
		
		int izbor = int_input("Izberi opciq: ");
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				promqna_ili_iztrivane();
				break;
			case 3: 
				izvejdane();
				break;
			case 4: 
				izvejdane2();
				break;
				
			default: printf("Nevaliden izbor: %d\n", izbor);
		}	
	}
}



