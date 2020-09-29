
#include "neshta.c"


struct Node_data{////
	char id[11];//egn
	char ime[51];
	uint vuzrast;
	char lekar[51];
	char diagnoza[51];
};

struct Node{
	struct Node_data data;
	struct Node*next;
};
struct Node* PURVI=NULL;



char*str_to_id(char*str){////
	return str;
}

char*id_to_str(char*id){////
	return id;
}


void print_nodedata(struct Node_data data){////
	printf("EGN: %s\n", data. id);
	printf("Ime: %s\n", data. ime );
	printf("Vuzrast: %u\n", data. vuzrast );
	printf("Lekar: %s\n", data. lekar );
	printf("Diagnoza: %s\n", data. diagnoza );
}

void print_node(struct Node*node){
	print_nodedata(node->data);
}

char*node_dir(char* id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

struct Node*node_input(){
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	for(;;){
		
		str__input_EGN("EGN: ", sledvasht->data. id); ////
		
		int failed = 0;
		for(struct Node*next = PURVI; next!=NULL ; next = next->next){
			if( strcmp(id_to_str(sledvasht->data.id), id_to_str(next->data.id) )==0){
				echo("Node s takova ID veche ima");
				failed = 1;
				break;
			}
		}
		if(failed==0)break;
	}
	
	/////
	str__input_capital_up_to_50("Ime: ", sledvasht->data. ime);
	sledvasht->data. vuzrast = input_positive_uint("Vuzrast: ");
	str__input_capital_up_to_50("Lekar: ", sledvasht->data. lekar);
	str__input_capital_up_to_50("Diagnoza: ", sledvasht->data. diagnoza);
	/////
	
	return sledvasht;
}


///////////////////////////////////

void append_node(struct Node*node){
	
	char*f_name = node_dir( id_to_str(node->data.id) );
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	fwrite(&(node->data), sizeof(struct Node_data), 1, f);
	
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

void load_nodes(){
	
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
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		sledvasht->next = NULL;
		
		fread(&(sledvasht->data), sizeof(struct Node_data), 1, f);
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
}

void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp( id_to_str(next->data.id), id_to_str(node->data.id) )==0){
			
			char*tmp = id_to_str(next->data.id);
			
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

struct Node*choose_node(){
	for(;;){
		struct Node*next = PURVI;
		int i=1;
		for(;;i++){
			if(next==NULL)break;
			echo("");
			printf("Izbor nomer: %d\n", i);
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


