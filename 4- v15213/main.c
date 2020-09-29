
#include "node_neshta.c"

#include<float.h>

/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void iztrivane_po_rejisior(){
	char*rejisior = input("Rejisior: ");
	for(;;){
		int done=1;
		for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
			if(strcmp(rejisior, next->rejisior)==0){
				echo("Iztrit:");
				print_node(next);
				delete_node(next);
				done=0;
				break;
			}
		}
		if(done==1)break;
	}
}

/////////////////////////

void izvejdane_po_godina(){
	
	int godina = int_input("Godina: ");
	
	for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
		if(godina == next->godina){
			echo("");
			print_node(next);
		}
	}
}

/////////////////////////

void izvejdane_po_nomer(){
	uint nomer = uint_input("Nomer: ");
	for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
		if(nomer == next->id){
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
		echo("2/ Iztrivane na filmite ot daden rejisior");
		echo("3/ Izvejdane na filmite ot dadena godina");//
		echo("4/ Izvejdane na film po nomer");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				iztrivane_po_rejisior();
				break;
			case 3: 
				izvejdane_po_godina();
				break;
			case 4: 
				izvejdane_po_nomer();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



