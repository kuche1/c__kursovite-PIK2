
#include "node_neshta.c"


/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void nai_dulga_ekskurziq(){
	int nai_mnogo = 0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		int test = next-> produljitelnost;
		if( test > nai_mnogo ){
			nai_mnogo = test;
		}
	}
	
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		int test = next->produljitelnost;
		if( test == nai_mnogo){
			echo("");
			print_node(next);
		}
	}
}

/////////////////////////

void izvejdane_data(){
	char*tursi_se = date_input("Dneshna data: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( compare_date(next->data, tursi_se) < 0){
			echo("Iztekul: ");
			print_node(next);
		}
	}
}


/////////////////////////

void iztrivane_po_kod(){
	char*tursi_se = input("Kod: ");
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( id_same( tursi_se, next->id)){
			echo("Iztrit:");
			print_node(next);
			delete_node(next);
			break;
		}
	}
}

/////////////////////////


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na ekskurziq");//
		echo("2/ Nai-dulgata ekskurziq");//
		echo("3/ Izvejdane sled data");
		echo("4/ Iztrivane po kod");//
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				nai_dulga_ekskurziq();
				break;
			case 3: 
				izvejdane_data();
				break;
			case 4: 
				iztrivane_po_kod();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



