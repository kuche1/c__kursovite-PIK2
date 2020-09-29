
#include "neshta.c"


char*node_dir(char* id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////


struct Node{
	char*id;
	char*ime;
	char*rejisior;
	float produljitelnost;
	int godina;
	
	struct Node*next;
};

struct Node* PURVI=NULL;

/*
int id_same(char* id1, char*id2){
	return strcmp(id1, id2)==0;
}*/

char*str_to_id(char*str){
	return str;
}

char*id_to_str(char*id){
	return id;
}


void print_node(struct Node*node){
	printf("Nomer: %s\n", node->id);
	printf("Ime: %s\n", node->ime);
	printf("Rejisior: %s\n", node->rejisior);
	printf("Produljitelnost: : %f\n", node->produljitelnost);
	printf("Godina: %d\n", node->godina);
}


struct Node*node_input(){
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	/////
	sledvasht->id = str__input_int_12("Nomer: ");
	sledvasht->ime = input_up_to_50("Ime: ");
	sledvasht->rejisior = input_up_to_50("Rejisior: ");
	sledvasht->produljitelnost = float_input("Produljitelnost: ");
	sledvasht->godina = int_input("Godina: ");
	/////
	
	return sledvasht;
}

void append_node(struct Node*node){
	
	char*f_name = node_dir( id_to_str(node->id) );
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	////
	write_str(f, node->ime);
	write_str(f, node->rejisior);
	write_float(f, node->produljitelnost);
	write_int(f, node->godina);
	////
	
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
		
		sledvasht->id = str_to_id(node_file_name);
		////
		sledvasht -> ime = read_str(f);
		sledvasht -> rejisior = read_str(f);
		sledvasht -> produljitelnost = read_float(f);
		sledvasht -> godina = read_int(f);
		////
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}

///////////////////////////////////

void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		//if( id_same(next->id, node->id) ){
		if( strcmp( id_to_str(next->id), id_to_str(node->id) )==0){
			
			char*tmp = id_to_str(next->id);
			
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


