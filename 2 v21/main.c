
#include "node_neshta.c"


/////////////////////////




void dobavqne_na_dvumerna_figura_s_unikalen_kod(){
	struct Node*sledvasht = node_input();
	append_node(sledvasht);
}


/////////////////////////

void promqna_na_figura_ili_iztrivane(){
	struct Node*izbran_node = choose_node();
	
	for(;;){
		echo("1/ Iztrii");
		echo("2/ Promeni");
		uint izbor = uint_input("Izberi: ");
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

void izvejdane_na_figurete_po_restej_na_perimetura(){
	
	int minimalno_nai_malko = -1;
	for(;;){
		int nai_malko= INT_MAX;
		for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
			float perimetur = next->perimetur;
			if(perimetur <= minimalno_nai_malko)continue;
			
			if(perimetur < nai_malko){
				nai_malko = perimetur;
			}
		}
		minimalno_nai_malko = nai_malko;
		
		for(struct Node*next = PURVI ; next!=NULL ; next = next-> next){
			if(next->perimetur == nai_malko){
				echo("");
				print_node(next);
			}
		}
		
		if(minimalno_nai_malko == INT_MAX)break;
		
	}
	
}

/////////////////////////

void izvedi_figurite_s_nai_golqmo_lice(){
	float nai_golqmo = -1;
	struct Node*next = PURVI;
	for(;next!=NULL; next = next->next){
		float lice = next->lice;
		if(lice > nai_golqmo)nai_golqmo=lice;
	}
	
	if(nai_golqmo==-1){
		echo("Nqma");
		return;
	}
	
	next = PURVI;
	for(;next!=NULL; next = next->next){
		if(next->lice == nai_golqmo){
			echo("");
			print_node(next);
		}
	}
}



void main(){
	
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na nova dvumerna figura s unikalen kod");//raboti, no kakvo e dvumerna figura ?
		echo("2/ Promqna na figura / Iztrivane");//gotovo
		echo("3/ Izvejdane na vsichki fuguri, po rastej na perimetura");//gotovo
		echo("4/ Izvejdane na figura/figuri s nai-golqmo lice");//gotovo
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne_na_dvumerna_figura_s_unikalen_kod();
				break;
			case 2: 
				promqna_na_figura_ili_iztrivane();
				break;
			case 3: 
				izvejdane_na_figurete_po_restej_na_perimetura();
				break;
			case 4: 
				izvedi_figurite_s_nai_golqmo_lice();
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



