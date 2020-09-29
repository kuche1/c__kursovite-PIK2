
#include "node_neshta.c"


/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void nai_mnogo_knigi(){
	uint nai_mnogo = 0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		uint test = next-> knigi;
		if( test > nai_mnogo ){
			nai_mnogo = test;
		}
	}
	
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		uint test = next->knigi;
		if( test == nai_mnogo){
			echo("");
			print_node(next);
		}
	}
}

/////////////////////////

void tursene_ime(){
	char*tursi_se = input("Za tursene: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(next->imena, tursi_se) == 0){
			echo("Nameren: ");
			print_node(next);
		}
	}
}


/////////////////////////

void iztrivane_nomer_bez_knigi(){
	char*tursi_se = input("Nomer: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( id_same( tursi_se, next->id)){
			if( next->knigi == 0){
				echo("Iztrit:");
				print_node(next);
				delete_node(next);
				break;
			}
		}
	}
}

/////////////////////////


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Registrirane na chitatel");
		echo("2/ Chitatelq/lite s nai-mnogo vzeti knigi");
		echo("3/ Tursene po ime");
		echo("4/ Iztrivane po nomer, ako nqma vzeti knigi");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				nai_mnogo_knigi();
				break;
			case 3: 
				tursene_ime();
				break;
			case 4: 
				iztrivane_nomer_bez_knigi();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



