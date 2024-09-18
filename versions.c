/**
 * @file
 * @brief Implementacion del API de gestion de versiones
 * @author Erwin Meza Vega <emezav@unicauca.edu.co>
 * @copyright MIT License
*/

#include "versions.h"
#include <linux/limits.h>

/**
 * @brief Crea una version en memoria del archivo
 * Valida si el archivo especificado existe y crea su hash
 * @param filename Nombre del archivo
 * @param hash Hash del contenido del archivo
 * @param comment Comentario
 * @param result Nueva version en memoria
 *
 * @return Resultado de la operacion
 */
return_code create_version(char * filename, char * comment, file_version * result);

/**
 * @brief Verifica si existe una version para un archivo
 *
 * @param filename Nombre del archivo
 * @param hash Hash del contenido
 *
 * @return 1 si la version existe, 0 en caso contrario.
 */
int version_exists(char * filename, char * hash);

/**
 * @brief Obtiene el hash de un archivo.
 * @param filename Nombre del archivo a obtener el hash
 * @param hash Buffer para almacenar el hash (HASH_SIZE)
 * @return Referencia al buffer, NULL si ocurre error
 */
char *get_file_hash(char * filename, char * hash);

/**
 * @brief Copia un archivo
 *
 * @param source Archivo fuente
 * @param destination Destino
 *
 * @return
 */
int copy(char * source, char * destination);

/**
* @brief Almacena un archivo en el repositorio
*
* @param filename Nombre del archivo
* @param hash Hash del archivo: nombre del archivo en el repositorio
*
* @return
*/
int store_file(char * filename, char * hash);

/**
* @brief Almacena un archivo en el repositorio
* @param hash Hash del archivo: nombre del archivo en el repositorio
* @param filename Nombre del archivo
*
* @return
*/
int retrieve_file(char * hash, char * filename);

/**
 * @brief Adiciona una nueva version de un archivo.
 *
 * @param filename Nombre del archivo.
 * @param comment Comentario de la version.
 * @param hash Hash del contenido.
 *
 * @return 1 en caso de exito, 0 en caso de error.
 */
int add_new_version(file_version * v);


return_code create_version(char * filename, char * comment, file_version * result) {

	// Llena a estructura result recibida por referencia.
	// Debe validar:
	// 1. Que el archivo exista y sea un archivo regular
	// 2. Obtiene y guarda en la estructura el HASH del archivo
	// Llena todos los atributos de la estructura y retorna VERSION_CREATED
	// En caso de fallar alguna validacion, retorna VERSION_ERROR

	return VERSION_ERROR;

}


//Pendiente revisar si los !=0  o NULL corresponden a los errores de cada caso
return_code add(char * filename, char * comment) {
	file_version v;

	// 1. Crea la nueva version en memoria
	// Si la operacion falla, retorna VERSION_ERROR
	if(create_version(filename, comment, &v) == NULL){
		printf("Error al crear versión");
		return VERSION_ERROR;
	}

	// 2. Verifica si ya existe una version con el mismo hash
	// Retorna VERSION_ALREADY_EXISTS si ya existe
	if(version_exists(filename, v.hash)==0){
		printf("Versión existente");
		return VERSION_ALREADY_EXISTS;
	}

	// 3. Almacena el archivo en el repositorio.
	// El nombre del archivo dentro del repositorio es su hash (sin extension)
	// Retorna VERSION_ERROR si la operacion falla
	if(store_file(filename, v.hash)!=0){
		printf("Error al guardar la versión");
		return VERSION_ERROR;
	}

	// 4. Agrega un nuevo registro al archivo versions.db
	// Si no puede adicionar el registro, se debe borrar el archivo almacenado en el paso anterior
	// Si la operacion falla, retorna VERSION_ERROR
	if(add_new_version(&v)==0){
		printf("Exito al añadir la versión");
		return VERSION_ADDED;
	}else{
		//cierra y elimina el anterior archivo
		remove(filename);
	}
	// Si la operacion es exitosa, retorna VERSION_ADDED
	return VERSION_ERROR;
}

int add_new_version(file_version * v) {
	FILE * fp;
	// Adiciona un nuevo registro (estructura) al archivo versions.db
	return 0;
}


void list(char * filename) {

	//Abre el la base de datos de versiones (versions.db)
	//Muestra los registros cuyo nombre coincide con filename.
	//Si filename es NULL, muestra todos los registros.

}

char *get_file_hash(char * filename, char * hash) {
	char *comando;
	FILE * fp;

	struct stat s;

	//Verificar que el archivo existe y que se puede obtener el hash
	if (stat(filename, &s) < 0 || !S_ISREG(s.st_mode)) {
		perror("stat");
		return NULL;
	}

	sha256_hash_file_hex(filename, hash);

	return hash;

}

int copy(char * source, char * destination) {
	// Copia el contenido de source a destination (se debe usar open-read-write-close, o fopen-fread-fwrite-fclose)
	fopen(source,"r");
	fopen(destination,"w");
}


//ojo
int version_exists(char * filename, char * hash) {
	// Verifica si en la bd existe un registro que coincide con filename y hash
	if(strcmp(*hash,get_file_hash(*filename,*hash))==0){
		printf("Existe un archivo %s que coincide con %s ",*filename,*hash);
		return 0;
	}
	printf("NO existe un archivo %s que coincide con %s ",*filename,*hash);
	return 1;
}

int get(char * filename, int version) {
	file_version r;
	//1. Abre la BD y busca el registro r que coincide con filename y version
	if(retrieve_file(r.hash, r.filename)!=0){
		return -1;
	}
	return 0;
}


int store_file(char * filename, char * hash) {
	char dst_filename[PATH_MAX];
	snprintf(dst_filename, PATH_MAX, "%s/%s", VERSIONS_DIR, hash);
	return copy(filename, dst_filename);
}

int retrieve_file(char * hash, char * filename) {
	char src_filename[PATH_MAX];
	snprintf(src_filename, PATH_MAX, "%s/%s", VERSIONS_DIR, hash);
	return copy(src_filename, filename);
}

