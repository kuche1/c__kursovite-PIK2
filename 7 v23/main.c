
#include "node_neshta.c"


/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void promqna(){
	struct Node*choosen = choose_node();
	for(;;){
		echo("1/Iztrii");
		echo("2/Promeni");
		int cho = int_input(">");
		if(cho==1){
			delete_node(choosen);
			echo("Iztrit!");
			break;
		}
		else if (cho==2){
			delete_node(choosen);
			echo("Vuvedi novite danni");
			append_node( node_input());
			break;
		}else echo("Nevaliden izbor");
	}
}

/////////////////////////

void kriteriq1(){
	uint izbran_nomer_blok = positive_uint_input("Blok: ");
	
	uint global_minimum = 0;
	for(;;){
		uint minimum = UINT_MAX;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( izbran_nomer_blok != next->nomer_blok)continue;
			
			uint test = next->mesta;
			if( global_minimum >= test) continue;
			if( minimum > test){
				minimum = test;
			} 
		}
		if(minimum==UINT_MAX)break;
		global_minimum = minimum;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			uint test = next->mesta;
			if( test == minimum){
				echo("");
				print_node(next);
			}
		}
	}
}


/////////////////////////

void kriteriq2(){
	uint izbran_blok_nomer = positive_uint_input("Izberi nomer: ");
	uint obsht_broi = 0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( next->nomer_blok == izbran_blok_nomer){
			obsht_broi += next->mesta;
		}
	}
	printf("Obsht broi mesta: %u\n", obsht_broi);
}

/////////////////////////


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na nova zala");
		echo("2/ Promqna ili iztrivate");
		echo("3/ Izvejdane na dannite za vlischki zali v daden blok, podredeni po mesta");
		echo("4/ Opredelqne na broi mesta v nomer blok");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				promqna();
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



