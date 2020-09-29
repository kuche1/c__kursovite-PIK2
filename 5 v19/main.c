
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
	if(nov->legla){
		echo("Tvoita bolnica nqma legla, nqma da q priema");
		free(nov);
		return;
	}
	append_node(nov);
}

/////////////////////////

void izvejdane_po_kriteriq(){
	
	char* desired_adres = input("Adres: ");
	
	struct Node* global_nai_malko=NULL;
	
	for(;;){
		struct Node* nai_malko=NULL;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( strcmp(desired_adres, next->adres)!=0 )continue;
			//printf("Ednakvi adresi: %s %s\n", desired_adres, next->adres);
			
			//if( (global_nai_malko != NULL) )printf("%d <= %d\n", global_nai_malko->otdeleniq, next->otdeleniq);
			if( (global_nai_malko != NULL) && (global_nai_malko->otdeleniq >= next->otdeleniq)  )continue;
			//printf("DA!\n");
			
			if( nai_malko == NULL ){
				nai_malko = next;
				continue;
			}
			if( nai_malko->otdeleniq > next->otdeleniq ){
				nai_malko = next;
			}
		}
		//echo("");
		//echo("NAI MALKOTO E:");
		//if(nai_malko==NULL)echo("NULL");
		//else print_node(nai_malko);
		//echo("");
		
		if( nai_malko==NULL){
			free(desired_adres);
			return;
		}
		global_nai_malko = nai_malko;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if(next->otdeleniq == nai_malko->otdeleniq){
				echo("");
				print_node(nai_malko);
			}
		}
	}
	
}


/////////////////////////

void izvejdane_po_kriteriq2(){
	float broi = 0.0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		broi += 1.0;
	}
	float sredno=0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		sredno += next->biudjet;
	}
	sredno /= broi;
	printf("Sredno %f\n", sredno);
}

/////////////////////////


void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na nova bolnica");
		echo("2/ Promqna na dannite");
		echo("3/ Izvejdane na bolnicite, po reda na narastvane na otdeleniqta");
		echo("4/ Izvejdane na sredniq biudjet");
		
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
				izvejdane_po_kriteriq2();//
				break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



