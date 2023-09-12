#include <stdio.h>
#include <sqlite3.h>

int main(){

	sqlite3 *db;
	char *errMessage = 0;


	// open db
	int rc = sqlite3_open("test.db",&db);
	if(rc){
		fprintf(stderr, "cannot open db : %s\n",sqlite3_errmsg(db));
		return(0);
	}
	else{
		fprintf(stdout, "open db\n");
	}

	// create table
	const char *createTableSQL = 
		"CREATE TABLE IF NOT EXISTS TestTable("\
		"ID INT PRIMARY KEY NOT NULL,"\
		"NAME TEXXT NOT NULL);";

	rc = sqlite3_exec(db, createTableSQL,0,0,&errMessage);
	if(rc != SQLITE_OK){
		fprintf(stderr, "create table error : %s\n",errMessage);
		sqlite3_free(errMessage);
	}
	else{
		fprintf(stdout,"success to create table\n");
	}

	// insert data
	const char *insertSQL = "INSERT INTO TestTable (ID,NAME) VALUES (1,'John');";
	rc = sqlite3_exec(db,insertSQL,0,0,&errMessage);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "insert error : %s\n",errMessage);
		sqlite3_free(errMessage);
	}
	else{
		fprintf(stdout, "insert data\n");
	}

	// select data
	const char *selectSQL = "SELECT * FROM TestTable;";
	sqlite3_stmt *stmt;

	rc = sqlite3_prepare_v2(db,selectSQL,-1,&stmt,0);
	if(rc==SQLITE_OK){
		while(sqlite3_step(stmt)==SQLITE_ROW){
			int id=sqlite3_column_int(stmt,0);
			const unsigned char *name = sqlite3_column_text(stmt,1);
			printf("ID: %d, Name: %s\n",id,name);
		}
	}
	else{
		fprintf(stderr,"select data error : %s\n",sqlite3_errmsg(db));
	}


	sqlite3_close(db);
	return 0;
}
