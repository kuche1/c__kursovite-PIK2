
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
	uint GOOODIIINAAAA = uint_input("Minimalna godina: ");
	
	uint GOD_min_godina = 0;
	
	for(;;){
		uint min_godina = UINT_MAX;
		
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			uint test = next->data. godina;
			if( test < GOOODIIINAAAA) continue;
			if( test <= GOD_min_godina )continue;
			if( test < min_godina ){
				min_godina = test;
			}
		}
		if( min_godina==INT_MAX)break;
		GOD_min_godina = min_godina;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			uint test = next->data. godina;
			if( test == min_godina ){
				echo("");
				print_node(next);
			}
		}
	}
}


void nai_malko_kilometri(){
	uint nai_mnogo = 0;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		uint test = next->data. kilometri;
		if( test > nai_mnogo ){
			nai_mnogo = test;
		}
	}
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		uint test = next->data. kilometri;
		if( test == nai_mnogo){
			echo("");
			print_node(next);
		}
	}
}




void main(){
	load_nodes();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na avtobus");
		echo("2/ Iztrivane ili promqna");
		echo("3/ Izvejdane podredeno, sled godina");
		echo("4/ Nai-maluk izminat kilometraj");
		
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
				nai_malko_kilometri();
				break;
				
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



