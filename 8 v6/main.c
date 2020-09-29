
#include "node_neshta.c"

#include <float.h>

/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void promqna_ili_iztrivane_po_kod(){
	char*kod = kod_input("Vuvedi kod: ");
	
	struct Node*izbran_node = NULL;
	for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
		if(strcmp(next->id, kod)==0){
			izbran_node = next;
			break;
		}
	}
	
	if(izbran_node==NULL){
		echo("Nishto ne e namereno");
		return;
	}
	
	for(;;){
		echo("1/ Iztrii");
		echo("2/ Promeni");
		int izbor = int_input("Izberi: ");
		if( izbor==1 ){
			delete_node(izbran_node);
			break;
		}else if(izbor==2){
			delete_node(izbran_node);
			echo("Vuvedi novite danni");
			struct Node*nov = node_input();
			append_node(nov);
			break;
		}else{
			echo("Nevaliden izbor");
		}
	}
}

/////////////////////////

void izvejdane_po_avtori_v_namalqnasht_na_cenata_red(){
	
	int len = 0;
	for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
		len++;
	}
	
	struct Node*nodes[len];
	int ind=0;
	for(struct Node*next = PURVI; ind < len; ind++, next = next-> next){
		nodes[ind] = next;
	}
	
	int done=0;;
	for(;;){
		done = 1;
		for(int ind=0; ind<len-1; ind++){
			if( strcmp(nodes[ind]->ime_avtor, nodes[ind+1]->ime_avtor) > 0){
				struct Node*tmp = nodes[ind];
				nodes[ind] = nodes[ind+1];
				nodes[ind+1] = tmp;
				done = 0;
			}
		}
		if(done)break;
	}
	
	done=0;
	for(;;){
		done = 1;
		for(int ind=0; ind<len-1; ind++){
			struct Node*n1 = nodes[ind];
			struct Node*n2 = nodes[ind+1];
			if( strcmp(n1->ime_avtor, n2->ime_avtor) == 0 ){
				if( n1->cena > n2->cena ){
					nodes[ind] = n2;
					nodes[ind+1] = n1;
					done = 0;
				}
			}
		}
		if(done)break;
	}
	
	
	for(int ind=0; ind<len; ind++){
		echo("");
		print_node( nodes[ind] );
	}
	
}

/////////////////////////


void aktualizaciq(){
	char*kod = kod_input("Kod za aktualizaciq: ");
	for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
		if( strcmp(next->id, kod)==0 ){
			delete_node(next);
			echo("\nVuvedi novi danni\n");
			struct Node*node = node_input();
			append_node(node);
			break;
		}
	}
}



void main(){
	
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne");
		echo("2/ Iztrivane / aktualizaciq po kod");
		echo("3/ Izvejdane po avtori, v namalqvasht na cenata red");
		echo("4/ Aktualizaciq");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				promqna_ili_iztrivane_po_kod();
				break;
			case 3: 
				izvejdane_po_avtori_v_namalqnasht_na_cenata_red();
				break;
			case 4:
				aktualizaciq();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



