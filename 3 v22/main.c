
#include "node_neshta.c"

#include<float.h>

/////////////////////////

void dobavqne(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}

/////////////////////////

void promqna_ili_iztrivane(){
	struct Node*izbran_node = choose_node();
	
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

void izvejdane_po_kriteriq(){
	
	float minimalen_obem = ufloat_input("Minimalen obem: ");//#... da me se include-va
	
	float maximalno_golqmo = FLT_MAX;//#...
	for(;;){
		float nai_golqmo= FLT_MIN;//#...
		for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
			float kandidat = next->obem;//#...
			
			if(kandidat <= minimalen_obem)continue;
			
			if(kandidat >= maximalno_golqmo)continue;
			
			if(kandidat > nai_golqmo){
				nai_golqmo = kandidat;
			}
		}
		maximalno_golqmo = nai_golqmo;
		
		for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
			float kandidat = next->obem;//#...
			if(kandidat == nai_golqmo){
				echo("");
				print_node(next);
			}
		}
		
		if(maximalno_golqmo == FLT_MIN)break;
		
	}
	
}

/////////////////////////

void izvedi_nai_golqmoto(){
	int ima_nai_golqmo = 0;
	uint nai_golqmo = 0;//#...
	struct Node*next = PURVI;
	for(;next!=NULL; next = next->next){
		uint kandidat = next->steni;//#...
		if(ima_nai_golqmo==0 || kandidat > nai_golqmo){
			ima_nai_golqmo = 1;
			nai_golqmo=kandidat;
		}
	}
	
	if(ima_nai_golqmo==0){
		echo("Nqma");
		return;
	}
	
	next = PURVI;
	for(;next!=NULL; next = next->next){
		uint kandidat = next->steni;//#...
		if(kandidat == nai_golqmo){
			echo("");
			print_node(next);
		}
	}
}



void main(){
	
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na novo primerno tqlo");
		echo("2/ Promqna na izbranoto tqlo / iztrivane");
		echo("3/ Izvejdane na vsichki fuguri, s obem nad zadadeniq, podredeni");
		echo("4/ Tqloto nai-golqm broi steni");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne();
				break;
			case 2: 
				promqna_ili_iztrivane();
				break;
			case 3: 
				izvejdane_po_kriteriq();
				break;
			case 4: 
				izvedi_nai_golqmoto();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



