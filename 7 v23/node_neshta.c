
#include "neshta.c"




char*node_dir(char* id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

void copy_paste_str(char*target, char*source){
	for(int i=0; i <= strlen(source); i++){
		target[i] = source[i];
	}
}

/////////////////////////


struct Optimal_node{ //#...
	uint id;
	char ime[50];
	uint nomer_blok;
	uint etaj;
	uint mesta;
};

struct Node{ //#...
	uint id;
	char ime[50];
	uint nomer_blok;
	uint etaj;
	uint mesta;
	
	struct Node*next;
};

struct Node* PURVI=NULL;





void format_node(struct Optimal_node*opt_node, struct Node*node){
	opt_node->id = node->id;
	copy_paste_str( opt_node->ime, node->ime );
	opt_node->nomer_blok = node->nomer_blok;
	opt_node->etaj = node->etaj;
	opt_node->mesta = node->mesta;
}

void format_optimal_node(struct Node*node, struct Optimal_node*opt_node){
	node->id = opt_node->id;
	copy_paste_str( node->ime, opt_node->ime );
	node->nomer_blok = opt_node->nomer_blok;
	node->etaj = opt_node->etaj;
	node->mesta = opt_node->mesta;
}



void print_node(struct Node*node){ //#...
	printf("Nomer: %d\n", node->id);
	printf("Ime na otgovornik: %s\n", node->ime);
	printf("Nomer na blok: %u\n", node->nomer_blok);
	printf("Etaj: %u\n", node->etaj);
	printf("Mesta: %u\n", node->mesta);
}

struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	sledvasht->id = positive_uint_input("Nomer: ");//
	
	input_capital_50("Ime: ", sledvasht->ime);
	
	
	sledvasht->nomer_blok = positive_uint_input("Blok: ");//
	
	sledvasht->etaj = positive_uint_input("Etaj: ");//
	
	sledvasht->mesta = positive_uint_input("Mesta: ");//
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = uint_to_str(node->id);//
	
	f_name = node_dir(f_name);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	/*
	struct Node*tmp = node->next;
	node->next = NULL;
	fwrite(node, sizeof(struct Node), 1, f);
	node->next = tmp;
	*/
	struct Optimal_node*optimal_node = NULL;
	optimal_node = (struct Optimal_node*)malloc(sizeof(struct Optimal_node));
	format_node(optimal_node, node);
	fwrite(optimal_node, sizeof(struct Optimal_node), 1, f);
	
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
		
		char*dir = node_dir(node_file_name);
		FILE*f = fopen(dir, "rb");
		free(dir);
		if(f==NULL)error2("Ne moga da otvorq failla na node-a: ", node_file_name);
		
		/*
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		
		fread(sledvasht, sizeof(struct Node), 1, f);
		sledvasht->next = NULL;
		*/
		struct Optimal_node*node = NULL;
		node = (struct Optimal_node*)malloc(sizeof(struct Optimal_node));
		
		fread(node, sizeof(struct Optimal_node), 1, f);
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		
		format_optimal_node(sledvasht, node);
		free(node);
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}


void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( next->id == node->id ){ //
			
			char*tmp = uint_to_str(next->id); //
			
			char*dir = node_dir( tmp );
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


