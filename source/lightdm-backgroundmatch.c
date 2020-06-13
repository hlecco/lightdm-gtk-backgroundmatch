#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strtools.h>

#define PATH_CONF "/etc/lightdm/lightdm-gtk-backgroundmatch.conf"
#define PATH_LIGHTDM "/etc/lightdm/lightdm-gtk-greeter.conf"

enum {
	SUCCESS,
	ERR_NOT_ROOT,
	XFCE_READ_FAIL,
	LIGHTDM_READ_FAIL,
	CONF_READ_FAIL,
	LIGHTDM_CONFIG_FAIL,
	LIGHTDM_CONFIG_BAD
};

char *copyFile(FILE *stream) {
	char *output;
	output=NULL;
	int i;
	i=0;

	do {
		if(i%4096==0) {
			output=(char *) realloc(output,((i/4096)+1)*4096);
		}
		output[i++]=getc(stream);
	}
	while(output[i-1]!=EOF);
	output[i-1]=0;

	output=realloc(output,i);
	return(output);
}

void copyToFile(char *input, FILE *file) {
	for (int i=0;input[i]!=0;i++) {
		fprintf(file,"%c",input[i]);
	}
}

int main(int argc, char *argv[]) {
	FILE *xfceback;
	FILE *lightdmback;
	FILE *conf;
	char *strconf;

	if(getuid()!=0) {
		printf("Root privilege is required!\n");
		return ERR_NOT_ROOT;
	}


	conf = fopen(PATH_CONF,"r");
	if(conf==NULL) {
		printf("Couldn't open /etc/lightdm/lightdm-gtk-backgroundmatch.conf file. File does not exist or user has no permission to access.i\n");
		return CONF_READ_FAIL;
	}
	strconf = copyFile(conf);
	fclose(conf);

	if(stringFind(strconf,"xfce-path",0)==STRING_NOT_FOUND) {
		printf("lightdm-gtk-backgroundmatch.conf is badly configured. Check xfce-path.\n");
		return LIGHTDM_CONFIG_BAD;
	}
	char *PATH_XFCE;
	PATH_XFCE = stringSep(&(strconf[stringFind(strconf,"/",stringFind(strconf,"xfce-path",0))]),'\"');
	free(strconf);
	xfceback=fopen(PATH_XFCE,"r");
	if(xfceback==NULL) {
		printf("Couldn't open xfce config file %s. File does not exist or user has no permission to access.\n",PATH_XFCE);
		return XFCE_READ_FAIL;
	}
	lightdmback=fopen(PATH_LIGHTDM,"r");
	if(lightdmback==NULL) {
		printf("Couldn't open lightdm-gtk-greeter config file %s. File does not exist or user has no permission to access.\n",PATH_XFCE);
		return LIGHTDM_READ_FAIL;
	}

	char *strxfce;
	char *strlightdm;
	char *pathxfce;
	char *pathlightdm;
	char *newstrlightdm;

	strxfce=copyFile(xfceback);
	strlightdm=copyFile(lightdmback);
	if(stringFind(strlightdm,"user-background",0)!=STRING_NOT_FOUND) {
		newstrlightdm=stringCut(strlightdm,stringFind(strlightdm,"user-background",0),stringFind(strlightdm,"\n",stringFind(strlightdm,"user-background",0)));
		free(strlightdm);
		strlightdm=newstrlightdm;
	}
	if(stringFind(strlightdm,"background",0)==STRING_NOT_FOUND) {
		printf("Background configuration in lightdm-gtk-greeter is not set appropriately. Please set to any image or color other than black.\n");
		return LIGHTDM_CONFIG_FAIL;
	}


	pathxfce = stringSep(&(strxfce[stringFind(strxfce,"value",stringFind(strxfce,"last-image",0))+stringSize("value=\"")]),'\"');
	pathlightdm = stringSep(&(strlightdm[stringFind(strlightdm,"/",stringFind(strlightdm,"background",0))]),'\n');

	fclose(xfceback);
	fclose(lightdmback);

	newstrlightdm=stringSubstitute(strlightdm,pathlightdm,pathxfce);
	
	lightdmback=fopen(PATH_LIGHTDM,"w");
	copyToFile(newstrlightdm,lightdmback);
	fclose(lightdmback);

	free(PATH_XFCE);
	free(strxfce);
	free(strlightdm);
	free(pathxfce);
	free(pathlightdm);
	free(newstrlightdm);
	return 0;
}


