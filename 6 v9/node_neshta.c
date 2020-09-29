
#include "neshta.c"





char*node_dir_str(char*id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}
char*node_dir(char* id){// uint id ???
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////


struct Node{ //#...
	char*id;
	char*ime_predpriqtie;
	char*ime_otrasul;
	float prihodi;
	float dulgove;
	int slujiteli;
	
	struct Node*next;
};

struct Node* PURVI=NULL;




void print_node(struct Node*node){ //#...
	printf("ID: %s\n", node->id);
	printf("Predpriqtie: %s\n", node->ime_predpriqtie);
	printf("Otrasul: %s\n", node->ime_otrasul);
	printf("Prihodi: %f\n", node->prihodi);
	printf("Dulgove: %f\n", node->dulgove);
	printf("Slujiteli: %d\n", node->slujiteli);
}

struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	for(;;){
		char*id = input("ID: ");//
		if(strlen(id)!=12 ){
			echo("Trqbva da e 12 znaka");
			free(id);
			continue;
		}
		if( is_str_int(id)==0){
			echo("Trqbva da e cifra");
			free(id);
			continue;
		}
		sledvasht-> id = id;
		break;
	}

	sledvasht-> ime_predpriqtie = input("Ime predpriqtie: ");//
	sledvasht-> ime_otrasul = input("Ime otrasul: ");//
	sledvasht-> prihodi = float_input("Prihodi: ");//
	sledvasht-> dulgove = float_input("Dulgove: ");//
	sledvasht-> slujiteli = int_input("Slujiteli: ");//
	
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node_dir(node->id);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	
	write_str(f, node->ime_predpriqtie);//
	write_str(f, node->ime_otrasul);//
	write_float(f, node->prihodi);//
	write_float(f, node->dulgove);//
	write_int(f, node->slujiteli);//

	
	fclose(f);
	
	if(PURVI==NULL){
		PURVI = node;
		return;
	}
	struct Node*next = PURVI;
	for(; next->next!=NULL ; next = next->next){
	}
	next->next = node;
}

void load_nodes(){ //#...
	
	struct Node* nachalo = NULL;
	nachalo = (struct Node*)malloc(sizeof(struct Node));
	nachalo->next = NULL;
	
	struct dirent *de;
	DIR *dr = opendir("nodes"); 
	if (dr == NULL)error("Ne moga da otvorq papkata s node-ovete");
	
	while( (de=readdir(dr)) != NULL){
		char*node_file_name = copy_str(de -> d_name);
		if( strcmp(node_file_name,".")==0 || strcmp(node_file_name,"..")==0)continue;
		
		char*dir = node_dir_str(node_file_name);
		FILE*f = fopen(dir, "rb");
		free(dir);
		if(f==NULL)error2("Ne moga da otvorq failla na node-a: ", node_file_name);
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		sledvasht->next = NULL;
		
		sledvasht-> id = node_file_name; //
		sledvasht -> ime_predpriqtie = read_str(f); //
		sledvasht -> ime_otrasul = read_str(f); //
		sledvasht -> prihodi = read_float(f); //
		sledvasht -> dulgove = read_float(f); //
		sledvasht -> slujiteli = read_int(f); //
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}


void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(next->id, node->id)==0 ){ //
			
			char*dir = node_dir(next->id);
			int res = remove(dir);
			free(dir);
			if(res!=0)echo("Ne mojah da iztriq faila");
			
			struct Node*real_next = next->next;
			free(next);
			if(prev==NULL){
				PURVI = real_next;
			}else{
				prev->next = real_next;
			}
			return;
		}
		prev = next;
	}
	error("Cant delete a node that doesnt exist");
}

///////////////////////////////////

struct Node*choose_node(){
	for(;;){
		struct Node*next = PURVI;
		int i=1;
		for(;;i++){
			if(next==NULL)break;
			echo("");
			printf("IZBOR NOMER: %d\n", i);
			print_node(next);
			echo("");
			next = next->next;
		}
		i--;
		uint izbor = uint_input("Izberi: ");
		if( izbor > (uint)i || izbor == 0 ){
			echo("Nevaliden izbor");
			continue;
		}
		
		int izbrana_figura = (int)izbor;
		
		i=1;
		for(struct Node*next = PURVI; ; next = next->next){
			if(i==izbrana_figura)return next;
			i++;
		}
		break;
	}
}


