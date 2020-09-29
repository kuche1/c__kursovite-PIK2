
#include "node_neshta.c"

#include<float.h>

/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void promqna(){
	struct Node*izbran_node = choose_node();
	delete_node(izbran_node);
	echo("Vuvedi novite danni");
	struct Node*nov = node_input();
	append_node(nov);
}

/////////////////////////

void izvejdane_po_kriteriq(){
	
	float min = float_input("Minimum: ");
	float max = float_input("Maximum: ");
	
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		float sredno = next->godina1 + next->godina2 + next->godina3 + next->godina4 + next->godina5;
		sredno /= 5;
		if(min < sredno && sredno < max){
			echo("\n");
			print_node(next);
			printf("Sredno: %f\n", sredno);
			echo("\n");
		}
	}
	
}


/////////////////////////

void izvedi_po_id(){
	char id[200];
	input_id(id);
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(id, next->id)==0 ){
			print_node(next);
			break;
		}
	}
}

/////////////////////////


void main(){
	
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na nova firma");
		echo("2/ Aktualizaciq na firma");
		echo("3/ Srednata pechalba na vsichki firmi v interval, za poslednite 5 godini");
		echo("4/ Izvejdane, po danuchen nomer");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();//
				break;
			case 2: 
				promqna();//
				break;
			case 3: 
				izvejdane_po_kriteriq();//
				break;
			case 4: 
				izvedi_po_id();//
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



